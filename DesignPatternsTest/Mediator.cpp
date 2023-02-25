#include "util.h"

/**
 * @brief 中介者
 * 分类: 行为型(对象)
 * 用一个中介对象来封装一系列的对象交互。
 * 中介者使各对象不需要显示的相互引用，
 * 从而使得其耦合松散。
*/

class Staff;
// Mediator Interface
class ControlTower
{
public:
    virtual void notify(Staff* sender, const string& event) const = 0;
};

class Staff
{
protected:
    string m_name;
    ControlTower* m_controlTower;
public:
    Staff(const string& name, ControlTower* controlTower = nullptr)
        :m_name(name), m_controlTower(controlTower) {}
    string name() { return m_name; }
    void setMediator(ControlTower* controlTower) {
        m_controlTower = controlTower;
    }
};

class Pilot : public Staff
{
public:
    Pilot(const string& name) :Staff(name) {}
    void takeOff() {
        cout << name() + ": 请求起飞。" << endl;
        m_controlTower->notify(this, "请求起飞");
    }

    void copy() {
        cout << name() + ": 收到。" << endl;
    }
};

class GroundGrew : public Staff
{
public:
    GroundGrew(const string& name) :Staff(name) {}
    void maintainance() {
        cout << name() + ": 请求维护。" << endl;
        m_controlTower->notify(this, "请求维护");
    }

    void copy() {
        cout << name() + ": 收到。" << endl;
    }
};

class ConcreteControlTower : public ControlTower
{
private:
    Pilot* m_pilot1;
    Pilot* m_pilot2;
    Pilot* m_pilot3;
    GroundGrew* m_ground1;
public:
    ConcreteControlTower(Pilot* p1, Pilot* p2, Pilot* p3, GroundGrew* g1)
        :m_pilot1(p1), m_pilot2(p2), m_pilot3(p3), m_ground1(g1) {
        m_pilot1->setMediator(this);
        m_pilot2->setMediator(this);
        m_pilot3->setMediator(this);
        m_ground1->setMediator(this);
    }

    virtual void notify(Staff* sender, const string& event) const override {
        cout << "控制塔: 收到" + sender->name() + event + "。" << endl;
        if (event == "请求起飞") {
            m_ground1->copy();
            if (sender != m_pilot1) {
                m_pilot1->copy();
            }
            if (sender != m_pilot2) {
                m_pilot2->copy();
            }
            if (sender != m_pilot3) {
                m_pilot3->copy();
            }
        }
        if (event == "请求维护") {
            m_pilot1->copy();
            m_pilot2->copy();
            m_pilot3->copy();
        }
    }
};

void TestMediator() {
    Pilot p1("空军1号");
    Pilot p2("空军2号");
    Pilot p3("空军3号");
    GroundGrew g1("地勤1");

    ConcreteControlTower controlTower(&p1, &p2, &p3, &g1);
    p1.takeOff();
    g1.maintainance();
}