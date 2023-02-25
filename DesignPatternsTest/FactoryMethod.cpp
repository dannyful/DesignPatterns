#include "util.h"

/**
 * @brief 工厂方法
 * 分类: 创建型(类)
 * 定义一个用于创建对象的接口，
 * 让子类决定实例化哪一个类。
 * factoryMethod 使一个类的实例化延迟到其子类。
*/

class Transport
{
public:
    virtual ~Transport() {};
    virtual void deliver() const = 0;
};

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