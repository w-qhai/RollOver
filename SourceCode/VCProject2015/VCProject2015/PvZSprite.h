#pragma once
#include "CommonClass.h"
#include <iostream>
#include <string>
#include <set>
#include <thread>
class PvZSprite : public CAnimateSprite
{
public:
    PvZSprite(const char* sprite_name);
    virtual const std::string get_type() = 0;
    bool is_exist() { return exist; }
    virtual void set_exist(bool exist) {}
protected:
    bool exist;
};

