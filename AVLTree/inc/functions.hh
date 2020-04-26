#include <iostream>
#include "tree.hh"

/*
    show available option for user
 */
void show_menu();

/*
 	allow to insert many random numbers to tree
 */
void insert_random(AVLTree<int> &avl,int amount_keys,int min_value,int max_value);