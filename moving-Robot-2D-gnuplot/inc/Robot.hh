#ifndef ROBOT_HH
#define ROBOT_HH

/*!
 *\file 
 *\brief Definicja klasy Robot
 *
 * Plik zawiera definicje klasy Robot,
 * ktory moze byc poruszany i obracany
 * w ukladzie wspolrzednych
 */

#include "Przeszkoda.hh"
#include "ZbiorWierzcholkow.hh"
#include "Wektor2D.hh"
#include "Macierz2x2.hh"
#include "ObiektGraf.hh"

/*! 
 *\brief Klasa Robot
 *
 * Robot jest obiektem dziedziczonym z ObiektuGraficzneg
 * Moze sie poruszac i obracac w ukladzie wspolrzednych
 * Jego celem jest symalacja prawdziwego robota na ekranie
 */
class Robot:public ObiektGraf{
  
  /*! 
 *\brief Zmienna lokalna
 *
 * Zmienna sluzy do obrotu robota wzgledem
 * srodka ukladu wspolrzednych zeby potem
 * moc obrocic go normalnie
 */
  ZbW lokalw;

  /*!
   *\brief Slad
   *
   * Zmienna sluzy do zapamietywania 
   * srodkow robota i tworzenia sladu
   */
  ZbW slad;

     /*! 
 *\brief Wektor Kierunek
 *
 * Wektor ten pokazuje w jaka
 * strone obrocony jest robot
 * Ulatwia to potem orientacje 
 * i umozliwia ruch na wprost
 */
  Wektor2D Kierunek;
public:

   /*! 
 *\brief Zmienna kolizyjna
 *
 * Zmienna statyczna zlicza ile 
 * razy robot uderzyl w jakas przeszkoda
 */
  static int ilekolizji;

   /*! 
 *\brief Konstruktor Robota
 *
 * Kostruktor ustawia na poczatku wspolrzedne
 * lokalne i globalne 
 */
  Robot(float x,float y);

  
    /*! 
 *\brief Przecizenie globalnych wsp
 *
 * Umozliwia wyswietlenie wspolrzednych 
 * globalnych robota
 */
  Wektor2D operator[](int i)const{return globalw[i];};

   /*! 
 *\brief Przeciazenie globalnych wsp
 *
 * Umozliwia przypisanie globalnym wsp
 * konkretnych wartosci
 */
  Wektor2D& operator[](int i){return globalw[i];};

   /*! 
 *\brief Rotacja Robota
 *
 * Rotacja sprawia ze robot moze zostac
 * obrocony o jakikolwiek kat 
 * wzgledem poczatku ukladu wsp
 */
  virtual void Rotacja(Macierz2x2 Ma,float alfa);

   /*! 
 *\brief Poruszanie Robota
 *
 * Ruch umozliwia poruszanie sie robota
 * w lini w ktora jest on skierowany
 */
  virtual void Ruch(float ile); //klasa robot

   /*! 
 *\brief Translacja Robota
 *
 * Translacja Robota przerzuca go w konkretne 
 * miejsce o zadany wektor
 */
  virtual void Translacja(Wektor2D We);

   /*! 
 *\brief Kolizja Robota
 *
 * Metoda ta sprawdza czy Robot uderzyl  
 * w przeszkode lub innego robota czy nie
 */
  virtual bool Kolizja(ObiektGraf* OG);
  
  /*!
   *\brief Promien
   *
   * Zwraca promien okregu
   * opsanego na roobcie
   */
  virtual Wektor2D Promien();

  /*!
   *\brief Srodek
   *
   * Zwraca wspolrzende
   * srodka robota
   */
  virtual Wektor2D Srodek(){return globalw[3];}

  /*!
   *\brief Metoda wys
   *
   * Wyswietla wspolrzedne 
   * robota 
   */
  virtual ostream& print(ostream& out)const;
    };

#endif
