#include <iostream>
using namespace std;


class Printer
{
public:
    static Printer *getInstance()  // static method
    {
        static Printer printer;  // Meyers Singleton
        return &printer;
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
};


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
