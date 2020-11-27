#include <cstdio>
#include <iostream>

#include "timer.h"
using namespace std;
using ll = long long;

const int P = 1e9, n = 1e9 - 1e4;

int main() {
  Timer t;
  t.start();
  ll ans = 1;
  for (int i = 1; i <= n; i++) ans = ans * i % P;
  t.stop();
  cout << t.elapsed_ms() << endl;
  cout << ans << endl;
  return 0;
}
