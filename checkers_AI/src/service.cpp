#include "service.hh"


char play_1_vs_1()
{

	//innit all important veriables
	Board board;	
	Ind i = A;
	char tmp1 = 'y';
	int tmp2;
	Spot mv_from;
	Spot mv_to;

	
	while(true)
	{

		//check if game is finished
		if(board.finished() == true) break;
		
		//loop for checking if move of player is correct
		//if is not than loop start again
		while(true)
		{
			//clear terminal and print board on terminal
			system("clear");
			board.show_board();
			
			cout << "Player 1 move from (for example: A 1): ";
			cin >> tmp1 >> tmp2 ;
			
			if(tmp1 == 'q') break;
			
			i = convert(tmp1);
			mv_from.set_x(i);
			mv_from.set_y(tmp2 - 1);
			
			cout << "Player 1 move to (for example: B 2): " ;
			cin >> tmp1 >> tmp2 ;

			if(tmp1 == 'q') break;
			
			i = convert(tmp1);
			mv_to.set_x(i);
			mv_to.set_y(tmp2 - 1);
			
			//send our moves to board
			if(board.move("white",false,mv_from,mv_to) == true) break;
		}

		//check if game is finished
		if(board.finished() == true) break;
		
		//loop for checking if move of player is correct
		//if is not than loop start again
		while(true)
		{
			//clear terminal and print board on terminal
			system("clear");
			board.show_board();
			
			cout << "Player 2 move from (for example: A 1): ";
			cin >> tmp1 >> tmp2 ;
			
			if(tmp1 == 'q') break;
			
			i = convert(tmp1);
			mv_from.set_x(i);
			mv_from.set_y(tmp2 - 1);
			cout << "Player 2 move to (for example: B 2): " ;
			cin >> tmp1 >> tmp2 ;

			if(tmp1 == 'q') break;
			
			i = convert(tmp1);
			mv_to.set_x(i);
			mv_to.set_y(tmp2 - 1);

			//send our moves to board
			if(board.move("black",false,mv_from,mv_to) == true) break;
		}
		
		
	}
	return 'q';
}

char play_vs_comp()
{

	Board board;	
	Ind i = A;
	char tmp1 = 'y';
	int tmp2;
	Spot mv_from;
	Spot mv_to;

	
	while(true)
	{

		//check if game is finished
		if(board.finished() == true) break;
		
		//loop for checking if move of player is correct
		//if is not than loop start again
		while(true)
		{
			//clear terminal and print board on terminal
			system("clear");
			board.show_board();
			
			cout << "Player 1 move from (for example: A 1): ";
			cin >> tmp1 >> tmp2 ;
			
			if(tmp1 == 'q') break;
			
			i = convert(tmp1);
			mv_from.set_x(i);
			mv_from.set_y(tmp2 - 1);
			
			cout << "Player 1 move to (for example: B 2): " ;
			cin >> tmp1 >> tmp2 ;

			if(tmp1 == 'q') break;
			
			i = convert(tmp1);
			mv_to.set_x(i);
			mv_to.set_y(tmp2 - 1);
			
			//give sleep to make game more fluent
			usleep(200000);

			//send our moves to board
			if(board.move("white",false,mv_from,mv_to) == true) break;
		}

		//check if game is finished
		if(board.finished() == true) break;
		
		//clear terminal and print board on terminal
		system("clear");
		board.show_board();

		//give sleep to make game more fluent
		usleep(200000);

		//make computer move
		board.comp_move();
		
		
	}
	return 'q';
}


void show_menu()
{
	cout << "q - quit" << endl;
	cout << "w - player vs player" << endl;
	cout << "c - player vs computer" << endl;
	cout << "Choose option: " << endl;
}