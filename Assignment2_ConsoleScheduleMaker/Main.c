/********************************************************************************
  Begin #include statements
********************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "ExamSchedule.h"
//#include "_test.h"
#include "040570022.h"

/********************************************************************************
  Begin main()
********************************************************************************/

int main(void) {
  int i = 0;
  // sets exam schedule for each student
	for (i = 0; i < (sizeof(examBookings)/sizeof(examBookings[0])); i++) {
    setBookingTime(examBookings[i][0], examBookings[i][1], examBookings[i][2], examBookings[i][3], examBookings[i][4]);
  }
  // print the unsheduled time of both exam weeks
  getUnscheduledTime();
}
