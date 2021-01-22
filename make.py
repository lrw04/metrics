import json


def main():
    mk = open("Makefile", "w")
    tests = json.load(open("tests.json"))
    mk.write("CXX = c++\n")
    mk.write(f'CXXFLAGS = {" ".join(tests["cxxflags"])}\n')
    mk.write(f'LDFLAGS = {" ".join(tests["ldflags"])}\n')
    mk.write(
        """
result.tar: result.csv cxx.out os.out
\ttar cf result.tar result.csv *.out

"""
    )
    mk.write("result.csv: curate.py")
    for test in tests["tests"]:
        mk.write(" " + test["name"] + ".out")
    mk.write(
        """
\tpython curate.py > result.csv
cxx.out:
\t$(CXX) -v 2> cxx.out
os.out:
\tuname -mprsv > os.out
all: result.tar

"""
    )
    for src in tests["common"]:
        mk.write(f"{src}.o: {src}.cpp {src}.h\n\t$(CXX) $(CXXFLAGS) -c {src}.cpp\n")
    mk.write("\n")
    for test in tests["tests"]:
        name = test["name"]
        mk.write(f"{name}.out: {name}")
        if "input" in test.keys():
            mk.write(f' {test["input"]}')
        mk.write(f"\n\t./{name}")
        if "input" in test.keys():
            mk.write(f' < {test["input"]}')
        mk.write(f" > {name}.out\n")
    mk.write("\n")
    for test in tests["tests"]:
        name = test["name"]
        mk.write(f"{name}: {name}.cpp")
        for src in tests["common"]:
            mk.write(f" {src}.o")
        mk.write(f"\n\t$(CXX) $(CXXFLAGS) -c {name}.cpp")
        if "cxxflags" in test:
            mk.write(f" {' '.join(test['cxxflags'])}")
        mk.write("\n")
        mk.write(f"\t$(CXX) $(CXXFLAGS) -o {name} {name}.o")
        for src in tests["common"]:
            mk.write(f" {src}.o")
        mk.write(" $(LDFLAGS)\n")
    mk.write("\nclean:\n\trm -f -- result.csv *.o *.out")
    for test in tests["tests"]:
        mk.write(f' {test["name"]}')
    mk.write("\n.PHONY: clean all\n")
    mk.close()


if __name__ == "__main__":
    main()
