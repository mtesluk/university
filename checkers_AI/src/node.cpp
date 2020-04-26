#include "node.hh"


void Node::insert(int i,vector <Figure> w,vector <Figure> b,vector <vector <char>> f)
{
	children[i]->set_white(w);
	children[i]->set_black(b);
	children[i]->set_fields(f);
}

void Node::set_pawns(vector <Figure> w,vector <Figure> b)
{
	for(int i=0;i<int(w.size());i++)
	{
		white.push_back(w[i]);
	}
	for(int i=0;i<int(b.size());i++)
	{
		black.push_back(b[i]);
	}
}

void Node::make_children(int size)
{
	for(int i=0;i<size;i++)
		{
			children.push_back(make_shared <Node>());
		}

}