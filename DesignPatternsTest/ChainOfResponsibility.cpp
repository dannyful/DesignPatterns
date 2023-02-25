#include "util.h"

/**
 * @brief 职责链
 * 分类: 行为型(对象)
 * 使多个对象都有机会处理请求，
 * 从而避免请求的发送者和接受者之间的耦合关系。
 * 将这些对象连城一条链，
 * 并沿着这条链传递该请求，
 * 直到有一个对象处理它为止。
*/

class Handler
{
public:
    virtual Handler* setNext(Handler* handler) = 0;
    virtual string handle(string request) = 0;
};

class BaseHandler: public Handler
{
private:
    Handler* m_nextHandler;

public:
    virtual Handler* setNext(Handler* handler) override {
        m_nextHandler = handler;
        return m_nextHandler;
    }
    virtual string handle(string request) override {
        if (m_nextHandler) {
            return m_nextHandler->handle(request);
        }
        return "";
    }
};

class RobotAI: public BaseHandler
{
public:
    virtual string handle(string request) override {
        if (request == "使用向导") {
            return "RobotAI: 我来处理-" + request;
        }
        return BaseHandler::handle(request);
    }
};

class TelOperator : public BaseHandler
{
public:
    virtual string handle(string request) override {
        if (request == "常见问题") {
            return "TelOperator: 我来处理-" + request;
        }
        return BaseHandler::handle(request);
    }
};

class Expert : public BaseHandler
{
public:
    virtual string handle(string request) override {
        if (request == "疑难杂症") {
            return "Expert: 我来处理-" + request;
        }
        return BaseHandler::handle(request);
    }
};

void clientCode(Handler& handler) {
    list<string> problems = {
        "常见问题",
        "使用向导",
        "疑难杂症",
        "其它问题" };

    for (const string& str : problems) {
        string res = handler.handle(str);
        cout << "Client: 谁来处理->" << str << endl;
        if (res.empty()) {
            cout << "处理结果: 没有人能够处理。" << endl;
        } else {
            cout << "处理结果: " << res << endl;
        }
    }
}

void TestChainOfResponsibility() {
    RobotAI robotAI;
    TelOperator tel;
    Expert expert;
    robotAI.setNext(&tel)->setNext(&expert);
    cout << "Chain: robot->tel->expert" << endl;
    clientCode(robotAI);
}