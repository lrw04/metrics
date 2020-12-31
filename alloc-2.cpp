#include <algorithm>
#include <cinttypes>
#include <cstdio>
#include <iostream>
#include <random>
#include <vector>

#include "timer.h"
using namespace std;

class Splay {
  struct Node {
    int size, val;
    bool rev;
    Node *fa, *ch[2];
  };
  Node *root;
  int tch(Node *);
  void push_up(Node *);
  void push_down(Node *);
  Node *build(int, int, Node *);
  void rotate(Node *);
  void stretch(Node *, Node *);
  Node *at(int);
  void write(Node *, vector<int> &);

 public:
  Splay(int n) { root = build(0, n + 1, nullptr); }
  void reverse(int l, int r) {
    Node *ln = at(l), *rn = at(r + 2);
    stretch(ln, nullptr);
    stretch(rn, ln);
    root->ch[1]->ch[0]->rev ^= 1;
  }
  void write(vector<int> &ans) { write(root, ans); }
};

int Splay::tch(Node *u) { return u == u->fa->ch[1] ? 1 : 0; }

void Splay::push_up(Node *u) {
  if (!u) return;
  u->size = 1;
  for (int i = 0; i < 2; i++)
    if (u->ch[i]) u->size += u->ch[i]->size;
}

void Splay::push_down(Node *u) {
  if (!u) return;
  if (u->rev) {
    for (int i = 0; i < 2; i++)
      if (u->ch[i]) u->ch[i]->rev ^= 1;
    swap(u->ch[0], u->ch[1]);
    u->rev = false;
  }
}

Splay::Node *Splay::build(int l, int r, Node *fa) {
  if (l > r) return nullptr;
  Node *u = new Node;
  int mid = (l + r) / 2;
  u->fa = fa;
  u->val = mid;
  u->ch[0] = build(l, mid - 1, u);
  u->ch[1] = build(mid + 1, r, u);
  push_up(u);
  return u;
}

void Splay::rotate(Node *u) {
  Node *f = u->fa, *ff = f->fa;
  push_down(u);
  push_down(f);
  int t = tch(u);
  f->ch[t] = u->ch[t ^ 1];
  if (f->ch[t]) f->ch[t]->fa = f;
  u->ch[t ^ 1] = f;
  if (ff) ff->ch[tch(f)] = u;
  f->fa = u;
  u->fa = ff;
  push_up(f);
  push_up(u);
}

void Splay::stretch(Node *u, Node *goal) {
  while (u->fa != goal) {
    Node *f = u->fa, *ff = f->fa;
    if (ff != goal) {
      if (tch(f) ^ tch(u)) {
        rotate(u);
      } else {
        rotate(f);
      }
    }
    rotate(u);
  }
  if (!goal) root = u;
}

Splay::Node *Splay::at(int rank) {
  Node *u = root;
  while (true) {
    push_down(u);
    if (u->ch[0]) {
      if (u->ch[0]->size >= rank)
        u = u->ch[0];
      else if (u->ch[0]->size + 1 == rank)
        return u;
      else {
        rank -= u->ch[0]->size + 1;
        u = u->ch[1];
      }
    } else {
      if (rank == 1)
        return u;
      else {
        rank--;
        u = u->ch[1];
      }
    }
  }
}

void Splay::write(Node *u, vector<int> &ans) {
  push_down(u);
  if (u->ch[0]) write(u->ch[0], ans);
  ans.push_back(u->val);
  if (u->ch[1]) write(u->ch[1], ans);
}

const int n = 2e6, m = n;
int *ql, *qr;
mt19937_64 rng;

int main() {
  ql = new int[m];
  qr = new int[m];

  uint64_t seed;
  cin >> seed;
  rng.seed(seed);
  for (int i = 0; i < m; i++) {
    ql[i] = uniform_int_distribution<int>(1, n)(rng);
    qr[i] = uniform_int_distribution<int>(1, n)(rng);
    if (ql[i] > qr[i]) swap(ql[i], qr[i]);
  }

  Timer timer;
  timer.start();
  Splay t(n);
  for (int i = 0; i < m; i++) t.reverse(ql[i], qr[i]);
  vector<int> ans;
  t.write(ans);
  timer.stop();

  cout << timer.elapsed_ms() << endl;
  uint64_t dig = 0;
  for (int i = 1; i <= n; i++) dig ^= i * ans[i];
  cout << dig << endl;
  delete[] ql;
  delete[] qr;
}
