#include "MacUILib.h"
#include "food.h"

Food::Food()
{
    srand(time(0));
    numberOfFood = 3;
    
    
}

Food::~Food()
{

}

void Food::generateFood(objPos blockOff, objPos inputItem, int xRange, int yRange)
{
    //from ppa3
    bool unique = false;
    while (!unique)
    {
        unique = true;
        inputItem.pos->x = rand() % (xRange - 2) + 1; //check what to use
        inputItem.pos->y = rand() % (yRange - 2) + 1;
        
        inputItem.symbol = (char)(rand() % (126 - 33 + 1) + 33);

        if ((inputItem.symbol == '*' || inputItem.symbol == '#' || inputItem.symbol == ' ')||
        (inputItem.pos->x == blockOff.pos->x && inputItem.pos->y == blockOff.pos->y)) //double check symbols
        {
            unique = false;
            continue;
        }
    }
}

void Food::generateFoodBucket(objPos blockOff, int xRange, int yRange)
{
    objPos temp;

    for(int i = 0; i<numberOfFood; i++)
    {
        generateFood(blockOff, temp, xRange, yRange);
        foodBucket->getElement(i) = temp;
    }

    for(int i = 0; i<numberOfFood; i++)
    {
        for(int j = 0; j<numberOfFood; j++)
        {
            if(i!=j)
            {
                if(foodBucket->getElement(i).pos->x == foodBucket->getElement(j).pos->x 
                && foodBucket->getElement(i).pos->y == foodBucket->getElement(j).pos->y)
                {
                    generateFood(blockOff, temp, xRange, yRange);
                    foodBucket->getElement(i) = temp;
                    i = 0; 
                    j = 0;
                }
            }
        }
    }
}

objPosArrayList* Food::getFoodBucket() const
{
    return foodBucket;
}

int Food::getAmountOfFood() const
{
    return numberOfFood;
}