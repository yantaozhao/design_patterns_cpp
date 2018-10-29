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

    void update() override
    {
        std::cout << "Iam " << name_.c_str() << ", will read the newspaper" << std::endl;
    }

private:
    std::string name_;
};


int main(int argc, char *argv[])
{
    PostOffice post_office;
    Person jack("Jack");
    Person eric("Eric");
    Person bill("Bill");

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
}
