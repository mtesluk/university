#include "functions.hh"

void show_menu()
{
  cout << "a - add to tree\n";
  cout << "m - add many to tree\n";
  cout << "r - remove from tree\n";
  cout << "s - show root of tree\n";
  cout << "d - show all numbers of tree (pre-order)\n";
  cout << "i - show all numbers of tree (in-order)\n";
  cout << "p - show all numbers of tree (post-order)\n";
  cout << "q - exit\n";
}

void insert_random(AVLTree<int> &avl,int amount_keys,int min_value,int max_value)
{
  int random_num = 0;
  for(int i=1;i<=amount_keys;i++)
    {
      random_num = rand() % (max_value - min_value) + min_value;
      avl.insert(random_num);
    }
}