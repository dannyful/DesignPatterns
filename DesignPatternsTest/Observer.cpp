#include "util.h"

/**
 * @brief 观察者
 * 分类: 行为型(对象)
 * 定义对象间的一种一对多关系，
 * 当一个对象的状态发生改变时，
 * 所有依赖于它的对象都得到通知并自动更新。
*/

class IObserver
{
public:
    virtual void update(const string& msgFromSubject) = 0;
};

class ISubject
{
public:
    virtual void attach(IObserver* observer) = 0;
    virtual void detach(IObserver* observer) = 0;
    virtual void notify() = 0;
};

class Mate50 : public ISubject
{
private:
    list<IObserver*> m_observerList;
    string m_msg;
public:
    virtual void attach(IObserver* observer) override {
        m_observerList.push_back(observer);
    }
    virtual void detach(IObserver* observer) override {
        m_observerList.remove(observer);
    }
    virtual void notify() override {
        list<IObserver*>::iterator iter = m_observerList.begin();
        while (iter != m_observerList.end()) {
            (*iter++)->update(m_msg);
        }
    }

    void createMessage(const string& msg = "") {
        m_msg = msg;
        notify();
    }
};

class Customer : public IObserver
{
private:
    ISubject* m_mate50;
    string m_msgFromMate50;
    int m_number;
    static int m_staticNumber;
public:
    Customer(ISubject* subject):m_mate50(subject) {
        m_mate50->attach(this);
        cout << "我是[" << ++Customer::m_staticNumber << "]号订购者。" << endl;
        m_number = Customer::m_staticNumber;
    }

    virtual void update(const string& msgFromSubject) override {
        m_msgFromMate50 = msgFromSubject;
        printInfo();
    }

    void printInfo() {
        cout << "[" << m_number << "]号订购者: 接收到新的消息:" << endl;
        cout << m_msgFromMate50 << endl;
    }

    void removeFromList() {
        m_mate50->detach(this);
        cout << "[" << m_number << "]号订购者: 从列表中移除。" << endl;
    }
};
int Customer::m_staticNumber = 0;

void TestObserver() {

    Mate50* mate50 = new Mate50();
    Customer* c1 = new Customer(mate50);
    Customer* c2 = new Customer(mate50);
    Customer* c3 = new Customer(mate50);


    mate50->createMessage("Mate50 即将到店.....");
    Customer* c4 = new Customer(mate50);

    mate50->createMessage("Mate50 明天到店.....");
    Customer* c5 = new Customer(mate50);
    c2->removeFromList();
    mate50->createMessage("Mate50 开售.....");

    delete c1;
    delete c2;
    delete c3;
    delete c4;
    delete c5;
}