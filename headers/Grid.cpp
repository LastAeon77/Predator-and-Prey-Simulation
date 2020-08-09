#include "Grid.h"

//set the current previous to a string
void Grid::setPrevious(std::string k)
{
    Previous = k;
}

//get the "previous" string
std::string Grid::GetPrevious()
{
    return Previous;
}

//returns the current age
int Grid::currAge()
{
    return age;
}

//returns Current health
int Grid::currHealth()
{
    return Health;
}
