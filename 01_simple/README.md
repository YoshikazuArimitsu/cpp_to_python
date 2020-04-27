# 

https://docs.python.org/ja/3/extending/embedding.html

公式にある高水準埋め込みを利用して C++ から Python を利用する例。

```
 $ g++ -o simple main.cpp  `python3.8-config --cflags --ldflags --embed`
 $ ./simple test.py
```

```
 # Anaconda環境の場合、Anaconda提供のコンパイラを使わないとダメ
 $ conda install gxx_impl_linux-64
 $ x86_64-conda_cos6-linux-gnu-g++ -o simple main.cpp  `python3.6-config --cflags --ldflags`
```

コンパイル通っても PYTHONHOME 絡みのエラーが出る模様。やっぱり Anaconda は糞。
pyenv で python ごと別環境作ってしまえば↑の方法でいける。
