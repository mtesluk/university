#ifndef PRZESZKODA_HH
#define PRZESZKODA_HH

#include <iomanip>
#include <iostream>
#include "Wektor2D.hh"
#include "ObiektGraf.hh"



using namespace std;

//klasa dla prostokata, stworzona z wektorow
class Przeszkoda:public ObiektGraf {
public:

  /*!
   *\brief Kontruktor
   *
   * Kontruktor umozlia nadanie 
   * na samym poczatku stowrzenia 
   * przeszkody wspolrzednych
   */
  Przeszkoda(float x,float y,float prze);

  /*!
   *\brief Translacja
   *
   * Sprawia ze obiekt mozna 
   * przesunac gdzie tylko sie chce
   * o zadany wektor
   */
  virtual void Translacja(Wektor2D We);

  /*!
   *\brief Przeciazenie 
   *
   * Umozliwia uzycie danej
   * wspolrzencyh
   */
  Wektor2D operator[](int i)const{return globalw[i];};

  /*!
   *\brief Przeciazenie
   *
   * Umozliwia nadanie danych
   * konkretnych wpolrzednym
   */
  Wektor2D& operator[](int i){return globalw[i];};

  /*!
   *\brief Wyswietla dane
   *
   * Wyswietla wszykie wspolrzende
   * prostokata
   */
  virtual ostream& print(ostream &out)const;

  /*!
   *\brief KOlzija
   *
   * Sprawdza czy zaszla kolizja 
   * miedzy robotem a prostokatem
   */
  virtual bool Kolizja(ObiektGraf* OG);
};

#endif
