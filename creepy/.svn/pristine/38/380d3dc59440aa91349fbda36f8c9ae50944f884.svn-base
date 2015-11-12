#include <stdio.h>
#include "student.h"
#include "input.h"

extern int score_histogram[NUM_BUCKETS];
extern int grade_tally[NUM_LETTER_GRADES];
extern short score_ranges[2*NUM_BUCKETS];
extern char grade_letters[NUM_LETTER_GRADES][2];

void compute_totals ()
{
  int i;
  int j;
  int sum;

  for ( i = 0; i < NUM_STUDENTS;  i++){
    sum = 0;
    for ( j = 0; j < 5; j++){
      sum += students[i].scores[j];
    }
    students[i].total = sum;
  }
}


void compute_grades ()
{
  int i, j;
  int max_score, min_score, range;

  max_score = 500;
  min_score = 0;
  range = max_score - min_score;

  for(i = 0; i < NUM_STUDENTS; i++){
    if(students[i].total <= (min_score + range/5)){
      students[i].grade = 'F';
    }
    else if (students[i].total <= (min_score + (2*range)/5)){
      students[i].grade = 'D';
    }
    else if (students[i].total <= (min_score + (3*range)/5)){
      students[i].grade = 'C';
    }
    else if (students[i].total <= (min_score + (4*range)/5)){
      students[i].grade = 'B';
    }
    else if (students[i].total <= (min_score + range)){
      students[i].grade = 'A';
    }
  }
}


void compute_histogram ()
{
  int i;

  for(i = 0; i < NUM_STUDENTS; i++){
    if(students[i].total <= 50){
      score_histogram[0]++;
    }
    else if(students[i].total <= 100){ 
      score_histogram[1]++;
    }
    else if(students[i].total <= 150){ 
      score_histogram[2]++;
    }
    else if(students[i].total <= 200){ 
      score_histogram[3]++;
    }
    else if(students[i].total <= 250){ 
      score_histogram[4]++;
    }
    else if(students[i].total <= 300){ 
      score_histogram[5]++;
    }
    else if(students[i].total <= 350){ 
      score_histogram[6]++;
    }
    else if(students[i].total <= 400){ 
      score_histogram[7]++;
    }
    else if(students[i].total <= 450){ 
      score_histogram[8]++;
    }
    else if(students[i].total <= 500){ 
      score_histogram[9]++;
    }

    switch(students[i].grade){
    case 'A':
      grade_tally[0]++;
      break;
    case 'B':
      grade_tally[1]++;
      break;
    case 'C':
      grade_tally[2]++;
      break;
    case 'D':
      grade_tally[3]++;
      break;
    case 'F':
      grade_tally[4]++;
      break;
    }
  }

}


