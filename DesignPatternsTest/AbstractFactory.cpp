#include "util.h"

/**
 * @brief 抽象工厂
 * 分类: 创建型(对象)
 * 提供一个创建一系列相关或相互依赖对象的接口，
 * 而无需制定他们具体的类。
*/

class Chair
{
public:
    virtual ~Chair() {}
    virtual void sitOn() const = 0;
};

class ModernChair :public Chair
{
public:
    virtual ~ModernChair() {}
    virtual void sitOn() const override {
        cout << "可以北坐下的ModernChair" << endl;
    }
};

class ChineseChair :public Chair
{
public:
    virtual ~ChineseChair() {}
    virtual void sitOn() const override {
        cout << "可以北坐下的ChineseChair" << endl;
    }
};

class Table
{
public:
    virtual ~Table() {}
    virtual void putOn() const = 0;
};

class ModernTable :public Table
{
public:
    virtual ~ModernTable() {}
    virtual void putOn() const override {
        cout << "ModernTable可以放东西。" << endl;
    }
};

class ChineseTable :public Table
{
public:
    virtual ~ChineseTable() {}
    virtual void putOn() const override {
        cout << "ChineseTable可以放东西。" << endl;
    }
};

class FurnitureFactory
{
public:
    virtual Chair* createChair() const = 0;
    virtual Table* createTable() const = 0;
};

class ModernStyleFactory :public FurnitureFactory
{
public:
    virtual Chair* createChair() const override {
        return new ModernChair();
    }
    virtual Table* createTable() const override {
        return new ModernTable();
    }
};

class ChineseStyleFactory :public FurnitureFactory
{
public:
    virtual Chair* createChair() const override {
        return new ChineseChair();
    }
    virtual Table* createTable() const override {
        return new ChineseTable();
    }
};

class Client
{
    FurnitureFactory* m_factory;
public:
    Client(FurnitureFactory* factory) :m_factory(factory) {}
    void buyFurniture() {
        Chair* chair = m_factory->createChair();
        Table* table = m_factory->createTable();
        chair->sitOn();
        table->putOn();
        delete chair;
        delete table;
    }
    void setFactory(FurnitureFactory* factory) {
        m_factory = factory;
    }
};


void TestAbstractFactory() {
    ModernStyleFactory mf;
    ChineseStyleFactory cf;
    Client client(&mf);
    client.buyFurniture();
    client.setFactory(&cf);
    client.buyFurniture();
}