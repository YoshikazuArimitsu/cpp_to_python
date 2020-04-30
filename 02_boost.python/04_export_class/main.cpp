#include <iostream>
#include <fstream>
#include <boost/python.hpp>

using namespace boost::python;
using namespace boost::python::api;

class Data
{
public:
    Data(const std::string &sv = "", int iv = 0, float fv = 0.0f) : stringValue(sv), intValue(iv), floatValue(fv) {}

    std::string stringValue;
    int intValue;
    float floatValue;
};

BOOST_PYTHON_MODULE(data)
{
    class_<Data>("Data", init<const std::string &, int, double>())
        .def_readwrite("stringValue", &Data::stringValue)
        .def_readwrite("intValue", &Data::intValue)
        .def_readwrite("floatValue", &Data::floatValue);
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
        auto func_dump_data = main_namespace["dump_data"];

        object data = (class_<Data>("Data", init<const std::string &, int, double>())
                           .def_readwrite("stringValue", &Data::stringValue)
                           .def_readwrite("intValue", &Data::intValue)
                           .def_readwrite("floatValue", &Data::floatValue))("Data", 42, 37.564f);
        func_dump_data(data);
    }
    catch (boost::python::error_already_set)
    {
        PyErr_Print();
    }
}
