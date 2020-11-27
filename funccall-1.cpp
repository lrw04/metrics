#include <algorithm>
#include <cstdio>
#include <iostream>
#include <cinttypes>
#include <random>

#include "timer.h"
using namespace std;
using ll = long long;

const ll MO_P = 366 * 97 + 365 * 303, MP_A = 366 * 100 + 365 * 300;
const ll md[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
const ll delim =
    md[1] + md[2] + md[3] + md[4] + md[5] + md[6] + md[7] + md[8] + md[9] + 3;

bool extra_an(ll y) { return y % 4 == 0; }
bool extra_mo(ll y) { return y % 400 == 0 || (y % 4 == 0 && y % 100 != 0); }
bool is_extra(ll y) {
  if (y <= 1582) return extra_an(y);
  return extra_mo(y);
}
ll year_days(ll year) { return is_extra(year) ? 366 : 365; }
ll month_days(ll year, ll month) {
  if (month == 2) return md[month] + is_extra(year);
  return md[month];
}

struct Result {
  ll y, m, d;
  Result(ll y = 0, ll m = 0, ll d = 0) : y(y), m(m), d(d) {}
};

Result solve(ll tar) {
  ll year = -4712;
  {
    ll dy = tar / MP_A * 400;
    dy = min(dy, (1582ll + 4712) / 400 * 400);
    year += dy;
    tar -= dy / 400 * MP_A;
  }
  while (year < 1582 && tar >= year_days(year)) {
    tar -= year_days(year);
    year++;
  }
  if (year < 1582 || (year == 1582 && tar <= delim)) {
    ll m = 1, d = 1;
    while (tar >= month_days(year, m)) {
      tar -= month_days(year, m);
      m++;
      if (m == 13) {
        m = 1;
        year++;
      }
    }
    d += tar;
    return {year, m, d};
  }
  tar += 10;
  ll dy = tar / MO_P * 400;
  year += dy;
  tar -= dy / 400 * MO_P;
  while (tar >= year_days(year)) {
    tar -= year_days(year);
    year++;
  }
  ll m = 1, d = 1;
  while (tar >= month_days(year, m)) {
    tar -= month_days(year, m);
    m++;
    if (m == 13) {
      m = 1;
      year++;
    }
  }
  d += tar;
  return {year, m, d};
}

const int n = 1e6;
ll qs[n];
Result rs[n];
mt19937 rng;

int main() {
  uint32_t seed;
  cin >> seed;
  rng.seed(seed);
  for (int i = 0; i < n; i++) qs[i] = uniform_int_distribution<ll>(0, 1e18)(rng);

  Timer t;
  t.start();
  for (int i = 0; i < n; i++) rs[i] = solve(qs[i]);
  t.stop();

  cout << t.elapsed_ms() << endl;
  uint64_t ans = 0;
  for (int i = 0; i < n; i++) ans ^= rs[i].y * (i + 1) + rs[i].m * 233 + rs[i].d * 923;
  cout << ans << endl;
}
