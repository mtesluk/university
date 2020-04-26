#
#  To sa opcje dla kompilacji
#
CXXFLAGS=-g -Iinc -Wall -pedantic -std=c++0x

all: clean obj obj/main.o
	g++ -Wall -pedantic -o sort obj/main.o

obj:
	mkdir obj/

obj/main.o: src/main.cpp 
	g++ -c ${CXXFLAGS} -o obj/main.o src/main.cpp

clean:	
	rm obj/* -f
	rm src/*~ -f
	rm inc/*~ -f
