#include <iostream>
#include <fstream>
#include <boost/python.hpp>

using namespace boost::python;
using namespace boost::python::api;

class Buffer
{
private:
    const char *bufferPtr_;
    unsigned long length_;

public:
    Buffer(const char *buffer, unsigned long length) : bufferPtr_(buffer), length_(length)
    {
    }

    object memoryView()
    {
        boost::python::handle<> handle(PyMemoryView_FromMemory((char *)bufferPtr_, length_, PyBUF_READ));
        return boost::python::object(handle);
    }
};

BOOST_PYTHON_MODULE(data)
{
    class_<Buffer>("Buffer", init<char *, unsigned long>())
        .def("memoryview", &Buffer::memoryView);
}

int main(int argc, char **argv)
{
    Py_Initialize();

    object main_module = import("__main__");
    object main_namespace = main_module.attr("__dict__");

    try
    {
        std::ifstream ifs("./dump.py");
        if (ifs)
        {
            std::string script((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
            exec(script.c_str(), main_namespace);
        }

        std::vector<char> buffer(1024 * 1024);

        auto func_dump_mv = main_namespace["dump_mv"];

        auto pybuffer = class_<Buffer>("Buffer", init<char *, unsigned long>())
                            .def("memoryview", &Buffer::memoryView)((const char *)buffer.data(), buffer.size());
        func_dump_mv(pybuffer);
    }
    catch (boost::python::error_already_set)
    {
        PyErr_Print();
    }
}
