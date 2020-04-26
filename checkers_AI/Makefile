#
#  To sa opcje dla kompilacji
#
CXXFLAGS=-g -Iinc -Wall -pedantic -std=c++0x

all: clean obj obj/main.o obj/board.o obj/node.o obj/service.o
	g++ -Wall -pedantic -o game obj/main.o obj/board.o obj/node.o obj/service.o

obj:
	mkdir obj/

obj/main.o: src/main.cpp 
	g++ -c ${CXXFLAGS} -o obj/main.o src/main.cpp

obj/board.o: src/board.cpp 
	g++ -c ${CXXFLAGS} -o obj/board.o src/board.cpp

obj/node.o: src/node.cpp 
	g++ -c ${CXXFLAGS} -o obj/node.o src/node.cpp

obj/service.o: src/service.cpp 
	g++ -c ${CXXFLAGS} -o obj/service.o src/service.cpp

clean:	
	rm obj/* -f
	rm src/*~ -f
	rm inc/*~ -f
