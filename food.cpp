#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "food.h"

Food::Food()
{
    numberOfFood = 3;
    foodBucket = new objPosArrayList();
    foodBucket->setListSize(numberOfFood);

}

Food &Food::operator=(const Food &copy)
{
    delete[] foodBucket;

    foodBucket = new objPosArrayList();
    numberOfFood = copy.getAmountOfFood();

    foodBucket->setListSize(numberOfFood);

    for(int i = 0; i<numberOfFood; i++)
    {
        foodBucket->getElement(i).pos->x = copy.foodBucket->getElement(i).pos->x;
        foodBucket->getElement(i).pos->y = copy.foodBucket->getElement(i).pos->y;
    }

    

}

Food::Food(const Food &copy)
{

    foodBucket = new objPosArrayList();
    numberOfFood = copy.getAmountOfFood();

    foodBucket->setListSize(numberOfFood);

    for(int i = 0; i<numberOfFood; i++)
    {
        foodBucket->getElement(i).pos->x = copy.foodBucket->getElement(i).pos->x;
        foodBucket->getElement(i).pos->y = copy.foodBucket->getElement(i).pos->y;
    }
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
    char food[] = {'$', '%', '!', '~'};
    //from ppa3
    do
    {
        inputItem->pos->x = rand() % (xRange - 2) + 1; //check what to use
        inputItem->pos->y = rand() % (yRange - 2) + 1;
        inputItem->symbol = food[(rand() % 3)];

    } while((inputItem->pos->x == blockOff.pos->x) && (inputItem->pos->y == blockOff.pos->y));
}

void Food::generateFoodBucket(objPosArrayList blockOff, int xRange, int yRange)
{
    objPos temp;
    bool valid = false;

    for(int i = 0; i<foodBucket->getSize(); i++)
    {
        valid = false;

        while(!valid)
        {

            valid = true;
            
            for(int j = 0; j<foodBucket->getSize(); j++)
            {
                generateFood(blockOff.getElement(i), &temp, xRange, yRange);

                if(i!=j)
                {
                    if((temp.pos->x == foodBucket->getElement(j).pos->x) 
                    && (temp.pos->y == foodBucket->getElement(j).pos->y))
                    {
                        valid = false;
                        break;
                    }
                }
            }

            for(int k = 0; k<blockOff.getSize(); k++)
            {
                generateFood(blockOff.getElement(i), &temp, xRange, yRange);
                if((temp.pos->x == blockOff.getElement(k).pos->x 
                && temp.pos->y == blockOff.getElement(k).pos->y))
                {
                    valid = false;
                    break;
                }
            }

            if(valid)
            {
                foodBucket->setElement(i, temp);
            }
        }

    }
}



int Food::getAmountOfFood() const
{
    return numberOfFood;
}