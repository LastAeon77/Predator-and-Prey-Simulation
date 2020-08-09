#pragma once
#include "Grid.h"

class Rabbit : public Grid

{

public:
    Rabbit(int walk = 5, int defHealth = 4, int spawnrate = 2, int maxage = 4) : Grid(walk, defHealth, spawnrate, maxage) {}
    void eat();
    int move();
    int multiply();
    bool check();
    bool act();
    void die();
    ~Rabbit()
    {
    }
    int powerLevel();
    std::string type();
    bool checkHealth();
    
};
#include "rabbit.cpp"