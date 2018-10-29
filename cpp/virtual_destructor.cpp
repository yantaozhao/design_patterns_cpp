/*
 * Summary:
 * A common guideline is that:
 * a destructor for a base class must be either "public and virtual" or "protected and non-virtual".
 *
 * @See: https://en.cppreference.com/w/cpp/language/destructor
 */

#include <iostream>
using namespace std;

// base class destructor: virtual
class A1
{
public:
    A1() { cout << __func__ << endl; }
    virtual ~A1() { cout << __func__ << endl; }  // virtual
};

class A2 : public A1
{
public:
    A2() { cout << __func__ << endl; }
    ~A2() { cout << __func__ << endl; }
};

class A3 : public A2
{
public:
    A3() { cout << __func__ << endl; }
    ~A3() { cout << __func__ << endl; }
};

// base class destructor: non-virtual
class B1
{
public:
    B1() { cout << __func__ << endl; }
    ~B1() { cout << __func__ << endl; }  // non-virtual
};

class B2 : public B1
{
public:
    B2() { cout << __func__ << endl; }
    ~B2() { cout << __func__ << endl; }
};

class B3 : public B2
{
public:
    B3() { cout << __func__ << endl; }
    ~B3() { cout << __func__ << endl; }
};

int main(int argc, char *argv[])
{
    A1 *ptr1 = new A3();
    delete ptr1;
    cout << "------" << endl;

    A2 *ptr2 = new A3();
    delete ptr2;
    cout << "======" << endl;

    B1 *ptr3 = new B3();
    delete ptr3;
    cout << "------" << endl;

    B2 *ptr4 = new B3();
    delete ptr4;
}
