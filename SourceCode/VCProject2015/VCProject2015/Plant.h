#pragma once
#include "PvZSprite.h"
#include "Zombie.h"
#include "Arms.h"
#include "Assist.h"

// 植物基类
class Plant : public PvZSprite 
{
public:
    Plant(const char* sprite_name, double health, int attack_interval, int cost);
    virtual int attack(float delta_time) = 0;
    virtual bool attacked_by(Zombie* zombie);
    
    const char* get_type() override;
    void set_exist(bool exist);
    int get_cost() { return cost; }
    void change_zombie_animation();
    void die();
protected:
    double health;                      // 血量
    long double next_attack;            // 距离下次攻击时间
    const float attack_interval;        // 攻击间隔
    static const char* type;            // 类型
    int cost;                           // 消耗阳光
    std::set<Zombie*> set_attack_zombie;    // 正在实施攻击的Zombie对象
};

// 豌豆射手 继承自植物基类
class PeaShooter : public Plant {

public:
    PeaShooter(const char* plant_name, Pea* pea);
    int attack(float delta_time) override;
private:
    Pea* pea;
};


// 向日葵 继承自植物基类
class Sunflower : public Plant {

public:
    Sunflower(const char* plant_name, Sun* sun);
    int attack(float delta_time) override;
private:
    Sun* sun;
};

// 樱桃炸弹 继承自植物基类
class CherryBomb : public Plant {

public:
    CherryBomb(const char* plant_name, Boom* boom, long double plant_time);
    int attack(float delta_time) override;
    bool preparation(float delta_time);
    void set_exist(bool exist) override;
private:
    Boom* boom;
    long double plant_time;
};


// 土豆地雷 继承自植物基类
class PotatoMine : public Plant {

public:
    PotatoMine(const char* plant_name, Boom* boom, long double plant_time);
    int attack(float delta_time) override;
    bool preparation(float delta_time);
private:
    Boom* boom;
    long double plant_time;
    const float preparation_time;
};

// 坚果 继承自植物基类
class WallNut : public Plant {

public:
    WallNut(const char* plant_name);
    virtual bool attacked_by(Zombie* zombie) override;
    int attack(float delta_time) override; // 纯虚函数 坚果无攻击行为，所以是个空函数
};

// 火爆辣椒 继承自植物基类
class Jalapeno : public Plant {

public:
    Jalapeno(const char* plant_name, Boom* boom, long double plant_time);
    int attack(float delta_time) override;
    bool preparation(float delta_time);
    void set_exist(bool exist) override;
private:
    Boom* boom;
    long double plant_time;
};


