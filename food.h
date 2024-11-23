#ifndef FOOD_H  
#define FOOD_H

#include "objPos.h"
#include "objPosArrayList.h"

#include <cstdlib>
#include <time.h>

using namespace std;

class Food
{
    private:
        //Holds the most recently generated food position and its ASCII symbol
        objPosArrayList* foodBucket;
        int numberOfFood;

    public:
        Food();
        ~Food();

        void generateFood(objPos blockOff, objPos inputItem, int xRange, int yRange); //random food generation algorithm - ppa3
        void generateFoodBucket(objPos blockOff, int xRange, int yRange);
       //Getter method for obtaining a copy of the current position of the food.
        objPosArrayList* getFoodBucket() const;

        int getAmountOfFood() const;
};

#endif