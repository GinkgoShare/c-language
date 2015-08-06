#include <wchar.h>
#include <locale.h>
#include <assert.h>
#include <string.h>

typedef const unsigned int CINT;
typedef char* string;

#define NYD 1
#define GHD 33
#define VD 45
#define SPD 76
#define AFD 91
#define RD 315
#define CD 359
#define BD 360

CINT NEW_YEARS_DAY = NYD;
CINT GROUND_HOG_DAY = GHD;
CINT VALENTINES_DAY = VD;
CINT ST_PATRICKS_DAY = SPD;
CINT APRIL_FOOLS_DAY = AFD;
CINT REMEMBRANCE_DAY = RD;
CINT CHRISTMAS_DAY = CD;
CINT BOXING_DAY = BD;

CINT HolidayDayOfYear[] = {NYD, GHD, VD, SPD, AFD, RD, CD, BD};

string Holidays[] = {"New Year's", "Ground Hog", "Valentine's", "St. Particks", "April Fool's", "Remembrance", "Christmas", "Boxing"};

static int getHolidayIndex(CINT dyOfYr){
   int ctr = -1;
   assert((dyOfYr < 366) || (dyOfYr > 0));
   while ((dyOfYr != HolidayDayOfYear[++ctr]) && ctr < 8){}
   return ((ctr > 7) ? -1 : ctr);
}

size_t getHolidayStringLength(CINT dyOfYr){
   int holidayIndex = getHolidayIndex(dyOfYr);
   return (((holidayIndex < 0)  || (holidayIndex > 8)) ? 0 : strlen(Holidays[holidayIndex])); // return zero if it is not a holiday
} 

string getHolidayString(CINT dyOfYr){
   int holidayIndex = getHolidayIndex(dyOfYr);
   return ((holidayIndex < 0) ? NULL : Holidays[holidayIndex]);
}



