# Boost.Python 組み込み(C++にPythonを埋め込む)

```
$ g++ -o write_hello write_hello.cpp -lboost_python3 `python3.8-config --cflags --ldflags --embed`
$ ./write_hello
```