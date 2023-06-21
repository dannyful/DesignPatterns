#include "util.h"

/**
 * @brief 生成器
 * 分类: 创建型(对象)
 * 意图:
 * 将一个复杂对象的构建与它的表示分离，
 * 使得同样的构建过程可以创建不同的表示。
 * 即将对象构造代码从产品类中抽取出来，
 * 并将其放在一个名为Builder的独立对象中。
 * 适用性:
 * 1. 当创建复杂对象的算法应该独立于该对象的组成部分以及它们的装配方式时
 * 2. 当构造过程必须允许被构造的对象有不同的表示时
*/

/**
 * @brief Product
 * 表示被构造的复杂对象，ConcreteBuilder创建该产品的内部表示并定义它的装配过程
 * 包含定义组成部件的类，包括将这些部件装配成最终产品的接口
*/
class SimpleHouse
{
public:
    vector<string> m_parts;
    void printParts() const {
        cout << "SimpleHouse 包括:" << endl;
        for (string str : m_parts) {
            cout << str << endl;
        }
        cout << "-------------------------" << endl;
    }
};

/**
 * @brief Builder
 * 为创建一个Product对象的各个部件指定抽象接口
*/
class Builder
{
public:
    virtual ~Builder() {}
    virtual void reset() = 0;
    virtual void makeBaseHouse() = 0;
    virtual void makeGarage() = 0;
    virtual void makePool() = 0;
};

/**
 * @brief ConcreteBuilder
 * 实现Builder的接口以构造和装配该产品的各个部件
 * 定义并明确它所创建的表示
 * 提供一个检索产品的接口 getResult
*/
class SimpleHouseBuilder : public Builder
{
    SimpleHouse* m_simpleHouse;
public:
    SimpleHouseBuilder() {
        reset();
    }

    ~SimpleHouseBuilder() {
        delete m_simpleHouse;
    }
    void reset() override {
        m_simpleHouse = new SimpleHouse();
    }
    virtual void makeBaseHouse() override {
        m_simpleHouse->m_parts.push_back("BaseHouse");
    }
    virtual void makeGarage() override {
        m_simpleHouse->m_parts.push_back("Garage");
    }
    virtual void makePool() override {
        m_simpleHouse->m_parts.push_back("Pool");
    }
    SimpleHouse* getResult() {
        SimpleHouse* result = m_simpleHouse;
        reset();
        return result;
    }
};

/**
 * @brief Director
 * 构造一个使用Builder接口的对象
*/
class Director
{
    Builder* m_builder;
public:
    void setBuilder(Builder* b) {
        m_builder = b;
    }

    void makeSimpleHouse() {
        m_builder->makeBaseHouse();
        m_builder->makeGarage();
    }
    void makeFullHouse() {
        m_builder->makeBaseHouse();
        m_builder->makeGarage();
        m_builder->makePool();
    }

};


void client(Director* d) {
    cout << "客户自己设计流程:-------------" << endl;
    SimpleHouseBuilder* builder = new SimpleHouseBuilder();
    builder->makeBaseHouse();
    builder->makeGarage();
    SimpleHouse* s = builder->getResult();
    s->printParts();
    delete s;
    cout << "主管设计流程:-------------" << endl;
    d->setBuilder(builder);
    d->makeFullHouse();
    s = builder->getResult();
    s->printParts();
    delete s;
    delete builder;
}

void TestBuilder() {
    Director director;
    client(&director);
}