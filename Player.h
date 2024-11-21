#ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"

class Player
{
    // Construct the remaining declaration from the project manual.

    // Only some sample members are included here

    // You will include more data members and member functions to complete your design.

    
    public:
        enum Dir {UP, DOWN, LEFT, RIGHT, STOP};  // This is the direction state

        Player(GameMechs* thisGMRef);

        //Creation of destructor member function for player
        ~Player();

        objPos getPlayerPos() const; // Upgrade this in iteration 3.  
        void setPlayerPos(int x, int y);     
        void updatePlayerDir();
        void movePlayer();
        char getSymbol();
        void setSymbol(char letter);

        // More methods to be added here

    private:
        objPos playerPos;  // Upgrade this in iteration 3fff.       
        enum Dir myDir;
        char symbol;

        // Need a reference to the Main Game Mechanisms
        GameMechs* mainGameMechsRef;
};

#endif


