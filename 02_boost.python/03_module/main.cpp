#include <iostream>
#include <fstream>
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
        std::ifstream ifs("./greet.py");
        if (ifs)
        {
            std::string script((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
            exec(script.c_str(), main_namespace);
        }

        auto func = main_namespace["greet"];
        auto result = func();

        // Pythonのstrをstd::stringに展開
        auto result_string = boost::python::extract<std::string>(boost::python::str(result))();

        std::cout << result_string << std::endl;
    }
    catch (boost::python::error_already_set)
    {
        PyErr_Print();
    }
}
