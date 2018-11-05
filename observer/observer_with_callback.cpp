#include <iostream>
#include <string>
#include <list>


class SubjectInterface;
class ObserverInterface;

class SubjectInterface
{
public:
    virtual ~SubjectInterface() = default;

    virtual void addObserver(ObserverInterface *ob) = 0;
    virtual void deleteObserver(ObserverInterface *ob) = 0;
    virtual void notifyAllObservers() = 0;

protected:
    std::list<ObserverInterface *> observers_;
};

class ObserverInterface
{
public:
    virtual ~ObserverInterface() = default;

    virtual void update() = 0;
};

class PostOffice : public SubjectInterface
{
public:
    void addObserver(ObserverInterface *ob) override
    {
        for (auto &o : observers_)
        {
            if (o == ob)
            {
                return;
            }
        }
        observers_.push_back(ob);
    }

    void deleteObserver(ObserverInterface *ob) override
    {
        for (auto &it = observers_.begin(); it != observers_.end(); ++it)
        {
            if ((*it) == ob)
            {
                observers_.erase(it);
                break;
            }
        }
    }

    void notifyAllObservers() override
    {
        for (auto &ob : observers_)
        {
            ob->update();
        }
    }
};

class Person : public ObserverInterface
{
public:
    Person(std::string name)
    {
        name_ = name;
    }

    Person(std::string name, void(*p)(void))
    {
        name_ = name;
        callback_ = p;
    }

    void update() override
    {
        if (callback_)
        {
            std::cout << "Iam " << name_.c_str() << ",";
            callback_();
        }
        else
        {
            std::cout << "Iam " << name_.c_str() << ", no callback" << std::endl;
        }
    }

private:
    std::string name_;
    void(*callback_)(void) = nullptr;
};


int main(int argc, char *argv[])
{
    PostOffice post_office;
#if 0
    Person jack("Jack");
    Person eric("Eric");
    Person bill("Bill");
#else
    Person jack("Jack", []()->void {std::cout << "read the newspaper" << std::endl; });
    Person eric("Eric", []()->void {std::cout << "read my magazine" << std::endl; });
    auto cb = []()->void {std::cout << "have a rest, then read the book" << std::endl; };
    Person bill("Bill", cb);
#endif

    post_office.addObserver(&jack);
    post_office.addObserver(&eric);
    post_office.notifyAllObservers();
    std::cout << "------" << std::endl;

    post_office.addObserver(&bill);
    post_office.notifyAllObservers();
    std::cout << "======" << std::endl;

    post_office.deleteObserver(&eric);
    post_office.notifyAllObservers();

    getchar();
    return 0;
}
