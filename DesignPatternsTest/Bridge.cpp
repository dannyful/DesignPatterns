#include "util.h"

/**
 * @brief 桥接
 * 分类: 结构型(对象)
 * 将抽象部分与它的实现部分分离，
 * 使他们都可以独立的变化。
 * 即使用组合的方式来替代继承，
 * 将一个类层次转化为多个相关的类层次，
 * 避免但各类层次的失控。
 * 在抽象和实现间架起一座桥梁。
*/

// 实现
class Device
{
public:
    virtual ~Device(){}
    virtual string turnOn() const = 0;
    virtual string turnOff() const = 0;
    virtual string mute() const = 0;
};

class TV :public Device
{
public:
    ~TV(){}
    string turnOn() const override {
        return "TV:开机...";
    }
    string turnOff() const override {
        return "TV:关机...";
    }
    string mute() const override {
        return "TV:静音...";
    }
};

class Radio :public Device
{
public:
    ~Radio() {}
    string turnOn() const override {
        return "Radio:开机...";
    }
    string turnOff() const override {
        return "Radio:关机...";
    }
    string mute() const override {
        return "Radio:静音...";
    }
};


// 抽象
class BaseRemoteController
{
protected:
    Device* m_implementation;
public:
    virtual ~BaseRemoteController() {}
    BaseRemoteController(Device* device) :m_implementation(device) {}

public:
    virtual void setDevice(Device* device) {
        m_implementation = device;
    }

    virtual string sendTurnOn() const {
        return "基础遥控器发出TurnOn: "
            + m_implementation->turnOn();
    }
    virtual string sendTurnOff() const {
        return "基础遥控器发出TurnOff: "
            + m_implementation->turnOff();
    }
};

class AdvancedRemoteController : public BaseRemoteController
{
public:
    ~AdvancedRemoteController() {}
    AdvancedRemoteController(Device* device)
        :BaseRemoteController(device) {}

public:
    virtual string sendTurnOn() const {
        return "高级遥控器发出TurnOn: "
            + m_implementation->turnOn();
    }
    virtual string sendTurnOff() const {
        return "高级遥控器发出TurnOff: "
            + m_implementation->turnOff();
    }
    virtual string sendMute() const {
        return "高级遥控器发出Mute: "
            + m_implementation->mute();
    }
};

void TestBridge() {
    Radio radio;
    BaseRemoteController baseRC(&radio);
    AdvancedRemoteController advancedRC(&radio);
    cout << baseRC.sendTurnOn() << endl;
    cout << baseRC.sendTurnOff() << endl;
    cout << advancedRC.sendTurnOn() << endl;
    cout << advancedRC.sendTurnOff() << endl;
    cout << advancedRC.sendMute() << endl;

    cout << "-----------------" << endl;
    TV tv;
    baseRC.setDevice(&tv);
    advancedRC.setDevice(&tv);
    cout << baseRC.sendTurnOn() << endl;
    cout << baseRC.sendTurnOff() << endl;
    cout << advancedRC.sendTurnOn() << endl;
    cout << advancedRC.sendTurnOff() << endl;
    cout << advancedRC.sendMute() << endl;
}