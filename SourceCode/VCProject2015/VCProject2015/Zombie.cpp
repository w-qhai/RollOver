#include "Zombie.h"
#include "Plant.h"
const char* Zombie::type = "Zombie";

Zombie::Zombie(const char* sprite_name, int health, int move_speed, double power) :
    PvZSprite(sprite_name),
    health(health),
    move_speed(move_speed),
    power(power),
    next_attack(0),
    attack_interval(1),
    eating(false),
    eating_plant(nullptr)
{

}

const char* Zombie::get_type() {
    return type;
}
bool Zombie::is_eating() {
    return eating;
}

void Zombie::set_eating(bool eating) {
    this->eating = eating;
}

void Zombie::set_plant(Plant* plant) {
    eating_plant = plant;
}
Plant* Zombie::get_plant() {
    return eating_plant;
}

void Zombie::set_eating_plant(Plant* eating_plant) {
        this->eating_plant = eating_plant;
}

/////////////////////////
// 普通僵尸

OrdinaryZombie::OrdinaryZombie(const char* zombie_name) : Zombie(zombie_name, 200, 3, 50)
{

}

/// <summary>
/// 让僵尸开始移动
/// </summary>
void OrdinaryZombie::move() {
    this->eating = false;
    this->set_status();
    this->SetSpriteLinearVelocityX(-this->move_speed);
}

void OrdinaryZombie::stop() {
    this->set_status();
    this->SetSpriteLinearVelocityX(0);
}

void OrdinaryZombie::eat_plant(Plant* plant, long double delta_time) {
    if (delta_time - next_attack > attack_interval) {
        std::cout << "eating" << std::endl;
        plant->attacked_by(this);
        next_attack = delta_time;
    }
}



void OrdinaryZombie::attacked_by(Arms* arms) {
    this->health -= arms->get_power();
    if (this->health <= 0) {
        this->die(arms->get_power());
    }
    else {
        this->set_status();
    }
    arms->after_hit();
}

/// <summary>
/// 被击倒后
/// </summary>
void OrdinaryZombie::die(int power) {
    if (power < 1800) {
        this->SetSpriteWidth(20.625);
        this->SetSpriteHeight(10.625);
        this->SetSpriteLinearVelocityX(0);
        this->AnimateSpritePlayAnimation("ZombieDieAnimation", false);
        
    }
    else {
        this->SetSpriteLinearVelocityX(0);
        this->SetSpriteWidth(9.875);
        this->SetSpriteHeight(14.125);
        this->SetSpriteLinearVelocityX(0);
        this->AnimateSpritePlayAnimation("BoomDieAnimation", false);
    }
    this->SetSpriteCollisionActive(false, false);
    // 播放死亡动画
    this->SetSpriteLifeTime(1);
    exist = false;
}

double OrdinaryZombie::get_power() {
    return power;
}

OrdinaryZombie::~OrdinaryZombie() {
    std::cout << "~OrdinaryZombie()" << std::endl;
}

void OrdinaryZombie::set_status() {
        std::string currentAnimation = this->GetAnimateSpriteAnimationName();
        float currentPositionY = this->GetSpritePositionY();
        if (this->health > 100) {
                if (eating_plant && eating_plant->is_exist()) {
                        if (currentAnimation != "ZombieAttackAnimation") {
                                this->AnimateSpritePlayAnimation("ZombieAttackAnimation", false);

                        }
                }
                else {
                        if (currentAnimation != "OrdinaryZombieAnimation") {
                                this->AnimateSpritePlayAnimation("OrdinaryZombieAnimation", false);
                        }
                }
        }
        else if (this->health <= 100) {
                if (eating_plant && eating_plant->is_exist()) {
                        if (currentAnimation != "ZombieLoseHeadAttackAnimation") {
                                this->AnimateSpritePlayAnimation("ZombieLoseHeadAttackAnimation", false);
                                this->SetSpriteWidth(11.125);
                                this->SetSpriteHeight(12.875);
                                this->SetSpritePositionY(currentPositionY + 1);
                        }
                }
                else {
                        if (currentAnimation != "ZombieLoseHeadAnimation") {
                                this->AnimateSpritePlayAnimation("ZombieLoseHeadAnimation", false);
                                this->SetSpriteWidth(10.000);
                                this->SetSpriteHeight(11.875);
                                this->SetSpritePositionY(currentPositionY + 1);
                        }
                }
        }
}

/////////////////////////
// 路障僵尸

BarricadeZombie::BarricadeZombie(const char* zombie_name) : Zombie(zombie_name, 640, 3, 50)
{

}

/// <summary>
/// 让僵尸开始移动
/// </summary>
void BarricadeZombie::move() {
        this->eating = false;
        this->set_status();
        this->SetSpriteLinearVelocityX(-this->move_speed);
}

void BarricadeZombie::stop() {
        this->set_status();
        this->SetSpriteLinearVelocityX(0);
}

void BarricadeZombie::eat_plant(Plant* plant, long double delta_time) {
        if (delta_time - next_attack > attack_interval) {
                std::cout << "eating" << std::endl;
                plant->attacked_by(this);
                next_attack = delta_time;
        }
}



void BarricadeZombie::attacked_by(Arms* arms) {
        this->health -= arms->get_power();

        std::cout << "路障僵尸当前血量：" << this->health << std::endl;

        if (this->health <= 0) {
                this->die(arms->get_power());
        }
        else {
                this->set_status();
        }
        arms->after_hit();
}

/// <summary>
/// 被击倒后
/// </summary>
void BarricadeZombie::die(int power) {
        if (power < 1800) {
                this->SetSpriteWidth(20.625);
                this->SetSpriteHeight(10.625);
                this->SetSpriteLinearVelocityX(0);
                this->AnimateSpritePlayAnimation("ZombieDieAnimation", false);
        }
        else {
                this->SetSpriteLinearVelocityX(0);
                this->SetSpriteWidth(9.875);
                this->SetSpriteHeight(14.125);
                this->SetSpriteLinearVelocityX(0);
                this->AnimateSpritePlayAnimation("BoomDieAnimation", false);
        }
        this->SetSpriteCollisionActive(false, false);
        // 播放死亡动画
        this->SetSpriteLifeTime(1);
        exist = false;
}

double BarricadeZombie::get_power() {
        return power;
}

BarricadeZombie::~BarricadeZombie() {
        std::cout << "~OrdinaryZombie()" << std::endl;
}

void BarricadeZombie::set_status() {
        std::string currentAnimation = this->GetAnimateSpriteAnimationName();
        float currentPositionY = this->GetSpritePositionY();
        if (this->health > 270) {
                if (eating_plant && eating_plant->is_exist()) {
                        if (currentAnimation != "BarricadeZombieAttackAnimation") {
                                this->AnimateSpritePlayAnimation("BarricadeZombieAttackAnimation", false);
                                this->SetSpriteWidth(10.875);
                                this->SetSpriteHeight(18.00);
                        }


                }
                else {
                        if (currentAnimation != "BarricadeZombieAnimation") {
                                this->AnimateSpritePlayAnimation("BarricadeZombieAnimation", false);
                                this->SetSpriteWidth(10.875);
                                this->SetSpriteHeight(18.00);
                        }
                        
                }
        }
        else if (this->health >= 90) {
                if (eating_plant && eating_plant->is_exist()) {
                        if (currentAnimation != "ZombieAttackAnimation") {
                                this->AnimateSpritePlayAnimation("ZombieAttackAnimation", false);
                                this->SetSpriteWidth(10.875);
                                this->SetSpriteHeight(15.50);
                                this->SetSpritePositionY(currentPositionY + 1);
                        }
                        
                }
                else {
                        if (currentAnimation != "OrdinaryZombieAnimation") {
                                this->AnimateSpritePlayAnimation("OrdinaryZombieAnimation", false);
                                this->SetSpriteWidth(10.875);
                                this->SetSpriteHeight(15.50);
                                this->SetSpritePositionY(currentPositionY + 1);
                        }

                }
        }
        else
        {
                if (eating_plant && eating_plant->is_exist()) {
                        if (currentAnimation != "ZombieLoseHeadAttackAnimation") {
                                this->AnimateSpritePlayAnimation("ZombieLoseHeadAttackAnimation", false);
                                this->SetSpriteWidth(11.125);
                                this->SetSpriteHeight(12.875);
                                float currentPositionY = this->GetSpritePositionY();
                                this->SetSpritePositionY(currentPositionY + 1);
                        }


                }
                else {
                        if (currentAnimation != "ZombieLoseHeadAnimation") {
                                this->AnimateSpritePlayAnimation("ZombieLoseHeadAnimation", false);

                                this->SetSpriteWidth(10.000);
                                this->SetSpriteHeight(11.875);
                                float currentPositionY = this->GetSpritePositionY();
                                this->SetSpritePositionY(currentPositionY + 1);
                        }

                }
        }
}


/////////////////////////
// 铁桶僵尸

BucketheadZombie::BucketheadZombie(const char* zombie_name) : Zombie(zombie_name, 1370, 3, 50)
{

}

/// <summary>
/// 让僵尸开始移动
/// </summary>
void BucketheadZombie::move() {
        this->eating = false;
        this->set_status();
        this->SetSpriteLinearVelocityX(-this->move_speed);
}

void BucketheadZombie::stop() {
        this->set_status();
        this->SetSpriteLinearVelocityX(0);
}

void BucketheadZombie::eat_plant(Plant* plant, long double delta_time) {
        if (delta_time - next_attack > attack_interval) {
                std::cout << "eating" << std::endl;
                plant->attacked_by(this);
                next_attack = delta_time;
        }
}



void BucketheadZombie::attacked_by(Arms* arms) {
        this->health -= arms->get_power();

        std::cout << "铁桶僵尸当前血量：" << this->health << std::endl;

        if (this->health <= 0) {
                this->die(arms->get_power());
        }
        else {
                this->set_status();
        }
        arms->after_hit();
}

/// <summary>
/// 被击倒后
/// </summary>
void BucketheadZombie::die(int power) {
        if (power < 1800) {
                this->SetSpriteWidth(20.625);
                this->SetSpriteHeight(10.625);
                this->SetSpriteLinearVelocityX(0);
                this->AnimateSpritePlayAnimation("ZombieDieAnimation", false);
        }
        else {
                this->SetSpriteLinearVelocityX(0);
                this->SetSpriteWidth(9.875);
                this->SetSpriteHeight(14.125);
                this->SetSpriteLinearVelocityX(0);
                this->AnimateSpritePlayAnimation("BoomDieAnimation", false);
        }
        this->SetSpriteCollisionActive(false, false);
        // 播放死亡动画
        this->SetSpriteLifeTime(1);
        exist = false;
}

double BucketheadZombie::get_power() {
        return power;
}

BucketheadZombie::~BucketheadZombie() {
        std::cout << "~OrdinaryZombie()" << std::endl;
}

void BucketheadZombie::set_status() {
        std::string currentAnimation = this->GetAnimateSpriteAnimationName();
        float currentPositionY = this->GetSpritePositionY();
        if (this->health > 270) {
                if (eating_plant && eating_plant->is_exist()) {
                        if (currentAnimation != "BucketheadZombieAttackAnimation") {
                                this->AnimateSpritePlayAnimation("BucketheadZombieAttackAnimation", false);
                                this->SetSpriteWidth(11.5);
                                this->SetSpriteHeight(17.625);
                        }


                }
                else {
                        if (currentAnimation != "BucketheadZombieAnimation") {
                                this->AnimateSpritePlayAnimation("BucketheadZombieAnimation", false);
                                this->SetSpriteWidth(11.5);
                                this->SetSpriteHeight(17.625);
                        }

                }
        }
        else if (this->health >= 90) {
                if (eating_plant && eating_plant->is_exist()) {
                        if (currentAnimation != "ZombieAttackAnimation") {
                                this->AnimateSpritePlayAnimation("ZombieAttackAnimation", false);
                                this->SetSpriteWidth(10.875);
                                this->SetSpriteHeight(15.50);
                                this->SetSpritePositionY(currentPositionY + 1);
                        }

                }
                else {
                        if (currentAnimation != "OrdinaryZombieAnimation") {
                                this->AnimateSpritePlayAnimation("OrdinaryZombieAnimation", false);
                                this->SetSpriteWidth(10.875);
                                this->SetSpriteHeight(15.50);
                                this->SetSpritePositionY(currentPositionY + 1);
                        }

                }
        }
        else
        {
                if (eating_plant && eating_plant->is_exist()) {
                        if (currentAnimation != "ZombieLoseHeadAttackAnimation") {
                                this->AnimateSpritePlayAnimation("ZombieLoseHeadAttackAnimation", false);
                                this->SetSpriteWidth(11.125);
                                this->SetSpriteHeight(12.875);
                                float currentPositionY = this->GetSpritePositionY();
                                this->SetSpritePositionY(currentPositionY + 1);
                        }


                }
                else {
                        if (currentAnimation != "ZombieLoseHeadAnimation") {
                                this->AnimateSpritePlayAnimation("ZombieLoseHeadAnimation", false);

                                this->SetSpriteWidth(10.000);
                                this->SetSpriteHeight(11.875);
                                float currentPositionY = this->GetSpritePositionY();
                                this->SetSpritePositionY(currentPositionY + 1);
                        }

                }
        }
}


/////////////////////////
// 二大爷

NewspaperZombie::NewspaperZombie(const char* zombie_name) : Zombie(zombie_name, 450, 3, 50)
{
        this->hasnewspaper = true;
}

/// <summary>
/// 让僵尸开始移动
/// </summary>
void NewspaperZombie::move() {
        this->eating = false;
        this->set_status();
        this->SetSpriteLinearVelocityX(-this->move_speed);
}

void NewspaperZombie::stop() {
        this->set_status();
        this->SetSpriteLinearVelocityX(0);
}

void NewspaperZombie::eat_plant(Plant* plant, long double delta_time) {
        if (delta_time - next_attack > attack_interval) {
                std::cout << "eating" << std::endl;
                plant->attacked_by(this);
                next_attack = delta_time;
        }
}



void NewspaperZombie::attacked_by(Arms* arms) {
        this->health -= arms->get_power();

        std::cout << "报纸僵尸当前血量：" << this->health << std::endl;

        if (this->health <= 0) {
                this->die(arms->get_power());
        }
        else {
                this->set_status();
        }
        arms->after_hit();
}

/// <summary>
/// 被击倒后
/// </summary>
void NewspaperZombie::die(int power) {
        if (power < 1800) {
                this->SetSpriteWidth(20.625);
                this->SetSpriteHeight(10.625);
                this->SetSpriteLinearVelocityX(0);
                this->AnimateSpritePlayAnimation("NewspaperZombieDieAnimation", false);
        }
        else {
                this->SetSpriteLinearVelocityX(0);
                this->SetSpriteWidth(9.875);
                this->SetSpriteHeight(14.125);
                this->SetSpriteLinearVelocityX(0);
                this->AnimateSpritePlayAnimation("BoomDieAnimation", false);
        }
        this->SetSpriteCollisionActive(false, false);
        // 播放死亡动画
        this->SetSpriteLifeTime(1);
        exist = false;
}

double NewspaperZombie::get_power() {
        return power;
}

NewspaperZombie::~NewspaperZombie() {
        
}

void NewspaperZombie::set_status() {
        std::string currentAnimation = this->GetAnimateSpriteAnimationName();
        float currentPositionY = this->GetSpritePositionY();
        if (this->health > 350) {
                if (eating_plant && eating_plant->is_exist()) {
                        if (currentAnimation != "NewspaperZombieAttackAnimation") {
                                this->AnimateSpritePlayAnimation("NewspaperZombieAttackAnimation", false);
                                this->SetSpriteWidth(12.0);
                                this->SetSpriteHeight(17.125);
                        }


                }
                else {
                        if (currentAnimation != "NewspaperZombieAnimation") {
                                this->AnimateSpritePlayAnimation("NewspaperZombieAnimation", false);
                                this->SetSpriteWidth(12.0);
                                this->SetSpriteHeight(17.125);
                        }

                }
        }
        else if (this->health >= 90) {

                if (this->hasnewspaper) {
                        if (currentAnimation != "NewspaperZombieLoseNewspaperAnimation")
                        {
                                this->SetSpriteLinearVelocityX(0);
                                this->power = 0;
                                this->AnimateSpritePlayAnimation("NewspaperZombieLoseNewspaperAnimation", false);
                                std::thread t([=] {
                                        while (!this->IsAnimateSpriteAnimationFinished())
                                                Sleep(50);
                                        this->power = 70;
                                        this->move_speed = this->move_speed + 2;
                                        this->SetSpriteLinearVelocityX(-this->move_speed);
                                        this->hasnewspaper = false;
                                        this->AnimateSpritePlayAnimation("NewspaperZombieCrazyAnimation", false);
                                        this->SetSpriteWidth(12.0);
                                        this->SetSpriteHeight(15.5);

                                });
                                t.detach();
                        }

                }
                else if (eating_plant && eating_plant->is_exist()) {
                        if (currentAnimation != "NewspaperZombieCrazyAttackAnimation" && currentAnimation != "NewspaperZombieLoseNewspaperAnimation") {
                                this->AnimateSpritePlayAnimation("NewspaperZombieCrazyAttackAnimation", false);
                                this->SetSpriteWidth(11.5);
                                this->SetSpriteHeight(15.5);
                                this->SetSpritePositionY(currentPositionY + 1);
                        }

                }
                else {
                        if (currentAnimation != "NewspaperZombieCrazyAnimation" && currentAnimation != "NewspaperZombieLoseNewspaperAnimation") {
                                this->AnimateSpritePlayAnimation("NewspaperZombieCrazyAnimation", false);
                                this->SetSpriteWidth(12.0);
                                this->SetSpriteHeight(15.5);
                                this->SetSpritePositionY(currentPositionY + 1);
                        }

                }
        }
        else
        {
                if (eating_plant && eating_plant->is_exist()) {
                        if (currentAnimation != "NewspaperZombieLoseHeadAttackAnimation" && currentAnimation != "NewspaperZombieLoseNewspaperAnimation") {
                                this->AnimateSpritePlayAnimation("NewspaperZombieLoseHeadAttackAnimation", false);
                                this->SetSpriteWidth(10.8);
                                this->SetSpriteHeight(12.5);
                                float currentPositionY = this->GetSpritePositionY();
                                this->SetSpritePositionY(currentPositionY + 1);
                        }


                }
                else {
                        if (currentAnimation != "NewspaperZombieLoseHeadAnimation" && currentAnimation != "NewspaperZombieLoseNewspaperAnimation") {
                                this->AnimateSpritePlayAnimation("NewspaperZombieLoseHeadAnimation", false);
                                this->SetSpriteWidth(10.8);
                                this->SetSpriteHeight(12.5);
                                float currentPositionY = this->GetSpritePositionY();
                                this->SetSpritePositionY(currentPositionY + 1);
                        }

                }
        }
}


/////////////////////////
// 橄榄球僵尸

FootballZombie::FootballZombie(const char* zombie_name) : Zombie(zombie_name, 1600, 4.5, 50)
{

}

/// <summary>
/// 让僵尸开始移动
/// </summary>
void FootballZombie::move() {
        this->eating = false;
        this->set_status();
        this->SetSpriteLinearVelocityX(-this->move_speed);
}

void FootballZombie::stop() {
        this->set_status();
        this->SetSpriteLinearVelocityX(0);
}

void FootballZombie::eat_plant(Plant* plant, long double delta_time) {
        if (delta_time - next_attack > attack_interval) {
                std::cout << "eating" << std::endl;
                plant->attacked_by(this);
                next_attack = delta_time;
        }
}



void FootballZombie::attacked_by(Arms* arms) {
        this->health -= arms->get_power();

        std::cout << "橄榄球僵尸当前血量：" << this->health << std::endl;

        if (this->health <= 0) {
                this->die(arms->get_power());
        }
        else {
                this->set_status();
        }
        arms->after_hit();
}

/// <summary>
/// 被击倒后
/// </summary>
void FootballZombie::die(int power) {
        if (power < 1800) {
                this->SetSpriteWidth(20.625);
                this->SetSpriteHeight(10.625);
                this->SetSpriteLinearVelocityX(0);
                this->AnimateSpritePlayAnimation("ZombieDieAnimation", false);
        }
        else {
                this->SetSpriteLinearVelocityX(0);
                this->SetSpriteWidth(9.875);
                this->SetSpriteHeight(14.125);
                this->SetSpriteLinearVelocityX(0);
                this->AnimateSpritePlayAnimation("BoomDieAnimation", false);
        }
        this->SetSpriteCollisionActive(false, false);
        // 播放死亡动画
        this->SetSpriteLifeTime(1);
        exist = false;
}

double FootballZombie::get_power() {
        return power;
}

FootballZombie::~FootballZombie() {

}

void FootballZombie::set_status() {
        std::string currentAnimation = this->GetAnimateSpriteAnimationName();
        float currentPositionY = this->GetSpritePositionY();
        if (this->health > 530) {
                if (eating_plant && eating_plant->is_exist()) {
                        if (currentAnimation != "FootballZombieAttackAnimation") {
                                this->AnimateSpritePlayAnimation("FootballZombieAttackAnimation", false);
                                this->SetSpriteWidth(16.25);
                                this->SetSpriteHeight(17.0);
                        }


                }
                else {
                        if (currentAnimation != "FootballZombieAnimation") {
                                this->AnimateSpritePlayAnimation("FootballZombieAnimation", false);
                                this->SetSpriteWidth(19.25);
                                this->SetSpriteHeight(20.0);
                        }

                }
        }
        else if (this->health >= 150) {
                if (eating_plant && eating_plant->is_exist()) {
                        if (currentAnimation != "FootballZombieLoseHatAttackAnimation") {
                                this->AnimateSpritePlayAnimation("FootballZombieLoseHatAttackAnimation", false);
                                this->SetSpriteWidth(16.25);
                                this->SetSpriteHeight(17.0);
                                float currentPositionY = this->GetSpritePositionY();
                                this->SetSpritePositionY(currentPositionY + 1);
                        }

                }
                else {
                        if (currentAnimation != "FootballZombieLoseHatAnimation") {
                                this->AnimateSpritePlayAnimation("FootballZombieLoseHatAnimation", false);
                                this->SetSpriteWidth(19.25);
                                this->SetSpriteHeight(20.0);
                                float currentPositionY = this->GetSpritePositionY();
                                this->SetSpritePositionY(currentPositionY + 1);
                        }

                }
        }
        else
        {
                if (eating_plant && eating_plant->is_exist()) {
                        if (currentAnimation != "FootballZombieLoseHeadAttackAnimation") {
                                this->AnimateSpritePlayAnimation("FootballZombieLoseHeadAttackAnimation", false);
                                this->SetSpriteWidth(15.25);
                                this->SetSpriteHeight(16.0);
                                float currentPositionY = this->GetSpritePositionY();
                                this->SetSpritePositionY(currentPositionY + 1);
                        }


                }
                else {
                        if (currentAnimation != "FootballZombieLoseHeadAnimation") {
                                this->AnimateSpritePlayAnimation("FootballZombieLoseHeadAnimation", false);
                                this->SetSpriteWidth(17.25);
                                this->SetSpriteHeight(18.0);
                                float currentPositionY = this->GetSpritePositionY();
                                this->SetSpritePositionY(currentPositionY + 1);
                        }

                }
        }
}