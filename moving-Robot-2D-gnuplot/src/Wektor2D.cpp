#include "Wektor2D.hh"
#include <math.h>
#include <iomanip>

float Wektor2D::Modul(){
  return sqrt(x*x+y*y);
}

Wektor2D operator+(Wektor2D W1,Wektor2D W2){
  Wektor2D W3;
  W3[0]=W1[0]+W2[0];
  W3[1]=W1[1]+W2[1];
  return W3;
}

Wektor2D operator-(Wektor2D W1,Wektor2D W2){
  Wektor2D W3;
  W3[0]=W1[0]-W2[0];
  W3[1]=W1[1]-W2[1];
  return W3;
}

istream& operator >> (istream &in, Wektor2D &Wek){
  in>>Wek[0];
  if(in.fail()) {cerr<<"Blad wczytania wektora"<<endl; return in;};
  in>>Wek[1];
  if(in.fail()) {cerr<<"Blad wczytania wektora"<<endl; return in;};
  return in;
  }

ostream& operator << (ostream &out,Wektor2D Wek){
  out<<fixed<<setprecision(10)<<Wek[0]<<" "<<fixed<<setprecision(10)<<Wek[1]<<endl;
  return out;
  }
