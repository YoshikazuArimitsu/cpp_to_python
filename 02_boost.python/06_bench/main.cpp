#include <random>
#include <iostream>
#include <fstream>
#include <chrono>

#include <boost/python.hpp>

using namespace boost::python;
using namespace boost::python::api;

static char* c_buffer;
static unsigned long c_bufferSize;

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
    bool mode_file_ = false;
    int buffer_size = 1024 * 1024 * 10;
    Py_Initialize();

    if (argc < 2)
    {
        std::cerr << "must set file/memoryview" << std::endl;
        return -1;
    }
    if (std::string(argv[1]) == "file")
    {
        mode_file_ = true;
    }

    std::cout << "bench " << (mode_file_ ? "file" : "memoryview") << std::endl;

    // 前準備
    object main_module = import("__main__");
    object main_namespace = main_module.attr("__dict__");
    object py_endpoint;

    auto myrand = std::bind(std::uniform_int_distribution<int>(0, 255),
                             std::mt19937(static_cast<unsigned int>(42)));

    try
    {
        std::ifstream ifs("./dump.py");
        if (ifs)
        {
            std::string script((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
            exec(script.c_str(), main_namespace);
        }

        py_endpoint = mode_file_ ? main_namespace["endpoint_file"] : main_namespace["endpoint_memoryview"];
    }
    catch (boost::python::error_already_set)
    {
        PyErr_Print();
        return -1;
    }
    auto pybuffer_ctor = class_<Buffer>("Buffer", init<>())
                                    .def("memoryview", &Buffer::memoryView);

    // 計測開始
    auto start = std::chrono::system_clock::now();
    for (int n = 0; n < 1000; n++)
    {
        std::vector<char> buffer(buffer_size);
        c_buffer = buffer.data();
        c_bufferSize = buffer.size();

        // 遅いからやめとく
        // for(auto& a : buffer) {
        //     a = static_cast<char>(myrand());
        // }

        if (mode_file_)
        {
            {
                std::ofstream ofs("data.bin", std::ios::binary);
                if(ofs) {
                    ofs.write(buffer.data(), buffer.size());
                } else {
                    std::cerr << "Open data.bin failed" << std::endl;
                    return -1;
                }
            }

            try
            {
                py_endpoint();
            }
            catch (boost::python::error_already_set)
            {
                PyErr_Print();
                return -1;
            }
        }
        else
        {
            try
            {
                auto pybuffer = pybuffer_ctor();
                py_endpoint(pybuffer);
            }
            catch (boost::python::error_already_set)
            {
                PyErr_Print();
                return -1;
            }
        }

        if(n % 100 == 0) {
            std::cout << "." << std::flush;
        }
    }
    std::cout << std::endl;

    auto end = std::chrono::system_clock::now();
    double elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count(); //処理に要した時間をミリ秒に変換
    std::cout << "elapsed " << elapsed << "msec" << std::endl;
}
