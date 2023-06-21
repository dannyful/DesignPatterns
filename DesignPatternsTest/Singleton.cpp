#include "util.h"

/**
 * @brief 单例
 * 分类: 创建型(对象)
 * 意图:
 * 保证一个类只有一个实例，
 * 并提供一个访问它的全局访问点。
 * 适用性:
 * 1. 当类只能有一个实例而且客户可以从一个众所周知的访问点访问它时
 * 2. 当这个唯一实例应该是通过子类化可扩展的，
 *    并且客户应该无需更改代码就能使用一个扩展的实例时
*/


/**
 * @brief Singleton
 * 定义一个Instance的操作(getInstance)，允许客户访问它的唯一实例
 * Instance是一个类操作 getInstance
 * 可能负责创建它自己的唯一实例
*/
class Singleton
{
private:
    Singleton(const string value):m_value(value){}
    ~Singleton(){}
    string m_value;
    static Singleton* m_instance;
    static mutex m_mutex;

public:
    Singleton(Singleton&) = delete;
    Singleton(const Singleton&) = delete;
    void operator=(const Singleton&) = delete;
    string value() const { return m_value; }

    static Singleton* getInstance(const string& value);
};

Singleton* Singleton::m_instance = nullptr;
mutex Singleton::m_mutex;

Singleton* Singleton::getInstance(const string& value) {
    //lock_guard<mutex> lock(m_mutex);
    //if (!m_instance) {
    //    m_instance = new Singleton(value);
    //}
    //return m_instance;
    static Singleton* instance = new Singleton(value);
    return instance;
}

void Cat() {
    Singleton* singleton = Singleton::getInstance("Cat");
    cout << singleton << endl;
    cout << singleton->value() << endl;
}

void Dog() {
    Singleton* singleton = Singleton::getInstance("Dog");
    cout << singleton << endl;
    cout << singleton->value() << endl;
}

void TestSingleton() {
    //Cat();
    //Dog();

    thread t1(Cat);
    thread t2(Dog);
    t1.join();
    t2.join();

}