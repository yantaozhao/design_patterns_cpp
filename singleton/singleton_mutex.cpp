#include <iostream>
#include <memory>
#include <mutex>
using namespace std;


class Printer
{
public:
    ~Printer()  // must be public
    {
        cout << this << "#" << __func__ << ":" << __LINE__ << endl;
    }

    static Printer *getInstance()  // static method
    {
        if (!s_instance_)
        {
            std::lock_guard<std::mutex> lck(s_mtx_);
            if (!s_instance_)  // must double check here
            {
                s_instance_.reset(new Printer());
                cout << __func__ << ":" << __LINE__ << endl;
            }
        }
        return s_instance_.get();
    }

    void someMethod1()
    {
        cout << this << "#" << __func__ << ":" << __LINE__ << endl;
    }

    void someMethod2()
    {
        cout << this << "#" << __func__ << ":" << __LINE__ << endl;
    }

private:
    static std::unique_ptr<Printer> s_instance_;
    static std::mutex s_mtx_;

    Printer()
    {
        cout << this << "#" << __func__ << ":" << __LINE__ << endl;
    }

    /* copy constructor, copy assignment operator */
    Printer(const Printer &) = delete;
    Printer &operator=(const Printer &) = delete;
};

std::unique_ptr<Printer> Printer::s_instance_;
std::mutex Printer::s_mtx_;


void test()
{
    cout << __func__ << ":" << __LINE__ << endl;

    Printer::getInstance()->someMethod1();
    Printer::getInstance()->someMethod2();

    cout << __func__ << ":" << __LINE__ << endl;
}

int main(int argc, char *argv[])
{
    cout << __func__ << ":" << __LINE__ << endl;
    test();
    cout << __func__ << ":" << __LINE__ << endl;

    getchar();
    cout << __func__ << ":" << __LINE__ << endl;
    return 0;
}
