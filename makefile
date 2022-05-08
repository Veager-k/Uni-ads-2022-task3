main:
	gcc -c main.c
	gcc -c stack.c
	gcc -c queue.c
	ar cr libData.a stack.o queue.o
	gcc main.o libData.a -o main.exe
	.\main.exe