#
#  To sa opcje dla kompilacji
#
CXXFLAGS=-g -Iinc -Wall -pedantic -std=c++0x


zadanie: obj obj/main.o obj/Przeszkoda.o obj/Macierz2x2.o obj/Wektor2D.o\
           obj/lacze_do_gnuplota.o  obj/Robot.o obj/ZbiorWierzcholkow.o obj/ObiektGraf.o obj/Obsluga.o obj/Scena.o
	g++ -Wall -pedantic -std=c++0x -o zadanie obj/main.o obj/Wektor2D.o\
                        obj/Macierz2x2.o obj/Przeszkoda.o obj/Robot.o obj/lacze_do_gnuplota.o obj/ZbiorWierzcholkow.o obj/ObiektGraf.o obj/Obsluga.o obj/Scena.o 

obj:
	mkdir obj

obj/Obsluga.o: src/Obsluga.cpp inc/Obsluga.hh 
	g++ -c ${CXXFLAGS} -o obj/Obsluga.o src/Obsluga.cpp

obj/lacze_do_gnuplota.o: inc/lacze_do_gnuplota.hh src/lacze_do_gnuplota.cpp
	g++ -c ${CXXFLAGS} -o obj/lacze_do_gnuplota.o src/lacze_do_gnuplota.cpp

obj/main.o: src/main.cpp inc/Przeszkoda.hh inc/Macierz2x2.hh inc/Wektor2D.hh inc/Robot.hh inc/Obsluga.hh inc/Scena.hh 
	g++ -c ${CXXFLAGS} -o obj/main.o src/main.cpp

obj/Przeszkoda.o: src/Przeszkoda.cpp inc/Przeszkoda.hh
	g++ -c ${CXXFLAGS} -o obj/Przeszkoda.o src/Przeszkoda.cpp

obj/ZbiorWierzcholkow.o: src/ZbiorWierzcholkow.cpp inc/ZbiorWierzcholkow.hh
	g++ -c ${CXXFLAGS} -o obj/ZbiorWierzcholkow.o src/ZbiorWierzcholkow.cpp

obj/ObiektGraf.o: src/ObiektGraf.cpp inc/ObiektGraf.hh
	g++ -c ${CXXFLAGS} -o obj/ObiektGraf.o src/ObiektGraf.cpp

obj/Scena.o: src/Scena.cpp inc/Scena.hh
	g++ -c ${CXXFLAGS} -o obj/Scena.o src/Scena.cpp

obj/Robot.o: src/Robot.cpp inc/Robot.hh
	g++ -c ${CXXFLAGS} -o obj/Robot.o src/Robot.cpp

obj/Macierz2x2.o: src/Macierz2x2.cpp inc/Macierz2x2.hh 
	g++ -c ${CXXFLAGS} -o obj/Macierz2x2.o src/Macierz2x2.cpp

obj/Wektor2D.o: src/Wektor2D.cpp inc/Wektor2D.hh
	g++ -c ${CXXFLAGS} -o obj/Wektor2D.o src/Wektor2D.cpp

clean:
	rm -f obj/*.o obroty_2D
	rm src/*.*~
	rm inc/*.*~
