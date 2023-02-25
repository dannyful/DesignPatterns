#include "util.h"

/**
 * @brief 策略
 * 分类: 行为型(对象)
 * 定义一些列的算法，
 * 把他们一个个封装起来。
 * 并且使它们可以相互替换。
 * 本模式使得算法可独立于使用它的客户而变化。
*/

// Strategy Interface
class Weapon
{
public:
    virtual string fightAlgorithm() const = 0;
};

class Nife: public Weapon
{
public:
    virtual string fightAlgorithm() const override {
        return "使用匕首计算损伤。";
    }
};

class Axe : public Weapon
{
public:
    virtual string fightAlgorithm() const override {
        return "使用斧子计算损伤。";
    }
};

// Context
class Hero1{
private:
    Weapon* m_weapon;
public:
    Hero1(Weapon* weapon) : m_weapon(weapon) {}
    void setWeapon(Weapon* weapon) {
        m_weapon = weapon;
    }

    void fight() {
        cout << m_weapon->fightAlgorithm() << endl;
    }
};

void TestStrategy() {
    cout << "客户端: 英雄使用匕首攻击。" << endl;
    Nife nife;
    Hero1 hero(&nife);
    hero.fight();
    cout << "客户端: 英雄使用斧子攻击。" << endl;
    Axe axe;
    hero.setWeapon(&axe);
    hero.fight();
}