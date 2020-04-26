#ifndef BOARD_HH
#define BOARD_HH

#include <iostream>
#include <vector>
#include <algorithm> 
#include <cstdlib> 
#include "pawn.hh"
#include "tree.hh"

/*
  settings for pawns
  and settings for estimating value of moves
*/
#define AMOUNT_OF_PAWNS 12
#define ROWS 8
#define COLUMNS 8
#define VALUE_WHITE_WINS 1000
#define VALUE_BLACK_WINS -1000
#define VALUE_WHITE_KILL 30
#define VALUE_BLACK_KILL -30
#define VALUE_WHITE_MOVE 5
#define VALUE_BLACK_MOVE -5

using namespace std;
/*
  enum responsible for making moves of playes
  when you put for example A 4
  than it send to class board indexes
  of fields and pawns 0 3
*/
enum Ind {A,B,C,D,E,F,G,H};

/*
  Class board is a main place in program
  responsible for all moves, behaviours,
  kills, computer plays
*/
class Board
{

  //init all figures and states of fields on board
  vector <vector <char>> fields;
  vector <Figure> white;
  vector <Figure> black;
public:

  /*
    Constructor of our board,
    init every field of board with correct coordinates,
    ane init every pawn on starting field
  */
  Board();

  /*
    According to acctual positions and chars 
    show everything in terminal 
  */
  void show_board();

  /*
    Main method responsible for making move and
    all operations connected with it
    like checking if is it possible
  */
  bool move(string color,bool computer,Spot move_from,Spot move_to);

  /*
    Method check if any pawn won
  */
  bool finished();

  /*
    Main method operates computer moves,
    first make tree and next with minmax algorithm
    make appropraite moves
  */
  void comp_move();
private:

  /*
    Method check if white pawns won
  */
  bool white_win(vector <Figure> w);

  /*
    Method check if white pawns won
  */
  bool black_win(vector <Figure> b);

  /*
    Method return all possible moves for actual positions of pawns
  */
  vector <Info> possible_moves(string color,vector <Figure> w,vector <Figure> b,vector <vector <char>> chars);

  /*
    Method check if given move from and move to are correct]
    and if are possible to do
  */
  bool check_if_able_to_move_for_pawn(string color,Spot mv_from,Spot mv_to,vector <vector <char>> chars);

  /*
    Method check if current pawn is able to kill
  */
  bool check_if_able_to_kill_for_pawn(string color,Spot mv_from,vector <vector <char>> chars);

  /*
    Method remove pawns from board if all 
    conditions are true
  */
  void remove_opponent(string color,Spot mv_from, Spot mv_to);

  /*
    Method checks if given move is possible to be executed as kill
  */
  bool check_if_good_move_to_kill(string color,Spot mv_from,Spot mv_to,vector <vector <char>> chars);

  /*
    Method checks if any of pawns can make beat
  */
  bool check_if_any_has_kill(string color,vector <Figure> w,vector <Figure> b,vector <vector <char>> chars);

  /*
    Method returns all possible moves
  */
  vector <Spot> able_moves(string color,Spot mv_from,vector <vector <char>> chars);

  /*
    Method returns all possible kills
  */
  vector <Spot> able_kills(string color,Spot mv_from,vector <vector <char>> chars);

  /*
    Make new nodes to tree and fill them with positions on board
  */
  void add_nodes(DecisionTree &tree,PTR_NODE ptr,string color,int depth);

  /*
    update fields in nodes
  */
  vector <vector <char>> update_fields(vector <Figure> w,vector <Figure> b,vector <vector <char>> chars);

  /*
    Return value of predictable moves and states
  */
  int estimate_value(string color,PTR_NODE ptr);

  /*
    Better algorith than minmax because it delete 
    unappropriate options, which means time is better 
  */
  int alfabeta(PTR_NODE ptr,int depth,int alfa,int beta,bool maximizingPlayer);

  /*
    Method which modify comp move to board move
  */
  void move(PTR_NODE root,PTR_NODE ptr);

  /*
    Fill nodes with pawns and fields
  */
  void fill_nodes(DecisionTree &tree,PTR_NODE ptr,string color,vector <Info> moves,vector <Figure> white,vector <Figure> black,vector <vector <char>> chars);
};

/*
  convert {A,B,C,D,E}
  to 0,1,2,3,4,5
*/
Ind convert(char c);


#endif