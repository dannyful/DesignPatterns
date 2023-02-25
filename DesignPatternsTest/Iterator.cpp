#include "util.h"

/**
 * @brief 迭代器
 * 分类: 行为型(对象)
 * 提供一种方法顺序访问一个聚合对象中各个元素，
 * 而又不需暴露该对象的内部表示。
*/

template <class T, class D>
class Iterator
{
public:
    typedef typename list<T>::iterator Pointer;
    Iterator(D* container, bool reverse = false)
        :m_container(container) {};

    void first() {
        m_iter = m_container->m_data.begin();
    }

    void next() {
        m_iter++;
    }

    bool empty() {
        return m_iter == m_container->m_data.end();
    }

    Pointer current() {
        return m_iter;
    }

private:
    D* m_container;
    Pointer m_iter;
};

template <class T>
class Container
{
    friend class Iterator<T, Container>;
public:
    Iterator<T, Container>* createIterator(){
        return new Iterator<T, Container>(this);
    }
    void add(T data) {
        m_data.push_back(data);
    }
private:
    list<T> m_data;
};

class MenuItem
{
public:
    ~MenuItem() {}
    virtual void setData(string data1, string data2 = "") = 0;
    virtual string data() const = 0;
};


class BeverageTea :public MenuItem
{
public:
    BeverageTea(string data1, string data2)
        :m_data1(data1), m_data2(data2) {}
    ~BeverageTea() {}
    virtual void setData(string data1, string data2 = "") override {
        m_data1 = data1;
        m_data2 = data2;
    }
    virtual string data() const override {
        return m_data1 +"_" + m_data2;
    }
private:
    string m_data1;
    string m_data2;
};

class Pizza :public MenuItem
{
public:
    Pizza(string data) :m_data(data) {}
    ~Pizza() {}
    virtual void setData(string data1, string data2 = "") override {
        m_data = data1;
    }
    virtual string data() const override {
        return m_data;
    }
private:
    string m_data;
};

template <class T>
void clientCode(T* iter) {
    for (iter->first(); !iter->empty(); iter->next()) {
        cout << iter->current()->data() << endl;
    }
}

void TestIterator() {

    Container<BeverageTea> beverageMenu;
    BeverageTea coffer("美式", "咖啡"), bubbleTea("珍珠", "奶茶");
    beverageMenu.add(coffer);
    beverageMenu.add(bubbleTea);

    cout << "Iterator 用于遍历BeverageTea菜单:" << endl;
    //Iterator<BeverageTea, Container<BeverageTea>>* 
    auto it = beverageMenu.createIterator();
    clientCode(it);

    Container<Pizza> pizzaMenu;
    Pizza a("蔬菜披萨"), b("海鲜披萨"), c("披萨");
    pizzaMenu.add(a);
    pizzaMenu.add(b);
    pizzaMenu.add(c);

    cout << "Iterator 用于遍历Pizza菜单:" << endl;
    //Iterator<Pizza, Container<Pizza>>* 
    auto it2 = pizzaMenu.createIterator();
    clientCode(it2);
}