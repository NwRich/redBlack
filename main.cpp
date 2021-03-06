/*Nicholas Rich 5/16/18
 *a red black tree
 */
#include <iostream>
#include <ctype.h>
#include <cstring>
#include <stdlib.h>
#include <fstream>

using namespace std;
/*all containing the node and its functions*/  
struct node {
  node* left = NULL;
  node* right = NULL;
  node* parent = NULL;
  int color = 0;
  int value = NULL;
};

node* parent(node* n) {//returns the parent of the nod
  return n->parent;
}

node* grandParent(node* n) {//returns the grandparent of the node
  node* p = parent(n);
  if (p == NULL) {
    return NULL;
  }
  return p->parent;
}

node* brother(node* n) {//returns the left or right of the parent of thenode
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

node* uncle(node* n) {//returns the uncle of the node
  node* p = parent(n);
  node* g = grandParent(n);
  if (g == NULL) {
    return NULL;
  }
  return brother(p);
}

/*prototypes*/
void insertRe(node* root, node* n);
void insertRepairTree(node* n);
node* insert(node* root, node* n);//maybe pass in root by reference
void rotateLeft(node* n);
void rotateRight(node* n);
void print(node* current, int depth);
void insertCase1(node* n);
void insertCase2(node* n);
void insertCase3(node* n);
void insertCase4(node* n);
void replaceNode(node* n, node* child);
void deleteOneChild(node* n);
void deleteCase1(node* n);
void deleteCase2(node* n);
void deleteCase3(node* n);
void deleteCase4(node* n);
void deleteCase5(node* n);
void deleteCase6(node* n);
node* IOS(node* n);
void del(node* n, node* &root);
node* search(node* current, int input);

int main () {
  node* root = NULL;//used to hold the tree
  char* input = new char[16];//used for user input
  bool working = true;//used to end the program
  while (working = true) {//while the user is working
    cout << "input a number, from a file, search, delete, or quit" << endl;//promt the user for an input
    cin.getline(input, 16);//get the response
    if (strcmp(input, "quit") == 0) {//if the response is quit
      return 0;//end the program
    }
    else if (strcmp(input, "delete") == 0) {
      cout << "what number do you want to delete?" << endl;
      int input;
      cin >> input;
      if (root != NULL) {
	node* n = search(root, input);
	del(n, root);//not the right function
      }
      else {
	cout << "the tree is empty" << endl;
      }
    }
    else if (strcmp(input, "search") == 0) {
      int input = 0;
      cout << "what number do you want to search for?" << endl;
      cin >> input;
      search(root, input);
    }
    else if (strcmp(input, "file") == 0) {//if the input is file
      cout << "input the file name" << endl;//promt for an input
      ifstream inFile;//read in from a file
      cin >> input;
      inFile.open(input);
      char inputFile[500];
      inFile.getline(inputFile, 500);
      inFile.close();
      char* c = strtok(inputFile, ",");
      while (c != NULL) {
	node* n = new node();
	n->value = atoi(c);
	root = insert(root, n);
	c = strtok(NULL, ",");
      }
    }
    else {//otherwise add to the tree
      node* n = new node;
      n->value = atoi(input);
      root = insert(root, n);
      print(root,0);
    }
  }
  return 0;
}

void rotateLeft(node* n) {//used to rotate left around a node
  node* newn = n->right;
  if (newn != NULL) {
    n->right = newn->left;
    if (newn->left != NULL) {
      newn->left->parent = n;
    }
    newn->left = n;
    newn->parent = n->parent;
    if (n->parent != NULL && n->parent->right == n) {
      n->parent->right = newn;
    }
    else if (n->parent != NULL && n->parent->left == n) {
      n->parent->left = newn;
    }
    if (newn->parent != NULL && newn->parent->right == newn) {
      newn->parent->right = newn;
    }
    else if (newn->parent != NULL && newn->parent->left == newn) {
      newn->parent->left = newn;
    }
    n->parent = newn;
  }
}

void rotateRight(node* n) {//used to rotate right around a node
  node* newn = n->left;
  if (newn != NULL) {
    n->left = newn->right;
    if (n->left != NULL) {
      n->left->parent = n;
    }
    newn->parent = n->parent;
    if (newn->parent != NULL) {
      if (newn->parent->left == n) {
	newn->parent->left = newn;
      }
      else {
	newn->parent->right = newn;
      }
    }
    newn->right = n;
    n->parent = newn;
  }
}

node* insert(node* root, node* n) {//maybe pass in root by reference
  insertRe(root, n);//call insert recusivley to put the node in place
  insertRepairTree(n);//repair the tree passing in the new node
  root = n;
  while (parent(root) != NULL) {
    root = parent(root);
  }
  return root;
}

void insertRe(node* root, node* n) {
  if (root == NULL) {
    return;
  }
  if (n->value < root->value) {//if the input is less than the root
    if (root->left != NULL) {//and the left root is not empty
      insertRe(root->left, n);//go left and call insertRe again
      return;//end
    }
    else {//otherwise
      root->left = n;//set left to be the input
      //n->parent = root;//was commeted out
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
  n->parent = root;
  n->left = NULL;
  n->right = NULL;
  n->color = 0;
}

void insertRepairTree(node* n) {//repair the tree
  if (parent(n) == NULL) {
    insertCase1(n);
    }
  else if (parent(n)->color == 1 && parent(n) != NULL) {
    insertCase2(n);
  }
  else if (uncle(n) != NULL && uncle(n)->color == 0) {
    insertCase3(n);
  }
  else {
    insertCase4(n);
  }
}

void insertCase1(node* n) {//if its a root
  if (parent(n) == NULL) {
    n->color = 1;
  }
}

void insertCase2(node* n) {//dont do anything
  return;
}

void insertCase3(node* n) {//if parent and uncle are red repaint them black
  parent(n)->color = 1;
  uncle(n)->color = 1;
  grandParent(n)->color = 0;
  insertRepairTree(grandParent(n));
}

void insertCase4(node* n) {//do some fancy stuff thats no fun
  if (grandParent(n)->left != NULL && n == grandParent(n)->left->right) {
    rotateLeft(parent(n));
    n = n->left;
  }
  else if (grandParent(n)->right != NULL && n == grandParent(n)->right->left) {
    rotateRight(parent(n));
    n = n->right;
  }
  parent(n)->color = 1;
  n->color = 0;
  grandParent(n)->color = 0;
  if (n == parent(n)->left) {
    rotateRight(grandParent(n));
  }
  else if (n == parent(n)->right) {
    rotateLeft(grandParent(n));
  }
}

void replaceNode(node* n, node* child) {
  child->parent = n->parent;
  if (n->parent != NULL) {
    if (n == n->parent->left) {
      n->parent->left = child;
    }
    else {
      n->parent->right = child;
    }
  }
}

void deleteOneChild(node* n) {
  node* child;
  if (n->left != NULL && n->right == NULL) {
    child = n->left;
  }
  else if (n->right != NULL && n->left == NULL) {
    child = n->right;
  }
  replaceNode(n,child);
  if (n->color == 1) {
    if (child->color = 0) {
      child->color = 1;
    }
    else {
      deleteCase1(child);
    }
  }
  delete n;
}

void deleteCase1(node* n) {
  cout << "case 1" << endl;
  if (n->parent != NULL) {
    deleteCase2(n);
  }
}

void deleteCase2(node* n) {
  cout << "case 2" << endl;
  node* b = brother(n);
  if (b->color == 0) {
    n->parent->color = 0;
    b->color = 1;
    if (n->parent != NULL && n == n->parent->left) {
      rotateLeft(n->parent);
    }
    else {
      rotateRight(n->parent);
    }
  }
  deleteCase3(n);
}

void deleteCase3(node* n) {
  cout << "case 3" << endl;
  node* b = brother(n);
  if (n->parent->color == 1 && b->color == 1 && b->left->color == 1 && b->right->color == 1) {
    b->color = 0;
    deleteCase1(n->parent);
  }
  else {
    deleteCase4(n);
  }
}

void deleteCase4(node* n) {
  cout << "case 4" << endl;
  node* b = brother(n);
  if (b->left != NULL && b->right != NULL) {
    if (n->parent->color == 0 && b->color == 1 && b->left->color == 1 && b->right->color == 1) {
      b->color = 0;
      n->parent->color = 1;
    }
  }
  else {
    deleteCase5(n);
  }
}

void deleteCase5(node* n) {
  cout << "case 5" << endl;
  node* b = brother(n);
  if (b != NULL && b->color == 1) {
    if (n == n->parent->left &&
	(b->right == NULL || b->right->color == 1) && (b->left != NULL && b->left->color == 0)) {
      b->color = 0;
      b->left->color = 1;
      rotateRight(b);
    }
    else if (n == n->parent->right &&
	     (b->left == NULL || b->left->color == 1) && (b->right != NULL && b->right->color == 0)) {
      b->color = 0;
      b->right->color = 1;
      rotateLeft(b);
    }
  }
  deleteCase6(n);
}

void deleteCase6(node* n) {
  cout << "case 6" << endl;
  node* b = brother(n);
  b->color = n->parent->color;
  n->parent->color = 1;
  if (n == n->parent->left && b->right != NULL) {
    b->right->color = 1;
    rotateLeft(n->parent);
  }
  else if (b->left != NULL) {
    b->left->color = 1;
    rotateRight(n->parent);
  }
}

void del(node* n, node* &root) {
  node* ios = n;
  if(n->left != NULL && n->right != NULL) {
    ios = IOS(n->right);
    int temp = n->value;
    n->value = ios->value;
    ios->value = temp;
  }
  if(ios->left == NULL && ios->right == NULL) {
    if (ios->color == 1) {
      deleteCase1(ios);
    }
    if(ios->parent != NULL) {
      if (ios->parent->left == ios) {
	ios->parent->left == NULL;
      }
      else {
	ios->parent->right = NULL;
      }
    }
    else {
      root = NULL;
    }
    delete ios;
    return;
  }
  if (n == root) {
    if (n->left != NULL) {
      root = n->left;
      n->left->parent = NULL;
      n->left->color = 1;
    }
    else if (n->right != NULL) {
      root = n->right;
      n->right->parent = NULL;
      n->right->color = 1;
    }
    delete n;
    return;
  }
  deleteOneChild(ios);
}

node* IOS(node* n) {
  if (n->left != NULL) {
    IOS(n->left);
  }
  else {
    return n;
  }
}

node* search(node* current, int input) {
  if (current->value == input) {
    return current;
  }
  if (input > current->value) {
    return search(current->right, input);
  }
  else {
    return search(current->left, input);
  }
}

void print(node* current, int depth) {
  if (current->right != NULL) {//if there is a node to the right
    print(current->right, depth+1);//go to the right increasing the depth
  }
  for (int i = 0; i < depth; i++) {//print out the right amount of tabs
    cout << "\t";
  }
  if (current->value != 0) {
    cout << current->value;//print out the value of the node
    
    if (current->color == 0) {//if the node is red
      cout << " Red\n";//print out red
    }
    else {//otherwise the node is black
      cout << " Black\n";//print out black
    }
  }
  if (current->left != NULL) {//if left is not empty
    print(current->left, depth+1);//go down to the left
  }
}
