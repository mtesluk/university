#ifndef ZBIORWIERZCHOLKOW_HH
#define ZBIORWIERZCHOLKOW_HH

/*!
 * \file
 * \brief Definicja klasy ZbiorWierzcholkow 
 *
 * Plik zawiera definicje klasy ZbiorWierzcholkow
 * ktora stanowi podstawe nastepnych klas
 */

#include "Wektor2D.hh"
#include <vector>

/*!
 * \brief Klasa ZbiorWierzcholkow 
 *
 * Klasa zawiera dynamiczna strukture wektorow
 * umozliwia to lepsza kontrole nad pamiecia.
 * Dzieki temu nie trzeba na samym poczatku 
 * stwierdzac ile danych zainicjowac
 */
class ZbW{

  /*!
 * \brief Szablon vector 
 *
 * Szablon te umozliwia tworzenie dynamicznej
 * tablicy Wektorow. Mozemy dodawac na jej stos
 * tyle ile chcemy 
 */
  vector <Wektor2D> wsp;
public:

  /*!
 * \brief Konstruktor  
 *
 * Konstruktor rezerwuje automatycznie
 * 30 slotow, ulatwia to potem 
 * przenoszenie pamieci
 */
  ZbW(){wsp.reserve(30);}

   /*!
 * \brief Metoda indekusjaca  
 *
 * Metoda ma za zadanie wyswietlanie
 *  konkretnego slotu w tablicy wektorow
 */
  Wektor2D operator[](size_t i)const{return wsp[i];};

   /*!
 * \brief Metoda indeksujaca  
 *
 * Metoda ma na celu wczytanie wektora
 * do konkretnego slota
 */
  Wektor2D& operator[](size_t i){return wsp[i];};

   /*!
 * \brief Ile Wspolrzednych  
 *
 * Zwraca ile wektorow zostalo juz 
 * utworzonych w tablicy
 */
  size_t IleWsp()const{return wsp.size();};

   /*!
 * \brief Ustaw wektor  
 *
 * Ustawia wektor na gorze stosu tablicy
 *  
 */
  void Ustaw(Wektor2D We){wsp.push_back(We);};
  
  
};

 /*!
 * \brief Przeciazenie wyswietlenia  
 *
 * Wyrzuca na ekran wektory w tablicy
 *  
 */
ostream& operator<<(ostream &out,ZbW Z);

#endif
