/*Nicholas Rich 4/11/18
 *a red black tree
 */
#include <iostream>

using namespace std;
/*all containing the node and its functions*/  
struct node {
  node* left = NULL;
  node* right = NULL;
  node* parent = NULL;
  int color;
  int value;
  node(int number) {
  color = 0;//0 is red 1 is black
  value = number;
  }
};

node* parent(node* n) {
  return n->parent;
  }
node* grandParent(node* n) {
  node* p = parent(n);
  if (p == NULL) {
    return NULL;
  }
  return parent(p);
}
node* brother(node* n) {
  node* p = parent(n);
  if (p == NULL) {
    return NULL;
  }
  if (n == p->left) {
    return p->right;
  }
  else {
    return p->left;
  }
}
node* uncle(node* n) {
  node* p = parent(n);
  node* g = grandParent(n);
  if (g == NULL) {
    return NULL;
  }
  return brother(p);
}
void insertRe(node* root, node* n);
void insertRepairTree(node* n);
node* insert(node* root, node* n);
void rotateLeft(node* n);
void rotateRight(node* n);
void print(node* current, int depth);

int main () {
  //test code start
  node* root;
  node* n = new node(5);
  insert(root,n);
  node* b = new node(4);
  insert(root,b);
  node* c = new node(6);
  insert(root,c);
  node* d = new node(5);
  insert(root,d);
  print(n,0);
  //test code end
  return 0;
}

void rotateLeft(node* n) {
  node* r = n->right;
  if (r) {
    n->right = r->left;
    if (n->right) {
      n->right->parent = n;
    }
    r->parent = n->parent;
    if (r->parent) {
      if (r->parent->left == n) {
	r->parent->left = r;
      }
      else {
	r->parent->right = r;
      }
    }
    r->left = n;
    n->parent = r;    
  }
}

void rotateRight(node* n) {
  node* l = n->left;
  if (l) {
    n->left = l->right;
    if (n->left) {
      n->left->parent = n;
    }
    l->parent = n->parent;
    if (l->parent) {
      if (l->parent->left == n) {
	l->parent->left = l;
      }
      else {
	l->parent->right = l;
      }
    }
    l->right = n;
    n->parent = l;
  }
}
  
node* insert(node* root, node* n) {
  insertRe(root, n);//call insert recusivley to put the node in place
  insertRepairTree(n);//repair the tree passing in the new node
  root = n;//root becomes the new node
  while (parent(root) != NULL) {//while root has a parent
    root = parent(root);//go up to the top of the tree
  }
  return root;//return root
}

void insertRe(node* root, node* n) {
  if (n->value < root->value) {//if the input is less than the root
    if (root->left != NULL) {//and the left root is not empty
      insertRe(root->left, n);//go left and call insertRe again
      return;//end
    }
    else {//otherwise
      root->left = n;//set left to be the input
    }
  }
  else if(n->value >= root->value) {//if the input is greater than or equal to the root
    if (root->right != NULL) {//and the right root is not empty
      insertRe(root->right, n);//go down the tree to the right
      return;//end
    }
    else {//otherwise
      root->right = n;//set the right root as input
    }
  }
}

void insertRepairTree(node* n) {
  if (parent(n) == NULL) {//case 1
    n->color = 1;//set the color to black
  }
  else if (parent(n)->color == 0) {//if the color is red
    if (uncle(n) != NULL && uncle(n)->color == 0) {//if the uncle is real and the uncle is red
      uncle(n)->color = 1;//set the uncle to black
      parent(n)->color = 1;//set the parent to black
      grandParent(n)->color = 0;//set the grandparent to red
      insertRepairTree(grandParent(n));//call inserRepairTree again with the grandparent
    }
    else {//otherwise
      if (grandParent(n)->left != NULL && n == grandParent(n)->left->right != NULL) {//if the grandparent is left and left right are real 
	rotateLeft(parent(n));//rotate left passing in the parent of node
	n = n->left;//n becomes the left of n
      }
      else if (grandParent(n)->right != NULL && n == grandParent(n)->right->left != NULL) {//the grandparents right and right left
	rotateRight(parent(n));//rotate right passing in parent of node
	n = n->right;//n becomes the right of n
      }
      grandParent(n)->color = 0;//set the grandparents color to red
      parent(n)->color = 1;//set the parents color to black
      if (parent(n)->left == n) {//if the parents left is n
	rotateRight(grandParent(n));//rotate right passing in the grandparent
      }
      else {//otherwise
	rotateLeft(grandParent(n));//rotate left passing in the grandparent
      }
    }
  }
}
 
void print(node* current, int depth) {
  if (current->right != NULL) {//if there is a node to the right
    print(current->right, depth+1);//go to the right increasing the depth
  }
  for (int i = 0; i < depth; i++) {//print out the right amount of tabs
    cout << "\t";
  }
  cout << current->value;//print out the value of the node
  if (current->color == 0) {//if the node is red
    cout << " Red\n";//print out red
  }
  else {//otherwise the node is black
    cout << " Black\n";//print out black
  }
  if (current->left != NULL) {//if left is not empty
    print(current->left, depth+1);//go down to the left
  }
}
