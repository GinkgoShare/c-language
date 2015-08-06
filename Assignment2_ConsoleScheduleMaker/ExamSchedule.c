/********************************************************************************
  Begin #include statements
********************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "ExamSchedule.h"

/********************************************************************************
  Begin #define statements
********************************************************************************/

#define ARSZ 1000
#define daysInWeek 7
#define byte 8
#define lluBits (byte*sizeof(long long int))

/********************************************************************************
______________________________BEGIN IMPLEMENTATION______________________________

PROGRAM PURPOSE: Output the unscheduled time within a two week exam schedule.

AUTHOR: Christopher JW Elliott

HISTORY: 11/30/2014 Version 1.1 
********************************************************************************/

typedef long long unsigned int lluInt;
typedef unsigned int UINT;

StudentSchedule students[ARSZ] = {0};
lluInt examSchedule[2] = {0};
int i = 0, j = 0, k = 0;

static void setExamSchedule(void);
void showBinary(lluInt);

/********************************************************************************
PURPOSE: Returns an exam schedule as a long long unsigned int for a given 
         student.

INPUTS:  Student number, the day of the exam (Mon., Tue., Wed., etc...), 
         the exam's starting time by the hour, and the exam's length in hours.

OUTPUTS: The students exam time as a long long unsigned int.

AUTHOR:  David Houtman modified by Christopher JW Elliott
********************************************************************************/

static lluInt getBinExamTime(int studentNum, int day, int startTime, int examLength) {
	int initShift = 0;
	lluInt bookingMask = 0xFFFFFFFFFFFFFFFF;
	startTime -= 9; // offset time
	initShift = lluBits - examLength;
	bookingMask <<= initShift;
	bookingMask >>= startTime;
	bookingMask >>= (day*byte);
  showBinary(bookingMask); // prints the exam time mask (Leave it, it looks cool)
	return bookingMask;
}

/********************************************************************************
PRECONDITION: Exam time must be available within the students schedule for
              successful completion of this function.

PURPOSE: Inputs a students exam time into their respective exam schedule.

INPUTS: The student number, week, day of the exam, start time, and the length of
        the exam. All as integer values.  

OUTPUTS: Returns an unsigned int value which determines the success or failure
         of the function depending on available space within the students
         schedule.
********************************************************************************/

UINT setBookingTime(int studentNum, int week, int day, int startTime, int examLength) {
	lluInt bookingMask = getBinExamTime(studentNum, day, startTime, examLength);
	lluInt tempMask = students[studentNum].examSchedule[week] & bookingMask;
	if (tempMask > 0)
		return 0;
	else {
		students[studentNum].examSchedule[week] += bookingMask;
		return 1;
	}
}

/********************************************************************************
PURPOSE: Returns the long long unsigned int value of a given exam week schedule
         for a given students.

INPUTS:  The student number and week as integer values.  

OUTPUTS: The long long unsigned int  value that represents the students schdule
         for the week.
********************************************************************************/

lluInt getBinExamWeekInfo(int studentNum, int week) {
	return students[studentNum].examSchedule[week];	
}

/********************************************************************************
PURPOSE: This function sets the exam schedule for each week from the array of
         1000 students.
********************************************************************************/

static void setExamSchedule() {
  for (i = 0; i < ARSZ; i++) {
		examSchedule[0] |= getBinExamWeekInfo(i, 0); // set the exam schedule for week one ie. 0
		examSchedule[1] |= getBinExamWeekInfo(i, 1); // set the exam schedule for week two ie. 1
	}
}

/********************************************************************************
PURPOSE: Outputs the available times to schedule an exam. This is based on the 
         previously inputed times from setBookingTime().

ALGORITHM: Anding each bit of the two exam schedules long long unsigned int 
           values of the examWeeks[] array. If the result of the an is > zero then
           there is no available space during that hour. Hence, no available time
           will be printed to the console. If the result of the anding is equal
           to zero then there is a time slot available, which will be printed to
           the console. A flag is set to track the length of time available.
********************************************************************************/

void getUnscheduledTime() {
  setExamSchedule();
  int flag = 0; lluInt mask = 0x8000000000000000;
  char *days[] = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun", ""};
  printf("\nThe following times are available for scheduling an exam: \n");  
  for (i = 0; i < 2; i++) { // i equals the week (only 2)
    printf("\nWeek %u:", (i+1));
    lluInt mask = 0x8000000000000000;
    for (j = 0; j < daysInWeek; j++, flag = 0){ // j equals the day
      for (k = 0; k < byte; k++, mask >>= 1) { // k equals the hour
        if (!(examSchedule[i] & mask) && !(flag)) {
          printf("\n  %s: %2u:00 - ", days[j], (k+9));
          flag = 1;
        } else if ((examSchedule[i] & mask) && flag) {
          printf("%u:00", (k+9));
          flag = 0;
        }
      }
      if (flag) { printf("%u:00", (k+9)); }
	  }
    printf("\n\nExam Week %d Mask: ", (i+1));
    showBinary(examSchedule[i]);
  }
  printf("\n");	
}

/********************************************************************************
PURPOSE: Prints the mask of a long long unsigned int value to console.

INPUTS: The long long unsigned int value to print. 

OUTPUTS: The binary value of the input long long unsigned int value to console.

AUTHOR:  David Houtman
********************************************************************************/

void showBinary(lluInt myLLuVal){
	lluInt mask = 0x8000000000000000;
	for (int i=0; i < (lluBits-8); i++){
		printf((myLLuVal & mask)?"1":"0");
		mask >>= 1;
	}	
	printf("\n");
}
