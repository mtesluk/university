#include "Scena.hh"

void Scena::WyborRobota(int i){
  typ=i;
}

Scena::Scena(){
  typ=1;
  
  obiekt.push_back(Fabryka::Zbuduj(OG_Przeszkoda,-900,-900,400));
  
}

void Scena::WyswietlWspRobotow(){
  for(size_t j=0;j<roboty.size();j++){
    cout<<j+1<<". "<<roboty[j]->Srodek();}
  
  
}

void Scena::AktualnyRobot(){
  if(!roboty.empty()){
    cout<<"Aktualny robot:                          |"<<endl;
    cout<<"Wspolrzedne: "<<roboty[typ-1]->Srodek();}
}

void Scena::ZbudujRobota(TypObiektu TypOb,float a,float b,float p){
  if(TypOb==OG_Robot) {
    PTR WRO=Fabryka::Zbuduj(OG_Robot,a,b,p);
    obiekt.push_back(WRO);
    roboty.push_back(static_pointer_cast<Robot>(WRO));}
  else if(TypOb==OG_Przeszkoda)
    obiekt.push_back(Fabryka::Zbuduj(OG_Przeszkoda,a,b,p));
}

void Scena::Translacja(Wektor2D We){

  for(list<PTR>::iterator iter=obiekt.begin();iter!=obiekt.end();iter++)
    (*iter)->Translacja(We);
}

void Scena::ObrotRobota(Macierz2x2 Ma,float alfa){
  roboty[typ-1]->Rotacja(Ma,alfa);
}

void Scena::RuchRobota(float ile){
  roboty[typ-1]->Ruch(ile);
}

bool Scena::KolizjaRobota(){
  for(list<PTR>::iterator iter=obiekt.begin();iter!=obiekt.end();iter++){
    if(iter->get()!=&(*roboty[typ-1]))
    if((*iter)->Kolizja(&(*roboty[typ-1]))==true)
      return true;}
  return false;
}
  
bool Scena::PrzykladZapisuWspolrzednychDoPliku( const char  *sNazwaPliku)
{
  ofstream  out;

  out.open(sNazwaPliku);
  if (!out.is_open())  {
    cerr << ":(  Operacja otwarcia do zapisu \"" << sNazwaPliku << "\"" << endl
	 << ":(  nie powiodla sie." << endl;
    return false;
  }

  for(list<PTR>::iterator iter=obiekt.begin();iter!=obiekt.end();iter++)
  out<<*(*iter);
   
  out.close();
  return !out.fail();
}
