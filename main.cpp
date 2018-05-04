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
  int color = 0;
  int value = 0;
};

node* parent(node* n) {
  return n->parent;
  }
node* grandParent(node* n) {
  node* p = parent(n);
  if (p == NULL) {
    return NULL;
  }
  else {
    return p->parent;
  }
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

node* root = new node();
void insertRe(node* root, node* n);
void insertRepairTree(node* n);
node* insert(node* root, node* n);
void rotateLeft(node* n);
void rotateRight(node* n);
void print(node* current, int depth);
void insertCase1(node* n);
void insertCase2(node* n);
void insertCase3(node* n);
void insertCase41(node* n);
void insertCase42(node* n);

int main () {
  node* n = new node();
  n->value = 1;
  insert(root,n);
  node* b = new node();
  b->value = 2;
  insert(root,b);
  node* c = new node();
  c->value = 13;
  insert(root,c);
  node* d = new node();
  d->value = 24;
  insert(root,d);
  print(n,0);
  return 0;
}

void rotateLeft(node* n) {
  node* r = n->right;
  if (r != NULL) {
    n->right = r->left;
    r->left = n;
    r->parent = n->parent;
    n->parent = r;
    if (r->parent != NULL && r->parent->left == n) {
      r->parent->left = r;
    }
    else if (r->parent != NULL && r->parent->right == n) {
      r->parent->right = r;
    }
    if (n == root) {
      root = r;
      root->color = 1;
    }
  }
}

void rotateRight(node* n) {
  node* l = n->left;
  if (l != NULL) {
    if (n->parent != NULL && n == n->parent->left) {
      n->parent->left = n->left;
    }
    else if (n->parent != NULL && n == n->parent->right) {
      n->parent->right = n->left;
    }
    n->left = l->right;
    if (l->right != NULL) {
      l->right->parent = n;
    }
    l->right = n;
    l->parent = n->parent;
    n->parent = l;
    if (n == root) {
      root = l;
      root->color = 1;
    }
  }
}

node* insert(node* root, node* n) {
  insertRe(root, n);//call insert recusivley to put the node in place
  insertRepairTree(n);//repair the tree passing in the new node
}

void insertRe(node* root, node* n) {
  if (root->value == -1) {
    root->value = n->value;
      }
  else if (n->value < root->value) {//if the input is less than the root
    if (root->left != NULL) {//and the left root is not empty
      insertRe(root->left, n);//go left and call insertRe again
      return;//end
    }
    else {//otherwise
      root->left = n;//set left to be the input
      n->parent = root;
    }
  }
  else if(n->value >= root->value) {//if the input is greater than or equal to the root
    if (root->right != NULL) {//and the right root is not empty
      insertRe(root->right, n);//go down the tree to the right
      return;//end
    }
    else {//otherwise
      root->right = n;//set the right root as input
      n->parent = root;
    }
  }
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
    insertCase41(n);
  }
}

void insertCase1(node* n) {
  if (parent(n) == NULL) {
    n->color = 1;
  }
}

void insertCase2(node* n) {
  cout << "case 2" << endl;
  return;
}

void insertCase3(node* n) {
  parent(n)->color = 1;
  uncle(n)->color = 1;
  grandParent(n)->color = 0;
  insertRepairTree(grandParent(n));
}

void insertCase41(node* n) {
  node* p = n->parent;
  node* g = grandParent(n);
  if (g != NULL && g->left != NULL && g->left->right != NULL) {
    if (n == g->left->right) {
      rotateLeft(p);
      n = n->left;
    }
    else if (g != NULL && g->right != NULL && g->right->left != NULL) {
      if (n == g->right->left) {
	rotateRight(p);
	n = n->right;
      }
    }
  }
  if (grandParent(n) != NULL) {
  insertCase42(n);
  }
}

void insertCase42(node* n) {
  node* p = parent(n);
  node* g = grandParent(n);
  if (p->left != NULL && n == p->left) {
    rotateRight(g);
  }
  else {
    rotateLeft(g);
  }
  p->color = 1;
  g->color = 0;
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
