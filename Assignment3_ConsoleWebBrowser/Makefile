OBJS = main Main.o ParseURL.o getHTMLPage.o

main: Main.o ParseURL.o getHTMLPage.o
	gcc -o main Main.o ParseURL.o getHTMLPage.o

Main.o: Main.c ParseURL.h getHTMLPage.h
	gcc -c Main.c

ParseURL.o: ParseURL.c ParseURL.h
	gcc -c ParseURL.c

getHTMLPage.o: getHTMLPage.c getHTMLPage.h
	gcc -c getHTMLPage.c

clean:
	rm -rf $(OBJS)


