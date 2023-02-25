#include "util.h"

/**
 * @brief 访问者
 * 分类: 行为型(对象)
 * 表示一个作用于某对象结构中的各元素的操作。
 * 它使你可以在不改变各元素的类的前提下，
 * 定义作用于这些元素的新操作。
*/

class Man;
class Woman;
class Action
{
private:
    string m_state;
public:
    Action(const string& state) :m_state(state) {}

    virtual void getManConclusion(const Man* man) const = 0;
    virtual void getWomanConclusion(const Woman* woman) const = 0;
    string getState() const { return m_state; }
};

class Person
{
private:
    string m_type;
public:
    Person(const string& type) : m_type(type) {}
    virtual void accept(Action* visitor) const = 0;
    virtual string getType() const { return m_type; }
};

// 对象结构 男人
class Man : public Person
{
public:
    Man() : Person("男人") {}
    virtual void accept(Action* visitor) const override {
        visitor->getManConclusion(this);
    }
};

// 对象结构 女人
class Woman : public Person
{
public:
    Woman() : Person("女人") {}
    virtual void accept(Action* visitor) const override {
        visitor->getWomanConclusion(this);
    }
};


// Action 成功
class Success : public Action
{
public:
    Success() :Action("成功") {}

    virtual void getManConclusion(const Man* man) const override {
        cout << man->getType() << getState() << "时，背后多半有一个伟大的女人！" << endl;
    }
    virtual void getWomanConclusion(const Woman* woman) const override {
        cout << woman->getType() << getState() << "时，背后大多有一个不成功的男人！" << endl;
    }
};

// Action 失败
class Failing : public Action
{
public:
    Failing() :Action("失败") {}

    virtual void getManConclusion(const Man* man) const override {
        cout << man->getType() << getState() << "时，闷头喝酒，谁也不用劝！" << endl;
    }
    virtual void getWomanConclusion(const Woman* woman) const override {
        cout << woman->getType() << getState() << "时，眼泪汪汪，谁也劝不动！" << endl;
    }
};

// Action 恋爱
class Amativeness : public Action
{
public:
    Amativeness() :Action("恋爱") {}

    virtual void getManConclusion(const Man* man) const override {
        cout << man->getType() << getState() << "时，凡事不懂也要装懂！" << endl;
    }
    virtual void getWomanConclusion(const Woman* woman) const override {
        cout << woman->getType() << getState() << "时，遇事懂也装作不懂！" << endl;
    }
};

// Action 结婚
class Marriage : public Action
{
public:
    Marriage() :Action("结婚") {}

    virtual void getManConclusion(const Man* man) const override {
        cout << man->getType() << getState() << "时，感慨道: 恋爱游戏终结时，'有妻徒刑'遥无期！" << endl;
    }
    virtual void getWomanConclusion(const Woman* woman) const override {
        cout << woman->getType() << getState() << "时，感慨道: 爱情长跑路漫漫，婚姻保鲜保平安！" << endl;
    }
};

class ObjectStructure
{
private:
    list<Person*> m_persons;
public:
    void attach(Person* person) {
        m_persons.push_back(person);
    }
    void detach(Person* person) {
        m_persons.remove(person);
    }
    void display(Action* visitor) {
        for (auto p : m_persons) {
            p->accept(visitor);
        }
    }
};

void TestVisitor() {
    ObjectStructure o;
    Man man;
    Woman woman;
    o.attach(&man);
    o.attach(&woman);

    Success     s1;
    Failing     s2;
    Amativeness s3;
    cout << "-------" << endl;
    o.display(&s1);
    cout << "-------" << endl;
    o.display(&s2);
    cout << "-------" << endl;
    o.display(&s3);

    Marriage    s4;
    cout << "-------" << endl;
    o.display(&s4);
}