import json


def main():
    tests = json.load(open("tests.json"))
    results = []
    for test in tests['tests']:
        name = test['name']
        time = open(name + '.out').readline().strip()
        results.append((name, time))
    results.sort(key=lambda t : t[0])
    names = [t[0] for t in results]
    times = [t[1] for t in results]
    print(','.join(names))
    print(','.join(times))


if __name__ == "__main__":
    main()
