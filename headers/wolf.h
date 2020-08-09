#pragma once
#include "Grid.h"
class Wolf : public Grid
{

public:
    Wolf(int walk, int defHealth, int spawnrate, int maxage) : Grid(walk, defHealth, spawnrate, maxage) {}
    void eat();
    int move();
    int multiply();
    bool act();
    void die();
    ~Wolf()
    {
    }
    int powerLevel();
    std::string type();
    bool checkHealth();
};
#include "wolf.cpp"