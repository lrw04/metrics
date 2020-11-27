# metrics

metrics is a benchmark suite for single-threaded performance.

## Requirements

- Make
- C++ compiler at `c++` supporting C++17
- Python 3.7+
- 4GiB+ RAM for `cache-1`

## Instructions

```
$ python make.py
$ make
```

`result.csv` then contains times for tested items, with `cxx.out` containing C++ compiler version info and `os.out` containing OS info. `result.tar` contains times and outputs for verification of correctness.
