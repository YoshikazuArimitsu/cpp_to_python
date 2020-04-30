# Boost.Python 組み込み(C++にPythonを埋め込む)

## 概要

C++ で確保したバッファを Python に渡し、Python から memoryview を使用してアクセスするサンプル

## 検証環境

Ubuntu 18.04
g++ 8.4.0
libboost-python1.65-dev
Python 3.8.2 (pyenv)

## コンパイル・実行方法

```
$ g++ -o test main.cpp -lboost_python3 `python3.8-config --cflags --ldflags --embed`

$ ./test
<class 'memoryview'>
length = 1048576
tobytes = <class 'bytes'>
mv[:32] = b'this is C++ memory\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00'
```

## 参考資料

[Python公式 他アプリケーションへの Python の埋め込み](https://docs.python.org/ja/3/extending/embedding.html)

[Boost.Pythonドキュメント(組み込みの章あたり)](http://alpha.osdn.jp/devel/boost.python_ja.pdf)


