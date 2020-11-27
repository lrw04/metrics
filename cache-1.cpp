#include <cassert>
#include <cinttypes>
#include <iostream>
#include <random>

#include "timer.h"
using namespace std;

const int n = 5e8;
uint32_t *a, *b;
mt19937_64 rng;
int sum0[256], sum1[256], sum2[256], sum3[256];

int main() {
  a = new uint32_t[n];
  b = new uint32_t[n];
  uint64_t seed;
  cin >> seed;
  rng.seed(seed);
  for (int i = 0; i < n; i++) a[i] = uniform_int_distribution<uint32_t>()(rng);
  for (int i = 0; i < 256; i++) sum0[i] = sum1[i] = sum2[i] = sum3[i] = 0;

  Timer t;
  t.start();

  for (int i = 0; i < n; i++) {
    sum0[a[i] >> 0 & 255]++;
    sum1[a[i] >> 8 & 255]++;
    sum2[a[i] >> 16 & 255]++;
    sum3[a[i] >> 24 & 255]++;
  }
  for (int i = 1; i < 256; i++) sum0[i] += sum0[i - 1];
  for (int i = 1; i < 256; i++) sum1[i] += sum1[i - 1];
  for (int i = 1; i < 256; i++) sum2[i] += sum2[i - 1];
  for (int i = 1; i < 256; i++) sum3[i] += sum3[i - 1];
  for (int i = n - 1; i >= 0; i--) b[--sum0[a[i] >> 0 & 255]] = a[i];
  for (int i = n - 1; i >= 0; i--) a[--sum1[b[i] >> 8 & 255]] = b[i];
  for (int i = n - 1; i >= 0; i--) b[--sum2[a[i] >> 16 & 255]] = a[i];
  for (int i = n - 1; i >= 0; i--) a[--sum3[b[i] >> 24 & 255]] = b[i];
  t.stop();

  for (int i = 1; i < n; i++) assert(a[i - 1] <= a[i]);
  cout << t.elapsed_ms() << endl;
  uint32_t dig = 0;
  for (uint32_t i = 0; i < n; i++) dig ^= (i + 1) * a[i];
  cout << dig << endl;
  delete[] a;
  delete[] b;
}
