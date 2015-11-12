/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This[6~ is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* Copyright (C) 1991-2012 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* We do support the IEC 559 math functionality, real and complex.  */
/* wchar_t uses ISO/IEC 10646 (2nd ed., published 2011-03-15) /
   Unicode 6.0.  */
/* We do not support C11 <threads.h>.  */
/* 
 * negativeOne - return a value of -1 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int negativeOne(void) {
       /* not 1 and then add 1 to the result to get -1 */
       int x;
       x = (~1) + 1;
  return x;
}
/* 
 * bitwiseOr - x|y using only ~ and & 
 *   Example: bitwiseOr(6, 5) = 7
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 1
 */
int bitwiseOr(int x, int y) {
  /* Use DeMorgan's law: ~(A+B) = ~A + ~B, negate the whole thing for A+B */
  int z;
  z = ~((~x) & (~y));
  return z;
}
/* 
 * cpLSB - set all bits of result to least significant bit of x
 *   Example: cpLSB(5) = 0xFFFFFFFF, cpLSB(6) = 0x00000000
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int cpLSB(int x) {
  /* sizeof(int) is 4 bytes (32 bits) */
  /* Use the fact that << pads right side with 0s, and >> pads with MSB */
  int y, z;
  y = x << 31;
  z = y >> 31;
  return z;
}
/* 
 * areEqual - return 1 if x == y, and 0 otherwise 
 *   Examples: areEqual(5,5) = 1, areEqual(4,5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int areEqual(int x, int y) {
  /* Use xor to detect conflicting bits. ! will convert any non-zero 
     number to a logical 1 or 0 */
  int z;
  z = x^y;
  return !z;
}
/* 
 * anEvenBit - return 1 if any even-numbered bit in word set to 1
 *   Examples anEvenBit(0xA) = 0, anEvenBit(0xE) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int anEvenBit(int x) {
  /* Use masks of even bits. Need 4 total since we can only use 8-bit integers. 
     Start at 85 (low even bits) and use << to get the higher masks. */
  int mask1_8, mask9_16, mask17_24, mask25_32;
  int x1_8, x9_16, x17_24, x25_32;
  int z;

  mask1_8 = 85;
  mask9_16 = mask1_8 << 8;
  mask17_24 = mask9_16 << 8;
  mask25_32 = mask17_24 << 8;

  x1_8 = x & mask1_8; 
  x9_16 = x & mask9_16; 
  x17_24 = x & mask17_24;
  x25_32 = x & mask25_32;
  
  z = !(x1_8 | x9_16 | x17_24 | x25_32);
  return !z;
}
/* 
 * replaceAByte(x,n,c) - Replace byte n in x with c
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: replaceAByte(0x12345678,1,0xab) = 0x1234ab78
 *   You can assume 0 <= n <= 3 and 0 <= c <= 255
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 3
 */
int replaceAByte(int x, int n, int c) {
  /*First, erase byte n by ANDing with a mask.  Then, shift c until it is
    at the correct byte position. To get the correct shifts, note that 
    0=0*2^3, 8=1*2^3, 16=2*2^3, and 24=3*2^3. So the shift number is 
    n*2^3. A right shift is a multiplication by 2, so the shift number
    is (n << 3). Finally, OR the erased x with the shifted c for the 
    replacement. */
  int shift_num, mask, shifted_c, z;
  shift_num = (n << 3);
  mask = 255 << shift_num; //mask of 1s for 2 bytes, 0xFF.
  shifted_c = (c << shift_num);
  z = shifted_c | (~mask & x);
  return z;
}
/* 
 * Tcmax - return maximum 2's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tcmax(void) {
  /*Maximum (positive) 32-bit 2's complement integer is 0x7FFFFFFF. In binary
    this is all 1s except the MSB which is 0.  Start with 1, shift it 31 times
    to get the 1 in the MSB, the bitwise not for 0x7FFFFFFF. */
  int x, z;
  x = 1;
  z = x << 31;
  return ~z;
}
/*
 * isTCmax - returns 1 if x is the maximum, 2's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTCmax(int x) {
  /*If x is the maximum (positive) 2s complement number, then adding 
   1 to it will cause it to become the smallest number (most negative). A bitwise
  NOT will cause it to become to largest again. First though, have to make sure
  x is not 1111 since adding 1 to that would overflow.*/
  int negx, y, z;
  negx = !(!(~x));  //This is zero for x=0xFFFFFFFF, 1 otherwise;
  y = ~(x + 1);
  z = negx & !(x^y); 
  return z;
}
