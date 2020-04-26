#include "Robot.hh"

ostream& Robot::print(ostream& out)const{
  out<<globalw[1];
  out<<globalw[2];
  out<<globalw[4];
  out<<globalw[5];
  out<<globalw[0];
  out<<globalw[1];
  out<<globalw[2];
  out<<globalw[3];
  out<<endl;
  out<<slad[0];
  for(size_t i=2;i<slad.IleWsp();i++){
    out<<slad[i-1];
    out<<slad[i];
  }
  out<<endl;

  return out;
  }

Wektor2D Robot::Promien(){
  return globalw[3]-globalw[0];
}


Robot::Robot(float x,float y){

  ObiektGraf::zwieksz();
  
  Wektor2D We;
  We[0]=x;We[1]=y;globalw.Ustaw(We); //wspolrzedne punktow
  We[0]=x+50;We[1]=y;globalw.Ustaw(We); //zostaja wrzucone
  We[0]=x+80;We[1]=y+50;globalw.Ustaw(We); //do dynamicznej
  We[0]=x+40;We[1]=y+50;globalw.Ustaw(We); //tablicy
  We[0]=x+50;We[1]=y+100;globalw.Ustaw(We);
  We[0]=x;We[1]=y+100;globalw.Ustaw(We);

  We[0]=-40;We[1]=-50;lokalw.Ustaw(We); //ustawione sa 
  We[0]=10;We[1]=-50;lokalw.Ustaw(We); //lokalne wsp
  We[0]=40;We[1]=0;lokalw.Ustaw(We);  //robota
  We[0]=0;We[1]=0;lokalw.Ustaw(We);
  We[0]=10;We[1]=50;lokalw.Ustaw(We);
  We[0]=-40;We[1]=50;lokalw.Ustaw(We);

  slad.Ustaw(globalw[3]);
}

bool Robot::Kolizja(ObiektGraf* OG){
  Wektor2D s1=globalw[3]; //srodek robota
  Wektor2D r1=globalw[3]-globalw[2]; //wektor promienia okregu robota 
  Wektor2D s2=OG->Srodek();
  Wektor2D r2=OG->Promien(); //wektor promienia robota
  Wektor2D odlw=s1-s2; //wektor laczacy srodki roboto
  float odl=odlw.Modul(); //odleglosc srodkow robota
  float r2d=r2.Modul(); //promien drugi
  float r1d=r1.Modul(); //promien pierwszy
  if(odl<(r2d+r1d)) return true;
  
  return false;
}

void Robot::Ruch(float ile){
  
  Kierunek=globalw[2]-globalw[3]; //wektor laczocy srodek z poczatkiem robota

  float x=Kierunek.Modul(); //dlugosc kierunku

  Kierunek[0]=(Kierunek[0]/x)*ile; //wyliczenie wersora z kierunku
  Kierunek[1]=(Kierunek[1]/x)*ile; //i wymnozenie go o ile sie chce 
                                   //zeby robot przeszedl
  for(size_t i=0;i<6;i++)
    globalw[i]=globalw[i]+Kierunek;

  slad.Ustaw(globalw[3]);
}

void Robot::Translacja(Wektor2D We){
  for(size_t i=0;i<globalw.IleWsp();i++)
    globalw[i]=globalw[i]+We;

  for(size_t i=0;i<slad.IleWsp();i++)
    slad[i]=slad[i]+We;

}

void Robot::Rotacja(Macierz2x2 Ma,float alfa){
  Wektor2D T;
  Ma.wypelnij(alfa);
  for(size_t i=0;i<6;i++){
  T=globalw[i]-lokalw[i]; //wektor ktory wysyla na srodek
  lokalw[i]=Ma*lokalw[i]; //obrocenie lokalnych
  globalw[i]=T+lokalw[i]; //powrot do globalnych
  }
  
}

