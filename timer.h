#ifndef TIMER_H
#define TIMER_H

#include <chrono>

class Timer {
  std::chrono::time_point<std::chrono::system_clock> t0, t1;

 public:
  void start();
  void stop();
  double elapsed_ms();
};

#endif
