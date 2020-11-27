#include <algorithm>
#include <cinttypes>
#include <complex>
#include <iostream>
#define _USE_MATH_DEFINES
#include <cmath>
#include <random>

#include "timer.h"
using namespace std;
using cd = complex<double>;

const int n = 27;
const double V = 1e4;
cd *a;
mt19937_64 rng;
int r[1 << n];

void fft(int n, cd *a, int rank) {
  for (int i = 1; i < 1 << n; i++) r[i] = r[i >> 1] >> 1 | (i & 1 << (n - 1));
  for (int i = 0; i < 1 << n; i++)
    if (i < r[i]) swap(a[i], a[r[i]]);
  for (int k = 1; k < 1 << n; k *= 2) {
    cd omega(cos(rank * M_PI / k), sin(rank * M_PI / k));
    for (int i = 0; i < 1 << n; i += k * 2) {
      cd t = 1;
      for (int j = 0; j < k; j++, t *= omega) {
        auto x = a[i + j], y = a[i + j + k];
        a[i + j] = x + y;
        a[i + j + k] = x - y;
      }
    }
  }
}

int main() {
  a = new cd[1 << n];
  uint64_t seed;
  cin >> seed;
  rng.seed(seed);
  for (int i = 0; i < 1 << n; i++)
    a[i] = uniform_real_distribution<double>(-V, V)(rng);

  Timer t;
  t.start();
  fft(n, a, 1);
  t.stop();

  cout << t.elapsed_ms() << endl;
  double ans = 0;
  for (int i = 0; i < 1 << n; i++) ans += a[i].real() * (i + 2) / (i - 1);
  cout << ans << endl;
}
