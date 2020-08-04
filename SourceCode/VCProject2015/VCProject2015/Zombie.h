#pragma once
#include "PvZSprite.h"
#include "Arms.h"
//#include "Plant.h"
class Plant;

class Zombie : public PvZSprite {
public:
    Zombie(const char* sprite_name, int health, int speed, double power);
    const char* get_type() override;

    virtual void move() = 0;
    virtual void stop() = 0;
    virtual void eat_plant(Plant* plant, long double delta_time) = 0;
    virtual void die(int power) = 0;
    virtual void attacked_by(Arms* arm) = 0;
    virtual double get_power() = 0;
    virtual void set_status() = 0;

    void set_exist(bool exist) { this->exist = exist; }

    bool is_eating();
    void set_eating(bool eating);
    void set_plant(Plant* plant);
    void set_eating_plant(Plant* eating_plant);
    Plant* get_plant();
protected:
    int health;
    int move_speed;
    double power;
    bool eating;
    Plant* eating_plant;
    float next_attack;                // 距离下次攻击时间
    const float attack_interval;      // 攻击间隔
    static const char* type;
};

class OrdinaryZombie : public Zombie {
public:
    OrdinaryZombie(const char* zombie_name);
    ~OrdinaryZombie();
    void move() override;
    void stop() override;
    void eat_plant(Plant* plant, long double delta_time) override;
    void die(int power) override;
    void attacked_by(Arms* arm) override;
    double  get_power() override;
    void set_status() override;
};


class BarricadeZombie : public Zombie {
public:
	BarricadeZombie(const char* zombie_name);
	~BarricadeZombie();
	void move() override;
	void stop() override;
	void eat_plant(Plant* plant, long double delta_time) override;
	void die(int power) override;
	void attacked_by(Arms* arm) override;
	double  get_power() override;
	void set_status() override;
};



class BucketheadZombie : public Zombie {
public:
	BucketheadZombie(const char* zombie_name);
	~BucketheadZombie();
	void move() override;
	void stop() override;
	void eat_plant(Plant* plant, long double delta_time) override;
	void die(int power) override;
	void attacked_by(Arms* arm) override;
	double  get_power() override;
	void set_status() override;
};


class NewspaperZombie : public Zombie {
public:
	NewspaperZombie(const char* zombie_name);
	~NewspaperZombie();
	void move() override;
	void stop() override;
	void eat_plant(Plant* plant, long double delta_time) override;
	void die(int power) override;
	void attacked_by(Arms* arm) override;
	double  get_power() override;
	void set_status() override;
private:
	bool hasnewspaper;
};

class FootballZombie : public Zombie {
public:
	FootballZombie(const char* zombie_name);
	~FootballZombie();
	void move() override;
	void stop() override;
	void eat_plant(Plant* plant, long double delta_time) override;
	void die(int power) override;
	void attacked_by(Arms* arm) override;
	double  get_power() override;
	void set_status() override;
};