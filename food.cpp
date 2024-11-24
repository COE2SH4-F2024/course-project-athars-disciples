#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "food.h"

Food::Food()
{
    numberOfFood = 5;
    foodBucket = new objPosArrayList();
    foodBucket->setListSize(5);
}

Food::~Food()
{
    delete foodBucket;
}

objPosArrayList* Food::getFoodBucket() const
{
    return foodBucket;
}

void Food::generateFood(objPos blockOff, objPos* inputItem, int xRange, int yRange)
{
    //from ppa3
    do
    {
        inputItem->pos->x = rand() % (xRange - 2) + 1; //check what to use
        inputItem->pos->y = rand() % (yRange - 2) + 1;
        inputItem->symbol = (char)(rand() % (126 - 33 + 1) + 33);

    } while((inputItem->pos->x == blockOff.pos->x && inputItem->pos->y == blockOff.pos->y));
}

void Food::generateFoodBucket(objPos blockOff, int xRange, int yRange)
{
    objPos temp;

    for(int r = 0; r<foodBucket->getSize(); r++)
    {
        generateFood(blockOff, &temp, xRange, yRange);
        foodBucket->setElement(r, temp);
    }

    for(int i = 0; i<foodBucket->getSize(); i++)
    {
        for(int j = 0; j<foodBucket->getSize(); j++)
        {
            if(i!=j)
            {
                if(foodBucket->getElement(i).pos->x == foodBucket->getElement(j).pos->x 
                && foodBucket->getElement(i).pos->y == foodBucket->getElement(j).pos->y)
                {
                    generateFood(blockOff, &temp, xRange, yRange);
                    foodBucket->setElement(i, temp);
                    break;
                }
            }
        }
    }
}



int Food::getAmountOfFood() const
{
    return numberOfFood;
}