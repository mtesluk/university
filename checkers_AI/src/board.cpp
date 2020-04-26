#include "board.hh"

/*
	Constructor of our board,
	init every field of board with correct coordinates,
	ane init every pawn on starting field
*/
Board::Board()
{
	//temporary variables
	int p = 0;
	int q = 0;

	//makes every row	  
	for(int i=0;i<ROWS;i++)
	{
		vector <char> tmp;
		fields.push_back(tmp);
	}

	//for every row makes 8 columns 
	for(int i=ROWS-1;i>=0;i--)
	{
		for(int j=0;j<COLUMNS;j++)
		{
			//fill in fields with '+' which means black fied on original board
			if(j%2 != 0 && i%2 != 0) fields[i].push_back('+');
			else if(j%2 == 0 && i%2 == 0) fields[i].push_back('+');
			else  
			{
				fields[i].push_back(' ');

			    //makes pawns in first 3 rows white
			    //and black in 3 last rows
			    // and next set indexes of every pawn
				if(i >= 5 && i <= 7)
				{
					white.push_back(Pawn('X'));
					white[p].set_x(j);
					white[p].set_y(7-i);
					p++;
				}
				else if(i >= 0 && i <= 2)
				{
					black.push_back(Pawn('O'));
					black[q].set_x(j);
					black[q].set_y(7-i);
					q++;
				}
			}
		}
	}
}

/*
	According to acctual positions and chars 
	show everything in terminal	
*/
void Board::show_board()
{

    //temporary variable
	int c = 8;

	//needed to print 
	char indexes [COLUMNS] = {'A','B','C','D','E','F','G','H'};

    //iter for every field
	for(int i=ROWS-1;i>=0;i--)
	{
		cout << "   " ;
		for(int j=0;j<COLUMNS;j++)
		{
			cout << "----";

		}
		cout << endl;
		cout << c ;
		c--;
		for(int j=0;j<COLUMNS;j++)
		{

	  		//update fields after some pawn changed his position
			if(j%2 != 0 && i%2 != 0) fields[i][j] = '+';
			else if(j%2 == 0 && i%2 == 0) fields[i][j] = '+';
			else fields[i][j] = ' ';

			//check in every pawn if this field dont have the same coordinates
			//if yes, then replace field with pawn symbol
			for(int p=0;p<int(white.size());p++)
			{
				if(i == white[p].get_y() && j == white[p].get_x())
				{
					fields[i][j] = white[p].get_sym();	   
				}
			}

	  		//the same what up but with black pawn
			for(int p=0;p<int(black.size());p++)
			{
				if(i == black[p].get_y() && j == black[p].get_x())
				{
					fields[i][j] = black[p].get_sym();	   
				}
			}
			cout << " | " << fields[i][j];
		}
		cout << " |" << endl;

	}
	cout << "   " ;
	for(int j=0;j<COLUMNS;j++)
	{
		cout << "----"; 
	}
	cout << endl;
	cout << " ";

    //show symbols of columns
	for(int j=0;j<COLUMNS;j++)
	{
		cout << "   " << indexes[j];	  
	}
	cout << endl;


}

int max_depth = 3;

/*
	Main method operates computer moves,
	first make tree and next with minmax algorithm
	make appropraite moves
*/
void Board::comp_move()
{
	//define tree
	DecisionTree tree;

	//init temporary values
	int ab=10000;
	int tmp;

	//fill tree with nodes and positions on board
	add_nodes(tree,tree.get_root(),"black",0);

	//get alfabeta from every depth to get the best one
	while(max_depth > 0)
	{
		if(alfabeta(tree.get_root(),0,-1000,1000,false) <= ab)
		{
			ab = alfabeta(tree.get_root(),0,-1000,1000,false);
			tmp = max_depth;
		}
		max_depth--;
	}

	//here we have the best option
	max_depth = tmp;
	ab = alfabeta(tree.get_root(),0,-1000,1000,false);

	//for every child of root
	for(int i=0;i<tree.get_root()->get_size_children();i++)
	{
		//if value whoch means what is the best way to make move
		//is the same as one of childs value it means than move is good
		if(ab == tree.get_root()->get_child(i)->get_value())
		{
			//make computer move
			move(tree.get_root(),tree.get_root()->get_child(i));
			break;
		}
	}

	//set standart value of depth
	max_depth = 3;
}


/*
	Better algorith than minmax because it delete 
	unappropriate options, which means time is better	
*/
int Board::alfabeta(PTR_NODE ptr,int depth,int alfa,int beta,bool maximizingPlayer)
{

	int tmp=0;
	int value=0;

	//check if is end of tree
	if(depth == max_depth)
	{
		//returns estimated values from boards of end of tree
		if(maximizingPlayer == true) return estimate_value("white",ptr);
		else return estimate_value("black",ptr);
	} 

	//if white has move
	if(maximizingPlayer == true)
	{
		//init some value
		value = -100000;

		//increment depth of tree
		depth++;

		//iterate through all child of node
		for(int i=0;i<ptr->get_size_children();i++)
		{
			//recurse through all children and get the value from them
			tmp = alfabeta(ptr->get_child(i),depth,alfa,beta,false);
			
			//check if this value from child is higher than last best value
			value = max(value,tmp);

			//set value of node
			ptr->get_child(i)->set_value(tmp);

			//set alfa of node to check if is chanec to prun
			alfa = max(alfa,value);
			if(alfa>=beta) break;
		}

		return value;
	}

	//if black has move
	else
	{
		//init some value
		value = 100000;

		//increment depth of tree
		depth++;

		//iterate through all child of node
		for(int i=0;i<ptr->get_size_children();i++)
		{
			//recurse through all children and get the value from them
			tmp = alfabeta(ptr->get_child(i),depth,alfa,beta,false);

			//check if this value from child is higher than last best value
			value = min(value,tmp);

			//set value of node
			ptr->get_child(i)->set_value(tmp);

			//set alfa of node to check if is chanec to prun
			alfa = min(beta,value);
			if(alfa>=beta) break;
		}

		return value;
	}
}

/*
	Method which modify comp move to board move
*/
void Board::move(PTR_NODE root,PTR_NODE ptr)
{
	//Init helpful veriables
	vector <Figure> w = root->get_all_white();
	vector <Figure> b = root->get_all_black();
	Spot mv_from;
	Spot mv_to;

	//get which child is apppropiate to way of best move
	for(int i=0;i<int(b.size());i++)
	{
		if((b[i].get_x() != ptr->get_all_black()[i].get_x()) && (b[i].get_y() != ptr->get_all_black()[i].get_y()))
		{
			mv_from.set_pos(b[i].get_x(),b[i].get_y());
			mv_to.set_pos(ptr->get_all_black()[i].get_x(),ptr->get_all_black()[i].get_y());
			if(move("black",true,mv_from,mv_to) == true) 
			{
				cout << "Move" << endl;
				return;
			}
		}
	}

}


/*
	Method return all possible moves for actual positions of pawns
*/
vector <Info> Board::possible_moves(string color,vector <Figure> w,vector <Figure> b,vector <vector <char>> chars)
{
	vector <Spot> tmp;
	Info tmp2;
	vector <Info> vector;


	if(color == "white")
	{
		//check at first if is any kill
		if(check_if_any_has_kill("white",w,b,chars) == true)
		{
			for(int i=0;i<int(w.size());i++)
			{
				//get all possible kills
				tmp = able_kills("white",w[i].get_pos(),chars);
				for(int j = 0;j < int(tmp.size());j++)
				{
					//put it as a one array of information from and destiny of possibles moves
					tmp2.mv_from.set_pos(w[i].get_x(),w[i].get_y());
					tmp2.mv_to.set_pos(tmp[j].get_x(),tmp[j].get_y());
					vector.push_back(tmp2);
				}
			}
		}
		//if doesn have any kill
		else
		{
			for(int i=0;i<int(w.size());i++)
			{
				//get all possible moves
				tmp = able_moves("white",w[i].get_pos(),chars);
				for(int j = 0;j < int(tmp.size());j++)
				{
					//put it as a one array of information from and destiny of possibles moves
					tmp2.mv_from.set_pos(w[i].get_x(),w[i].get_y());
					tmp2.mv_to.set_pos(tmp[j].get_x(),tmp[j].get_y());
					vector.push_back(tmp2);
				}
			}
		}
	}
	else
	{
		//check at first if is any kill
		if(check_if_any_has_kill("black",w,b,chars) == true)
		{
			for(int i=0;i<int(b.size());i++)
			{
				//get all possible kills
				tmp = able_kills("black",b[i].get_pos(),chars);
				for(int j = 0;j < int(tmp.size());j++)
				{
					//put it as a one array of information from and destiny of possibles moves
					tmp2.mv_from.set_pos(b[i].get_x(),b[i].get_y());
					tmp2.mv_to.set_pos(tmp[j].get_x(),tmp[j].get_y());
					vector.push_back(tmp2);
				}
			}
		}
		else
		{
			//check at first if is any kill
			for(int i=0;i<int(b.size());i++)
			{
				//get all possible moves
				tmp = able_moves("black",b[i].get_pos(),chars);
				for(int j = 0;j < int(tmp.size());j++)
				{
					//put it as a one array of information from and destiny of possibles moves
					tmp2.mv_from.set_pos(b[i].get_x(),b[i].get_y());
					tmp2.mv_to.set_pos(tmp[j].get_x(),tmp[j].get_y());
					vector.push_back(tmp2);
				}
			}
		}
	}

	return vector;
}

/*
	Return value of predictable moves and states
*/
int Board::estimate_value(string color,PTR_NODE ptr)
{
	if(white_win(ptr->get_all_white()) == true) return VALUE_WHITE_WINS;
	else if(black_win(ptr->get_all_black()) == true) return VALUE_BLACK_WINS;
	else if(check_if_any_has_kill("white",ptr->get_all_white(),ptr->get_all_black(),ptr->get_fields()) == true) return VALUE_WHITE_KILL;
	else if(check_if_any_has_kill("black",ptr->get_all_white(),ptr->get_all_black(),ptr->get_fields()) == true) return VALUE_BLACK_KILL;
	else if(color == "white") return VALUE_WHITE_MOVE;
	else if(color == "black") return VALUE_BLACK_MOVE;
	
	return 0;

}

/*
	Make new nodes to tree and fill them with positions on board
*/
void Board::add_nodes(DecisionTree &tree,PTR_NODE ptr,string color,int depth)
{
	vector <Info> moves;

	//finish adding when max_depth is reached
	if(depth == max_depth) return;

	//if thre is no tree yet
	if(tree.get_root() == NULL)
	{
		//get possibles moves for first move
		moves = possible_moves("black",white,black,fields);

		//set root to first nad main node
		tree.set_root(make_shared <Node>());

		//set fields and pawn in root node
		tree.get_root()->set_fields(fields);
		tree.get_root()->set_pawns(white,black);

		//set ptr to this root
		ptr=tree.get_root();

		//fill children of root with possibles move
		fill_nodes(tree,tree.get_root(),"black",moves,white,black,fields);
	}
	//if the tree is bigger and have root
	else
	{
		if(color == "white")
		{
			//get possible move
			moves = possible_moves("white",ptr->get_all_white(),ptr->get_all_black(),ptr->get_fields());

			//fill nodes with possible moves
			fill_nodes(tree,ptr,"white",moves,ptr->get_all_white(),ptr->get_all_black(),ptr->get_fields());
		}
		else
		{
			moves = possible_moves("black",ptr->get_all_white(),ptr->get_all_black(),ptr->get_fields());
			fill_nodes(tree,ptr,"black",moves,ptr->get_all_white(),ptr->get_all_black(),ptr->get_fields());
		}
	}

	//increment depth of tree
	depth++;

	if(color == "white")
	{
		for(int i=0;i<int(moves.size());i++)
		{
			//how many possibles moves are, make the same amount of children nodes
			add_nodes(tree,ptr->get_child(i),"black",depth);
		}
	}
	else
	{
		for(int i=0;i<int(moves.size());i++)
		{
			//how many possibles moves are, make the same amount of children nodes
			add_nodes(tree,ptr->get_child(i),"white",depth);
		}
	}
}


/*
	Fill nodes with pawns and fields
*/
void Board::fill_nodes(DecisionTree &tree,PTR_NODE ptr,string color,vector <Info> moves,vector <Figure> w,vector <Figure> b,vector <vector <char>> chars)
{

	vector <Figure> tmp;
	if(color == "white")
	{
		//tmp as original white paws
		tmp = w;

		//make empty children nodes
		ptr->make_children(int(moves.size()));

		//for every possible move
		for(int j=0;j<int(moves.size());j++)
		{
			for(int i=0;i<int(w.size());i++)
			{
				//check pewn every pawn which one is the correct one 
				if((w[i].get_x() == moves[j].mv_from.get_x()) && (w[i].get_y() == moves[j].mv_from.get_y()))
				{
					//make changes
					tmp[i].set_pos(moves[j].mv_to.get_x(),moves[j].mv_to.get_y());

					//update node by actual state of fields
					chars = update_fields(tmp,b,chars);

					//put to node information about white black pawns and fields 
					ptr->insert(j,tmp,b,chars);
					tmp=w;
				}
			}

		}
	}
	else
	{
		//tmp as original white paws
		tmp=b;

		//make empty children nodes
		ptr->make_children(int(moves.size()));

		//for every possible move
		for(int j=0;j<int(moves.size());j++)
		{
			for(int i=0;i<int(b.size());i++)
			{
				//check pewn every pawn which one is the correct one 
				if((b[i].get_x() == moves[j].mv_from.get_x()) && (b[i].get_y() == moves[j].mv_from.get_y()))
				{
					//make changes
					tmp[i].set_pos(moves[j].mv_to.get_x(),moves[j].mv_to.get_y());

					//update node by actual state of fields
					chars = update_fields(w,tmp,chars);

					//put to node information about white black pawns and fields 
					ptr->insert(j,w,tmp,chars);
					tmp=b;
				}
			}

		}
	}
}


/*
	update fields in nodes
*/
vector <vector <char>> Board::update_fields(vector <Figure> w,vector <Figure> b,vector <vector <char>> chars)
{
	for(int i=0;i<=ROWS-1;i++)
	{
		for(int j=0;j<COLUMNS;j++)
		{
			if(j%2 != 0 && i%2 != 0) chars[i][j] = '+';
			else if(j%2 == 0 && i%2 == 0) chars[i][j] = '+';
			else chars[i][j] = ' ';

			//check in every pawn if this field dont have the same coordinates
			//if yes, then replace field with pawn symbol
			for(int p=0;p<int(w.size());p++)
			{
				if(i == w[p].get_y() && j == w[p].get_x())
				{
					chars[i][j] = w[p].get_sym();	   
				}
			}

	        //the same what up but with black pawn
			for(int p=0;p<int(b.size());p++)
			{
				if(i == b[p].get_y() && j == b[p].get_x())
				{
					chars[i][j] = b[p].get_sym();	   
				}
			}
		}
	}

	return chars;
}

/*
	Method responsible for making move and
	all operations connected with it
	like checking if is it possible
*/
bool Board::move(string color,bool computer,Spot mv_from, Spot mv_to)
{

	//check what color to move
	if(color == "white")
	{	
		//iter through all white pawns
		for(int p=0;p<int(white.size());p++)
		{ 
			//if our move is correct as cordinates of some pawn
			if(mv_from.get_y() == white[p].get_y() && mv_from.get_x() == white[p].get_x())
			{
				//check if any of pawn has possibility to kill/beat
				//if some can and our move wasnt all right than 
				//return false and start choosing move from beginning
				//if there is no pawn to beat than check if normal move was
				//done and if is correct
				if(check_if_able_to_kill_for_pawn("white",mv_from,fields) == true)
				{
					if(check_if_good_move_to_kill("white",mv_from,mv_to,fields) == false) return false;
				}
				else
				{
					if(check_if_any_has_kill("white",white,black,fields) == true) return false;
					else
					{
						if(check_if_able_to_move_for_pawn("white",mv_from,mv_to,fields) == false) return false;
					}
				}


				//if our move was good then it can change pawns coordinates
				white[p].set_x(mv_to.get_x());
				white[p].set_y(mv_to.get_y());

				//if some pawn is on the end of board
				//choose where you would like to move it
				if(white[p].get_y() == 7) 
				{
					int tmp1;
					int tmp2;
					Ind i = A;

					cout << "Where do you want to send your pawn: " ;
					cin >> tmp1 >> tmp2;

					i = convert(tmp1);
					white[p].set_x(i); white[p].set_y(tmp2);


				}

				return true;
			}
		}
	}
	else if(color == "black")
	{
		//iter through all black pawns
		for(int p=0;p<int(black.size());p++)
		{
			//if our move is correct as cordinates of some pawn
			if(mv_from.get_y() == black[p].get_y() && mv_from.get_x() == black[p].get_x())
			{
				//check if any of pawn has possibility to kill/beat
				//if some can and our move wasnt all right than 
				//return false and start choosing move from beginning
				//if there is no pawn to beat than check if normal move was
				//done and if is correct
				if(check_if_able_to_kill_for_pawn("black",mv_from,fields) == true)
				{
					if(check_if_good_move_to_kill("black",mv_from,mv_to,fields) == false) return false;
				}
				else
				{

					if(check_if_any_has_kill("black",white,black,fields) == true) return false;
					else
					{
						if(check_if_able_to_move_for_pawn("black",mv_from,mv_to,fields) == false) return false;
					}
				}

				//if our move was good then it can change pawns coordinates
				black[p].set_x(mv_to.get_x());
				black[p].set_y(mv_to.get_y());



				if(black[p].get_y() == 0) 
				{
					if(computer == true)
					{
						//computer choose where is best option to jump
						//to make it easy he will choose first row of blacks moves
						while(true)
						{
							int choices[4] = {1,3,5,7};
							int num = rand() % 4;
							int choice = choices[num];
							cout << choice << endl;
							if(fields[choice][7] == '+')
							{
								cout << "JEST" << endl;
								black[p].set_x(choice); black[p].set_y(7);
								cout << black[p].get_x() << " " << black[p].get_y() << endl;
								break;
							}
						}
					}
					else
					{
						//choose where you would like to move it if you are playes
						int tmp1;
						int tmp2;
						Ind i = A;
						cout << "Where do you want to send your pawn: " ;
						cin >> tmp1 >> tmp2;

						i = convert(tmp1);
						black[p].set_x(i); black[p].set_y(tmp2-1);
					}
				}
				//if some pawn is on the end of board
				
				return true;
			}
		}
	}

	//if something was wrong return false
	//and next everything is beginning from start
	return false;
}


/*
	Method check if given move from and move to are correct]
	and if are possible to do
*/
bool Board::check_if_able_to_move_for_pawn(string color,Spot mv_from,Spot mv_to,vector <vector <char>> chars)
{
	//check which player moves
	if(color == "white")
	{
		//check only possibility to move which is 
		//move for only one square and move foreahead
		//for white it is up
		if(((mv_to.get_x() == mv_from.get_x() + 1 && mv_to.get_y() == mv_from.get_y() + 1)
			|| (mv_to.get_x() == mv_from.get_x() - 1 && mv_to.get_y() == mv_from.get_y() + 1))
			&& (chars[mv_to.get_y()][mv_to.get_x()] == '+')) 
		{
			return true;
		}
	}
	else
	{
		//check only possibility to move which is 
		//move for only one square and move foreahead
		//for black it is down
		if((((mv_to.get_x() == mv_from.get_x() + 1) && (mv_to.get_y() == mv_from.get_y() - 1))
			|| ((mv_to.get_x() == mv_from.get_x() - 1) && (mv_to.get_y() == mv_from.get_y() - 1)))
			&& (chars[mv_to.get_y()][mv_to.get_x()] == '+')) 
		{
			return true;
		}
	}

	return false;
}


/*
	Method remove pawns from board if all 
	conditions are true
*/
void Board::remove_opponent(string color,Spot mv_from,Spot mv_to)
{
	Spot opponent_cor;

	if((color == "white") && (mv_to.get_x() > mv_from.get_x()) && (mv_to.get_y() > mv_from.get_y()))
	{
		opponent_cor.set_x(mv_from.get_x() + 1);
		opponent_cor.set_y(mv_from.get_y() + 1);
	}
	else if((color == "white") && (mv_to.get_x() < mv_from.get_x()) && (mv_to.get_y() > mv_from.get_y()))
	{
		opponent_cor.set_x(mv_from.get_x() - 1);
		opponent_cor.set_y(mv_from.get_y() + 1);
	}
	if((color == "white") && (mv_to.get_x() > mv_from.get_x()) && (mv_to.get_y() < mv_from.get_y()))
	{
		opponent_cor.set_x(mv_from.get_x() + 1);
		opponent_cor.set_y(mv_from.get_y() - 1);
	}
	else if((color == "white") && (mv_to.get_x() < mv_from.get_x()) && (mv_to.get_y() < mv_from.get_y()))
	{
		opponent_cor.set_x(mv_from.get_x() - 1);
		opponent_cor.set_y(mv_from.get_y() - 1);
	}
	else if((color == "black") && (mv_to.get_x() > mv_from.get_x()) && (mv_to.get_y() < mv_from.get_y()))
	{
		opponent_cor.set_x(mv_from.get_x() + 1);
		opponent_cor.set_y(mv_from.get_y() - 1);
	}
	else if((color == "black") && (mv_to.get_x() < mv_from.get_x()) && (mv_to.get_y() < mv_from.get_y()))
	{
		opponent_cor.set_x(mv_from.get_x() - 1);
		opponent_cor.set_y(mv_from.get_y() - 1);
	}
	else if((color == "black") && (mv_to.get_x() > mv_from.get_x()) && (mv_to.get_y() > mv_from.get_y()))
	{
		opponent_cor.set_x(mv_from.get_x() + 1);
		opponent_cor.set_y(mv_from.get_y() + 1);
	}
	else if((color == "black") && (mv_to.get_x() < mv_from.get_x()) && (mv_to.get_y() > mv_from.get_y()))
	{
		opponent_cor.set_x(mv_from.get_x() - 1);
		opponent_cor.set_y(mv_from.get_y() + 1);
	}

	if(color == "white")
	{
		for(int p=0;p<int(black.size());p++)
		{
			if(opponent_cor.get_y() == black[p].get_y() && opponent_cor.get_x() == black[p].get_x())
			{
				black.erase(black.begin() + p);
			}
		}
	}
	else
	{
		for(int p=0;p<int(white.size());p++)
		{
			if(opponent_cor.get_y() == white[p].get_y() && opponent_cor.get_x() == white[p].get_x())
			{
				white.erase(white.begin() + p);
			}
		}
	}
}

/*
	Method check if white pawns won
*/
bool Board::white_win(vector <Figure> w)
{
	if(int(w.size()) == 0) return true;

	return false;
}

/*
	Method check if white pawns won
*/
bool Board::black_win(vector <Figure> b)
{
	if(int(b.size()) == 0) return true;

	return false;
}

/*
	Method check if any pawn won
*/
bool Board::finished()
{
	if(int(white.size()) == 0) return true;
	else if(int(black.size()) == 0) return true;

	return false;
}

/*
	Method check if given move is possible to execute
*/
vector <Spot> Board::able_moves(string color,Spot mv_from,vector <vector <char>> chars)
{
	vector <Spot> vector_spots;
	Spot tmp;
	if(color == "white")
	{
		if((mv_from.get_x() >= 1) && (mv_from.get_x() <= 6))
		{
			if(chars[mv_from.get_y()+1][mv_from.get_x()+1] == '+') 
			{
				tmp.set_pos(mv_from.get_x()+1,mv_from.get_y()+1);
				vector_spots.push_back(tmp);
			}
			if(chars[mv_from.get_y()+1][mv_from.get_x()-1] == '+') 
			{
				tmp.set_pos(mv_from.get_x()-1,mv_from.get_y()+1);
				vector_spots.push_back(tmp);
			}
		}
		else if(mv_from.get_x() == 0)
		{
			if(chars[mv_from.get_y()+1][mv_from.get_x()+1] == '+') 
			{
				tmp.set_pos(mv_from.get_x()+1,mv_from.get_y()+1);
				vector_spots.push_back(tmp);
			}
		}
		else if(mv_from.get_x() == 7)
		{
			if(chars[mv_from.get_y()+1][mv_from.get_x()-1] == '+') 
			{
				tmp.set_pos(mv_from.get_x()-1,mv_from.get_y()+1);
				vector_spots.push_back(tmp);
			}
		}
	}
	else
	{
		if((mv_from.get_x() >= 1) && (mv_from.get_x() <= 6))
		{
			if(chars[mv_from.get_y()-1][mv_from.get_x()+1] == '+') 
			{
				tmp.set_pos(mv_from.get_x()+1,mv_from.get_y()-1);
				vector_spots.push_back(tmp);
			}
			if(chars[mv_from.get_y()-1][mv_from.get_x()-1] == '+') 
			{
				tmp.set_pos(mv_from.get_x()-1,mv_from.get_y()-1);
				vector_spots.push_back(tmp);
			}
		}
		else if(mv_from.get_x() == 0)
		{
			if(chars[mv_from.get_y()-1][mv_from.get_x()+1] == '+') 
			{
				tmp.set_pos(mv_from.get_x()+1,mv_from.get_y()-1);
				vector_spots.push_back(tmp);
			}
		}
		else if(mv_from.get_x() == 7)
		{
			if(chars[mv_from.get_y()-1][mv_from.get_x()-1] == '+') 
			{
				tmp.set_pos(mv_from.get_x()-1,mv_from.get_y()-1);
				vector_spots.push_back(tmp);
			}
		}
	}

	return vector_spots;
}

/*
	Method check if current pawn is able to kill
*/
bool Board::check_if_able_to_kill_for_pawn(string color,Spot mv_from,vector <vector <char>> chars)
{
	if(color == "white")
	{
		if((mv_from.get_x() > 1) && (mv_from.get_x() < 6) && (mv_from.get_y() > 1) && (mv_from.get_y() < 6))
		{
			if(((chars[mv_from.get_y()+2][mv_from.get_x()+2] == '+') && (chars[mv_from.get_y()+1][mv_from.get_x()+1] == 'O'))
				|| ((chars[mv_from.get_y()+2][mv_from.get_x()-2] == '+') && (chars[mv_from.get_y()+1][mv_from.get_x()-1] == 'O'))
				|| ((chars[mv_from.get_y()-2][mv_from.get_x()+2] == '+') && (chars[mv_from.get_y()-1][mv_from.get_x()+1] == 'O'))
				|| ((chars[mv_from.get_y()-2][mv_from.get_x()-2] == '+') && (chars[mv_from.get_y()-1][mv_from.get_x()-1] == 'O')))
			{
				return true;
			}
		}
		else if((mv_from.get_x() > 1) && (mv_from.get_x() < 6) && (mv_from.get_y() <= 1))
		{
			if(((chars[mv_from.get_y()+2][mv_from.get_x()+2] == '+') && (chars[mv_from.get_y()+1][mv_from.get_x()+1] == 'O'))
				|| ((chars[mv_from.get_y()+2][mv_from.get_x()-2] == '+') && (chars[mv_from.get_y()+1][mv_from.get_x()-1] == 'O')))
			{
				return true;
			}
		}
		else if((mv_from.get_x() > 1) && (mv_from.get_x() < 6) && (mv_from.get_y() >= 6))
		{
			if(((chars[mv_from.get_y()-2][mv_from.get_x()+2] == '+') && (chars[mv_from.get_y()-1][mv_from.get_x()+1] == 'O'))
				|| ((chars[mv_from.get_y()-2][mv_from.get_x()-2] == '+') && (chars[mv_from.get_y()-1][mv_from.get_x()-1] == 'O')))
			{
				return true;
			}
		}
		else if((mv_from.get_x() <= 1) && (mv_from.get_y() > 1) && (mv_from.get_y() < 6))
		{
			if(((chars[mv_from.get_y()+2][mv_from.get_x()+2] == '+') && (chars[mv_from.get_y()+1][mv_from.get_x()+1] == 'O'))
				|| ((chars[mv_from.get_y()-2][mv_from.get_x()+2] == '+') && (chars[mv_from.get_y()-1][mv_from.get_x()+1] == 'O')))
			{
				return true;
			}
		}
		else if((mv_from.get_x() >= 6) && (mv_from.get_y() > 1) && (mv_from.get_y() < 6))
		{
			if(((chars[mv_from.get_y()+2][mv_from.get_x()-2] == '+') && (chars[mv_from.get_y()+1][mv_from.get_x()-1] == 'O'))
				|| ((chars[mv_from.get_y()-2][mv_from.get_x()-2] == '+') && (chars[mv_from.get_y()-1][mv_from.get_x()-1] == 'O')))
			{
				return true;
			}
		}
		else if((mv_from.get_x() <= 1) && (mv_from.get_y() <= 1))
		{
			if(((chars[mv_from.get_y()+2][mv_from.get_x()+2] == '+') && (chars[mv_from.get_y()+1][mv_from.get_x()+1] == 'O')))
			{
				return true;
			}
		}
		else if((mv_from.get_x() <= 1) && (mv_from.get_y() >= 6))
		{
			if(((chars[mv_from.get_y()-2][mv_from.get_x()+2] == '+') && (chars[mv_from.get_y()-1][mv_from.get_x()+1] == 'O')))
			{
				return true;
			}
		}
		else if((mv_from.get_x() >= 6) && (mv_from.get_y() >= 6))
		{
			if(((chars[mv_from.get_y()-2][mv_from.get_x()-2] == '+') && (chars[mv_from.get_y()-1][mv_from.get_x()-1] == 'O')))
			{
				return true;
			}
		}
		else if((mv_from.get_x() >= 6) && (mv_from.get_y() <= 1))
		{
			if(((chars[mv_from.get_y()+2][mv_from.get_x()-2] == '+') && (chars[mv_from.get_y()+1][mv_from.get_x()-1] == 'O')))
			{
				return true;
			}
		}
	}
	else
	{
		if((mv_from.get_x() > 1) && (mv_from.get_x() < 6) && (mv_from.get_y() > 1) && (mv_from.get_y() < 6))
		{
			if(((chars[mv_from.get_y()+2][mv_from.get_x()+2] == '+') && (chars[mv_from.get_y()+1][mv_from.get_x()+1] == 'X'))
				|| ((chars[mv_from.get_y()+2][mv_from.get_x()-2] == '+') && (chars[mv_from.get_y()+1][mv_from.get_x()-1] == 'X'))
				|| ((chars[mv_from.get_y()-2][mv_from.get_x()+2] == '+') && (chars[mv_from.get_y()-1][mv_from.get_x()+1] == 'X'))
				|| ((chars[mv_from.get_y()-2][mv_from.get_x()-2] == '+') && (chars[mv_from.get_y()-1][mv_from.get_x()-1] == 'X')))
			{
				return true;
			}
		}
		else if((mv_from.get_x() > 1) && (mv_from.get_x() < 6) && (mv_from.get_y() <= 1))
		{
			if(((chars[mv_from.get_y()+2][mv_from.get_x()+2] == '+') && (chars[mv_from.get_y()+1][mv_from.get_x()+1] == 'X'))
				|| ((chars[mv_from.get_y()+2][mv_from.get_x()-2] == '+') && (chars[mv_from.get_y()+1][mv_from.get_x()-1] == 'X')))
			{
				return true;
			}
		}
		else if((mv_from.get_x() > 1) && (mv_from.get_x() < 6) && (mv_from.get_y() >= 6))
		{
			if(((chars[mv_from.get_y()-2][mv_from.get_x()+2] == '+') && (chars[mv_from.get_y()-1][mv_from.get_x()+1] == 'X'))
				|| ((chars[mv_from.get_y()-2][mv_from.get_x()-2] == '+') && (chars[mv_from.get_y()-1][mv_from.get_x()-1] == 'X')))
			{
				return true;
			}
		}
		else if((mv_from.get_x() <= 1) && (mv_from.get_y() > 1) && (mv_from.get_y() < 6))
		{
			if(((chars[mv_from.get_y()-2][mv_from.get_x()+2] == '+') && (chars[mv_from.get_y()-1][mv_from.get_x()+1] == 'X'))
				|| ((chars[mv_from.get_y()+2][mv_from.get_x()+2] == '+') && (chars[mv_from.get_y()+1][mv_from.get_x()+1] == 'X')))
			{
				return true;
			}
		}
		else if((mv_from.get_x() >= 6) && (mv_from.get_y() > 1) && (mv_from.get_y() < 6))
		{
			if(((chars[mv_from.get_y()-2][mv_from.get_x()-2] == '+') && (chars[mv_from.get_y()-1][mv_from.get_x()-1] == 'X'))
				|| ((chars[mv_from.get_y()+2][mv_from.get_x()-2] == '+') && (chars[mv_from.get_y()+1][mv_from.get_x()-1] == 'X')))
			{
				return true;
			}
		}
		else if((mv_from.get_x() <= 1) && (mv_from.get_y() <= 1))
		{
			if(((chars[mv_from.get_y()+2][mv_from.get_x()+2] == '+') && (chars[mv_from.get_y()+1][mv_from.get_x()+1] == 'X')))
			{
				return true;
			}
		}
		else if((mv_from.get_x() <= 1) && (mv_from.get_y() >= 6))
		{
			if(((chars[mv_from.get_y()-2][mv_from.get_x()+2] == '+') && (chars[mv_from.get_y()-1][mv_from.get_x()+1] == 'X')))
			{
				return true;
			}
		}
		else if((mv_from.get_x() >= 6) && (mv_from.get_y() >= 6))
		{
			if(((chars[mv_from.get_y()-2][mv_from.get_x()-2] == '+') && (chars[mv_from.get_y()-1][mv_from.get_x()-1] == 'X')))
			{
				return true;
			}
		}
		else if((mv_from.get_x() >= 6) && (mv_from.get_y() <= 1))
		{
			if(((chars[mv_from.get_y()+2][mv_from.get_x()-2] == '+') && (chars[mv_from.get_y()+1][mv_from.get_x()-1] == 'X')))
			{
				return true;
			}
		}
	}

	return false;
}

/*
	Method returns all possible kills
*/
vector <Spot> Board::able_kills(string color,Spot mv_from,vector <vector <char>> chars)
{
	vector <Spot> vector_spots;
	Spot tmp;
	if(color == "white")
	{
		if((mv_from.get_x() > 1) && (mv_from.get_x() < 6) && (mv_from.get_y() > 1) && (mv_from.get_y() < 6))
		{
			if((chars[mv_from.get_y()+2][mv_from.get_x()+2] == '+') && (chars[mv_from.get_y()+1][mv_from.get_x()+1] == 'O'))
			{
				tmp.set_pos(mv_from.get_x()+2,mv_from.get_y()+2);
				vector_spots.push_back(tmp);
			}
			if((chars[mv_from.get_y()+2][mv_from.get_x()-2] == '+') && (chars[mv_from.get_y()+1][mv_from.get_x()-1] == 'O')) 
			{
				tmp.set_pos(mv_from.get_x()-2,mv_from.get_y()+2);
				vector_spots.push_back(tmp);
			}
			if((chars[mv_from.get_y()-2][mv_from.get_x()+2] == '+') && (chars[mv_from.get_y()-1][mv_from.get_x()+1] == 'O')) 
			{
				tmp.set_pos(mv_from.get_x()+2,mv_from.get_y()-2);
				vector_spots.push_back(tmp);
			}
			if((chars[mv_from.get_y()-2][mv_from.get_x()-2] == '+') && (chars[mv_from.get_y()-1][mv_from.get_x()-1] == 'O'))
			{
				tmp.set_pos(mv_from.get_x()-2,mv_from.get_y()-2);
				vector_spots.push_back(tmp);
			}
		}
		else if((mv_from.get_x() > 1) && (mv_from.get_x() < 6) && (mv_from.get_y() <= 1))
		{
			if((chars[mv_from.get_y()+2][mv_from.get_x()+2] == '+') && (chars[mv_from.get_y()+1][mv_from.get_x()+1] == 'O'))
			{
				tmp.set_pos(mv_from.get_x()+2,mv_from.get_y()+2);
				vector_spots.push_back(tmp);
			}
			if((chars[mv_from.get_y()+2][mv_from.get_x()-2] == '+') && (chars[mv_from.get_y()+1][mv_from.get_x()-1] == 'O'))
			{
				tmp.set_pos(mv_from.get_x()-2,mv_from.get_y()+2);
				vector_spots.push_back(tmp);
			}
			
		}
		else if((mv_from.get_x() > 1) && (mv_from.get_x() < 6) && (mv_from.get_y() >= 6))
		{
			if((chars[mv_from.get_y()-2][mv_from.get_x()+2] == '+') && (chars[mv_from.get_y()-1][mv_from.get_x()+1] == 'O')) 
			{
				tmp.set_pos(mv_from.get_x()+2,mv_from.get_y()-2);
				vector_spots.push_back(tmp);
			}
			if((chars[mv_from.get_y()-2][mv_from.get_x()-2] == '+') && (chars[mv_from.get_y()-1][mv_from.get_x()-1] == 'O')) 
			{
				tmp.set_pos(mv_from.get_x()-2,mv_from.get_y()-2);
				vector_spots.push_back(tmp);
			}
			
		}
		else if((mv_from.get_x() <= 1) && (mv_from.get_y() > 1) && (mv_from.get_y() < 6))
		{
			if((chars[mv_from.get_y()+2][mv_from.get_x()+2] == '+') && (chars[mv_from.get_y()+1][mv_from.get_x()+1] == 'O')) 
			{
				tmp.set_pos(mv_from.get_x()+2,mv_from.get_y()+2);
				vector_spots.push_back(tmp);
			}
			if((chars[mv_from.get_y()-2][mv_from.get_x()+2] == '+') && (chars[mv_from.get_y()-1][mv_from.get_x()+1] == 'O')) 
			{
				tmp.set_pos(mv_from.get_x()+2,mv_from.get_y()-2);
				vector_spots.push_back(tmp);
			}
			
		}
		else if((mv_from.get_x() >= 6) && (mv_from.get_y() > 1) && (mv_from.get_y() < 6))
		{
			if((chars[mv_from.get_y()+2][mv_from.get_x()-2] == '+') && (chars[mv_from.get_y()+1][mv_from.get_x()-1] == 'O')) 
			{
				tmp.set_pos(mv_from.get_x()-2,mv_from.get_y()+2);
				vector_spots.push_back(tmp);
			}
			if((chars[mv_from.get_y()-2][mv_from.get_x()-2] == '+') && (chars[mv_from.get_y()-1][mv_from.get_x()-1] == 'O')) 
			{
				tmp.set_pos(mv_from.get_x()-2,mv_from.get_y()-2);
				vector_spots.push_back(tmp);
			}
			
		}
		else if((mv_from.get_x() <= 1) && (mv_from.get_y() <= 1))
		{
			if((chars[mv_from.get_y()+2][mv_from.get_x()+2] == '+') && (chars[mv_from.get_y()+1][mv_from.get_x()+1] == 'O')) 
			{
				tmp.set_pos(mv_from.get_x()+2,mv_from.get_y()+2);
				vector_spots.push_back(tmp);
			}

		}
		else if((mv_from.get_x() <= 1) && (mv_from.get_y() >= 6))
		{
			if((chars[mv_from.get_y()-2][mv_from.get_x()+2] == '+') && (chars[mv_from.get_y()-1][mv_from.get_x()+1] == 'O')) 
			{
				tmp.set_pos(mv_from.get_x()+2,mv_from.get_y()-2);
				vector_spots.push_back(tmp);
			}

		}
		else if((mv_from.get_x() >= 6) && (mv_from.get_y() >= 6))
		{
			if((chars[mv_from.get_y()-2][mv_from.get_x()-2] == '+') && (chars[mv_from.get_y()-1][mv_from.get_x()-1] == 'O')) 
			{
				tmp.set_pos(mv_from.get_x()-2,mv_from.get_y()-2);
				vector_spots.push_back(tmp);
			}

		}
		else if((mv_from.get_x() >= 6) && (mv_from.get_y() <= 1))
		{
			if((chars[mv_from.get_y()+2][mv_from.get_x()-2] == '+') && (chars[mv_from.get_y()+1][mv_from.get_x()-1] == 'O')) 
			{
				tmp.set_pos(mv_from.get_x()-2,mv_from.get_y()+2);
				vector_spots.push_back(tmp);
			}

		}
	}
	else
	{
		if((mv_from.get_x() > 1) && (mv_from.get_x() < 6) && (mv_from.get_y() > 1) && (mv_from.get_y() < 6))
		{
			if((chars[mv_from.get_y()+2][mv_from.get_x()+2] == '+') && (chars[mv_from.get_y()+1][mv_from.get_x()+1] == 'X')) 
			{
				tmp.set_pos(mv_from.get_x()+2,mv_from.get_y()+2);
				vector_spots.push_back(tmp);
			}
			if((chars[mv_from.get_y()+2][mv_from.get_x()-2] == '+') && (chars[mv_from.get_y()+1][mv_from.get_x()-1] == 'X')) 
			{
				tmp.set_pos(mv_from.get_x()-2,mv_from.get_y()+2);
				vector_spots.push_back(tmp);
			}
			if((chars[mv_from.get_y()-2][mv_from.get_x()+2] == '+') && (chars[mv_from.get_y()-1][mv_from.get_x()+1] == 'X')) 
			{
				tmp.set_pos(mv_from.get_x()+2,mv_from.get_y()-2);
				vector_spots.push_back(tmp);
			}
			if((chars[mv_from.get_y()-2][mv_from.get_x()-2] == '+') && (chars[mv_from.get_y()-1][mv_from.get_x()-1] == 'X')) 
			{
				tmp.set_pos(mv_from.get_x()-2,mv_from.get_y()-2);
				vector_spots.push_back(tmp);
			}
		}
		else if((mv_from.get_x() > 1) && (mv_from.get_x() < 6) && (mv_from.get_y() <= 1))
		{
			if((chars[mv_from.get_y()+2][mv_from.get_x()+2] == '+') && (chars[mv_from.get_y()+1][mv_from.get_x()+1] == 'X')) 
			{
				tmp.set_pos(mv_from.get_x()+2,mv_from.get_y()+2);
				vector_spots.push_back(tmp);
			}
			if((chars[mv_from.get_y()+2][mv_from.get_x()-2] == '+') && (chars[mv_from.get_y()+1][mv_from.get_x()-1] == 'X')) 
			{
				tmp.set_pos(mv_from.get_x()-2,mv_from.get_y()+2);
				vector_spots.push_back(tmp);
			}
		}
		else if((mv_from.get_x() > 1) && (mv_from.get_x() < 6) && (mv_from.get_y() >= 6))
		{
			if((chars[mv_from.get_y()-2][mv_from.get_x()+2] == '+') && (chars[mv_from.get_y()-1][mv_from.get_x()+1] == 'X'))
			{
				tmp.set_pos(mv_from.get_x()+2,mv_from.get_y()-2);
				vector_spots.push_back(tmp);
			} 
			if((chars[mv_from.get_y()-2][mv_from.get_x()-2] == '+') && (chars[mv_from.get_y()-1][mv_from.get_x()-1] == 'X')) 
			{
				tmp.set_pos(mv_from.get_x()-2,mv_from.get_y()-2);
				vector_spots.push_back(tmp);
			}
		}
		else if((mv_from.get_x() <= 1) && (mv_from.get_y() > 1) && (mv_from.get_y() < 6))
		{
			if((chars[mv_from.get_y()-2][mv_from.get_x()+2] == '+') && (chars[mv_from.get_y()-1][mv_from.get_x()+1] == 'X'))
			{
				tmp.set_pos(mv_from.get_x()+2,mv_from.get_y()-2);
				vector_spots.push_back(tmp);
			}
			if((chars[mv_from.get_y()+2][mv_from.get_x()+2] == '+') && (chars[mv_from.get_y()+1][mv_from.get_x()+1] == 'X')) 
			{
				tmp.set_pos(mv_from.get_x()+2,mv_from.get_y()+2);
				vector_spots.push_back(tmp);
			}
		}
		else if((mv_from.get_x() >= 6) && (mv_from.get_y() > 1) && (mv_from.get_y() < 6))
		{
			if((chars[mv_from.get_y()-2][mv_from.get_x()-2] == '+') && (chars[mv_from.get_y()-1][mv_from.get_x()-1] == 'X')) 
			{
				tmp.set_pos(mv_from.get_x()-2,mv_from.get_y()-2);
				vector_spots.push_back(tmp);
			}
			if((chars[mv_from.get_y()+2][mv_from.get_x()-2] == '+') && (chars[mv_from.get_y()+1][mv_from.get_x()-1] == 'X')) 
			{
				tmp.set_pos(mv_from.get_x()-2,mv_from.get_y()+2);
				vector_spots.push_back(tmp);
			}

		}
		else if((mv_from.get_x() <= 1) && (mv_from.get_y() <= 1))
		{
			if((chars[mv_from.get_y()+2][mv_from.get_x()+2] == '+') && (chars[mv_from.get_y()+1][mv_from.get_x()+1] == 'X')) 
			{
				tmp.set_pos(mv_from.get_x()+2,mv_from.get_y()+2);
				vector_spots.push_back(tmp);
			}

		}
		else if((mv_from.get_x() <= 1) && (mv_from.get_y() >= 6))
		{
			if((chars[mv_from.get_y()-2][mv_from.get_x()+2] == '+') && (chars[mv_from.get_y()-1][mv_from.get_x()+1] == 'X')) 
			{
				tmp.set_pos(mv_from.get_x()+2,mv_from.get_y()-2);
				vector_spots.push_back(tmp);
			}

		}
		else if((mv_from.get_x() >= 6) && (mv_from.get_y() >= 6))
		{
			if((chars[mv_from.get_y()-2][mv_from.get_x()-2] == '+') && (chars[mv_from.get_y()-1][mv_from.get_x()-1] == 'X')) 
			{
				tmp.set_pos(mv_from.get_x()-2,mv_from.get_y()-2);
				vector_spots.push_back(tmp);
			}

		}
		else if((mv_from.get_x() >= 6) && (mv_from.get_y() <= 1))
		{
			if((chars[mv_from.get_y()+2][mv_from.get_x()-2] == '+') && (chars[mv_from.get_y()+1][mv_from.get_x()-1] == 'X')) 
			{
				tmp.set_pos(mv_from.get_x()-2,mv_from.get_y()+2);
				vector_spots.push_back(tmp);
			}
		}
	}

	return vector_spots;
}

/*
	Method checks if given move is possible to be executed as kill
*/
bool Board::check_if_good_move_to_kill(string color,Spot mv_from,Spot mv_to,vector <vector <char>> chars)
{

	if(((mv_to.get_x() == mv_from.get_x() + 2) && (mv_to.get_y() == mv_from.get_y() + 2))
		|| ((mv_to.get_x() == mv_from.get_x() - 2) && (mv_to.get_y() == mv_from.get_y() + 2))
		|| ((mv_to.get_x() == mv_from.get_x() + 2) && (mv_to.get_y() == mv_from.get_y() - 2))
		|| ((mv_to.get_x() == mv_from.get_x() - 2) && (mv_to.get_y() == mv_from.get_y() - 2)))
	{
		Spot opponent_cor;

		if((color == "white") && (mv_to.get_x() > mv_from.get_x()) && (mv_to.get_y() > mv_from.get_y()))
		{
			opponent_cor.set_x(mv_from.get_x() + 1);
			opponent_cor.set_y(mv_from.get_y() + 1);
		}
		else if((color == "white") && (mv_to.get_x() < mv_from.get_x()) && (mv_to.get_y() > mv_from.get_y()))
		{
			opponent_cor.set_x(mv_from.get_x() - 1);
			opponent_cor.set_y(mv_from.get_y() + 1);
		}
		if((color == "white") && (mv_to.get_x() > mv_from.get_x()) && (mv_to.get_y() < mv_from.get_y()))
		{
			opponent_cor.set_x(mv_from.get_x() + 1);
			opponent_cor.set_y(mv_from.get_y() - 1);
		}
		else if((color == "white") && (mv_to.get_x() < mv_from.get_x()) && (mv_to.get_y() < mv_from.get_y()))
		{
			opponent_cor.set_x(mv_from.get_x() - 1);
			opponent_cor.set_y(mv_from.get_y() - 1);
		}
		else if((color == "black") && (mv_to.get_x() > mv_from.get_x()) && (mv_to.get_y() < mv_from.get_y()))
		{
			opponent_cor.set_x(mv_from.get_x() + 1);
			opponent_cor.set_y(mv_from.get_y() - 1);
		}
		else if((color == "black") && (mv_to.get_x() < mv_from.get_x()) && (mv_to.get_y() < mv_from.get_y()))
		{
			opponent_cor.set_x(mv_from.get_x() - 1);
			opponent_cor.set_y(mv_from.get_y() - 1);
		}
		else if((color == "black") && (mv_to.get_x() > mv_from.get_x()) && (mv_to.get_y() > mv_from.get_y()))
		{
			opponent_cor.set_x(mv_from.get_x() + 1);
			opponent_cor.set_y(mv_from.get_y() + 1);
		}
		else if((color == "black") && (mv_to.get_x() < mv_from.get_x()) && (mv_to.get_y() > mv_from.get_y()))
		{
			opponent_cor.set_x(mv_from.get_x() - 1);
			opponent_cor.set_y(mv_from.get_y() + 1);
		}


		if(chars[mv_to.get_y()][mv_to.get_x()] == '+')
		{
			if(color == "white")
			{
				remove_opponent("white",mv_from,mv_to);
			}	
			else
			{
				remove_opponent("black",mv_from,mv_to);
			}	
			return true;
		}
	}
	return false;
}	


/*
	Method checks if any of pawns can make beat
*/
bool Board::check_if_any_has_kill(string color,vector <Figure> w,vector <Figure> b,vector <vector <char>> chars)
{
	if(color == "white")
	{
		//iterate through all pawns
		for(int p=0;p<int(w.size());p++)
		{
			if(check_if_able_to_kill_for_pawn("white",w[p].get_pos(),chars) == true)
			{
				return true;
			}
		}
	}
	else
	{
		//iterate through all pawns
		for(int p=0;p<int(b.size());p++)
		{
			if(check_if_able_to_kill_for_pawn("black",b[p].get_pos(),chars) == true)
			{
				return true;
			}
		}
	}

	return false;
}

/*
	convert {A,B,C,D,E}
	to 0,1,2,3,4,5
*/
Ind convert(char c)
{
  Ind rtn;

  switch (c)
  {
    case 'A': rtn = A;
    break;
    
    case 'B': rtn = B;
    break;
    
    case 'C': rtn = C;
    break;

    case 'D': rtn = D;
    break;

    case 'E': rtn = E;
    break;

    case 'F': rtn = F;
    break;

    case 'G': rtn = G;
    break;

    case 'H': rtn = H;
    break;
  }
  
  return rtn;

}