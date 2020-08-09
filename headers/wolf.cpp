#include "wolf.h"

bool Wolf::act()
{
    if (age == FullAge || Health == 0)
    {
        return true;
    }
    age++;
    Health--;
    return false;
}
void Wolf::eat()
{
    Health = FullHealth;
}
int Wolf::move()
{
    return baseWalkingDistance;
}
int Wolf::multiply()
{
    return spawnRate;
}

void Wolf::die()
{
    delete this;
}
int Wolf::powerLevel()
{
    return 3;
}
std::string Wolf::type()
{
    return "Wolf";
}
bool Wolf::checkHealth()
{
    if (Health <= (FullHealth / 2))
    {
        return false;
    }
    return true;
}
