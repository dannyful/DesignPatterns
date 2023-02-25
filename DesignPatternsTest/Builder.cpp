#include "util.h"

/**
 * @brief 生成器
 * 分类: 创建型(对象)
 * 将一个复杂对象的构建与它的表示分离，
 * 使得同样的构建过程可以创建不同的表示。
 * 即将对象构造代码从产品类中抽取出来，
 * 并将其放在一个名为Builder的独立对象中。
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

class Builder
{
public:
    virtual ~Builder() {}
    virtual void reset() = 0;
    virtual void makeBaseHouse() = 0;
    virtual void makeGarage() = 0;
    virtual void makePool() = 0;
};

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