#include <iostream>
#include <cstdlib>
#include "tree.hh"
#include "functions.hh"

using namespace std;

int main()
{
  AVLTree<int> avl;
  char choice = '0';
  int number = 0;
  int amount_keys = 0;
  int min_value = 0;
  int max_value = 0;
  
  system("clear");
  while(choice != 'q')
    {
      cout << "\n-----------------------\n";
      show_menu();
      cout << "Your choice: ";
      cin >> choice;
      switch(choice)
		{
		case 'a':
		  {
		    system("clear");
		    cout << "Give number: ";
		    cin >> number;
		    avl.insert(number);
		  }
		  break;
	  
		case 'r':
		  {
		    system("clear");
		    cout << "Give number to remove: ";
		    cin >> number;
		    avl.remove_number(number);
		  }
		  break;
	  
		case 's':
		  {
		    system("clear");
		    avl.show_root();
		  }
		  break;
		  
		case 'm':
	      {
	      	system("clear");
	      	cout<< "Give amount of numbers: ";
	      	cin>>amount_keys;
	      	cout<< "Give range(min) of numbers: ";
	      	cin>>min_value;
	      	cout<< "Give range(max) of numbers: ";
	      	cin>>max_value;
	      	insert_random(avl,amount_keys,min_value,max_value);
		  }
		  break;

		case 'd':
		  {
		    system("clear");
		    avl.show_numbers_pre_order();
		  }
		  break;

		 case 'i':
		  {
		    system("clear");
		    avl.show_numbers_in_order();
		  }
		  break;

		  case 'p':
		  {
		    system("clear");
		    avl.show_numbers_post_order();
		  }
		  break;
		}//switch
	}//while
  
  return 0;
}

