#include "../headers/functions.h"
#include <algorithm>
#include <random>
int main()
{
    srand(time(NULL));
    World field(n);
    /*
    
    Set rabbit initial parameter numbers 

    */
    std::stack<Rabbit *> rabbitS;
    for (int i = 0; i < initialRabbitNum; i++)
    {
        Rabbit *k = new Rabbit(rabbitWalk, rabbitMaxHealth, rabbitSpawnrate, rabbitMaxAge);
        rabbitS.push(k);
    }

    std::stack<Wolf *> wolfS;

    /*
    
    Set rabbit initial parameter numbers 

    */
    for (int i = 0; i < initialWolfNum; i++)
    {
        Wolf *k = new Wolf(wolfWalk, wolfMaxHealth, wolfSpawnrate, wolfMaxHealth);
        wolfS.push(k);
    }
    //filling up all the field.
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            // 1/4 chance to spawn something
            int temp = rand() % 4;
            if (temp == 3)
            {
                field[i][j] = new Dirt();
            }
            else if (temp == 2)
            {
                field[i][j] = ptrGenerator(new Grass());
            }
            else
            {
                //Check if all the wolves or rabbit has ran out.
                if (wolfS.size() > 0 && rabbitS.size() > 0)
                {
                    if (temp == 1)
                    {
                        field[i][j] = wolfS.top();
                        wolfS.pop();
                    }
                    else
                    {
                        Grid *k = rabbitS.top();
                        field[i][j] = k;
                        rabbitS.pop();
                    }
                }
                else if (wolfS.size() > 0)
                {
                    field[i][j] = wolfS.top();
                    wolfS.pop();
                }
                else if (rabbitS.size() > 0)
                {
                    field[i][j] = rabbitS.top();
                    rabbitS.pop();
                }
                else
                {
                    field[i][j] = ptrGenerator(new Grass());
                }
            }
        }
    }
    auto rng = std::default_random_engine{};
    for (int i = 0; i < n; i++)
    {
        std::shuffle(std::begin(field[i]), std::end(field[i]), rng);
    }
    //First, repopulate
    //when repopulating, the new species will spawn
    //if it spawns on its predator, it will die
    //if it spans at the edge, it will spawn up left instead
    //Second, move and interact
    //third keep data
    //repeat

    //csv file
    std::vector<int> WolfCount;
    std::vector<int> RabbitCount;
    std::vector<int> GrassCount;
    std::vector<int> DirtCount;
    std::vector<int> Years;
    std::string filename = "Animal_Num_Data.csv";
    int start = 0;
    //print(field);
    //<-Un comment this function if you want to see the field at the start of code.
    while (cycle--)
    {
        //first for loop to do all action
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                std::string temp = field[i][j]->GetPrevious();
                //First, Popoulate.
                populate(field, i, j);
                //Second, act. Check if it
                if (field[i][j]->act()) //checks if the guy inside is dead
                {

                    replace(field, ptrGenerator(temp), i, j);
                }
                moveAway(field, i, j);

            }
        }
        //print(field);
        int wolfTemp = 0;
        int rabbitTemp = 0;
        int grassTemp = 0;
        int dirtTemp = 0;
        //Second for loop to count number of wolves, rabbits, grass etc.
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (field[i][j]->type() == "Wolf")
                {
                    wolfTemp++;
                }
                else if (field[i][j]->type() == "Rabbit")
                {
                    rabbitTemp++;
                }
                else if (field[i][j]->type() == "Grass")
                {
                    grassTemp++;
                }
                else
                {
                    dirtTemp++;
                }
            }
        }
        Years.push_back(start);
        WolfCount.push_back(wolfTemp);
        RabbitCount.push_back(rabbitTemp);
        GrassCount.push_back(grassTemp);
        DirtCount.push_back(dirtTemp);
        start++;
    }
    //print(field); <-Un comment this function if you want to see the field at the end of code.

    std::vector<std::pair<std::string, std::vector<int>>> Data;
    Data.push_back({"Years", Years});
    Data.push_back({"Wolf", WolfCount});
    Data.push_back({"Rabbit", RabbitCount});
    Data.push_back({"Grass", GrassCount});
    Data.push_back({"Dirt", DirtCount});
    write_csv(filename, Data);
 
    return 0;
    //For testing
    /*
    int tempt = 5;
    World newfield(tempt);
    for (int i = 0; i < tempt; i++)
    {
        for (int j = 0; j < tempt; j++)
        {
            newfield[i][j] = new Grass(0,0,0,6);
        }
    }
    delete newfield[0][0];
    //delete newfield[1][1];
    newfield[0][0] = new Rabbit(1,5,1,10);
    //newfield[1][1] = new Wolf(1,4,1,8);
    //field=newfield;
    //n=tempt;
    print(newfield);
     int num=10;
    while (num--)
    {
        std::cout<<"Cycle "<<-num+10<<std::endl;
        for (int i = 0; i < tempt; i++)
        {
            for (int j = 0; j < tempt; j++)
            {
                std::string temp = newfield[i][j]->GetPrevious();
                //populate(newfield,i,j);
                
                moveAway(newfield, i, j);
            }
        }
        print(newfield);
    }
    */
}
