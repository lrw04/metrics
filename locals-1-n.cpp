#include <cinttypes>
#include <iostream>
#include <random>

#include "timer.h"
using namespace std;

const int n = 2e3;
const double V = 1e4;
double a[n][n], b[n][n], c[n][n];
mt19937_64 rng;

int main() {
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
}
