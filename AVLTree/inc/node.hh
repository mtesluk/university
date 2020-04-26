#include <iostream>

/*
  Class which is node for AVLTree
  Contains information about height, number,
  and pointers to the right, left and parent node
*/
template <typename T>
class AVLNode
{
  //int as information about balance
  int hf;

  //number inform us about position in the tree
  T num;

  //pointer to bigger node
  AVLNode<T> *right;

  //pointer to lower node
  AVLNode<T> *left;

  //pointer to parent's node
  AVLNode<T> *up;
  
public:

  //constructor
  AVLNode() {right=NULL;left=NULL;hf=0;};
  ~AVLNode(){delete right;delete left;};
  
  //getters and setters
  T getNum() const {return num;}
  void setNum(T number) {num = number;}
  int getHf() const {return hf;}
  void setHf(int hf1) {hf = hf1;}
  AVLNode<T>* getRight() const {return right;}
  void setRight(AVLNode<T> *ptr) {right = ptr;}
  AVLNode<T>* getLeft() const {return left;}
  void setLeft(AVLNode<T> *ptr) {left = ptr;}
  AVLNode<T>* getUp() const {return up;}
  void setUp(AVLNode<T> *ptr) {up = ptr;}
};

