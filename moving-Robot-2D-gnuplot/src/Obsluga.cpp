#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include "Wektor2D.hh"
#include "Macierz2x2.hh"
#include "Przeszkoda.hh"
#include "lacze_do_gnuplota.hh"
#include "Robot.hh"
#include "ZbiorWierzcholkow.hh"
#include "ObiektGraf.hh"
#include "Obsluga.hh"
#include <unistd.h>

using namespace std;

Fabryka Fabryka::_Fabryka;

void Obsluga(Scena Sc){
PzG::LaczeDoGNUPlota  Lacze;
float ob,odl;
Wektor2D We,pom;
Macierz2x2 Ma;
char wyb;
int predkosc=20;
 int rob;
 int x=0,y=0,prze=0;
  
  Lacze.UstawZakresX(-1000,1000); //ustawia zasieg osi
  Lacze.UstawZakresY(-1000,1000);
  Lacze.DodajNazwePliku("wspolrzedne.dat",PzG::RR_Ciagly,2);
  Lacze.ZmienTrybRys(PzG::TR_2D);
  Sc.PrzykladZapisuWspolrzednychDoPliku("wspolrzedne.dat");
  Lacze.Rysuj();
system("clear");
 
  while(wyb!='k'){
    showmenu();
    Sc.AktualnyRobot();
    cout<<"------------------------------------------"<<endl;
    cout<<"Opcja:";cin>>wyb;
    if(cin.fail()) cerr<<"Zly znak"<<endl;
  switch(wyb){
  case 't':{
    cout<<"O jaki wektor przeniesc scene: ";cin>>We;
    Sc.Translacja(We);
    Sc.PrzykladZapisuWspolrzednychDoPliku("wspolrzedne.dat");
    Lacze.Rysuj();
    system("clear");}break; 
      
  case 's':{
    cout<<"Podaj predkosc(im mniejsza tym szybciej;domyslna "<<predkosc<<"): "; cin>>predkosc;
    system("clear");}break;

    case 'r':{
    cout<<"Podaj wspolrzedna x i y skad ma startowac robot:";
    cin>>x>>y;
    Sc.ZbudujRobota(OG_Robot,x,y,0);
    Sc.PrzykladZapisuWspolrzednychDoPliku("wspolrzedne.dat");
    Lacze.Rysuj();
    system("clear");}break;

  case 'p':{
    cout<<"Podaj wspolrzedna x i y skad ma startowac robot oraz szerokosc przeszkoday:";
    cin>>x>>y>>prze;
    Sc.ZbudujRobota(OG_Przeszkoda,x,y,prze);
    Sc.PrzykladZapisuWspolrzednychDoPliku("wspolrzedne.dat");
    Lacze.Rysuj();
    system("clear");}break;

      
  case 'o':{
    cout<<"O ile stopni chcesz obrocic robota: ";cin>>ob;
    for(int i=0;i<10;i++){
    Sc.ObrotRobota(Ma,ob/10);
    Sc.PrzykladZapisuWspolrzednychDoPliku("wspolrzedne.dat");
    Lacze.Rysuj();
    usleep(100000);}
    system("clear");}break;

  case 'w':{  
    cout<<"Ile ma przejsc: ";cin>>odl;
    for(int i=0;i<predkosc;i++){
    Sc.RuchRobota(odl/predkosc);
    Sc.PrzykladZapisuWspolrzednychDoPliku("wspolrzedne.dat");
    Lacze.Rysuj();
    usleep(100000);
    if(Sc.KolizjaRobota()==true) {Robot::ilekolizji++;Sc.RuchRobota(-20);break;}
    }
    system("clear");}break;

  case 'z':{
    Sc.WyswietlWspRobotow();
    cout<<"Ktorego robota wybierasz: ";cin>>rob;
    Sc.WyborRobota(rob);
    system("clear");
  }break;
    
  case 'k':{
    break;}break;
  };//koniec switch
  }//koniec while
  system("clear");
  cout<<"------------------------------"<<endl;
  cout<<"Ilosc stworzonych obiektow:"<<ObiektGraf::ileobiektow()<<" |"<<endl;
  cout<<"------------------------------"<<endl;
}

void showmenu(){
  system("clear");
  cout<<"Lączna ilosc Wektor2D: "<<Wektor2D::ile()<<endl;
  cout<<"-------------------------"<<endl;
  cout<<"r - dodaj robota        |"<<endl;
  cout<<"p - dodaj przeszkode    |"<<endl;
  cout<<"-------------------------"<<endl;
  cout<<"o - obrot               |"<<endl;
  cout<<"w - idz do przodu       |"<<endl;
  cout<<"s - zmien predkosc      |"<<endl;
  cout<<"-------------------------"<<endl;
  cout<<"z - zmien robota        |"<<endl;
  cout<<"-------------------------"<<endl;
  cout<<"t - przenies cala scene |"<<endl;
  cout<<"-------------------------"<<endl;
  cout<<"k - koniec              |"<<endl;
  cout<<"-------------------------"<<endl;
  cout<<"Ilosc kolizji: "<<Robot::ilekolizji<<"        |"<<endl;
  cout<<"------------------------------------------"<<endl;
}

