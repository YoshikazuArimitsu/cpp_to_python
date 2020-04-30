#include <iostream>
#include <fstream>
#include <boost/python.hpp>

using namespace boost::python;
using namespace boost::python::api;

namespace
{
char *c_buffer;
unsigned long c_bufferSize;
} // namespace

class Buffer
{
    // クラスメンバとしてバッファを持つ方法は失敗
    // char* は Python の str に変換される為、コピーが発生する＆UTF-8じゃないと落ちる。
    /*
private:
    char *bufferPtr_;
    unsigned long length_;

public:
    Buffer(char *buffer, unsigned long length) : bufferPtr_(buffer), length_(length)
    {
    }
    */

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

BOOST_PYTHON_MODULE(data)
{
    class_<Buffer>("Buffer", init<>())
        .def("memoryview", &Buffer::memoryView);
}

int main(int argc, char **argv)
{
    Py_Initialize();

    object main_module = import("__main__");
    object main_namespace = main_module.attr("__dict__");

    try
    {
        /*
        std::ifstream ifs("./dump.py");
        if (ifs)
        {
            std::string script((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
            exec(script.c_str(), main_namespace);
        }
        */
        boost::python::exec_file("./dump.py", main_namespace, main_namespace);

        std::vector<char> buffer(1024 * 1024);
        c_buffer = buffer.data();
        c_bufferSize = buffer.size();

        auto func_dump_mv = main_namespace["dump_mv"];

        auto pybuffer = class_<Buffer>("Buffer", init<>())
                            .def("memoryview", &Buffer::memoryView)();
        func_dump_mv(pybuffer);
    }
    catch (boost::python::error_already_set)
    {
        PyErr_Print();
    }
}
