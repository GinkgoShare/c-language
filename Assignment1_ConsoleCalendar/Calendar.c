/****************************************************************************************
TITLE:    Calendar.c
AUTHOR:   Christopher Elliott S/N 040-570-022
VERSION:  1.0 2014/11/02

PURPOSE:  The Calendar.c file keeps track of the information associated with a calendar
          month and outputs an appropriate holiday string for a given day.

Begin #include statements, typedef's, and global variables
*****************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>
#include <unistd.h>
#include "Draw.h"
#include "HolidayInfo.h"
#include "ConsoleData.h"

typedef unsigned int UINT;

UINT month = 0, year = 0, leap = 0, startDay = 0, strLen = 0, daysToMonth = 0, monthSize = 0, dyOfYr = 0;

UINT monthSz[2][13] = {
  {0,31,28,31,30,31,30,31,31,30,31,30,31},
  {0,31,29,31,30,31,30,31,31,30,31,30,31}
};

UINT MonthFactor[2][13] = {
  {0,1,4,4,0,2,5,0,3,6,1,4,6},
  {0,0,3,4,0,2,5,0,3,6,1,4,6}
};

// sets the leap variable
static void isLeapYr() { leap = (year%4==0) && (year%100!=0) || ((year%400==0)); }
// sets the day that this month starts on
static void setStartDay() { startDay = ((year%100) + ((int)(year%100)/4) + MonthFactor[leap][month] + 6) % 7; }

// sets the number of days to the beginning of this month ie. Jan. 1st == Day 1 && Dec.31st == Day 365
static void calcDaysToMonth() {
  for (int i = 1;i < month; i++)
    daysToMonth += monthSz[leap][i];
}
// returns the size of the given month in days
static UINT getMonthSize() {
  return monthSz[leap][month];
}
// sets the month with user input
static void setMonth() {
  do {
    wprintf(L"Enter the month (Jan=1, Feb=2, etc.): ");
    wscanf(L"%d", &month);
    if (month > 12 || month < 1)
      wprintf(L"***INVALID***INPUT***\n");
  }while(month > 12 || month < 1);
}
// sets the year with user input
static void setYear() {
  wprintf(L"Enter the year (2012, 2013, 2014...): ");
  wscanf(L"%d", &year);
}
/****************************************************************************************
PURPOSE:  To print the appropriate characters within the box of any given day.

INPUTS:   This function switches on the line argument. Each row of the Calendar table
          is 4 lines. The day argument is printed on the first line, but is also
          needed to get the holiday string. The width argument is used to print the 
	  appropriate length of characters so the table maintains its proper alignment.

NOTES:    I chose the switch block because it provides better readability. Although it
          maybe adds more lines of code then if I were to use an if else, this keeps the
          code better organized.
****************************************************************************************/
extern void getBoxString(UINT line, UINT day, UINT width) {
  (month > 2) ? (dyOfYr = (daysToMonth+day-leap)) : (dyOfYr = (daysToMonth+day));
  switch (line) {
    case 1: // line 1: print the day
      // adds an extra space depending on whether the day is one or two digits
      // more then 2 digits do not need to be accounted for in this program
      (day > 9) ? wprintf(L"          %d ", day) : wprintf(L"           %d ", day); 
      break;
    case 2: // line 2: print empty line ie. whitespace
      for (int i = 0; i < width; ++i)
        wprintf(L" ");
      break;
    case 3: // line 3: print the holiday name if there is one
      strLen = getHolidayStringLength(dyOfYr);
      for (int i = 0; i < (width-(strLen)); ++i)
        wprintf(L" ");
      if (strLen)
        wprintf(L"%s", getHolidayString(dyOfYr));          
      break;
    case 4: // line 4: print the word "day" if needed
      if (getHolidayStringLength(dyOfYr) > 0) {
        for (int i = 0; i < (width-3); ++i)
          wprintf(L" ");
        wprintf(L"Day");
      }else { // if there is no holiday on this day then print whitespace
        for (int i = 0; i < width; ++i)
          wprintf(L" ");
      } 
      break;
  } 
}
/****************************************************************************************
PURPOSE:  calls the appropriate steps to get the necessary user input and print the 
	  corresponding calendar.

NOTES:	  Instead of exiting the program right away, if the calendar will not fit the
	  console, the program pauses to give the user time to expand their terminal.
****************************************************************************************/
extern void outputCalendar() {
  wprintf(L"\nWelcome! So you need to get organized do ya?\n");
  wprintf(L"Well just enter a date to get started. :)\n\n");
  setMonth();
  setYear();

  int attempts = 0; // attemps to resize the terminal window if the calendar will not fit
  int safeToDisplay = getConsoleWidthChars();
  while(attempts < 5) {
    if (safeToDisplay < 99){
      ++attempts;
      wprintf(L"***ERROR*** Please expand your console***ERROR***\n");
      sleep(3); // provides the user time to expand their console
      safeToDisplay = getConsoleWidthChars();
    }
    if (safeToDisplay >= 99) {
      isLeapYr();
      calcDaysToMonth(); // sets the number of days to the start of this month
      setStartDay(); // equates what day this month starts on
      setTableOffset(startDay, getMonthSize()); // see Draw.c
      outputTable(); // see Draw.c
      attempts = 5;
    }
  }
}
