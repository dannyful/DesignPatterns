#include "util.h"

/**
 * @brief 装饰
 * 分类: 结构型(对象)
 * 动态的给一个对象添加一些额外的职责。
 * 就增加功能来说，
 * 装饰模式相比生成子类更为灵活。
 * 找出基本组件和可选层次。
*/

// 接口: 具体被包裹的类，以及装饰类
class Beverage
{
public:
    virtual ~Beverage(){}
    virtual string operation() const = 0;
};

// 具体的被装饰类
class American: public Beverage
{
public:
    virtual ~American() {}
    virtual string operation() const override {
        return  "美式咖啡";
    }
};

// 装饰
// 基础部分(可能包括额外部分)
class Ingrdient: public Beverage
{
protected:
    Beverage* m_beverage;
public:
    virtual ~Ingrdient() {}
    Ingrdient(Beverage* beverage) : m_beverage(beverage) {}
    virtual string operation() const  override {
        // 核心代码，不是用来被基类覆盖的
        return m_beverage->operation();
    }
};

// 额外部分(需要委托基类，完成基础部分)
class Whip :public Ingrdient
{
public:
    ~Whip() {}
    Whip(Beverage* beverage):Ingrdient(beverage){}

    string operation() const  override {
        // 在基类的operation之前，之后都可以增加额外的操作
        return "奶昔 (" + Ingrdient::operation() + ")";
    }
};

class Mocha :public Ingrdient
{
public:
    ~Mocha() {}
    Mocha(Beverage* beverage) :Ingrdient(beverage) {}

    string operation() const  override {
        // 在基类的operation之前，之后都可以增加额外的操作
        return "摩卡 (" + Ingrdient::operation() + ")";
    }
};

void clientCode(Beverage* beverage) {
    cout << "执行结果: " << beverage->operation() << endl;
}

void TestDecorator() {
    cout << "来一杯普通美式咖啡:" << endl;
    Beverage* american = new American;
    clientCode(american);
    cout << endl;

    cout << "来一杯双份摩卡+奶昔的美式咖啡:" << endl;
    Beverage* whip = new Whip(american);
    Beverage* mocha1 = new Mocha(whip);
    Beverage* mocha2 = new Mocha(mocha1);
    clientCode(mocha2);
    cout << endl;


    delete american;
    delete whip;
    delete mocha1;
    delete mocha2;
}