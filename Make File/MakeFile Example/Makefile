run: func.o main.o
	g++ func.o main.o -o run
fun.o : func.c head.h
	g++ -c func.c
main.o : main.c func.c
	g++ -c main.c
clean:
	rm*.o run
