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
    if (deep == 0){
      deep++;
    }
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
    for (int j = i; SimilFields(a[j], a[j - 1]) > 0 && j > 0; j--){
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
  priority_queue < pair<long, Tree*> > q;
  for (int i = 0; i < 256; i++){
    if (chance[i] != 0){
      t = new Tree;
      (t -> value) = i;
      (t -> left) = NULL;
      (t -> right) = NULL;
      q.push(make_pair(-chance[i], t));
    }
  }
  int sum = 0;
  while (q.size() > 1){
    sum = 0;
    t = new Tree;
    (t -> left) = q.top().second;
    sum += q.top().first;
    q.pop();
    (t -> right) = q.top().second;
    sum += q.top().first;
    q.pop();
    q.push(make_pair(sum, t));
  }
  t = q.top().second;
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
    last_code = last_code << (c - last_c);
    last_c = c;
    table[j].bits = last_code;
  }
  for (int i = 0; i < 256; i++){
    out_buf.push_back(table[i].count_bit);
  }
  int k = 0;
  Byte cur = 0;
  for (int i = 0; i < in_buf.size(); i++){
    Byte c = in_buf[i];
    for (int j = table[c].count_bit - 1; j >= 0; j--){
      cur = cur | ((((table[c].bits & (1 << j)) != 0) ? 1 : 0) << k);
      k++;
      if (k > 7){
        k = 0;
        out_buf.push_back(cur);
        cur = 0;
      }
    }
  }
  if (k != 0){
    out_buf.push_back(cur);
  }
}

Tree* GetTree(){
  Tree* t = new Tree;
  t -> left = NULL;
  t -> right = NULL;
  return t;
}

bool de_comress1(vector<Byte> in_buf, vector<Byte> &out_buf, long long buf_len){
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
  Tree* t = GetTree(), *curt;
  long long lb = 0;
  int lc = 1;
  alfabat[0].bits = 0;
  for (int i = 1; i < alfabat.size(); i++){
    lb++;
    lb = lb << (alfabat[i].count_bit - lc);
    alfabat[i].bits = lb;
    lc = alfabat[i].count_bit;
  }
  for (int i = 0; i < alfabat.size(); i++){
    curt = t;
    for (int j = alfabat[i].count_bit - 1; j >= 0; j--){
      if ((alfabat[i].bits & (1 << j)) != 0){
        if (curt -> left == NULL){
          curt -> left = GetTree();
        }
        curt = curt -> left;
      }
      else{
        if (curt -> right == NULL){
          curt -> right = GetTree();
        }
        curt = curt -> right;
      }
    }
    curt -> value = alfabat[i].value;
  }
  Byte curb;
  curt = t;
  int readed_bytes = 0;
  int siz = in_buf.size();
  for (int i = 256; i < in_buf.size() && readed_bytes < buf_len; i++){
    curb = in_buf[i];
    for (int j = 0; j < 8 && readed_bytes < buf_len; j++){
      if ((curb & (1 << j)) != 0){
        curt = curt -> left;
      }
      else{
        curt = curt -> right;
      }
      if (curt -> left == NULL && curt -> right == NULL){
        out_buf.push_back(curt -> value);
        curt = t;
        readed_bytes++;
      }
    }
  }
}
