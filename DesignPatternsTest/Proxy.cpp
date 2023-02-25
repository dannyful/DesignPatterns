#include "util.h"

/**
 * @brief 代理
 * 分类: 结构型(对象)
 * 为其他对象提供一种代理以控制这个对象的访问。
 * 即新建一个与原服务器对象接口相同的代理类，
 * 代理将自己伪装成数据库对象，
 * 对客户而言是透明的。
*/

// 接口: 真实的数据库和代理数据库都依赖这个接口
class Database
{
public:
    virtual void requese() const = 0;
};

class RealDatabase: public Database
{
public:
    virtual void requese() const override {
        cout << "--RealDatabase: 处理业务请求。" << endl;
    }
};

class ProxyDatabase : public Database
{
private:
    RealDatabase* m_realDB;
    bool checAccess() const {
        cout << "ProxyDatabase: 在发出请求之前，检查一下。" << endl;
        return true;
    }
    void log() const {
        cout << "ProxyDatabase: 处理日志" << endl;
    }
public:
    ProxyDatabase(RealDatabase* db): m_realDB(db) {}
    virtual void requese() const override {
        if(checAccess()){
            cout << "ProxyDatabase: 通过代理处理数据库请求。" << endl;
            m_realDB->requese();
            log();
        } else {
            cout << "ProxyDatabase: 数据库请求被驳回。" << endl;
        }
    }
};

void clientCode(const Database& db) {
    db.requese();
}

void TestProxy() {
    cout << "Client: 直接使用真实数据库处理请求:" << endl;
    RealDatabase realDB;
    clientCode(realDB);

    cout << "Client: 通过代理处理数据库请求:" << endl;
    ProxyDatabase proxyDB(&realDB);
    clientCode(proxyDB);
}