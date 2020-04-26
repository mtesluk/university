#ifndef WEKTOR2D_HH
#define WEKTOR2D_HH

/*!
 * \file
 * \brief Definicja klasy Wektor
 *
 * Plik zawiera definicje klasy Wektor2D
 * ktora jest podstawa kazdej nastepnej klasy
 */

#include <iostream>
#include <cmath>

using namespace std;

/*!
 * \brief Klasa Wektor2D
 *
 * Klasa jest podstawa "jednosta" kazdej
 * nastepenj klasy, za jej pomoca tworzone 
 * sa punkty w ukladzie kartezjanskim
 */
class Wektor2D {
  
/*!
 * \brief Wspolrzedna punktu/wektora
 *
 * x to pierwsza wspolrzedna punktu
 * jest prywatna
 */
  float x;

  /*!
 * \brief Wsspolrzedna wektora/punktu
 *
 * y to druga wspolrzedna punktu
 * jest prywatna
 */
  float y;

/*!
 * \brief Ilosc wektorow
 *
 * Zlicza ile lacznie zostalo
 * stworzonych obiektow Wektor2D
 */
  static int ileobiektow;  
  
public:

/*!
 * \brief Getter
 *
 * Zwraca ilosc utworzoncyh
 * obiektow
 */
  static int ile(){return ileobiektow;}

  
/*!
 *\brief Konstruktor wektora
 *
 * Konstruktor daje poczatkowe 
 * wartosci wektora
 */
  Wektor2D(float x1=0,float y1=0){x=x1;y=y1;ileobiektow++;};
  
  /*!
 * \brief Modul
 *
 * Liczy modul z wektora
 * sqrt(x^2+y^2)
 */
  float Modul();
  
  /*!
 * \brief Metoda indeksujaca
 *
 * Metoda indeksujaca sluzy do 
 * wyswietlania i wczytywania wspolrzednych
 */
  float operator[](int i)const{return i==0 ? x:y ;};

  /*!
 * \brief Metoda indeksujaca
 *
 * Metoda ideksujaca sluzy do wyswietlania
 * i wczytywania wspolrzednych
 */
  float& operator[](int i) {return i==0 ? x:y ;};
  };

/*!
 * \brief Przeciazenie + 
 *
 * Funkcja sluzy do dodawania wektorow
 * Wektor+Wektor=Wektor
 */
Wektor2D operator+(Wektor2D W1,Wektor2D W2);

/*!
 * \brief Przeciazenie - 
 *
 * Funkcja do odejmowania wektorow
 * Wektor-Wektor=Wektor
 */
Wektor2D operator-(Wektor2D W1,Wektor2D W2);

/*!
 * \brief Przeciazenie wczytywania
 *
 * Przeciazenie to wczytuje do strumienia
 * Wektor, pozwala to np na cin>>Wektor
 */
istream& operator >> (istream &in, Wektor2D &Wek);

/*!
 * \brief Przeciazenie wyswietlania
 *
 * Przeciazenie to wyrzuca na pulpit 
 * dane Wektora, np cout<<Wektor; 
 */
ostream& operator << (ostream &out, Wektor2D Wek);

#endif
