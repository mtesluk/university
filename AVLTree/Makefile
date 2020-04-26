#
#  To sa opcje dla kompilacji
#
CXXFLAGS=-g -Iinc -Wall -pedantic -std=c++0x

all: obj obj/main.o obj/functions.o
	g++ -Wall -pedantic -o avl obj/main.o obj/functions.o

obj:
	mkdir obj/

obj/main.o: src/main.cpp inc/tree.hh 
	g++ -c ${CXXFLAGS} -o obj/main.o src/main.cpp

obj/functions.o: src/functions.cpp inc/functions.hh 
	g++ -c ${CXXFLAGS} -o obj/functions.o src/functions.cpp
