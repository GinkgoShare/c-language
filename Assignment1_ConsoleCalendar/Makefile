OBJS = main Main.o Calendar.o Draw.o HolidayInfo.o ConsoleData.o

main: Main.o Calendar.o Draw.o HolidayInfo.o ConsoleData.o
	gcc Main.o Calendar.o Draw.o HolidayInfo.o ConsoleData.o -o main -std=c99

Main.o: Main.c Calendar.h
	gcc -c Main.c -std=c99

Calendar.o: Calendar.c Draw.h HolidayInfo.h ConsoleData.h
	gcc -c Calendar.c -std=c99

Draw.o: Draw.c Calendar.h BoxDrawChars.h
	gcc -c Draw.c -std=c99

HolidayInfo.o: HolidayInfo.c
	gcc -c HolidayInfo.c -std=c99

ConsoleData.o: ConsoleData.c
	gcc -c ConsoleData.c -std=c99

clean:
	rm -r $(OBJS)
