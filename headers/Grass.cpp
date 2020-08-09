#include "Grass.h"

void Grass::eat() {}
int Grass::move() { return 0; }
int Grass::multiply() { return spawnRate; }
bool Grass::act()
{
    if (age == FullAge)
    {
        return true;
    }
    age++;
    return false;
}
int Grass::powerLevel()
{
    return 1;
}
std::string Grass::type()
{
    return "Grass";
}
bool Grass::checkHealth()
{
    return true;
}