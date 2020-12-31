#include <cstdio>
#include <iostream>

#include "timer.h"
using namespace std;
using ld = long double;

const int n = 1e8;

int main() {
  Timer t;
  t.start();
  ld ans = 0.61234567898765, j = 1, s = 0;
  for (int i = 1; i <= n; i++) s += (j *= ans);
  t.stop();
  cout << t.elapsed_ms() << endl;
  cout << s << endl;
}
