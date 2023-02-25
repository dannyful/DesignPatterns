#include "util.h"

/**
 * @brief 解释器
 * 分类: 行为型(对象)
 * 给定一个语言，
 * 定义它的文法的一种表示，
 * 并定义一个解释器，
 * 这个解释器使用该表示来解释语言中的句子。
*/


class Context;
class Expression
{
public:
    virtual void interpret(Context* context) const = 0;
};

class Context
{
private:
    string m_input;
    string m_output;
public:
    void setInput(const string& str) {
        m_input = str;
    }
    string getInput() const { return m_input; }

    void setOutput(const string& str) {
        m_output = str;
    }
    string getOutput() const { return m_output; }
};

class TerminalExpression :public Expression
{
public:
    virtual void interpret(Context* context) const override {
        cout << "终端解释器。" << endl;
    }
};

class NonTerminalExpression :public Expression
{
public:
    virtual void interpret(Context* context) const override {
        cout << "非终端解释器。" << endl;
    }
};


void TestInterpreter() {
    Context context;
    vector<Expression*> expressions;
    TerminalExpression te1;
    TerminalExpression te2;
    TerminalExpression te3;
    NonTerminalExpression nte1;

    expressions.push_back(&te1);
    expressions.push_back(&nte1);
    expressions.push_back(&te2);
    expressions.push_back(&te3);

    for (Expression* expression : expressions) {
        expression->interpret(&context);
    }
}