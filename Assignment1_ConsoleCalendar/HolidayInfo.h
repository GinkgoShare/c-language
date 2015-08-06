typedef const unsigned int CINT;

extern CINT NEW_YEARS_DAY;
extern CINT GROUND_HOG_DAY;
extern CINT VALENTINES_DAY;
extern CINT ST_PATRICKS_DAY;
extern CINT APRIL_FOOLS_DAY;
extern CINT REMEMBRANCE_DAY;
extern CINT CHRISTMAS_DAY;
extern CINT BOXING_DAY;

extern size_t getHolidayStringLength(int);
extern wchar_t *getHolidayString(CINT dyOfYr);
