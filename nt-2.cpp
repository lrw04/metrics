#include <cstdio>
#include <iostream>

#include "timer.h"
using namespace std;
using ll = long long;

const int n = 5e8, mp = 6e7;
ll p[mp], m[n];
int pc;

int main() {
  Timer t;
  t.start();
  for (ll i = 2; i < n; i++) {
    if (!m[i]) p[pc++] = m[i] = i;
    for (int j = 0; j < pc; j++) {
      if (m[i] < p[j] || p[j] > (n - 1) / i) break;
      m[i * p[j]] = p[j];
    }
  }
  t.stop();
  cout << t.elapsed_ms() << endl;
  ll ans = 0;
  for (int i = 0; i < pc; i++) ans ^= p[i] * (i + 1);
  cout << ans << endl;
  return 0;
}
