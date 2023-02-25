#include "util.h"

/**
 * @brief 适配器
 * 分类: 结构型(类，对象)
 * 将一个类的接口转换为客户希望的另一个接口。
 * 是的原本不兼容的一些类可以一起工作。
 * 即创建一个适配器。
 * 这是一个特殊的对象，
 * 能够转换对象接口。
*/

// Target: 客户端需要的目标接口
class JsonInfo
{
public:
    virtual ~JsonInfo() {}
    virtual string request() const {
        return "Some Json information......";
    }
};

// Adapter: 客户端不兼容的接口，需要转换为Target接口
class XmlInfo
{
public:
    virtual string specialRequest() const {
        return "Some Xml information......";
    }
};


// Adapter: 适配器，就是把Adapter包装起来，让他看上去像是Target
class Xml2JsonAdapter : public JsonInfo
{
private:
    XmlInfo* m_adapter;
public:
    Xml2JsonAdapter(XmlInfo* xmlInfo) {
        m_adapter = xmlInfo;
    }
    virtual string request() const override {
        string  str = m_adapter->specialRequest();
        return "Json <- Xml2JsonAdapter <- " + str;;
    }
};

void clientCode(const JsonInfo* info) {
    cout << "股票分析软件运行Json:" << info->request() << endl;
    cout << "---------------------" << endl;
}

void TestAdapter() {
    JsonInfo jsonInfo;
    clientCode(&jsonInfo);
    XmlInfo xmlInfo;
    Xml2JsonAdapter adapter(&xmlInfo);
    clientCode(&adapter);
}
