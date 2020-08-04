#pragma once
#include "PvZSprite.h"
// ÎäÆ÷»ùÀà
class Arms : public PvZSprite {
public:
    Arms(const char* sprite_name, int power);
    virtual void after_hit() = 0;
    virtual int get_power();
    const char* get_type() override;
protected:
    int power;
    static const char* type;
};


// Íã¶¹ ¼Ì³Ğ×ÔÎäÆ÷
class Pea : public Arms
{
public:
    Pea(const char* arms_name);
    void after_hit() override;
};

// ±¬Õ¨ ¼Ì³Ğ×ÔÎäÆ÷
class Boom : public Arms
{
public:
    Boom(const char* arms_name);
    void after_hit() override;
};
