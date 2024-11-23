#include "MacUILib.h"
#include "food.h"

Food::Food()
{
    srand(time(0));
    generateFood(objPos{-1, -1, ' '});
}

Food::~Food()
{

}

void Food::generateFood(objPos blockOff)
{
    //from ppa3
    bool unique = false;
    while (!unique)
    {
        unique = true;
        food.pos->x = rand() % (xRange - 2) + 1; //check what to use
        food.pos->y = rand() % (yRange - 2) + 1;
        food.symbol = (char)(rand() % (126 - 33 + 1) + 33);
        if (food.symbol == '*' || food.symbol == '#' || food.symbol == ' ') //double check symbols
        {
            unique = false;
            continue;
        }
        if (food.pos->x == blockOff.pos->x && food.pos->y == blockOff.pos->y)
        {
            unique = false;
            continue;
        }
    }
}

objPos Food::getFoodPos() const
{
    return food;
}