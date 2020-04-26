#ifndef MACIERZ2X2_HH
#define MACIERZ2X2_HH

/*!
 * \file  
 * \brief Definicja klasy Macierz2x2
 *
 * Plik zawiera definicje klasy Macierz,
 * sluzy do obrotow wokol srodka ukladu wspolrzednych
 */

#include <iostream>
#include <cmath>
#include "Wektor2D.hh"

using namespace std;

/*!
 * \brief Klasa Macierz2x2
 *
 * Klasa zawiera dwa wektory ktore reprezentuja 
 * w niej dwa wiersze, czyli razem 4 pola.
 * Dzieki niej mozliwe sa obroty punktow 
 * wzgledem srodka ukladu wspolrzednych
 */
class Macierz2x2 {

  /*!
 * \brief Dwa wektory
 *
 * Dwa wektory reprezentujace dwa wiersze
 * razem daje to 4 pola
 */
  Wektor2D Wiersz[2];
public:

  /*!
 * \brief Metoda wypelnij
 *
 * Umozliwia wypelnienie pol macierzy
 * konkretnymi liczbami wzgledem dobranego
 * kata ktore wrzucamy do funkcji
 */
  void wypelnij(float alfa);

  /*!
 * \brief Przeciazenie *
 *
 * Przeciazenie mnozenia Wektora i Macierzy
 * wynikiem tego jest wektor
 */
  Wektor2D  operator*( Wektor2D We);

  /*!
 * \brief Metoda indeksujaca
 *
 * Metoda ma na celu wyswietlenie wierszy 
 * macierzy
 */
  const Wektor2D& operator()(int W) const {return Wiersz[W];};

  /*!
 * \brief Metoda indeksujaca
 *
 * Metoda ma na celu wczytanie wiersza 
 * maceirzy czyli wektora
 */
  Wektor2D&  operator()(int W) {return Wiersz[W];}; 
};

 /*!
 *\brief Przeciazenie wyswietlenia
 *
 * Funkcja umozliwiajaca wyswietlenie
 * calej Macierzy
 */
ostream& operator << (ostream &Strm,  Macierz2x2 &Mac);

#endif
