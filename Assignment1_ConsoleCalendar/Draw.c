/****************************************************************************************
TITLE:    Draw.c

AUTHOR:   Christopher Elliott S/N 040-570-022

VERSION:  1.0 2014/11/02

PURPOSE:  The Draw.c file is designed to handle the draw functions for a table, which in 
	  this case is being used to draw a calendar with information provided by the 
	  Calendar.c library.

Begin #include statements, typedef's, forward declarations, and global variables
****************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>
#include "BoxDrawChars.h"
#include "Calendar.h"

typedef wchar_t* string;
typedef unsigned int UINT;

static void printColWidth(string*, string*);
static void printRowHeight(string*, string*);

UINT  width = 13, height = 4, nColumns = 7, row = 0, line = 0, offset = 0, 
      nBoxes = 0, currentColumn = 0, currentBox = 0;
/****************************************************************************************
PURPOSE:    outputTableString is one of the main functions of this library because 
	    printing to the console must be done one line at a time. This function takes 
	    care of printing each line of a table.

INPUTS:     Arrays of wchar_t characters used to print the table.

OUTPUTS:    The output is printed to the console using wprintf() functions.

ALGORITHMS: This function works by using the first argument until the current column is
	    past the offset value. The first column is printed outside of the loop that
	    prints the rest of the columns because no condition is needed to decide what
	    to print, it is always the "LEFT" char of the first argument.
	    See BoxDrawChars.h for details on the arrays. The function then begins to 
	    loop at the column 2 string, deciding which array to use for printing based
	    upon whether the current column being printed has passed the offset value or 
	    the current row being printed is not the first row, which has the more complex conditions.

NOTES:      Starting the current column at 1, for each output string, provides better 
	    readability of the code and maintains that the starting column is greater 
	    than the offset when offset == 0. 
****************************************************************************************/
void outputTableString(string list1[], string list2[]) {
  currentColumn = 1;
  (currentColumn <= offset) ? wprintf(list1[LEFT]) : wprintf(list2[LEFT]);
  printColWidth(list1, list2); // output the column width characters

  for (currentColumn = 2; currentColumn <= nColumns; currentColumn++) {
    if (currentColumn <= offset) {
      wprintf(list1[MIDDLE]); // before the offset print the first list argument character
    }else if (currentColumn == offset+1) {
      // only the first row needs the "LEFT" character printed once passed the offset
      (row > 1) ? wprintf(list2[MIDDLE]) : wprintf(list2[LEFT]); // usually past row 1 causing this to be shortcircuited mostly
    }else {
      wprintf(list2[MIDDLE]);
    }
    printColWidth(list1, list2); // see printColWidth(string*, string*)
  }
  wprintf(list2[RIGHT]); // caps the line
  wprintf(CR); // Carriage return; next line
}
/****************************************************************************************
PURPOSE:    This is the second main function of the Draw.c library which calls upon 
	    outputTableString() to print the entire table. This function decides which 
	    character array to pass through to outputTableString().

ALGORITHMS: The first row passes calls outputTableString() passing the whitespace array 
	    with the first line array as arguments. If there is no offset then the first 
	    line array, passed as the second argument, can handle the job of printing 
	    the necessary characters. As each row is printed it subtracts the number of 
	    printed boxes from the remaining boxes to print. To print the second row, 
	    the first and middle arrays are passed to outputTableString() as arguments. 
	    In the case of a zero offset, the middle will take over all of  the printing. 
	    The function then goes into a loop to print the middle rows as long as there
            are 7 or more boxes to print. If afterwards, there are still boxes to print, 
	    the offset is set to the remaining number of boxes left to print, and 
	    outputTableString() is called with either the intern array or the last array
	    as the first argument.

NOTES:      Starting the row at one provides better readability.
****************************************************************************************/
void outputTable() {
  row = 1; // tracks which row the program is printing: Row #1
  outputTableString(empty, first); // empty == whitespace for the offset columns Row #1
  printRowHeight(empty, intern); // output the row height strings Row #1
  ++row; // increments to the next row
  nBoxes -= (nColumns - offset); // subtracts the number of boxes printed from the amount needed
  outputTableString(first, middle); // Row #2
  printRowHeight(intern, intern); // Row #2
  ++row;
  nBoxes -= nColumns;
  // while the number of remaining boxes is >= 7(daysInWeek) print out middle rows: Rows  #(3, 4, ...)
  while (nBoxes >= nColumns) {
    outputTableString(middle, middle);
    printRowHeight(intern, intern);
    ++row;
    nBoxes -= nColumns;
  } // end while loop
  // plus one is needed in this case because we want to print the first argument array one column longer than the offset
  offset = nBoxes + 1;
  // we will usually have boxes left over to print so this can mostly be shortcircuited
  (nBoxes > 0) ? outputTableString(middle, last) : outputTableString(last, last);
  if (nBoxes != 0) {
    // we do not have to worry about printing past the offset anymore so we can reduce the number of columns to remaining boxes
    nColumns = nBoxes; 
    printRowHeight(intern, intern);
    outputTableString(last, last); // final string to cap the table
  }
}
/****************************************************************************************
PURPOSE:  This function resets the current box after every string of a row except the 
          last. It does not reset after the last line of the row because it will maintain
          the proper count for the next row. This is done in order to keep track of which 
          box we are printing since each row is printed in 5 lines we must loop back to 
          the beginning box four times in order to properly manage the current box.      
****************************************************************************************/
static void resetCurrentBox() {
  if (row == 1) // row 1 can subtract the value from itself because this is the incremented value
    currentBox -= currentBox;
  else if (nBoxes >= nColumns) // for the middle rows we reset by 7 bringing us to the initial count of the row
    currentBox -= nColumns;
  else // for the last row it will reset by the number of remaining boxes back to the first column
    currentBox -= nBoxes;
}
/****************************************************************************************
PURPOSE:  This function prints the width of a box. For line == 0 it will print a row
          divider otherwise it will call the extern function getBoxString() to provide 
	  the string for the content of the box. 
****************************************************************************************/
static void printColWidth(string list1[], string list2[]) {
  if (line > 0 && (row > 1 || currentColumn > offset)) { // only row 1 does not print boxes before the offset value
    currentBox++; // the getBoxString() function is called for every box so we can increment here
    getBoxString(line, currentBox, width);
  }else {
    for (int i = 0; i < width; i++) // prints the row divider character
      (currentColumn <= offset) ? wprintf(list1[BAR]) : wprintf(list2[BAR]);
  }
}
/****************************************************************************************
PURPOSE:  This function prints the height of each row and resets the current box to the
          beginning of each string until it completes the row. 
****************************************************************************************/
static void printRowHeight(string list1[], string list2[]) {
  for (line = 1; line <= height; line++) {
    outputTableString(list1, list2);
    if (line < 4) // resets to the appropriate current box until the height of the row is printed
      resetCurrentBox();
  }
  line = 0;
}
/****************************************************************************************
PURPOSE:  This function sets the offset of the table and sets the number of boxes the
          table needs to print. 
****************************************************************************************/
void setTableOffset(UINT offsetValue, UINT numOfVisibleBoxes) {
  offset = offsetValue;
  nBoxes = numOfVisibleBoxes;
}
/****************************************************************************************
PURPOSE:  This function will clear the console screen if the user wishes. 
****************************************************************************************/
void eraseTable() {
  wchar_t ans;
  wprintf(L"Do you want to clear the screen? (Y/N)");
  wscanf(L"%ls", &ans);
  if ((ans == L'Y') || (ans == L'y'))
    system("clear");
}



