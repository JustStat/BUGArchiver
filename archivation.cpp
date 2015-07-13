#include <iostream>
#include "archivation.h"
#include <queue>

using namespace std;
typedef unsigned char Byte;
typedef struct MyTree{
  Byte value;
  MyTree* left;
  MyTree* right;
} Tree;
typedef struct myField{
  int count_bit;
  int bits;
} Field;

Field table[256];

void TravelTree(Tree* t, int code, int deep){
  if (t -> left == NULL || t -> right == NULL){
    table[t -> value].bits = code;
    table[t -> value].count_bit = deep;
  }
  if (t -> left != NULL){
    TravelTree(t -> left, code | (1 << deep), deep + 1);
    TravelTree(t -> right, code, deep + 1);
  }
}

vector <Byte> compress(vector <Byte>& input){
  vector <Byte> res;
  int Chance[256];
  for (int i = 0; i < 256; i++){
    Chance[i] = 0;
  }
  pair <Tree*, int> t1, t2, t;

  for (int i = 0; i < input.size(); i++){
    Chance[input[i]]++;
  }
  priority_queue < pair<Tree*, int> > heap;

  for (int i = 0; i < 256; i++){
    if (Chance[i] != 0){
      t.first = new Tree;
      t.first -> right = NULL;
      t.first -> right = NULL;
      t.first -> left = NULL;
      t.first -> value = i;
      t.second = Chance[i];
      heap.push(t);
    }
  }

  while (heap.size() > 1){
    t1 = heap.top();
    heap.pop();
    t2 = heap.top();
    heap.pop();
    t.second = t1.second + t2.second;
    t.first = new Tree;
    t.first -> left = t1.first;
    t.first -> right = t2.first;
    heap.push(t);
  }
  t = heap.top();
  heap.pop();

  for (int i = 0; i < 256; i++){
    res.push_back(table[i].count_bit);
    res.push_back(table[i].bits);
  }
  TravelTree(t.first, 0, 0);
  Field f;
  int k = 0, m = 0;
  for (int i = 0; i < input.size(); i++){
    f = table[input[i]];
    res.push_back(0);
    for (int j = 0; j < f.count_bit; j++){
      if (k == 8){
        k = 0;
        res.push_back(0);
      }
      if (f.bits & (1 << j) != 0){
        m = res.back();
        m = m | (1 << k);
        res.pop_back();
        res.push_back(m);
        k++;
      }
    }
  }
  return res;
}
