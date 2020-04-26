#ifndef FABRYKA_HH
#define FABRYKA_HH

#include "Robot.hh"
#include "ObiektGraf.hh"
#include "Przeszkoda.hh"
#include <iostream>
#include <memory>

enum TypObiektu {OB_Robot, OB_Przeszkoda };

class Fabryka{
  static Fabryka   _Fabryka;
  
public:
static shared_ptr<ObiektGraf> Zbuduj( TypObiektu  TypOb,float a,float b,float p)
{return _Fabryka.UtworzObiekt(TypOb,a,b,p);}  

private:
  shared_ptr<ObiektGraf> UtworzObiekt( TypObiektu  TypOb,float a,float b,float p)const {
      switch (TypOb) {
      case OB_Robot: return make_shared<Robot>(a,b);
      case OB_Przeszkoda: return make_shared<Przeszkoda>(a,b,p);
      }
      return make_shared<Przeszkoda>(a,b,p);
    }

  }

#endif
