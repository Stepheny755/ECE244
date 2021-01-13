#include <iostream>

using namespace std;

class ListNode{
public:
  int key;
  ListNode* next;
};

void rotate(ListNode* h){

  if(h == NULL) return;

  int headval = h->key;

  while(h->next!=NULL){

  h->key = h->next->key;

  h = h->next;

  }

  h->key = headval;

}

class Novel{
public:
  Novel();
  virtual void print() const=0;
};

Novel::Novel(){

}

void Novel::print() const{
  cout<<"hehexd" << endl;
}

void bidirtraverse(ListNode* h){

  if(h == NULL){
    return;
  }
  cout << h->key << " ";
  bidirtraverse(h->next);
  cout << h->key << " ";

}

int main(){
  ListNode* head;
  head->key = 20;
  head->next = new ListNode;
  head->next->key = 10;
  head->next->next = new ListNode;
  head->next->next->key = 8;

  ListNode* tptr = head;

  while(tptr!=NULL){
    cout << tptr->key << endl;
    tptr = tptr->next;
  }

  rotate(head);

  bidirtraverse(head);

  Novel n;

  return 0;
}
