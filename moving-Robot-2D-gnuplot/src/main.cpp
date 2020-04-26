#include <iostream>
#include "Obsluga.hh"
#include "Scena.hh"
#include "Robot.hh"
#include "Wektor2D.hh"
#include "Macierz2x2.hh"

int Robot::ilekolizji=0;
int ObiektGraf::ile=0;
int Wektor2D::ileobiektow=0;

int main()
{
  
  Scena Sc;
  Obsluga(Sc);
  
}//koniec main

