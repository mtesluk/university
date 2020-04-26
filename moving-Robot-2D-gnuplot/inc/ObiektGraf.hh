#ifndef OBIEKTGRAF_HH
#define OBIEKTGRAF_HH

/*! 
 *\file
 *\brief Definicja obiektu graficznego
 *
 * Plik zawiera definicje obiektu graficzne,
 * ktory jest dziedziczony pozniej do robota,
 * sciezki i przeszkod 
 */

#include "ZbiorWierzcholkow.hh"
#include "Wektor2D.hh"
#include "Macierz2x2.hh"

/*! 
 *\brief Klasa Obiekt Graficzny
 *
 * Klasa zostala stworzona ze ZbioruWierzcholkow
 * posiada globalne wektory
 */
class ObiektGraf{

  
  /*! 
 *\brief Zmienna statyczna
 *
 * Zmienna statyczna zapamietujaca 
 * ilosc stworzonych obiektow 
 * ktore dziedzicza po obiekciegraf
 */
  static int ile;

protected:
  
  /*! 
 *\brief Zmienna globalna
 *
 * Zmienna globalna wektorowa w tablicy 
 * dynamicznej, wykorzystana do wyswietlenia 
 * polozenia kazdegoo nastepnego obiektu w 
 * ukladzie wspolrzednych
 */
  ZbW globalw;
  
public:
   
  /*!
   *\brief Ile obiektow
   *
   * Zwraca ilosc stworzzonych
   * obiektow
   */
  static int ileobiektow(){return ile;}

    /*!
   *\brief Zwieksza
   *
   * Inkrementuje ilosc
   * stworzonych obiektow
   */
  static void zwieksz(){ile++;}

    /*!
   *\brief Metoda wyswietlajaca
   *
   * Metoda ta sprawia ze mozliwe 
   * jest wyswietlenie obiektu
   */
  virtual ostream& print(ostream& out)const{return out;};

    /*!
   *\brief Translacja 
   *
   * Translacja dla kazdego
   * obiektu pochodnego
   */
  virtual void Translacja(Wektor2D We){;};

    /*!
   *\brief Poruszanie 
   *
   * Poruszanie dla 
   * robota
   */
  virtual void Ruch(int ile){};

  /*!
   *\brief Rotacja
   *
   * Rotacja dla robota
   */
  virtual void Rotacja(Macierz2x2 Ma,int ile){;};

    /*!
   *\brief Srodek robota
   *
   * Zwraca srodek 
   * robota
   */
  virtual Wektor2D Srodek(){return 0;};

    /*!
   *\brief Promien
   *
   * Zwraca promien okregu
   * opisanego na robocie
   */
  virtual Wektor2D Promien(){return 0;};

    /*!
   *\brief Kolizja 
   *
   * Sprawdza czy zawsze kolizja
   * w obiektach pochodnych
   */
  virtual bool Kolizja(ObiektGraf* OG){return false;};
  };

  /*!
   *\brief Przeciazenie wyswietlenia
   *
   * Sluzy do wyswietlenia obiektu 
   * oraz kazdej jej pochodnej
   */
ostream& operator<<(ostream& out,const ObiektGraf& ob);


#endif
