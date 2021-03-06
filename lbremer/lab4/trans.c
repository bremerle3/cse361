/* 
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */ 
#include <stdio.h>
#include "cachelab.h"

int is_transpose(int M, int N, int A[N][M], int B[M][N]);

/* 
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. 
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{
int Row,Column;
int i, j;
int d = 0;
int temp = 0;

if(M == 32 && N == 32)
{
  for(Row = 0; Row < N; Row = Row + 8)
    {
    for(Column = 0; Column < M; Column = Column + 8)
      {
      for(i = Row; i < Row + 8; i++)
	{
	for(j = Column; j < Column + 8; j++)
	  {
	  if(i != j)
	    {
	      B[j][i] = A[i][j];
	    }
	  else 
	    {
	      temp = A[i][j];
	      d = i;
	    }
	  }
	if (Row == Column)
	  {
	    B[d][d] = temp;
	  }
	}
      }
    }
 }

if(M == 61 && N == 67)
  {
  for(Row = 0; Row < N; Row = Row + 8)
    {
    for(Column = 0; Column < M; Column = Column + 8)
      {
      for(i = Column; (i < Column + 8 && i < M); i++)
	{
	for(j = Row; (j < Row + 8 && j < N); j++)
	  {
	  B[i][j] = A[j][i];
	  }
	}
      }
    }
  }


if(M == 64 && N == 64)
{
  for(Row = 0; Row < N; Row = Row + 4)
    {
    for(Column = 0; Column < M; Column = Column + 4)
      {
      for(i = Row; i < Row + 4; i++)
	{
	for(j = Column; j < Column + 4; j++)
	  {
	  if(i != j)
	    {
	      B[j][i] = A[i][j];
	    }
	  else 
	    {
	      temp = A[i][j];
	      d = i;
	    }
	  }
	if (Row == Column)
	  {
	    B[d][d] = temp;
	  }
	}
      }
    }
 }

/*
if(M == 32 && N == 32)
{
  for(Row = 0; Row < N; Row = Row + 8)
    {
    for(Column = 0; Column < M; Column = Column + 8)
      {
      for(i = Row; i < Row + 8; i++)
	{
	temp = A[i];
	if(Row == Column)
	  {
	    d = temp[i];
	  }
	for(j = Column; j < Column + 8; j++)
	  {
	  if(i != j)
	    {
	      B[j][i] = A[i][j];
	    }
	  }
	if(Row == Column)
	  {
	    B[i][i] = d;
	  }
	}
      }
    }
 }

if(M == 61 && N == 67)
  {
  for(Row = 0; Row < N; Row = Row + 8)
    {
    for(Column = 0; Column < M; Column = Column + 8)
      {
      for(i = Column; (i < Column + 8 && i < M); i++)
	{
	for(j = Row; (j < Row + 8 && j < N); j++)
	  {
	  B[i][j] = A[j][i];
	  }
	}
      }
    }
  }

if(M == 64 && N == 64)
{
  for(Row = 0; Row < N; Row = Row + 4)
    {
    for(Column = 0; Column < M; Column = Column + 4)
      {
      for(i = Row; i < Row + 4; i++)
	{
	temp = A[i];
	if(Row == Column)
	  {
	    d = temp[i];
	  }
	for(j = Column; j < Column + 4; j++)
	  {
	  if(i != j)
	    {
	      B[j][i] = A[i][j];
	    }
	  }
	if(Row == Column)
	  {
	    B[i][i] = d;
	  }
	}
      }
    }
 }

*/

}

/* 
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started. 
 */ 

/* 
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }    

}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc); 

    /* Register any additional transpose functions */
    registerTransFunction(trans, trans_desc); 

}

/* 
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}

