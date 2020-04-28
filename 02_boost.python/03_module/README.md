# Boost.Python 組み込み(C++にPythonを埋め込む)

C++ に Python module(.py) を import して呼び出す

```
$ g++ -o test main.cpp -lboost_python3 `python3.8-config --cflags --ldflags --embed`
$ ./test
```