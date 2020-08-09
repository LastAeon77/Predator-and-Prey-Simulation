#include "rabbit.h"

bool Rabbit::act()
{
    if (age == FullAge || Health == 0)
    {
        return true;
    }
    age++;
    Health--;
    return false;
}
void Rabbit::eat()
{
    Health = FullHealth;
}
int Rabbit::move()
{
    return baseWalkingDistance;
}
int Rabbit::multiply()
{
    return spawnRate;
}

void Rabbit::die()
{
    delete this;
}
int Rabbit::powerLevel()
{
    return 2;
}
std::string Rabbit::type()
{
    return "Rabbit";
}
bool Rabbit::checkHealth()

{
    if (Health <= (FullHealth / 2))
    {
        return false;
    }
    return true;
}
