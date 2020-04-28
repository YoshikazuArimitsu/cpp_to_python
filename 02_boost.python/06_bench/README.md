# File vs MemoryView

1. C++側で 1m のバッファを作成
2. ファイル or MemoryView で Python に渡す
3. Python 側で全データにアクセス

を繰り返してパフォーマンスを取得するサンプル

```
$ g++ -o bench main.cpp -lboost_python3 `python3.8-config --cflags --ldflags --embed`
$ ./bench file|memory

```

### EC2 t2-medium

```
$ ./bench file
bench file
..........
elapsed 15368msec

$ ./bench memory
bench memoryview
..........
elapsed 945msec
```

