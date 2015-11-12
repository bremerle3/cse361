/*  Source name		: hist.c
    Executable name	: hist
    Code model		: Protected-mode (32-bit C)
    Version		:
    Created date	:
    Last update		:
    Author		:
    Description		: This program outputs a histogram of total scores
			     and a frequency distribution of grades based
			     on a table of raw scores.
*/


#include <stdio.h>
#include <stdlib.h>
#include "student.h"
#include "input.h"
#include "yourcode.h"

static void print_results ();
static void print_score_histogram ();
static void print_grade_tally ();

int	score_histogram[NUM_BUCKETS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int	grade_tally[NUM_LETTER_GRADES] = {0, 0, 0, 0, 0};
short   score_ranges[2*NUM_BUCKETS] =	{   0,  50,
			       		   51, 100,
				       	  101, 150,
					  151, 200,
				       	  201, 250,
			       		  251, 300,
			       		  301, 350,
			       		  351, 400,
			       		  401, 450,
			       		  451, 500 };
char    grade_letters[NUM_LETTER_GRADES][2] = { "A", "B", "C", "D", "F" };


int main ()
{
  
  compute_totals ();
  compute_grades ();
  compute_histogram ();
  print_results ();
  exit (0);
}


void print_results()
{
    print_score_histogram();

    printf ("\n");

    print_grade_tally();
}


void print_score_histogram()
{
    int		i, j;

    for (i = 0; i < NUM_BUCKETS; i++)
    {
	printf("%3d - %3d: ", score_ranges[2*i], score_ranges[2*i+1]);

	for (j = 0; j < score_histogram[i]; j++)
	    printf("*");

	printf("\n");
    }
}

void print_grade_tally()
{
    int		i;

    for (i = 0; i < NUM_LETTER_GRADES; i++)
    {
	printf("Number of %s's:  %d\n", grade_letters[i], grade_tally[i]);
    }
}

