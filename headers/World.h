#pragma once
#include "Grid.h"
#include "Dirt.h"
#include "Grass.h"
#include "rabbit.h"
#include "wolf.h"
#include <stack>
#include <time.h>   //for time
#include <stdlib.h> //for rand
#include <iostream>
#include <vector>
#include "Parameters.h"
#include <fstream>

//World class: Stores the grid
class World
{
private:
    //This is the double vector filed with Pointers to Grid
    std::vector<std::vector<Grid *>> field;

public:
    //World Constructor. the input is the n dimension of the field
    World(int dimension)
    {
        for (int i = 0; i < dimension; i++)
        {
            std::vector<Grid *> temp;
            for (int j = 0; j < dimension; j++)
            {
                Grid *k;
                temp.push_back(k);
            }
            field.push_back(temp);
        }
    }
    //copy constructor
    World(World &other)
    {
        field=other.field;
    }
    //This operator allows you to access each specific coordinate of the field
    std::vector<Grid *> &operator[](int x) //return field
    {
        return field[x];
    }
    //This returns the width/Length of the world
    int size() //print out the size
    {
        return field.size();
    }
};

