#ifndef TREE_HH
#define TREE_HH

#include "node.hh"

using namespace std;

/*
  class of AVLTree
  contains needed methods to work it properly
  like insert or delete node
*/
template <typename T>
class AVLTree {
  
  /*
    pointer to our first node
  */
  AVLNode<T> *root;

  /*
    check if our AVLTree is empty or not
  */
  bool is_empty()
  {
    //if root dont point anything, means that tree is empty
    if(root == NULL) return true;
    else return false;
  }
  
  /*
    RR rotation
  */
  void RR(AVLNode<T> *ptr)
  {

    AVLNode<T> *parent = ptr->getUp();
    AVLNode<T> *right = ptr->getRight();
    ptr->setRight(right->getLeft());

    if(ptr->getRight() != NULL) ptr->getRight()->setUp(ptr);

    right->setLeft(ptr);
    ptr->setUp(right);
    right->setUp(parent);

    if(parent == NULL) root = right;
    else 
    {
      if(parent->getLeft() == ptr) parent->setLeft(right);
      else parent->setRight(right);
    } 

    if(right->getHf() == -1) 
    {
      ptr->setHf(0);
      right->setHf(0);
    }
    else
    {
      ptr->setHf(-1);
      right->setHf(1);
    }

  }
  
  /*
    LL rotation
  */
  void LL(AVLNode<T> *ptr)
  {
    AVLNode<T> *parent = ptr->getUp();
    AVLNode<T> *left = ptr->getLeft();

    ptr->setLeft(left->getRight());
    
    if(ptr->getLeft() != NULL) ptr->getLeft()->setUp(ptr);

    left->setRight(ptr);
    left->setUp(parent);
    ptr->setUp(left);

    if(parent == NULL) root = left;
    else 
    {
      if(parent->getLeft() == ptr) parent->setLeft(left);
      else parent->setRight(left);
    } 

    if(left->getHf() == 1) 
    {
      ptr->setHf(0);
      left->setHf(0);
    }
    else
    {
      ptr->setHf(1);
      left->setHf(-1);
    }


  }

  /*
    RL rotation
  */
  void RL(AVLNode<T> *ptr)
  {
    AVLNode<T> *parent = ptr->getUp();
    AVLNode<T> *right = ptr->getRight();
    AVLNode<T> *right_left = right->getLeft();

    right->setLeft(right_left->getRight());

    if(right->getLeft() != NULL) right->getLeft()->setUp(right);

    ptr->setRight(right_left->getLeft());

    if(ptr->getRight() != NULL) ptr->getRight()->setUp(ptr);

    right_left->setLeft(ptr);
    right_left->setRight(right);
    ptr->setUp(right_left);
    right->setUp(right_left);
    right_left->setUp(parent);

    if(parent == NULL)
    {
      root = right_left;
    }
    else
    {
      if(parent->getLeft() == ptr) parent->setLeft(right_left);
      else parent->setRight(right_left);
    }

    if(right_left->getHf() == -1) right->setHf(1);
    else right->setHf(0);

    if(right_left->getHf() == 1) ptr->setHf(-1);
    else ptr->setHf(0);

    right_left->setHf(0);
  }

  /*
    LR rotation
  */
  void LR(AVLNode<T> *ptr)
  {
    AVLNode<T> *parent = ptr->getUp();
    AVLNode<T> *left = ptr->getLeft();
    AVLNode<T> *left_right = left->getRight();

    left->setRight(left_right->getLeft());

    if(left->getRight() != NULL) left->getRight()->setUp(left);

    ptr->setLeft(left_right->getRight());

    if(ptr->getLeft() != NULL) ptr->getLeft()->setUp(ptr);

    left_right->setRight(ptr);
    left_right->setLeft(left);
    ptr->setUp(left_right);
    left->setUp(left_right);
    left_right->setUp(parent);

    if(parent == NULL)
    {
      root = left_right;
    }
    else
    {
      if(parent->getLeft() == ptr) parent->setLeft(left_right);
      else parent->setRight(left_right);
    }

    if(left_right->getHf() == 1) left->setHf(-1);
    else left->setHf(0);

    if(left_right->getHf() == -1) ptr->setHf(1);
    else ptr->setHf(0);

    left_right->setHf(0);
  }

  /*
    fix the unproporcial in tree
  */
  void rebalance(AVLNode<T> *ptr)
  {

    if(ptr->getHf() == -2) 
      if(ptr->getRight()->getHf() == -1)
        {
          RR(ptr);
        }
      else
        {
          RL(ptr);
        }
    else if(ptr->getHf() == 2)
    {
      if(ptr->getLeft()->getHf() == 1)
        {
          LL(ptr);
        }
      else
        {
          LR(ptr);
        }
    }
  }

  /*
    set the balance of node
  */
  void setHeight(AVLNode<T> *ptr)
  {
    ptr->setHf(Height(ptr->getLeft()) - Height(ptr->getRight()));  
  }

  /*
    put value to correct place in tree
  */
  void insert_private(T x, AVLNode<T> *ptr)
  {
    //if tree is empty, make a new first node
    //if not, compare number to node's keys and
    //put in right position
    
    AVLNode<T> *tmp = ptr;
  
    if(is_empty())
      {
      	root = new AVLNode<T>; 
      	ptr = root;    
      	root->setUp(NULL);
      	root->setNum(x);
      }
    else
      {
	     if(x > ptr->getNum())
	       {
	        if(ptr->getRight() == NULL)
	          {
      	     	ptr->setRight(new AVLNode<T>);
      	     	ptr->getRight()->setNum(x);
      	     	ptr->getRight()->setUp(tmp);
            }
	         else
	           {
		          insert_private(x,ptr->getRight());
	           }
            }
        else if(x < ptr->getNum())
	       {
	         if(ptr->getLeft() == NULL)
	           {
      		    ptr->setLeft(new AVLNode<T>);
      		    ptr->getLeft()->setNum(x);
      		    ptr->getLeft()->setUp(tmp);
	           }
	         else
	           {
		          insert_private(x,ptr->getLeft());
	           }
      }//x >||< ptr->nu,
    }//root != NULL
    
    setHeight(ptr);
    rebalance(ptr);
    
  }

  /*
    method going through all elements and 
    show numbers in special order
  */
  void pre_order(AVLNode<T> *ptr)
    {
      if(is_empty())
	     {
	       cout << "Tree is empty" <<endl;
	     }
      else
	     {
    	  if(ptr == NULL)
    	   {
    	      return;
    	   }
        else
    	  {
    	    cout << ptr->getNum() <<" "<<ptr->getHf()<<endl;
    	    pre_order(ptr->getLeft());
    	    pre_order(ptr->getRight());
    	  }
    	}
    }
  
  
  /*
     method going through all elements and 
     show numbers in special order
  */
  void in_order(AVLNode<T> *ptr)
    {
      if(is_empty())
	     {
        cout << "Tree is empty" <<endl;
	     }
      else
        {
        if(ptr == NULL)
	       {
	         return;
	       }
	       else
	       {
    	    in_order(ptr->getLeft());
    	    cout << ptr->getNum() <<" "<<ptr->getHf()<<endl;
    	    in_order(ptr->getRight());
	       }
        }
    }
  
  
  /*
    method going through all elements and 
    show numbers in special order
  */
  void post_order(AVLNode<T> *ptr)
  {
    if(is_empty())
      {
        cout << "Tree is empty" <<endl;
      }
    else
      {
        if(ptr == NULL)
	       {
          return;
	       }
        else
	       {
          post_order(ptr->getLeft());
    	    post_order(ptr->getRight());
    	    cout << ptr->getNum() <<" "<<ptr->getHf()<<endl;
	       }
      }
  }

  /*
     return node with maximum key
  */
  AVLNode<T> *maxNode(AVLNode<T> *ptr)
  { 
    while(ptr->getRight() != NULL) ptr = ptr->getRight();
    return ptr;
  }

  /*
    return node with maximum key but less that acctual node
  */
  AVLNode<T> *pred(AVLNode<T> *ptr)
  {
    return maxNode(ptr->getLeft());
  }

  /*
    remove given node
  */
  void remove(AVLNode<T> *ptr)
  {
  

    AVLNode<T> *parent;
    AVLNode<T> *right;
    AVLNode<T> *left;
    AVLNode<T> *max_left;

    parent = ptr->getUp();
    right = ptr->getRight();
    left = ptr->getLeft();

    if((right == NULL) && (left == NULL))
    { 
      if(ptr == root)
      {
        root = NULL;
      }
      else
      {
        if(parent->getRight() == ptr) parent->setRight(NULL);
        else parent->setLeft(NULL);
      }
    } 
    else if((left != NULL) && (right == NULL))
    {
      if(ptr == root)
      {
        root = left;
        left->setUp(NULL);
      }
      else
      {
        if(parent->getRight() == ptr) parent->setRight(left);
        else parent->setLeft(left);

        left->setUp(parent);

      }
    }
    else if((right != NULL) && (left == NULL))
    {
      if(ptr == root)
      {
        root = right;
        right->setUp(NULL);
      }
      else
      {
        if(parent->getRight() == ptr) parent->setRight(right);
        else parent->setLeft(right);

        right->setUp(parent);

      }
    }
    else
    {
      max_left = pred(ptr);

      max_left->setRight(right);
      right->setUp(max_left);

      if(ptr == root)
      {
        root = left;

        left->setUp(NULL);
      }
      else
      {
        if(parent->getRight() == ptr) parent->setRight(left);
        else parent->setLeft(left);

        left->setUp(parent);

      }
      
      while(right != NULL)
        {
        setHeight(right);
        rebalance(right);
        right = right->getUp();
        }

    }

    while(parent != NULL)
    {
      setHeight(parent);
      rebalance(parent);
      parent = parent->getUp();
    }
  }

  /*
    set the height of node
  */
  int Height(AVLNode<T> *ptr)
  {
    int height = 0;
    if(ptr == NULL) return height;
    else
      {
      	int left  = Height(ptr->getLeft());
      	int right = Height(ptr->getRight());
      	if(left > right) height = 1 + left;
      	else  height = 1 + right;
      	return height;
      }
    
    return height;
  }

  /*
    search and return node with given key
  */
  AVLNode<T> *find(T x, AVLNode<T> *ptr)
  {
    if(is_empty())
      {
        return NULL;
      }
    else
      {
      if(ptr != NULL)
        {
          if(x == ptr->getNum()) return ptr;
          else if(x < ptr->getNum()) return find(x,ptr->getLeft());
          else return find(x,ptr->getRight());
        }
      else return NULL;
      }

      return ptr;
  }
    
public:

  
  /*
    constructor, when you create tree
    it initiate pointer
  */
  AVLTree() 
  {
    root = NULL;
  }

  /*
    deconstructor, when you delete tree  
    the memory of root will be deleted too
  */
  ~AVLTree()
  {
    delete root;
  }

  /*
    search node with given key and remove if exist  
  */
  void remove_number(T x) 
  {
    AVLNode<T> *tmp;
    tmp = find(x,root);
    if(tmp) 
      {
        remove(tmp);
        //delete tmp;
      }
    else cout<< "There is no that key" <<endl;
  }

  /*
    method show all numbers from the first to last 
  */
  void show_numbers_pre_order() 
  {
    pre_order(root);
  }

  /*
    method show all numbers from the first to last 
  */
  void show_numbers_in_order() 
  {
    in_order(root);
  }

  /*
    method show all numbers from the first to last 
  */
  void show_numbers_post_order() 
  {
    post_order(root);
  }

  /*
    show value of root  
  */
  void show_root()
  {
    if(is_empty())
      {
        cout << "Tree is empty\n";
      }
    else
      {
        cout << "Root: "<<root->getNum()<<", hf: "<<root->getHf();
      }
  }
  
  
  /*
    activate of adding number to the tree  
  */
  void insert(T x) 
  {
    insert_private(x,root);
  }


};

#endif

    


    
