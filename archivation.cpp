//
//  archivation.cpp
//  BUGArchive
//
//  Created on 13.07.15.
//  Copyright (c) 2015 Buggers. All rights reserved.
//

#include "archivation.h"
#include <queue>

using namespace std;
typedef unsigned char Byte;
typedef struct MyTree{
  Byte value;
  MyTree* left;
  MyTree* right;
} Tree;
typedef struct myTable{
  int count_bit;
  int bits;
} Table;

Table table[256];

void TravelTree(Tree* t, int code, int deep){
  if (t -> left == NULL || (*t).right == NULL){
    table[t -> value].bits = code;
    table[t -> value].count_bit = deep;
  }
  if (t -> left != NULL){

  }
}

vector <Byte> compress(vector <Byte> &input){
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

  for (Byte i = 0; i < 256; i++){
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



}
