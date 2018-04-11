/*Nicholas Rich 4/11/18
 *a red black tree
 */
#include <iostream>
#include <assert.h>

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

/*end of node stuff*/

/*insert stuff*/
void insertRe(node* root, node* n);
void insertRepairTree(node* n);
node* root;
node* insert(node* root, node* n) {
  insertRe(root, n);
  insertRepairTree(n);
  root = n;
  while (parent(root) != NULL) {
    root = parent(root);
  }
  return root;
}
/*end of the insert stuff*/

/*creating the prototypes*/
void rotateLeft(node* n);
void rotateRight(node* n);
void print(node* current, int depth);
/*end of the prototypes*/

int main () {
  node* n = new node(5);
  insert(root,n);
  root = n;
  node* b = new node(6);
  insert(root,b);
  node* c = new node(7);
  insert(root,c);
  print(n,0);
  return 0;
}

void rotateLeft(node* n) {
  node* nnew = n->right;
  assert(nnew != NULL);
  n->right = nnew->left;
  nnew->left = n;
  nnew->parent - n->parent;
  n->parent = nnew;
}

void rotateRight(node* n) {
  node* nnew = n->left;
  assert(nnew != NULL);
  n->left = nnew->right;
  nnew->right = n;
  nnew->parent = n->parent;
  n->parent = nnew;
}

void insertRe(node* root, node* n) {
  if (root != NULL && n->value < root->value) {
    if (root->left != NULL) {
      insertRe(root->left, n);
      return;
    }
    else {
      root->left = n;
    }
  }
  else if(root != NULL) {
    if (root->right != NULL) {
      insertRe(root->right, n);
      return;
    }
    else {
      root->right = n;
    }
    n->parent = root;
    n->left = NULL;
    n->right = NULL;
    n->color = 0;  
  }
}

void insertRepairTree(node* n) {
  if (parent(n) == NULL) {//case 1
       if (parent(n) == NULL) {
	n->color = 1;
      }
  }
  else if (parent(n)->color == 1) {//case 2
    return;
  }
  else if(uncle(n)->color == 0) {//case3
    parent(n)->color = 1;
    uncle(n)->color = 1;
    grandParent(n)->color = 0;
    insertRepairTree(grandParent(n));
    }
  else {//case 4
    node* p = parent(n);
    node* g = grandParent(n);
    if (n == g->left->right) {
      rotateLeft(n);
      n = n->left;
    }
    else if (n == g->right->left) {
      rotateRight(p);
      n = n->right;
    }
    p = parent(n);
    g = grandParent(n);
    if (n == p->left) {
      rotateRight(g);
    }
    else {
      rotateLeft(g);
      p->color = 1;
      g->color = 0;
    }
  }
}

void print(node* current, int depth) {
  if (current->right != NULL && (current->right != NULL)) {
      print(current->right, depth+1);
    }
    int tab = depth;
    for (tab; tab > 0; tab--) {
      cout << "\t";
    }
    cout << current->value << endl;
    if (current->right != NULL && (current->left != NULL)) {
      print(current->right, depth+1);      
    }
}
