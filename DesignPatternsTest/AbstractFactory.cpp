#include "util.h"

/**
 * @brief 抽象工厂
 * 分类: 创建型(对象)
 * 意图:
 * 提供一个创建一系列相关或相互依赖对象的接口，
 * 而无需制定他们具体的类。
 * 适用性:
 * 1. 一个系统要独立于它的产品的创建，组合和表示时
 * 2. 一个系统要由多个产品系列中的一个来配置时
 * 3. 当你要强调一系列相关的产品对象的设计以便进行联合使用时
 * 4. 当你提供一个产品类库，而只想显示它们的接口而不是实现时
*/


/**
 * @brief AbstractProduct
 * 为一类产品对象声明一个接口
*/
class Chair
{
public:
    virtual ~Chair() {}
    virtual void sitOn() const = 0;
};

/**
 * @brief ConcreteProduct
 * 定义一个将被相应的具体工厂创建的产品对象
 * 实现AbstractProduct接口
*/
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

/**
 * @brief AbstractFactory
 * 声明一个创建抽象产品对象的操作接口
*/
class FurnitureFactory
{
public:
    virtual Chair* createChair() const = 0;
    virtual Table* createTable() const = 0;
};

/**
 * @brief ConCreteFactory
 * 实现创建具体产品对象的操作
*/
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

/**
 * @brief Client
 * 仅使用AbstractFactory和AbstractProduct类声明的接口
*/
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