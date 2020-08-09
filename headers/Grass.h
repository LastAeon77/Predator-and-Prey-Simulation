#pragma once
#include "Grid.h"

class Grass : public Grid

{

public:
    Grass(int walk = 0, int defHealth = 1, int spawnrate = 2, int maxage = 1000) : Grid(walk, defHealth, spawnrate, maxage) {}
    ~Grass()
    {
    }
    void eat();
    int move() ;
    int multiply();
    bool act();
    int powerLevel();
    std::string type();
    bool checkHealth();
};
#include "Grass.cpp"