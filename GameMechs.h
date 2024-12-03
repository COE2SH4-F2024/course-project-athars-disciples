#ifndef GAMEMECHS_H
#define GAMEMECHS_H

#include <cstdlib>
#include <time.h>

#include "objPos.h"
#include "objPosArrayList.h"
#include "food.h"

using namespace std;

class GameMechs
{
        

    public:
        enum Difficulty {Start, Easy, Medium, Hard, Impossible};

        GameMechs();
        GameMechs(int boardX, int boardY);
        ~GameMechs(); 
        
        bool getExitFlagStatus() const;
        bool getWinFlagStatus() const; 
        void setExit(bool value);

        bool getLoseFlagStatus() const;
        void setLoseFlag();

        char getInput() const;
        void setInput(char this_input);
        void clearInput();

        objPos getFoodPosition(int i);
        Food* getFood();

        int getBoardSizeX() const;
        int getBoardSizeY() const;
        
        int getScore() const;
        void incrementScore(int scoreAdd);
        
        void setDifficulty();
        Difficulty getDifficulty();

    private:
        char input;
        bool exitFlag;
        bool loseFlag;
        bool winFlag;
        int score;

        int boardSizeX;
        int boardSizeY;
        Food* foodObject;
        enum Difficulty diff;

};

#endif