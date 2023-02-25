#include "util.h"

/**
 * @brief 状态
 * 分类: 行为型(对象)
 * 允许一个对象在其内部状态改变时改变它的行为。
 * 对象看起来似乎改变了它的类。
*/

//class CandyMachine;
class State
{
protected:
    //CandyMachine* m_candyMachine;
public:
    //void setContext(CandyMachine* candyMachine) {
    //    m_candyMachine = candyMachine;
    //}
    virtual ~State() {}
    virtual void getCandy() = 0;
    virtual void returnCoin() = 0;
    virtual void putCoin() = 0;
};

class NoCoinState : public State
{
public:
    virtual ~NoCoinState() {}
    virtual void getCandy() override {
        cout << "请先投币。" << endl;
    }
    virtual void returnCoin() override {
        cout << "你并没有投币。" << endl;
    }
    virtual void putCoin() override {
        cout << "投币成功。" << endl;
    }
};

class HaveCoinState : public State
{
public:
    virtual ~HaveCoinState() {}
    virtual void getCandy() override {
        cout << "糖果投放中...." << endl;
    }
    virtual void returnCoin() override {
        cout << "投币退回中....." << endl;
    }
    virtual void putCoin() override {
        cout << "重复投币。" << endl;
    }
};

// Context
class CandyMachine
{
private:
    State* m_currentState;
    State* m_haveCoinState;
    State* m_noCoinState;
public:
    CandyMachine() {
        m_haveCoinState = new HaveCoinState();
        m_noCoinState = new NoCoinState();
        m_currentState = m_noCoinState;
        cout << "糖果机: 当前状态--->" << typeid(*m_currentState).name() << endl;
    }
    ~CandyMachine() {
        delete m_haveCoinState;
        delete m_noCoinState;
    }

    void putCoin() {
        cout << "糖果机: putCoin。" << endl;
        m_currentState->putCoin();
        changeState(m_haveCoinState);
    }

    void getCandy() {
        cout << "糖果机: getCandy。" << endl;
        m_currentState->getCandy();
        changeState(m_noCoinState);
    }

    void returnCoin() {
        cout << "糖果机: returnCoin。" << endl;
        m_currentState->returnCoin();
        changeState(m_noCoinState);
    }

private:
    void changeState(State* state) {
        m_currentState = state;
        cout << "糖果机: 当前状态--->" << typeid(*m_currentState).name() << endl;
    }
};

void TestState() {
    CandyMachine* mac = new CandyMachine();
    mac->getCandy();
    mac->returnCoin();

    mac->putCoin();
    mac->getCandy();
    mac->returnCoin();
    delete mac;
}