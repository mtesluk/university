#include "Macierz2x2.hh"
#include <cmath>
#include <unistd.h>

void Macierz2x2::wypelnij(float alfa){

  Wiersz[0][0]=cos((alfa*M_PI)/180); //Pole 0,0
  Wiersz[0][1]=-sin((alfa*M_PI)/180); //Pole 0,1
  Wiersz[1][0]=sin((alfa*M_PI)/180); //Pole 1,0
  Wiersz[1][1]=cos((alfa*M_PI)/180); //Pole 1,1
}

Wektor2D Macierz2x2::operator*(Wektor2D We){
  Wektor2D tmp;
  tmp[0]=Wiersz[0][0]*We[0]+Wiersz[0][1]*We[1];
  tmp[1]=Wiersz[1][0]*We[0]+Wiersz[1][1]*We[1];
    return tmp;
  }
