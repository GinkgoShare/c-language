#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>
#include "Calendar.h"

typedef wchar_t* string;
typedef unsigned int UINT;
/**************************************************************************************
PURPOSE: This program outputs a calendar month to the console. It will work for any
	 year of the 21st century.

VERSION: Version 1.0

AUTHOR:  Christopher Elliott S/N 040-570-022 

NOTES: 	 As you can see there is not much to this file. Refer to Calendar.c and Draw.c
	 for more details.
***************************************************************************************/

int main(void) {
  setlocale(LC_ALL, "");
  outputCalendar();
  return EXIT_SUCCESS;
}


