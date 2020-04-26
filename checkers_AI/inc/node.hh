#include <iostream>
#include <vector>
#include <memory>
#include "figure.hh"

using namespace std;

/*
	Node of tree
	contains information about predictable of boards
*/
class Node
{
	//value telling us about value of board
	int value;

	//information about state of board
	vector <Figure> white;
	vector <Figure> black;
	vector <vector <char>> fields;

	//pointers to out children
	vector <shared_ptr <Node>> children;
public:
	Node() {white.reserve(12);black.reserve(12);};

	//create children nodes
	void make_children(int size) ;

	//putting to given child state of pawns and fields
	void insert(int i,vector <Figure> w,vector <Figure> b,vector <vector <char>> f);

	//getters and setters
	void set_pawns(vector <Figure> w,vector <Figure> b);
	int get_value() {return value;};
	int get_size_children() {return int(children.size());};
	void set_value(int v) {value=v;};
	void set_white(vector <Figure> w) {white=w;};
	vector <Figure> get_all_white() {return white;};
	void set_black(vector <Figure> b) {black=b;};
	vector <Figure> get_all_black() {return black;};
	shared_ptr <Node> get_child(int index) {return children[index];};
	void set_fields(vector <vector <char>> f) {fields=f;};
	vector <vector <char>> get_fields() {return fields;};
};