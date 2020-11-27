#include <algorithm>
#include <cinttypes>
#include <iostream>
#include <random>

#include "timer.h"
using namespace std;

const int n = 1e6, q = n;
int a[n], b[n], qx[q], qy[q], ql[q], ans[q], c[3][3];
mt19937 rng;

int main() {
  uint32_t seed;
  cin >> seed;
  rng.seed(seed);

  for (int i = 0; i < n; i++) a[i] = uniform_int_distribution<int>(0, 2)(rng);
  for (int i = 0; i < n; i++) b[i] = uniform_int_distribution<int>(0, 2)(rng);
  for (int i = 0; i < q; i++) {
    qx[i] = uniform_int_distribution<int>(0, n - 1)(rng);
    qy[i] = uniform_int_distribution<int>(0, n - 1)(rng);
    ql[i] = uniform_int_distribution<int>(1, min(n - qx[i], n - qy[i]))(rng);
  }
  c[0][1] = c[1][2] = c[2][0] = 1;

  Timer t;
  t.start();
  for (int i = 0; i < q; i++) {
    int x = qx[i], y = qy[i], l = ql[i];
    ans[i] = 0;
    for (int j = 0; j < l; j++) ans[i] += c[a[x + j]][b[y + j]];
  }
  t.stop();

  cout << t.elapsed_ms() << endl;
  uint32_t dig = 0;
  for (uint32_t i = 0; i < q; i++) dig ^= (i + 1) * ans[i];
  cout << dig << endl;
}
