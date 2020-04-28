#include <boost/python.hpp>

using namespace boost::python;
using namespace boost::python::api;

int main(int argc, char **argv)
{
    Py_Initialize();

    object main_module = import("__main__");
    object main_namespace = main_module.attr("__dict__");
    try
    {
        object ignored = exec("hello = open('hello.txt', 'w')\n"
                              "hello.write('Hello world!')\n"
                              "hello.close()",
                              main_namespace);
    }
    catch (boost::python::error_already_set)
    {
        PyErr_Print();
    }
}
