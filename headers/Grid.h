#pragma once
#include <iostream>

class Grid

{
protected:
    int baseWalkingDistance;
    int Health;
    int spawnRate;
    int age;
    int FullHealth;
    int FullAge;
    bool movestatus;
    std::string Previous;

public:
    Grid(int walk = 10, int defHealth = 4, int spawnrate = 2, int maxage = 4)
    {
        baseWalkingDistance = walk;
        FullHealth = defHealth;
        spawnRate = spawnrate;
        age = 0;
        FullAge = maxage;
        Health = FullHealth / 2;
        Previous = "Dirt";
    }
    Grid(Grid &k)
    {
        baseWalkingDistance = k.baseWalkingDistance;
        Health = k.Health;
        spawnRate = k.spawnRate;
        age = k.age;
        FullHealth = k.FullHealth;
        FullAge = k.FullAge;
    }
    Grid &operator=(Grid &k)
    {
        baseWalkingDistance = k.baseWalkingDistance;
        Health = k.Health;
        spawnRate = k.spawnRate;
        age = k.age;
        FullHealth = k.FullHealth;
        FullAge = k.FullAge;
        return *this;
    }
    ~Grid()
    {
    }

    //Acts. Will increase age and decrease health. Grass and Dirt isn't affected
    //also checks if health is zero or age is full and will die if so.
    virtual bool act() = 0;

    //eats. Will restore health to full
    virtual void eat() = 0;

    //Returns
    virtual int move() = 0;

    //returns spawnrate
    virtual int multiply() = 0;

    //returns powerlevel of each species.
    //Wolf returns 3
    //Rabbit returns 2
    //grass returns 1
    //Dirt returns 0
    virtual int powerLevel() = 0;

    //returns the string to tell what type this is
    virtual std::string type() = 0;

    //this function will tell if the object is healthy enough to multiply
    virtual bool checkHealth() = 0;

    //set the current previous to a string
    void setPrevious(std::string k);

    //get the "previous" string
    std::string GetPrevious();

    //returns the current age
    int currAge();

    //returns Current health
    int currHealth();
};
#include "Grid.cpp"