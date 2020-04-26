obraz: main.o funkcje.o flagi.o
	cc main.o funkcje.o flagi.o -o obraz -lm

main.o: main.c funkcje.h
	cc main.c -c -o main.o 

funkcje.o: funkcje.c funkcje.h
	cc funkcje.c -c -o funkcje.o

flagi.o: flagi.c funkcje.h
	cc flagi.c -c -o flagi.o
