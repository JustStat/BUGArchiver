#include <iostream>
#include <cstdlib>
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
  Byte value;
  int count_bit;
  long long bits;
} Field;


Field table[256];

void TravelTree(Tree* t, int deep){
  if (t -> left == NULL || t -> right == NULL){
    table[t -> value].value = (t -> value);
    table[t -> value].count_bit = deep;
  }
  if (t -> left != NULL){
    TravelTree(t -> left, deep + 1);
    TravelTree(t -> right, deep + 1);
  }
}

void FreeTree(Tree* t){
  if (t -> left != NULL){
    FreeTree(t -> left);
  }
  if (t -> right != NULL){
    FreeTree(t -> right);
  }
  delete t;
}

int SimilFields(const Field& f1, const Field& f2){
  if ((f1.count_bit) > f2.count_bit){
    return -1;
  }
  else{
    return (f1.count_bit == f2.count_bit && f1.value > f2.value) ? -1 : 1;
  }
}

void Sort(vector <Field>& a){
  for (int i = 0; i < a.size(); i++){
    for (int j = i; SimilFields(a[j], a[j - 1]) > 1 && j > 0; j--){
      Field c = a[j];
      a[j] = a[j - 1];
      a[j - 1] = c;
    }
  }
}

bool compress(vector <Byte>& in_buf, vector <Byte>& out_buf){
  int chance[256];
  Tree* t, t1, t2;
  for (int i = 0; i < 256; i++){
    chance[i] = 0;
  }
  for (int i = 0; i < in_buf.size(); i++){
    chance[in_buf[i]]++;
  }
  priority_queue < pair<Tree*, int> > q;
  for (int i = 0; i < 256; i++){
    if (chance[i] != 0){
      t = new Tree;
      (t -> value) = i;
      (t -> left) = NULL;
      (t -> right) = NULL;
      q.push(make_pair(t, -chance[i]));
    }
  }
  int sum = 0;
  while (q.size() > 1){
    sum = 0;
    t = new Tree;
    (t -> left) = q.top().first;
    sum += q.top().second;
    (t -> right) = q.top().first;
    sum += q.top().second;
    q.push(make_pair(t, sum));
  }
  t = q.top().first;
  TravelTree(t, 0);
  FreeTree(t);
  vector < Field > len;
  for (int i = 0; i < 256; i++){
    if (chance[i] != 0){
      len.push_back(table[i]);
    }
  }
  Sort(len);
  long long last_code = 0;
  int last_c = len[0].count_bit;
  len[0].bits = 0;
  for (int i = 1; i < len.size(); i++){
    int j = len[i].value;
    int c = len[i].count_bit;
    last_code++;
    if (last_c != c){
      last_code = last_code << 1;
    }
    table[j].bits = last_code;
  }
  for (int i = 0; i < 256; i++){
    out_buf.push_back(table[i].count_bit);
  }
  int k = 0;
  Byte cur = 0;
  for (int i = 0; i < in_buf.size(); i++){
    Byte c = in_buf[i];
    for (int j = 0; j < table[c].count_bit; j++){
      if (k > 7){
        k = 0;
        out_buf.push_back(cur);
        cur = 0;
      }
      cur |= ((table[c].bits & (1 << j) != 0) ? 1 : 0 << j);
      k++;
    }
  }
}

bool de_comress1(vector<Byte> in_buff, vector<Byte> &out_buff, int buff_len){
  vector < Field > alfabat;
  Field f;
  for (int i = 0; i < 256; i++){
    if (in_buf[i] != 0){
      f.value = i;
      f.count_bit = in_buf[i];
      alfabat.push_back(f);
    }
  }
  Sort(alfabat);
  long long lb = 0;
  int lc = 0;
  alfabat[0].bits = 0;
  for (int i = 1; i < alfabat.size(); i++){
    lb++
    if (lc != alfabat[i].count_bit){
      lb = lb << 1;
    }
    alfabat[i].bits = lb;
  }
}
