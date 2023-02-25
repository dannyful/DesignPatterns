#include "util.h"

/**
 * @brief 命令
 * 分类: 行为型(对象)
 * 将一个请求封装为一个对象，
 * 从而可用不同的请求对客户进行参数化；
 * 对请求排队或记录请求日志，
 * 以及支持可撤销的操作。
*/

// Recevier
class Kitchen
{
private:
    Kitchen(){}
public:
    static Kitchen* getInstance() {
        static Kitchen* instance = new Kitchen();
        return instance;
    }

    void prepareFood(const string& food) {
        cout << "厨房: 正在准备(" << food << "。)" << endl;
    }
};

class Command
{
public:
    virtual ~Command() {}
    virtual void execute() const = 0;
};

// ConcreteCommand1
class Order : public Command
{
private:
    Kitchen* m_kitchen;     // reveiver
    vector<string> m_foods; // params
public:
    Order(Kitchen* kitchen, vector<string>& foods)
        :m_kitchen(kitchen), m_foods(foods) {}

    virtual ~Order() {}
    virtual void execute() const override {
        cout << "订单: 需要厨房进行处理..." << endl;
        for (const string& str : m_foods) {
            m_kitchen->prepareFood(str);
        }
    }
};

// Invoker
class Waitress
{
private:
    Command* m_command;
public:
    ~Waitress() {
        delete m_command;
    }

    void orderUp(Command* cmd) {
        cout << "服务员: ----提交订单----" << endl;
        m_command = cmd;
        m_command->execute();
    }
};

class Client
{
public:
    void orderFood(Waitress& waitress, vector<string> foods) {
        waitress.orderUp(new Order(Kitchen::getInstance(), foods));
    }
};

void TestCommand() {
    Client user1;
    Waitress waitress;  //Invoker
    user1.orderFood(waitress, { "面条", "啤酒" });
}