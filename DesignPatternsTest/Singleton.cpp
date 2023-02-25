#include "util.h"

/**
 * @brief 单例
 * 分类: 创建型(对象)
 * 保证一个类只有一个实例，
 * 并提供一个访问它的全局访问点。
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