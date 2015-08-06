#include <wchar.h>
#include <locale.h>
#include <stdio.h>
#include "HolidayInfo.h"

int main(void) {

   unsigned int dayOfYear;
   
   setlocale(LC_ALL, "");
   wprintf(L"Enter a day of the Year: ");
   scanf("%u", &dayOfYear);

   wchar_t *str = getHolidayString(dayOfYear);
   size_t len = getHolidayStringLength(dayOfYear);

   if (str != NULL){		// could also use (len > 0)
   	wprintf (L"The holiday is : %s\n", str);
        wprintf (L"and the length of holiday string is %zu\n", len);
   }
   else
	wprintf (L"This is Not a holiday day\n");
}
