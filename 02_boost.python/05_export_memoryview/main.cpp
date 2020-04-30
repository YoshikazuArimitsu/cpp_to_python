#include <iostream>
#include <fstream>
#include <boost/python.hpp>

using namespace boost::python;
using namespace boost::python::api;

// Pythonに見せるバッファ
namespace
{
char *c_buffer;
unsigned long c_bufferSize;
} // namespace

class Buffer
{
public:
    Buffer()
    {
    }

    object memoryView()
    {
        // グローバルに取った c_buffer, c_bufferSize から memoryview を作って返す。
        boost::python::handle<> handle(PyMemoryView_FromMemory(c_buffer, c_bufferSize, PyBUF_READ));
        return boost::python::object(handle);
    }
};

// PythonにBufferクラスをラップした Pythonクラスを見せる
BOOST_PYTHON_MODULE(buffer)
{
    class_<Buffer>("Buffer", init<>())
        .def("memoryview", &Buffer::memoryView);
}

int main(int argc, char **argv)
{
    // Python初期化
    Py_Initialize();
    object main_module = import("__main__");
    object main_namespace = main_module.attr("__dict__");

    try
    {
        // メインモジュール内に dump.py を読み込む
        exec_file("./dump.py", main_namespace, main_namespace);

        // C++側メモリを確保
        // メッセージを入れておく
        std::vector<char> buffer(1024 * 1024);
        c_buffer = buffer.data();
        c_bufferSize = buffer.size();

        std::string message = "this is C++ memory";
        std::copy(message.begin(), message.end(), buffer.begin());

        // Pythonクラスの Buffer インスタンスを作成
        auto pybuffer = class_<Buffer>("Buffer", init<>())
                            .def("memoryview", &Buffer::memoryView)();

        // dump.dump_mv() 呼び出し
        auto func_dump_mv = main_namespace["dump_mv"];
        func_dump_mv(pybuffer);
    }
    catch (error_already_set)
    {
        PyErr_Print();
    }
}
