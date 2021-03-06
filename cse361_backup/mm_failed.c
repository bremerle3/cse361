/*
 * mm-naive.c - The fastest, least memory-efficient malloc package.
 * 
 * In this naive approach, a block is allocated by simply incrementing
 * the brk pointer.  A block is pure payload. There are no headers or
 * footers.  Blocks are never coalesced or reused. Realloc is
 * implemented directly using mm_malloc and mm_free.
 *
 * NOTE TO STUDENTS: Replace this header comment with your own header
 * comment that gives a high level description of your solution.
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>
#include "mm.h"
#include "memlib.h"


//Constants
#define WSIZE 4 // Word and header/footer size in bytes
#define DSIZE 8 // Doubleword size in bytes
#define EXHEAPSIZE (1<<12) //Extend heap by this amount in bytes  (2 kilobytes)
#define MINFRAG 16
#define MINBLKSIZE 24

//Mini Helper Functions
#define MAX(x, y) ((x) > (y)? (x) : (y))
#define PACK(size, alloc) ((size) | (alloc)) //Pack size/alloc bit into a word

#define GET(p) (*(unsigned int *)(p)) // Read word at addr p
#define GET_PTR(p)  (*(unsigned int *)(p))
#define PUT(p, val) (*(unsigned int *)(p) = (val)) // Write word to addr p
#define PUT_PTR(p, val) ((*(unsigned int *)(p) = (val))

#define GET_SIZE(p)  (GET(p) & ~0x7) // Read size at addr p
#define GET_ALLOC(p) (GET(p) & 0x1) // Read alloc field at addr p

#define HDRP(bp)       ((char *)(bp) - WSIZE) // Given block ptr, find header addr
#define FTRP(bp)       ((char *)(bp) + GET_SIZE(HDRP(bp)) - DSIZE) // Given block ptr, find footer addr

#define NEXT_BLKP(bp)  ((char *)(bp) + GET_SIZE(((char *)(bp) - WSIZE))) //Given block ptr, find next block addr (points at payload)
#define PREV_BLKP(bp)  ((char *)(bp) - GET_SIZE(((char *)(bp) - DSIZE))) //Given block ptr, find prev block addr

#define NEXT_FREE(bp) (*(char **)(bp)) //Given bp is free returns pointer to next/prev free blocks
#define PREV_FREE(bp) (*(char **)(bp + WSIZE)) //currently both unused
//these have to be double pointers since they are memebers of a linked list

/*********************************************************
 * NOTE TO STUDENTS: Before you do anything else, please
 * provide your team information in the following struct.
 ********************************************************/
team_t team = {
    /* Team name */
    "Muy Mallocators",
    /* First member's full name */
    "Dan Witherspoon",
    /* First member's email address */
    "Daniel.Witherspoon@gmail.com",
    /* Second member's full name (leave blank if none) */
    "Leo Bremer",
    /* Second member's email address (leave blank if none) */
    "LBremer@wustl.edu"
};

/* single word (4) or double word (8) alignment */
#define ALIGNMENT 8  //Do not change

/* rounds up to the nearest multiple of ALIGNMENT */
#define ALIGN(size) (((size) + (ALIGNMENT-1)) & ~0x7)


#define SIZE_T_SIZE (ALIGN(sizeof(size_t)))


//Function Prototypes
static void *extend_heap(size_t words);
void mm_free(void *ptr);
void place (void *bp, size_t asize);
void fwdPointers(void *ptr, size_t frag);
void moveStart(void *ptr);
static void *coalesce(void *ptr);
static void delete_free_block(void * ptr);
int mm_check();
static void block_correct(void *ptr);

//Local Variable Declarations
static char *heapStart =0;  //pointer to start of the heap, default to 0, first mm_sbrk call will initialize it
static char *freeStart =0;  //pointer to start of the free list

char *EoL = 0;  
//char *freeStart = 0;
char *prevStart = 0;
char *prevFree = 0;
char *nextFree = 0;
int noFree = 1;
 
// mm_init - initialize the malloc package. 
int mm_init(void)
{
  if ((heapStart = mem_sbrk(2*16)) == (void *)-1)
      return -1;
  //Initial pointer to first empty spot on heap    

  //alignment padding
  PUT(heapStart, 0);
 
  //prologue block
  PUT(heapStart + (1*WSIZE), PACK(MINBLKSIZE, 1)); //header
  PUT(heapStart + (2*WSIZE), 0); //forward pointer (initialize to null)
  PUT(heapStart + (3*WSIZE), 0); //back pointer  (initialize to null)
  PUT(heapStart + (3*DSIZE), PACK(MINBLKSIZE, 1));  //footer  (leave DSIZE space free for reallocing data)

  //epilogue block
  PUT(heapStart + (1*WSIZE) + (3*DSIZE), PACK(0, 1));

  //move up heapStart to point at the foward pointer of the epilogue
  heapStart += (2*WSIZE);
  freeStart = heapStart;

  int tester = EXHEAPSIZE/WSIZE;
  if(extend_heap(EXHEAPSIZE/WSIZE) == NULL)
    return -1;
  
  return 0;   
}   
void moveStart(void *ptr){ //puts thing at pointer bp in front of free list
  NEXT_FREE(ptr) = freeStart;  //attach to old front of list
  PREV_FREE(ptr) = NULL;  //first element of free list has no predecessor
  PREV_FREE(freeStart) = ptr;  
  freeStart = ptr;  //ptr is now the start of the free list
}

void fwdPointers(void *ptr, size_t frag){ 

  char *bp = ptr;
  if((((char *) GET(bp)) == EoL) && (((char *) GET(bp + WSIZE)) == EoL)){ //removing only free object
    if(frag < MINFRAG){ //no frag
      noFree = 1;
    }
    else{ //frag
      noFree = 0;
    }
    freeStart = EoL;
  }
  else if(((char *) GET(bp)) == EoL){ //at end of free list
    PUT(GET(bp + WSIZE), GET(bp));
  }
  else if(((char *) GET(bp + WSIZE)) == EoL){ //at start of list
    PUT(((char *) GET(bp)) + WSIZE, GET(bp + WSIZE)); //Set back pointer of next free to 
    freeStart = (char *) GET(bp); //Move free start to next free block!!!!!!!!!!
  }
  else{ //at middle of list
    PUT(GET(bp) + WSIZE, GET(bp + WSIZE));
    PUT(GET(bp + WSIZE), GET(bp));
  }
}

//wrapper for mem_sbrk
static void *extend_heap(size_t words)
{
  char *bp;
  size_t size;
  
  // Allocate even number of words to maintain alignment. 
  size = (words % 2) ? (words + 1) * WSIZE : words *WSIZE;
  //If requested size is smaller than the minimum, request the minimum instead
  if (size < MINBLKSIZE)
    size = MINBLKSIZE;

  if ((long)(bp = mem_sbrk(size)) == -1)
    return NULL;

  //Init Free block head/foot and epilog header
  PUT(HDRP(bp), PACK(size, 0));  //overwrites the old epilogue word
  PUT(FTRP(bp), PACK(size, 0));
  PUT(HDRP(NEXT_BLKP(bp)), PACK(0, 1));  //make a new epilogue word

  //Coalesce if prev block free
  return coalesce(bp);
}

//Find free block size >= asize                  
void * find_fit(size_t asize){
  char *bp;
  //Scan free list, starting with freeStart and ending upon reaching the epilogue block
  //Note that the epilogue block is the only memeber of the free list whose allocate bit is high
  for (bp = freeStart; NEXT_FREE(bp) != NULL; bp = NEXT_FREE(bp)){
    if (asize <= GET_SIZE(HDRP(bp))){
      return bp;
    }
  }
  return NULL; //no fit, BUG allways returning NULL
}


//Called by mm_alloc, places 
void place (void *bp, size_t asize){
  size_t size = GET_SIZE(HDRP(bp));
  size_t frag = size - asize;

  //internal fragment
  if (frag < MINBLKSIZE){
    PUT(HDRP(bp), PACK(size, 1));
    PUT(FTRP(bp), PACK(size, 1));
    delete_free_block(bp);  //remove allocated block from free list
    //    fwdPointers(bp, frag); //Reassigns pointers
  }
    
  //external fragment
  else{
    PUT(HDRP(bp), PACK(asize, 1));
    PUT(FTRP(bp), PACK(asize, 1));
    //fwdPointers(bp, frag);      
    delete_free_block(bp);
    bp = NEXT_BLKP(bp); //Move pointer to next block
    PUT(HDRP(bp), PACK(frag, 0));
    PUT(FTRP(bp), PACK(frag, 0));
    coalesce(bp);
    //    moveStart(bp);
  }
}

// mm_malloc - Allocate a block by incrementing the brk pointer.
// Always allocate a block whose size is a multiple of the alignment.
void *mm_malloc(size_t size)
{
  size_t asize;
  size_t extendsize;
  char *bp;
  
  //Ignore idiots
  if (size <= 0)
    return NULL;
  
  //Adjust blk size to include overheard and alignment reqs
  if (size <= DSIZE)
    asize = 2 * DSIZE;
  else
    asize = DSIZE * ((size + (DSIZE) + (DSIZE-1)) / DSIZE);  
  

  //Use the provided macro instead
  //asize = MAX(ALIGN(size) + DSIZE, MINBLKSIZE);

  //Search free list for a fit
  if((bp = find_fit(asize)) != NULL){
    place(bp, asize);
    return bp;
  }
  
  //No fit found, request more memory
  extendsize = MAX(asize, EXHEAPSIZE);
  if ((bp = extend_heap(extendsize/WSIZE)) == NULL)
    return NULL;
  place(bp, asize);
  return bp;
}

// mm_realloc - Implemented simply in terms of mm_malloc and mm_free
void *mm_realloc(void *ptr, size_t size)
{
  void *oldptr = ptr;
  void *newptr;
  size_t copySize;
  
  newptr = mm_malloc(size);
  if (newptr == NULL)
    return NULL;
  copySize = *(size_t *)((char *)oldptr - SIZE_T_SIZE);
  if (size < copySize)
    copySize = size;
  memcpy(newptr, oldptr, copySize);
  mm_free(oldptr);
  return newptr;
}

/*
 * mm_free - Freeing a block does nothing.
 */
void mm_free(void *bp)
{
  if (bp == NULL)
    return;
  size_t size = GET_SIZE(HDRP(bp));
  PUT(HDRP(bp), PACK(size, 0));
  PUT(FTRP(bp), PACK(size, 0));

  //  moveStart(bp);
  coalesce(bp);
}

//Coalesce two free blocks into one, add to free list
static void *coalesce(void *bp)  //bp is pointer to a free block
{
  //use heap checker to detect problem
  int error_flag = mm_check();

  size_t prev_alloc = GET_ALLOC(FTRP(PREV_BLKP(bp))); 
  size_t next_alloc = GET_ALLOC(HDRP(NEXT_BLKP(bp)));
  size_t size = GET_SIZE(HDRP(bp));
  
  //both neighbot blocks are allocated, so we can't coalesce
  if (prev_alloc && next_alloc){
    return bp;
  }
  else if(prev_alloc && !next_alloc){
    //fwdPointers(NEXT_BLKP(bp), MINFRAG);
    size += GET_SIZE(HDRP(NEXT_BLKP(bp)));
    delete_free_block(NEXT_BLKP(bp));
    PUT(HDRP(bp), PACK(size, 0));
    PUT(FTRP(bp), PACK(size, 0));    
  } 
  
  else if(!prev_alloc && next_alloc){
    //fwdPointers(PREV_BLKP(bp), MINFRAG); //if desperate we can leave this in free list
    size += GET_SIZE(HDRP(PREV_BLKP(bp)));
    delete_free_block(PREV_BLKP(bp));
    PUT(FTRP(bp), PACK(size, 0));       
    PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0)); 
    //bp = PREV_BLKP(bp);
  }
  else if(!prev_alloc && !next_alloc) {
    //fwdPointers(PREV_BLKP(bp), MINFRAG);
    //fwdPointers(NEXT_BLKP(bp), MINFRAG);
    delete_free_block(NEXT_BLKP(bp));
    delete_free_block(PREV_BLKP(bp));
    size += GET_SIZE(HDRP(PREV_BLKP(bp))) + GET_SIZE(FTRP(NEXT_BLKP(bp)));
    PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
    PUT(FTRP(NEXT_BLKP(bp)), PACK(size, 0));
    //    bp = PREV_BLKP(bp);
  }
  moveStart(bp);
  return bp;
}

static void delete_free_block(void * ptr){

  //fix foward pointer of previous block
  if (PREV_FREE(ptr) == NULL){  //then we're deleting the first element of the free list  
    PREV_FREE(NEXT_FREE(ptr)) = NULL;  //fix backpointer  
    freeStart = NEXT_FREE(ptr);  //fix freeStart
  }
  else if(PREV_FREE(ptr) != NULL && NEXT_FREE(ptr) != NULL){  //not at the beginning or end of the free list
    PREV_FREE(NEXT_FREE(ptr)) = PREV_FREE(ptr);
    NEXT_FREE(PREV_FREE(ptr)) =  NEXT_FREE(ptr);   //fix back pointer of next block
  }
  else{ //we are deleting the last element of the list
    NEXT_FREE(PREV_FREE(ptr)) = NULL;
  }
}

int mm_check(void){
  void * bp = heapStart;
  if (GET_SIZE(HDRP(bp)) != MINBLKSIZE){
    printf("Error: check prologue size.");
    return 0;
  }

  return 1;
}

static void block_correct(void *ptr){
  if(GET_SIZE(HDRP(ptr)) % 8 != 0){
    printf("Error: byte misalignment.");
  }
  else if (GET(HDRP(ptr)) != GET(FTRP(ptr))){
    printf("Error: header/footer mismatch.");
  }
}
