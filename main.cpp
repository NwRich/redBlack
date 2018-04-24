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
  insertRe(root, n);
  insertRepairTree(n);
  root = n;
  while (parent(root) != NULL) {
    root = parent(root);
  }
  return root;
}

void insertRe(node* root, node* n) {
  if (n->value < root->value) {
    if (root->left != NULL) {
      insertRe(root->left, n);
      return;
    }
    else {
      root->left = n;
    }
  }
  else if(n->value >= root->value) {
    if (root->right != NULL) {
      insertRe(root->right, n);
      return;
    }
    else {
      root->right = n;
    }
  }
}

void insertRepairTree(node* n) {
  if (parent(n) == NULL) {//case 1
    n->color = 1;//set the color to black
  }
  else if (parent(n)->color == 0) {//if the color is red
    if (uncle(n) && uncle(n)->color == 0) {
      uncle(n)->color = 1;
      parent(n)->color = 1;
      grandParent(n)->color = 0;
      insertRepairTree(grandParent(n));
    }
    else {
      if (grandParent(n)->left && n == grandParent(n)->left->right) {
	rotateLeft(parent(n));
	n = n->left;
      }
      else if (grandParent(n)->right && n == grandParent(n)->right->left) {
	rotateRight(parent(n));
	n = n->right;
      }
      grandParent(n)->color= 0;
      parent(n)->color = 1;
      if (parent(n)->left == n) {
	rotateRight(grandParent(n));
      }
      else {
	rotateLeft(grandParent(n));
      }
    }
  }
}
 
void print(node* current, int depth) {
  if (current->right != NULL) {
    print(current->right, depth+1);
  }
  for (int i = 0; i < depth; i++) {
    cout << "\t";
  }
  cout << current->value;
  if (current->color == 0) {
    cout << " Red\n";
  }
  else {
    cout << " Black\n";
  }
  if (current->left != NULL) {
    print(current->left, depth+1);
  }
}
