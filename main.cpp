/*Nicholas Rich 4/11/18
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

node* parent(node* n) {
  return n->parent;
}

node* grandParent(node* n) {
  node* p = parent(n);
  if (p == NULL) {
    return NULL;
  }
  return p->parent;
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
node* insert(node* root, node* n);//maybe pass in root by reference
void rotateLeft(node* n);
void rotateRight(node* n);
void print(node* current, int depth);
void insertCase1(node* n);
void insertCase2(node* n);
void insertCase3(node* n);
void insertCase4(node* n);

int main () {
  node* root = NULL;
  char* input = new char[16];
  bool working = true;
  while (working = true) {
    cout << "input a number or file to import from a file or quit" << endl;
    cin.getline(input, 16);
    if (strcmp(input, "quit") == 0) {
      return 0;
    }
    else if (strcmp(input, "file") == 0) {
      cout << "input the file name" << endl;
      ifstream inFile;
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
    else {
      node* n = new node;
      n->value = atoi(input);
      root = insert(root, n);
      print(root,0);
    }
  }
  return 0;
}

void rotateLeft(node* n) {
  node* newn = n->right;
  if (newn != NULL) {
    n->right = newn->left;
    if (newn->left != NULL) {
      newn->left->parent = n;
      newn->parent->right = newn->left;
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

void rotateRight(node* n) {
  node* newn = n->left;
  if (newn != NULL) {
    n->left = newn->right;
    if (newn->right != NULL) {
      newn->right->parent = n;
      newn->parent->left = newn->right;
    }
    newn->right = n;
    newn->parent = n->parent;
    if(n->parent != NULL && n->parent->right == n) {
      n->parent->right == newn;
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
      // n->parent = root;//was commeted out
    }
  }
  n->parent = root;
  n->left = NULL;
  n->right = NULL;
  n->color = 0;
}

void insertRepairTree(node* n) {
  if (parent(n) == NULL) {
    insertCase1(n);
    }
  else if (parent(n)->color == 1 && parent(n) != NULL) {
    insertCase2(n);
  }
  else if (uncle(n) != NULL && uncle(n)->color == 0) {//calling uncle when it doesnt exist cause seg faults
    insertCase3(n);
  }
  else {
    insertCase4(n);
  }
}

void insertCase1(node* n) {
  if (parent(n) == NULL) {
    n->color = 1;
  }
}

void insertCase2(node* n) {
  return;
}

void insertCase3(node* n) {
  parent(n)->color = 1;
  uncle(n)->color = 1;
  grandParent(n)->color = 0;
  insertRepairTree(grandParent(n));
}

void insertCase4(node* n) {
  node* p = parent(n);
  node* g = grandParent(n);
  if(/*g != NULL &&*/ g->left != NULL && n == g->left->right) {
    rotateLeft(p);
    n = n->left;
  }
  else if (/*g != NULL &&*/ g->right != NULL && n == g->right->left) {
    rotateRight(p);
    n = n->right;
  }
  parent(n)->color = 1;
  n->color = 0;
  g->color = 0;
  if (p->left == n) {
    rotateRight(g);
  }
  else {
    rotateLeft(g);
  }
  /* if(n == parent(n)->left) {
    rotateRight(g);
  }
  else if (n == parent(n)->right) {
    rotateLeft(g);
  }
  parent(n)->color = 1;//put an if parent not null "fixes". the problem
  n->color = 0;
  g->color = 0;*/
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
