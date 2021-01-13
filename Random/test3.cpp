#include <iostream>

using namespace std;

class BSTNode{
public:
  int val;
  BSTNode* left;
  BSTNode* right;

  int getKey(){ return val; }
  BSTNode* getLeft(){return left;}
  BSTNode* getRight(){return right;}
  void setLeft(BSTNode* a){left=a;}
  void setRight(BSTNode* a){right=a;}
  BSTNode(int v);
  void insert(BSTNode* root,BSTNode* p);
  void insert_bst(BSTNode* p,BSTNode* r);
};

void BSTNode::insert(BSTNode* root,BSTNode* p) {
  if (p == NULL) return; // Nothing to insert
    if (root == NULL) { // basis
    root = p;
    root->setLeft (NULL);
    root->setRight(NULL);
    return;
    }
  // Helper function to facilitate the recursion
  insert_bst(p, root);
}

void BSTNode::insert_bst(BSTNode* p,BSTNode* r){
if (p->getKey() == r->getKey()) return;
if (p->getKey() < r->getKey()) {
if (r->getLeft() == NULL) {
r->setLeft(p);
return;
}
else insert_bst(p, r->getLeft());
}
if (p->getKey() > r->getKey()) {
if (r->getRight() == NULL) {
r->setRight(p);
return;
}
else insert_bst(p, r->getRight());
}
}

BSTNode::BSTNode(int v){
  val = v;
  left = NULL;
  right = NULL;
}

bool printInRange(BSTNode root,int lowerBound,int upperBound){
  if (root.val <= lowerBound||root.val >= upperBound){
    return false;
  }else{
    printInRange(*(root.left),lowerBound,upperBound);
    cout << root.val << " ";
    printInRange(*(root.right),lowerBound,upperBound);
  }
  return false;
}

int main(){
  BSTNode *root = NULL;
  root->insert(root,new BSTNode(6));
  cout << root << endl;

  printInRange(*root,5,13);
}
