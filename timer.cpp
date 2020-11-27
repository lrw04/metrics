#include "timer.h"

#include <chrono>
using namespace std;

void Timer::start() { t0 = chrono::system_clock::now(); }

void Timer::stop() { t1 = chrono::system_clock::now(); }

double Timer::elapsed_ms() {
  return chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();
}
