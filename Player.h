#ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"

class Player
{

    public:
        enum Dir {UP, DOWN, LEFT, RIGHT, STOP};  // This is the direction state

        Player(GameMechs* thisGMRef);

        //Creation of destructor member function for player
        ~Player();

        objPosArrayList* getPlayerPos() const;        
        void updatePlayerDir();
        Dir getPlayerDir();
        void movePlayer();

        bool checkSelfCollision();
        void checkFoodCollision();


        bool checkWinCondition();
        void insertPlayerTail();


    private:
         
        enum Dir myDir;
        objPosArrayList* playerPosList;
        int foodCollideIndex;

        // Need a reference to the Main Game Mechanisms
        GameMechs* mainGameMechsRef;
};

#endif


