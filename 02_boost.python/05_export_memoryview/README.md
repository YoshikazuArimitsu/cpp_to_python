# Boost.Python 組み込み(C++にPythonを埋め込む)

C++ で確保したバッファを Python から memoryview 経由でアクセスする。

```
$ g++ -o test main.cpp -lboost_python3 `python3.8-config --cflags --ldflags --embed`
$ ./test
```