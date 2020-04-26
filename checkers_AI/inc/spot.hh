#ifndef SPOT_HH
#define SPOT_HH

#include <iostream>

using namespace std;

/*
  Class which just contain coordinates
*/
class Spot
{
  int x;
  int y;
public:
  Spot() {;};

  //getters and setters
  int get_x() {return x;};
  int get_y() {return y;};
  void set_x(int xx) {x=xx;};
  void set_y(int yy) {y=yy;};
  void set_pos(int xx,int yy) {x=xx;y=yy;};
};

//Struct to have information about two coordinates
struct Info
{
  Spot mv_from;
  Spot mv_to;
};

#endif

 
