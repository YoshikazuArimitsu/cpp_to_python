# Boost.Python HelloWorld

```
$ sudo apt install libboost-python-dev
```

```
$ g++ `python3.8-config --cflags` -DPIC -shared -fPIC -o hello.so hello.cpp -lboost_python3
$ python
Python 3.8.2 (default, Apr 27 2020, 15:56:08)
[GCC 7.5.0] on linux
Type "help", "copyright", "credits" or "license" for more information.
>>> import hello
>>> hello.hello()
'hello world'
```
