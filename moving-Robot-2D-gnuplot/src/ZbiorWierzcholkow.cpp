#include "ZbiorWierzcholkow.hh"

ostream& operator<<(ostream &out,ZbW Z){
  for(size_t j=0;j<Z.IleWsp();j++)
    out<<Z[j];
      return out;
      }
