#pragma once
#include "Grid.h"

class Dirt : public Grid

{

public:
    //Constructor
    Dirt(int walk = 0, int defHealth = 4, int spawnrate = 0, int maxage = 4) : Grid(walk, defHealth, spawnrate, maxage) {}
    ~Dirt()
    {
    }
    void eat();
    int move();
    bool act();
    int multiply();
    int powerLevel();
    std::string type();
    bool checkHealth();
};
#include "Dirt.cpp"