#include <cassert>
#include <cinttypes>
#include <iostream>
#include <random>

#include "timer.h"
using namespace std;

const int n = 5e8;
uint32_t *a, *b;
mt19937_64 rng;
int sum0[65536], sum1[65536];

int main() {
  a = new uint32_t[n];
  b = new uint32_t[n];
  uint64_t seed;
  cin >> seed;
  rng.seed(seed);
  for (int i = 0; i < n; i++) a[i] = uniform_int_distribution<uint32_t>()(rng);
  for (int i = 0; i < 256; i++) sum0[i] = sum1[i] = 0;

  Timer t;
  t.start();

  for (int i = 0; i < n; i++) {
    sum0[a[i] >> 0 & 65535]++;
    sum1[a[i] >> 16 & 65535]++;
  }
  for (int i = 1; i < 65536; i++) sum0[i] += sum0[i - 1];
  for (int i = 1; i < 65536; i++) sum1[i] += sum1[i - 1];
  for (int i = n - 1; i >= 0; i--) b[--sum0[a[i] >> 0 & 65535]] = a[i];
  for (int i = n - 1; i >= 0; i--) a[--sum1[b[i] >> 16 & 65535]] = b[i];
  t.stop();

  for (int i = 1; i < n; i++) assert(a[i - 1] <= a[i]);
  cout << t.elapsed_ms() << endl;
  uint32_t dig = 0;
  for (uint32_t i = 0; i < n; i++) dig ^= (i + 1) * a[i];
  cout << dig << endl;
  delete[] a;
  delete[] b;
}
