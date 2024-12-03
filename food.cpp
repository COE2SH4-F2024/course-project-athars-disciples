#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "food.h"


//Default constructor for food class
Food::Food()
{
    //Initializing number of food to 5
    numberOfFood = 5;

    //Storing foodbucket as a pointer to an objPosArrayList defined by size number of food
    foodBucket = new objPosArrayList(numberOfFood);

    //Initializing the used variables to something random (simply to avoid access issues)
    for (int i = 0; i < numberOfFood; i++)
    {
        foodBucket->setElement(i, objPos(0, 0, 'A')); 
    }

}

//Copy assignment operator for food class
Food &Food::operator=(const Food &copy)
{

    //Deletes initial data stored in food class
    delete[] foodBucket;

    //Creates new foodbucket pointer
    foodBucket = new objPosArrayList();

    //Assigns numberofFood to reference amount of food
    numberOfFood = copy.getAmountOfFood();

    //Sets the size of the current foodBucket to the reference foodbucket
    foodBucket->setListSize(numberOfFood);


    //Copying over all the elements within the reference foodbucket to the current foodbucket
    for(int i = 0; i<numberOfFood; i++)
    {
        foodBucket->getElement(i).pos->x = copy.foodBucket->getElement(i).pos->x;
        foodBucket->getElement(i).pos->y = copy.foodBucket->getElement(i).pos->y;
        foodBucket->getElement(i).setSymbol(copy.foodBucket->getElement(i).symbol); 
    }

    

}


//Copy operator for food class
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

//Destructor for food class
Food::~Food()
{
    //Destroying the memory allocated for foodbucket
    delete[] foodBucket;
}


//Getter for the Food class foodbucket
objPosArrayList* Food::getFoodBucket() const
{
    //Returns pointer to the foodbucket
    return foodBucket;
}

//Generate single food item at random within a range
void Food::generateFood(objPos blockOff, objPos* inputItem, int xRange, int yRange)
{

    //food types
    char foodtypes[4] = {'A', 'B', 'C', 'D'}; 
    //using ppa logic for food generation 
    do
    {
        inputItem->pos->x = rand() % (xRange - 2) + 1; 
        inputItem->pos->y = rand() % (yRange - 2) + 1;
        inputItem->symbol = foodtypes[(rand() % 4)];

    } while((inputItem->pos->x == blockOff.pos->x) && (inputItem->pos->y == blockOff.pos->y));
}

//Generates foodBucket at random positions
void Food::generateFoodBucket(objPosArrayList blockOff, int xRange, int yRange)
{
    objPos temp;
    bool valid = false;

    for(int i = 0; i<numberOfFood; i++)
    {
        valid = false; //reset flag for each food item

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
            //Check for overlapping
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

//Getter for numberOfFood
int Food::getAmountOfFood() const
{
    return numberOfFood;
}

//Decreases numberOfFood by 1
void Food::decreaseFood()
{
    numberOfFood--;
}