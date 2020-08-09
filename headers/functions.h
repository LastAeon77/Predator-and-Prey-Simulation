#pragma once
#include "World.h"

//Opeartor<< to print out the whole world when needed
std::ostream &operator<<(std::ostream &out, Grid &k)
{
    out << k.type();
    return out;
}

//replace a pointer in grid[i][j] with *k
void replace(World &grid, Grid *k, int i, int j);

//Check if it is eaten. If it returns true, it means something is eaten (and dependeing on that it could get replaced)
//This function is used for moving animals around
//Bool because it makes it easier to test
bool checkHierachy(World &grid, int Currenti, int Currentj, int comingIni, int comingInj);

//similar function to earlier, except used for populating a new place.
//Bool because it makes it easier to test
bool checkHierachy(World &grid, Grid *current, Grid *comingIn, int i, int j);
//Move away from a place and check if that place is eaten
void moveAway(World &grid, int currentX, int currentY);

//repopulate itself
void populate(World &grid, int x, int y);

//generate pointers templated from another
Grid *ptrGenerator(Grid *k);

//generate pointers from string
Grid *ptrGenerator(std::string k);

//Print out the field
void print(World &grid);

//https://www.gormanalysis.com/blog/reading-and-writing-csv-files-with-cpp/
//Prints out the CSV file to input data at the end. Source above
void write_csv(std::string filename, std::vector<std::pair<std::string, std::vector<int>>> dataset);

//Deletes one grid to replace it with another.
//the value in k is copied over to grid[i][j]
void replace(World &grid, Grid *k, int i, int j)
{
    //deletes the grid[i][j]
    delete grid[i][j];
    //replaces it with the other grid object
    grid[i][j] = k;
}
bool checkHierachy(World &grid, int Currenti, int Currentj, int comingIni, int comingInj)
{

    //If the powerlevel of the current grid object is one higher then the incoming, the the current will eat the incoming.
    //for example, the Wolf powerlevel is 3, and the rabbit's 2. The rabbit will move in, but will become the wolf's meal instead
    if (grid[Currenti][Currentj]->powerLevel() - grid[comingIni][comingInj]->powerLevel() == 1)
    {
        //This returns the previous residence (Aka, the previous pointer "name") to us.
        std::string temp = grid[comingIni][comingInj]->GetPrevious();
        //The current grid will "eat", this allows it to regain max health
        grid[Currenti][Currentj]->eat();
        //The previous coordinate of the incoming Grid will be instead replaced by what was previously
        //held there by using the previous residence we got earlier.
        grid[comingIni][comingInj] = ptrGenerator(temp);
        //returns false because the current coordinate isn't replaced.
        return false;
    }
    //If the ones coming in has a higher powerlevel than the one currently in place(by one, wolves can't eat grass)
    //For example, a rabbit moves into a grass grid. It will eat the grass and replace itself with the grass. It's previous occupance is now repalced with dirt
    else if (grid[Currenti][Currentj]->powerLevel() - grid[comingIni][comingInj]->powerLevel() == -1)
    {
        //This returns the previous residence (Aka, the previous pointer "name") to us.
        std::string temp = grid[comingIni][comingInj]->GetPrevious();
        //the ones coming in has found food, and eaten.
        grid[comingIni][comingInj]->eat();
        //The one coming in is replacing the one currently here in this coordinate
        replace(grid, grid[comingIni][comingInj], Currenti, Currentj);
        //The previous coordinate of the incoming Grid will be instead replaced by what was previously
        //held there by using the previous residence we got earlie
        grid[comingIni][comingInj] = ptrGenerator(temp);
        return true; //current gets eaten
    }
    //If they are equal, nothing happens and returns false
    else if (grid[Currenti][Currentj]->powerLevel() == grid[comingIni][comingInj]->powerLevel())
    {
        //in this case, the ones that are going to come in and the ones residing in this coordinate is of the same type, so nothing happens
        return false;
    }
    //Otherwise, if the ones coming in if of higher power than the current, it will simply repalce it.
    else if (grid[comingIni][comingInj]->powerLevel() > grid[Currenti][Currentj]->powerLevel())
    {
        //This returns the previous residence (Aka, the previous pointer "name") to us.
        std::string temp = grid[comingIni][comingInj]->GetPrevious();
        //The one coming in is replacing the one currently here in this coordinate
        replace(grid, grid[comingIni][comingInj], Currenti, Currentj);
        //replaced by older coordinate.
        grid[comingIni][comingInj] = ptrGenerator(temp);
        //returns true because it has been succesfully replaced.
        return true;
    }
    //if the ones coming in is weaker than the ones here, nothing will happen. (However this is impossible anyways in the context of our project)
    //There is no animal that can move that is 2 levels above the other.
    return false;
}
bool checkHierachy(World &grid, Grid *current, Grid *comingIn, int i, int j)
{

    //works in the exact same way as above.
    if (current->powerLevel() - comingIn->powerLevel() == 1)
    {
        current->eat(); //make it eat
        return false; 
    }
    //If the power level of the one coming in is greater, replace.
    else if (current->powerLevel() - comingIn->powerLevel() == -1)
    {
        //make it eat
        comingIn->eat();
        replace(grid, comingIn, i, j);
        return true; //current gets eaten
    }
    //nothing happens if its equal
    else if (current->powerLevel() == comingIn->powerLevel())
    {
        return false;
    }
    //simply replace without doing anything
    else if (comingIn->powerLevel() > current->powerLevel())
    {
        replace(grid, comingIn, i, j);
        return true;
    }
    return false;
}
void moveAway(World &grid, int currentX, int currentY)
{
    //First, get the max distance by which the animal is allowed to move
    int distance = grid[currentX][currentY]->move();

    //Second, make the distance be in the range of {-distance...distance} for both x and y axis
    int randomx = (rand() % (distance * 2 + 1)) - distance;
    int randomy = (rand() % (distance * 2 + 1)) - distance;

    //While loop until the values are appropriate enough to be applied to the grid(We don't want to go off chart)
    while (!((currentX + randomx <= grid.size() - 1 && currentY + randomy <= grid.size() - 1 && currentX + randomx >= 0 && currentY + randomy >= 0)))
    {
        randomx = rand() % (distance * 2 + 1) - distance;
        randomy = rand() % (distance * 2 + 1) - distance;
    }
    //The reason we check this is because we want to make sure that things with no possibility to move doesn't confuse itself.
    if (distance != 0)
    {
        //keep the previous occupied slot. (For example a wolf might be sitting on grass/dirt)
        std::string tempPrev = grid[currentX][currentY]->GetPrevious();
        checkHierachy(grid, currentX + randomx, currentY + randomy, currentX, currentY);
    }
}
void populate(World &grid, int x, int y)
{
    //checkHealth returns true if the animal is healthy enough to multiply, if not it will not be able to multiply
    if (grid[x][y]->checkHealth())
    {
        //we get the age
        int step = (grid[x][y])->currAge();
        //we get the spawnrate.
        int spawnRate = (grid[x][y])->multiply();
        //one random number
        int randomx = rand() % 3 - 1;
        //another random number.
        int randomy = rand() % 3 - 1;

        //if spawnrate or step is zero, it means that its probably a dirt block
        if (spawnRate != 0 && step != 0)
        {

            if (step % spawnRate == 0)
            {
                //while loop until numbers are appropriate
                while (!((x + randomx <= grid.size() - 1 && y + randomy <= grid.size() - 1 && x + randomx >= 0 && y + randomy >= 0)))
                {
                    randomx = rand() % 3 - 1;
                    randomy = rand() % 3 - 1;
                }
                //we are multiplying, so we make a new node of the same pointer type
                Grid *temp = ptrGenerator(grid[x][y]);

                //check hierachy if the place it is spreading too is appropriate
                checkHierachy(grid, grid[x + randomx][y + randomy], temp, x + randomx, y + randomy);
            }
        }
    }
}

//this functions basically makes a brand new copy of the ptr type and returns it
Grid *ptrGenerator(Grid *k)
{
    if (k->type() == "Wolf")
    {
        return new Wolf(wolfWalk, wolfMaxHealth, wolfSpawnrate, wolfMaxHealth);
    }
    else if (k->type() == "Rabbit")
    {
        return new Rabbit(rabbitWalk, rabbitMaxHealth, rabbitSpawnrate, rabbitMaxAge);
    }
    else if (k->type() == "Grass")
    {
        return new Grass(grassWalk, grassMaxHealth, grassSpawnrate, grassMaxAge);
    }
    else
    {
        return new Dirt();
    }
}
//this functions basically makes a brand new copy of pointer from the name of the type
Grid *ptrGenerator(std::string k)
{
    if (k == "Grass")
    {
        return new Grass(grassWalk, grassMaxHealth, grassSpawnrate, grassMaxAge);
    }
    else if (k == "Dirt")
    {
        return new Dirt();
    }
    else
    {
        std::cerr << "Something is wrong I can feel it" << std::endl;
        return new Dirt();
    }
}
//This allows us to print out the whole grid.
void print(World &grid)
{
    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid.size(); j++)
        {
            std::cout << *(grid[i][j]) << "  ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}
void write_csv(std::string filename, std::vector<std::pair<std::string, std::vector<int>>> dataset)
{

    std::ofstream myFile(filename);

    // Send column names to the stream
    for (int j = 0; j < dataset.size(); ++j)
    {
        myFile << dataset.at(j).first;
        if (j != dataset.size() - 1)
            myFile << ","; // No comma at end of line
    }
    myFile << "\n";

    // Send data to the stream
    for (int i = 0; i < dataset.at(0).second.size(); ++i)
    {
        for (int j = 0; j < dataset.size(); ++j)
        {
            myFile << dataset.at(j).second.at(i);
            if (j != dataset.size() - 1)
                myFile << ","; // No comma at end of line
        }
        myFile << "\n";
    }

    // Close the file
    myFile.close();
}