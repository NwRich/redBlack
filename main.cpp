#include <iostream>

using namespace std;
struct node {
  node* left = NULL;
  node* right = NULL;
  node* parent = NULL;
  int color = 0;//0 is red 1 is black
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
node* insert(node* root, node* n) {
  insertRe(root, n);
  //insert repair tree(n)
  root = n;
  while (parent(root) != NULL) {
    root = parent(root);
  }
  return root;
}
void rotateLeft(node* n);//might have to fill these out
void rotateRight(node* n);

int main () {

  return 0;
}


void insertRe(node* root, node* n) {
  if (root != NULL && n->/*key??*/ < root->/*key??*/) {
    if (root->left != /*LEAF??*/) {
      insertRe(root->left, n);
      return;
    }
    else {
      root->left = n;
    }
    else if(root != NULL) {
      if (root->right != /*LEAF??*/) {
	insertRe(root->right, n);
	return;
      }
      else {
	root->right = n;
      }
    }
  }
}
# redBlack
