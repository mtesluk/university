#include <iostream>
#include "service.hh"

int main()
{
	char choice = ' ';

	//loop for choosing right option
	while(choice != 'q')
	{
		//clear terminal
		system("clear");

		show_menu();

		//ask for our choice which version we want to play
		cout << "Your choice: ";
		cin >> choice;
		
		switch(choice)
		{
			case 'w':
			{
				choice = play_1_vs_1();
			}break;

			case 'c':
			{
				choice = play_vs_comp();
			}break;
		}
	}

	return 0;
}



