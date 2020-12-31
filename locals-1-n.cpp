#include <cinttypes>
#include <iostream>
#include <random>

#include "timer.h"
using namespace std;

const int n = 2e3;
const double V = 1e4;
double *a[n], *b[n], *c[n];
mt19937_64 rng;

int main() {
  a[0] = new double[n * n];
  b[0] = new double[n * n];
  c[0] = new double[n * n];
  for (int i = 1; i < n; i++) {
    a[i] = a[i - 1] + n;
    b[i] = b[i - 1] + n;
    c[i] = c[i - 1] + n;
  }

  uint64_t seed;
  cin >> seed;
  rng.seed(seed);
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      a[i][j] = uniform_real_distribution<double>(-V, V)(rng);
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      b[i][j] = uniform_real_distribution<double>(-V, V)(rng);
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++) c[i][j] = 0;

  Timer t;
  t.start();
  for (int j = 0; j < n; j++)
    for (int k = 0; k < n; k++)
      for (int i = 0; i < n; i++) c[i][j] += a[i][k] * b[k][j];
  t.stop();

  cout << t.elapsed_ms() << endl;
  double dig = 0;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++) dig += i * j * (i * n + j) * c[i][j];
  cout << dig << endl;

  delete[] a[0];
  delete[] b[0];
  delete[] c[0];
}
