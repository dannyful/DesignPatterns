#include "util.h"

/**
 * @brief 工厂方法
 * 分类: 创建型(类)
 * 意图:
 * 定义一个用于创建对象的接口，
 * 让子类决定实例化哪一个类。
 * factoryMethod 使一个类的实例化延迟到其子类。
 * 适用性:
 * 1. 当一个类不知道它所必须创建的对象的类的时候
 * 2. 当一个类希望由它的子类来指定它所创建的对象的时候
 * 3. 当类将创建对象的职责委托给多个帮助子类中的某一个，
 *    并且你希望将哪一个帮助子类是代理者这一信息局部化的时候
 * 
*/

/**
 * @brief Product
 * 定义工厂方法所创建的对象的接口
*/
class Transport
{
public:
    virtual ~Transport() {};
    virtual void deliver() const = 0;
};

/**
 * @brief ConcreteProduct
 * 实现Product接口
*/
class Truck : public Transport
{
public:
    void deliver() const override {
        cout << "卡车运输货物中。" << endl;
    }
};

class Ship : public Transport
{
public:
    void deliver() const override {
        cout << "轮船运输货物中。" << endl;
    }
};

/**
 * @brief Creator
 * 声明工厂方法factoryMethod，返回一个Product类型对象
*/
class Logistics
{
public:
    virtual ~Logistics() {}
    virtual Transport* factoryMethod() const = 0;
    void doSomething() const {
        Transport* transport = factoryMethod();
        transport->deliver();
        delete transport;
    }
};

/**
 * @brief ConcreteCreator
 * 重定义(实现)工厂方法，返回一个ConcreteProduct实例
*/
class TruckLogistics : public Logistics
{
public:
    virtual ~TruckLogistics() {}
    virtual Transport* factoryMethod() const override {
        return new Truck();
    }
};

class ShipLogistics : public Logistics
{
public:
    virtual ~ShipLogistics() {}
    virtual Transport* factoryMethod() const override {
        return new Ship();
    }
};

void TestFactoryMethod() {
    Logistics* truckLogistics = new TruckLogistics;
    truckLogistics->doSomething();
    Logistics* shipLogistics = new ShipLogistics;
    shipLogistics->doSomething();
}