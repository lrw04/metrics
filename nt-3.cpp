#include <cinttypes>
#include <iostream>
#include <random>

#include "timer.h"
using namespace std;
using ll = long long;

const int n = 27, P = 998'244'353, G = 3;
ll *a;
mt19937_64 rng;
int *r;

ll qpow(ll base, ll exp) {
  exp = (exp + P - 1) % (P - 1);
  ll ans = 1;
  while (exp) {
    if (exp % 2) ans = ans * base % P;
    base = base * base % P;
    exp /= 2;
  }
  return ans;
}

void ntt(int n, ll *a, int rank) {
  r[0] = 0;
  for (int i = 1; i < 1 << n; i++) r[i] = r[i >> 1] >> 1 | (i & 1 << (n - 1));
  for (int i = 0; i < 1 << n; i++)
    if (i < r[i]) swap(a[i], a[r[i]]);
  for (int k = 1; k < 1 << n; k *= 2) {
    ll omega = qpow(G, (P - 1) / (k * 2) * rank);
    for (int i = 0; i < 1 << n; i += k * 2) {
      ll t = 1;
      for (int j = 0; j < k; j++, t = t * omega % P) {
        ll x = a[i + j], y = a[i + j + k];
        a[i + j] = (x + y) % P;
        a[i + j + k] = (x - y + P) % P;
      }
    }
  }
}

int main() {
  a = new ll[1 << n];
  r = new int[1 << n];

  uint64_t seed;
  cin >> seed;
  rng.seed(seed);
  for (int i = 0; i < 1 << n; i++)
    a[i] = uniform_int_distribution<ll>(0, P - 1)(rng);

  Timer t;
  t.start();
  ntt(n, a, 1);
  t.stop();

  cout << t.elapsed_ms() << endl;
  uint64_t ans = 0;
  for (uint64_t i = 0; i < 1 << n; i++) ans ^= (i + 1) * a[i];
  cout << ans << endl;
  delete[] a;
  delete[] r;
}
