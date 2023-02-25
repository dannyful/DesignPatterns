#include "util.h"

/**
 * @brief 组合
 * 分类: 结构型(对象)
 * 将对象组成树形结构以表示"部分-整体"的层次结构。
 * 使得用户对单个对象和组合对象的使用具有一致性。
*/

// 接口: 不管是商品还是盒子，都依赖这个接口
class OrderNode
{
private:
    OrderNode* m_parent;
    float m_price;
public:
    virtual ~OrderNode(){}
    OrderNode()
        :m_parent(nullptr), m_price(0.0) {};
    OrderNode(float price)
        :m_parent(nullptr), m_price(price) {};

    void setParent(OrderNode* node) {
        m_parent = node;
    }
    OrderNode* getParent() { return m_parent; }
    virtual bool isLeaf() const { return false; }

    void setPrice(float price) {
        m_price = price;
    }
    float getPrice() { return m_price; }

    virtual string operation() = 0;
};

// 产品
class Product :public OrderNode
{
public:
    ~Product(){}
    Product(float price): OrderNode(price){}
    virtual string operation() override {
        return "产品";
    }
};

// 盒子
class Box :public OrderNode
{
protected:
    list<OrderNode*> m_children;
public:
    ~Box(){}
    Box(){}
    virtual bool isLeaf() const override { return true; }

    void add(OrderNode* node) {
        m_children.emplace_back(node);
        node->setParent(this);
        setPrice(getPrice() + node->getPrice());
    }

    void removee(OrderNode* node) {
        m_children.remove(node);
        node->setParent(nullptr);
        setPrice(getPrice() - node->getPrice());
    }

    virtual string operation() override {
        string res;
        float totle = 0.0;
        for (OrderNode* node : m_children) {
            res += node->operation();
            if (node != m_children.back()) {
                res += "+";
            }
            totle += node->getPrice();
        }
        setPrice(totle);

        return "盒子 {" + res + "}";
    }
};

void clientCode(OrderNode* node) {
    cout << "结构: " << node->operation() << endl;
    cout << "价格: " << node->getPrice() << endl;
}

void TestComposite() {
    cout << "处理叶子节点...." << endl;
    Product leaf(5.0);
    clientCode(&leaf);

    cout << endl;
    cout << "处理组合节点....." << endl;
    Product leaf1(5.0);
    Product leaf2(5.0);
    Product leaf3(5.0);
    Box tree, branch1, branch2;
    branch1.add(&leaf1);
    branch1.add(&leaf2);
    branch2.add(&leaf3);
    tree.add(&branch1);
    tree.add(&branch2);
    clientCode(&tree);
    tree.add(&leaf);
    clientCode(&tree);
}