#include <random>
#include <cinttypes>
#include <iostream>

#include "timer.h"
using namespace std;

class ST {
  struct Node {
    int l, r, len;
    uint64_t sum, tag;
    Node *c[2];
    Node(int, int);
    void push_up();
    void push_down();
    void add(int, int, uint64_t);
    uint64_t qsum(int, int);
  };
  Node *root;

public:
  ST(int n) { root = new Node(0, n - 1); }
  void add(int l, int r, uint64_t val) { root->add(l, r, val); }
  uint64_t sum(int l, int r) { return root->qsum(l, r); }
};

ST::Node::Node(int _l, int _r) {
  l = _l;
  r = _r;
  len = r - l + 1;
  tag = 0;
  if (l == r) {
    c[0] = c[1] = nullptr;
    sum = 0;
    return;
  }
  int mid = (l + r) / 2;
  c[0] = new Node(l, mid);
  c[1] = new Node(mid + 1, r);
  push_up();
}

void ST::Node::push_up() { sum = c[0]->sum + c[1]->sum; }
void ST::Node::push_down() {
  if (!tag) return;
  c[0]->sum += c[0]->len * tag;
  c[1]->sum += c[1]->len * tag;
  c[0]->tag += tag;
  c[1]->tag += tag;
  tag = 0;
}

void ST::Node::add(int ql, int qr, uint64_t val) {
  if (r < ql || qr < l) return;
  if (ql <= l && r <= qr) {
    sum += len * val;
    tag += val;
    return;
  }
  push_down();
  c[0]->add(ql, qr, val);
  c[1]->add(ql, qr, val);
  push_up();
}

uint64_t ST::Node::qsum(int ql, int qr) {
  if (r < ql || qr < l) return 0;
  if (ql <= l && r <= qr) return sum;
  push_down();
  return c[0]->qsum(ql, qr) + c[1]->qsum(ql, qr);
}

const int n = 5e6, q = n;
int *typ, *ql, *qr;
uint64_t *val, *ans;
mt19937_64 rng;

int main() {
  typ = new int[q];
  ql = new int[q];
  qr = new int[q];
  val = new uint64_t[q];
  ans = new uint64_t[q];

  uint64_t seed;
  cin >> seed;
  rng.seed(seed);
  for (int i = 0; i < q; i++) {
    typ[i] = uniform_int_distribution<int>(0, 1)(rng);
    ql[i] = uniform_int_distribution<int>(0, n - 1)(rng);
    qr[i] = uniform_int_distribution<int>(0, n - 1)(rng);
    val[i] = uniform_int_distribution<uint64_t>()(rng);
    if (ql[i] > qr[i]) swap(ql[i], qr[i]);
    if (!typ[i]) ans[i] = 0;
  }

  Timer t;
  t.start();
  ST tr(n);
  for (int i = 0; i < q; i++) {
    if (typ[i]) ans[i] = tr.sum(ql[i], qr[i]);
    else tr.add(ql[i], qr[i], val[i]);
  }
  t.stop();

  cout << t.elapsed_ms() << endl;
  uint64_t dig = 0;
  for (uint64_t i = 0; i < q; i++) dig ^= (i + 1) * ans[i];
  cout << dig << endl;

  delete[] typ;
  delete[] ql;
  delete[] qr;
  delete[] val;
  delete[] ans;
}
