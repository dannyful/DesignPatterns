#include "util.h"

/**
 * @brief 原型
 * 分类: 创建型(对象)
 * 用原型实例指定创建对象的种类，
 * 并且通过拷贝这些原型创建新的对象。
 * 即复制已有对象，
 * 而无需使代码依赖他们所属的类。
*/

enum Type
{
    ROBOT_CAT = 0,
    ROBOT_DOG
};

class Robot
{
protected:
    string m_prototypeName = "";
    float m_stateOfCharge = 0.0;

public:
    Robot(string name) :m_prototypeName(name) {}
    virtual ~Robot() {}
    virtual Robot* clone() const = 0;
    virtual void setStateOfCharge(float) = 0;
};

class RobotCat :public Robot
{
    float m_CatValue = 0.0;
public:
    virtual ~RobotCat() {}
    RobotCat(string name, float value) :Robot(name), m_CatValue(value) {}

    virtual Robot* clone() const override {
        return new RobotCat(*this);
    }

    virtual void setStateOfCharge(float value) override {
        m_stateOfCharge = value;
        cout << "--" << m_prototypeName << "当前电量:" << m_stateOfCharge
            << ", m_CatValue:" << m_CatValue << endl;
    }
};

class RobotDog :public Robot
{
    float m_DogValue = 0.0;
public:
    virtual ~RobotDog() {}
    RobotDog(string name, float value) :Robot(name), m_DogValue(value) {}

    virtual Robot* clone() const override {
        return new RobotDog(*this);
    }

    virtual void setStateOfCharge(float value) override {
        m_stateOfCharge = value;
        cout << "--" << m_prototypeName << "当前电量:" << m_stateOfCharge
            << ", m_DogValue:" << m_DogValue << endl;
    }
};

class CloneFactory
{
    unordered_map<Type, Robot*> m_prototypes;
public:
    CloneFactory() {
        m_prototypes[ROBOT_CAT] = new RobotCat("机器猫", 5.0);
        m_prototypes[ROBOT_DOG] = new RobotDog("机器狗", 8.0);
    }
    ~CloneFactory() {
        delete m_prototypes[ROBOT_CAT];
        delete m_prototypes[ROBOT_DOG];
    }
    Robot* createRobot(Type type) {
        return m_prototypes[type]->clone();
    }
};

void client(CloneFactory& factory) {
    cout << "克隆机器猫:" << endl;
    Robot* clone = factory.createRobot(ROBOT_CAT);
    clone->setStateOfCharge(90);
    delete clone;
    clone = factory.createRobot(ROBOT_CAT);
    clone->setStateOfCharge(10);
    delete clone;
    cout << "克隆机器狗:" << endl;
    clone = factory.createRobot(ROBOT_DOG);
    clone->setStateOfCharge(70);
    delete clone;
}

void TestPrototype() {
    CloneFactory factory;
    client(factory);
}