#include "util.h"

/**
 * @brief 享元
 * 分类: 结构型(对象)
 * 运用共享技术有效的支持大量细粒度的对象
*/

// 内部状态(共享部分)
struct SharedState
{
    string m_brand;
    string m_model;
    string m_color;
    SharedState(const string& brand, const string& model, const string& color)
        :m_brand(brand), m_model(model), m_color(color) {}

    friend ostream& operator<<(ostream& os, const SharedState& ss) {
        return os << "[ " << ss.m_brand << ", " << ss.m_model << "," << ss.m_color << " ]";
    }
};

// 外部状态
struct UniqueState
{
    string m_owner;
    string m_plates;
    UniqueState(const string& owner, const string& plates)
        :m_owner(owner), m_plates(plates) {}

    friend ostream& operator<<(ostream& os, const UniqueState& us) {
        return os << "[ " << us.m_owner << ", " << us.m_plates << " ]";
    }
};

// 享元，存放共享状态，内部状态
class FlyWeight
{
private:
    SharedState m_sharedState;
public:
    FlyWeight(const SharedState& ss):m_sharedState(ss) {}
    void operation(UniqueState& us) const {
        // 使用的时候，使用外部状态作为参数，对整个context做出操作
        cout << "FlyWeight: 显示内部状态 ("
            << m_sharedState << "), 显示外部状态: ("
            << us << endl;
    }
};

class FlyWeightFactory
{
private:
    unordered_map<string, FlyWeight> m_flyWeights;

    string getKey(const SharedState& ss) const {
        return ss.m_brand + "_" + ss.m_model + "_" + ss.m_color;
    }
public:
    FlyWeightFactory(initializer_list<SharedState> sharedStates) {
        for (const SharedState& ss : sharedStates) {
            m_flyWeights.insert({ getKey(ss), ss });
        }
    }
    FlyWeight* getFlyWeight(const SharedState& ss) {
        string key = getKey(ss);
        if (m_flyWeights.find(key) == m_flyWeights.end()) {
            cout << "FlyWeightFactory: 没有找到需要的享元，创建一个新的" << endl;
            m_flyWeights.insert({ key, ss });
        } else {
            cout << "FlyWeightFactory: 返回一个现有的享元。" << endl;
        }
        return &m_flyWeights.at(key);
    }

    void listFlyWeights() const {
        int count = m_flyWeights.size();
        cout << "FlyWeightFactory: 我有" << count << "个享元:" << endl;
        for (pair<string, FlyWeight> item : m_flyWeights) {
            cout << item.first << endl;
        }
    }
};

class CarInfoContext
{
private:
    FlyWeight* m_flyWeight = nullptr;   // 内部状态
    UniqueState m_uniqueState;          // 外部状态
public:
    CarInfoContext(FlyWeight* fw, UniqueState* us)
    :m_flyWeight(fw), m_uniqueState(*us){}

    void operation() {
        m_flyWeight->operation(m_uniqueState);
    }
};

// 客户端
class PoliceCarDB
{
private:
    list<CarInfoContext*> m_carInfoDB;
public:
    ~PoliceCarDB() {
        for (auto item : m_carInfoDB) {
            delete item;
        }
    }

    void addCarToDB(FlyWeightFactory& ff,
        const string& owner, const string& plates,
        const string& brand, const string& model, const string& color) {
        cout << "客户端: 添加车辆信息到数据库" << endl;
        FlyWeight* fw = ff.getFlyWeight({ brand, model, color });
        UniqueState us(owner, plates);
        m_carInfoDB.emplace_back(new CarInfoContext(fw, &us));
        cout << "客户端: 数据库当前状态:" << endl;
        for (auto item : m_carInfoDB) {
            item->operation();
        }
    }
};

void TestFlyWeight() {
    FlyWeightFactory factory({
        SharedState("奔驰", "GLC", "白色"),
        SharedState("奥迪", "A7", "黑色"),
        SharedState("宝马", "X3", "白色")
        });
    factory.listFlyWeights();
    cout << endl;
    PoliceCarDB db;
    db.addCarToDB(factory, "user1", "陕A111111", "宝马", "X3", "白色");
    factory.listFlyWeights();
    cout << endl;
    db.addCarToDB(factory, "user1", "陕A111199", "比亚迪", "汉", "白色");
    db.addCarToDB(factory, "user1", "陕A111112", "奥迪", "A7", "黑色");
    factory.listFlyWeights();
    cout << endl;
}