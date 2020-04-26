#ifndef FIGURE_HH
#define FIGURE_HH

#include "spot.hh"

/*
  Class responsible for containg coordinates 
  and symbol of figure 
  Pawn inheritance for it
*/
class Figure
{
  //information if it is white or black figure
  char sym;

  //coordinates of figure
  Spot s;
public:
  Figure() {;};
  ~Figure() {;};

  //getters and setters
  char get_sym() {return sym;};
  void set_sym(char s) {sym = s;};
  int get_x() {return s.get_x();};
  void set_x(int xx) {s.set_x(xx);};
  int get_y() {return s.get_y();};
  void set_y(int yy) {s.set_y(yy);};
  Spot get_pos() {return s;};
  void set_pos(int xx,int yy) {s.set_y(yy); s.set_x(xx);};
};

#endif
