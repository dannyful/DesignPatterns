#include "util.h"

/**
 * @brief 备忘录
 * 分类: 行为型(对象)
 * 在不破坏封装性的前提下，
 * 捕获一个对象的内部状态。
 * 并在该对象之外保留这个状态。
 * 这样以后就可将该对象恢复到原先保存的状态。
*/

// Memento
class Memento
{
private:
    unsigned int m_state;
    string m_data;  //memento data
public:
    Memento(unsigned int state) :m_state(state) {
        time_t now = time(0);
        m_data = ctime(&now);
    }

    unsigned int getState() { return m_state; }
    string& getData() { return m_data; }

};

// Originator
class Hero
{
private:
    unsigned int m_state;
public:
    Hero(unsigned int state): m_state(state){
        cout << "英雄: 我的初始状态为:" << m_state << endl;
    }

    void fight() {
        cout << "英雄: 啊！被砍了一刀。" << endl;
        m_state -= (rand() % 20) +1;
        cout << "英雄: 当前状态变更为:" << m_state << endl;
    }

    Memento* save() {
        return new Memento(m_state);
    }

    void restore(Memento* memento) {
        m_state = memento->getState();
        cout << "英雄: 当前状态恢复为:" << m_state << endl;
    }
};

// Caretaker
class Caretaker
{
private:
    Hero* m_hero;
    vector<Memento*> m_mementos;
public:
    Caretaker(Hero* hero): m_hero(hero){}
    ~Caretaker() {
        for (Memento* memento : m_mementos) delete memento;
    }

    void backup() {
        cout << "管理者: 正在保存英雄状态...." << endl;
        m_mementos.push_back(m_hero->save());
    }

    void undo() {
        if (m_mementos.empty()) return;
        Memento* memento = m_mementos.back();
        m_mementos.pop_back();

        cout << "管理者: 英雄状态恢复为" << memento->getData() << endl;
        m_hero->restore(memento);
        delete memento;
    }
};

void TestMemento() {
    srand((unsigned int)time(0));
    Hero* hero = new Hero(100);
    Caretaker* caretaker = new Caretaker(hero);
    caretaker->backup();
    hero->fight();
    caretaker->backup();
    hero->fight();
    caretaker->undo();

    delete hero;
    delete caretaker;
}