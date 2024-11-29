#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "food.h"

Food::Food()
{
    numberOfFood = 5;
    foodBucket = new objPosArrayList(numberOfFood);
    for (int i = 0; i < numberOfFood; i++)
    {
        foodBucket->setElement(i, objPos(0, 0, 'A')); 
    }

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
        foodBucket->getElement(i).setSymbol(copy.foodBucket->getElement(i).symbol); 
    }

    

}

Food::Food(const Food &copy)
{

    foodBucket = new objPosArrayList();
    numberOfFood = copy.getAmountOfFood();

    foodBucket->setListSize(copy.getAmountOfFood());

    for(int i = 0; i<foodBucket->getSize(); i++)
    {
        foodBucket->getElement(i).pos->x = copy.foodBucket->getElement(i).pos->x;
        foodBucket->getElement(i).pos->y = copy.foodBucket->getElement(i).pos->y;
        foodBucket->getElement(i).setSymbol(copy.foodBucket->getElement(i).symbol);  ;
    }
}

Food::~Food()
{
    delete[] foodBucket;
}

objPosArrayList* Food::getFoodBucket() const
{
    return foodBucket;
}

void Food::generateFood(objPos blockOff, objPos* inputItem, int xRange, int yRange)
{

    char foodtypes[4] = {'A', 'B', 'C', 'D'}; 

    do
    {
        inputItem->pos->x = rand() % (xRange - 2) + 1; //check what to use
        inputItem->pos->y = rand() % (yRange - 2) + 1;
        inputItem->symbol = foodtypes[(rand() % 4)];

    } while((inputItem->pos->x == blockOff.pos->x) && (inputItem->pos->y == blockOff.pos->y));
}

void Food::generateFoodBucket(objPosArrayList blockOff, int xRange, int yRange)
{
    objPos temp;
    bool valid = false;

    for(int i = 0; i<numberOfFood; i++)
    {
        valid = false;

        while(!valid)
        {

            valid = true;
            generateFood(blockOff.getHeadElement(), &temp, xRange, yRange);
            
            for(int j = 0; j<numberOfFood; j++)
            {

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