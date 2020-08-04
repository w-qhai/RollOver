#include "Arms.h"

const char* Arms::type = "Arms";
Arms::Arms(const char* sprite_name, int power) :
    PvZSprite(sprite_name),
    power(power)
{

}

int Arms::get_power() {
    return power;
}

const char* Arms::get_type() {
    return type;
}


///////////////////////////////////////

Pea::Pea(const char* arms_name) :
    Arms(arms_name, 20)
{

}

/// <summary>
/// 攻击之后的特效
/// </summary>
void Pea::after_hit() {
    this->AnimateSpritePlayAnimation("BoomAnimation", false);
    this->SetSpriteCollisionActive(false, false);
    this->SetSpriteLinearVelocityX(0);
    this->SetSpriteLifeTime(0.5);
    exist = false;
}

///////////////////////

Boom::Boom(const char* arms_name) :
    Arms(arms_name, 1800)
{

}

/// <summary>
/// 攻击之后的特效
/// </summary>
void Boom::after_hit() {
    this->SetSpriteCollisionActive(false, false);
    this->SetSpriteLifeTime(0.5);
    exist = false;
}

///////////////////////