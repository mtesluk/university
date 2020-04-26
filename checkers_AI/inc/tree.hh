#include "node.hh"

typedef shared_ptr <Node> PTR_NODE;

/*
	DecisonTree is like normal tree but can contains many children
	not only 2
*/
class DecisionTree
{
	//root of tree
	PTR_NODE root;
public:
	//set root as NULL
	DecisionTree() {root = NULL;};

	//getters and setters
	PTR_NODE get_root() {return root;};
	void set_root(PTR_NODE ptr) {root = ptr;};
};