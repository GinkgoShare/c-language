OBJS = main Main.o ExamSchedule.o

main: Main.o ExamSchedule.o
	gcc -o main Main.o ExamSchedule.o

Main.o: Main.c ExamSchedule.h _test.h
	gcc -c Main.c

ExamSchedule.o: ExamSchedule.c
	gcc -c ExamSchedule.c -std=c99

clean:
	rm -rf $(OBJS)
