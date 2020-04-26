#include "Przeszkoda.hh"
#include <iomanip>

Przeszkoda::Przeszkoda(float x,float y,float prze){

  ObiektGraf::zwieksz();
  
  Wektor2D We;
  We[0]=x;We[1]=y;globalw.Ustaw(We);
  We[0]=x+prze;We[1]=y;globalw.Ustaw(We);
  We[0]=x+prze;We[1]=y+prze;globalw.Ustaw(We);
  We[0]=x;We[1]=y+prze;globalw.Ustaw(We);
}

ostream& Przeszkoda::print(ostream& out)const{
  out<< setw(16) << fixed << setprecision(10) << globalw[0]; 
  out<< setw(16) << fixed << setprecision(10) << globalw[1];
  out<< setw(16) << fixed << setprecision(10) << globalw[2];
  out<< setw(16) << fixed << setprecision(10) << globalw[3];
  out<< setw(16) << fixed << setprecision(10) << globalw[0];
  out<<endl;
  return out;
}

bool Przeszkoda::Kolizja(ObiektGraf* OG){
  Wektor2D s=OG->Srodek(); //srodek robota
  Wektor2D r=OG->Promien(); //promien robota
  float dl=r.Modul(); //dlugosc promienia
  if((s[0]>globalw[0][0]-dl) && (s[0]<globalw[1][0]+dl) &&
     (s[1]>globalw[0][1]-dl) && (s[1]<globalw[2][1]+dl)) return true;
  return false;
}

void Przeszkoda::Translacja(Wektor2D We){
  for(size_t i=0;i<globalw.IleWsp();i++)
  globalw[i]=globalw[i]+We;
  }
