#ifndef FOOD_H  
#define FOOD_H

#include "objPos.h"

#include <cstdlib>
#include <time.h>

using namespace std;

class Food
{
    private:
        objPos food; //Holds the most recently generated food position and its ASCII symbol
    public:
        Food();
        ~Food();
        void generateFood(objPos blockOff); //random food generation algorithm - ppa3
        objPos getFoodPos() const; //Getter method for obtaining a copy of the current position of the food.
};

#endif