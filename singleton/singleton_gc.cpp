#include <iostream>
using namespace std;


class Printer
{
public:
    static Printer *getInstance()  // static method
    {
        if (!s_instance_)
        {
            cout << __func__ << ":" << __LINE__ << endl;
            s_instance_ = new Printer();
        }
        return s_instance_;
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
    static Printer *s_instance_;

    Printer()
    {
        cout << this << "#" << __func__ << ":" << __LINE__ << endl;
    }

    ~Printer()
    {
        cout << this << "#" << __func__ << ":" << __LINE__ << endl;
    }

    /* copy constructor, copy assignment operator */
    Printer(const Printer &) = delete;
    Printer &operator=(const Printer &) = delete;

    // inner class which ensures to call `delete` the pointer
    class MyGC
    {
    public:
        MyGC()
        {
            cout << this << "#" << __func__ << ":" << __LINE__ << endl;
        }
        ~MyGC()
        {
            if (s_instance_)
            {
                cout << this << "#" << __func__ << ":" << __LINE__ << endl;
                delete s_instance_;
                s_instance_ = nullptr;
            }
            else
            {
                cout << this << "#" << __func__ << ":" << __LINE__ << endl;
            }
        }
    };
    static MyGC gc;
};

Printer *Printer::s_instance_ = nullptr;
Printer::MyGC Printer::gc;  // REMEMBER HERE


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
