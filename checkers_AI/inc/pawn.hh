#ifndef PAWN_HH
#define PAWN_HH

#include "figure.hh"

class Pawn: public Figure
{
public:
  Pawn(char s) {set_sym(s);};
};

#endif
