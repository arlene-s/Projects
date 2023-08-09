/* 
 * File:   Player.h
 * Author: Arlene Sagaoinit
 * Created on December 12, 2021, 6:41 PM
 * Purpose: Player Class Specification
 *          -Contains players information
 *          -Inherited from abstract player class
 *          -Overloaded operators
 */

#ifndef PLAYER_H
#define PLAYER_H
#include "Hand.h"
#include "AbsPlayer.h"


class Player:public AbsPlayer{
    protected:
        Hand *plyrHnd;
        int betAmt;
        int chipsWon;
        int totChips;
        unsigned int games;
        unsigned int wins;
        unsigned int losses;
        bool status;
    public:
        Player();
        void operator=(Player *);
        bool operator>(Player *);
        bool operator!=(Player *);
        void setHand(Hand *);
        void setBet(int);
        void setChips(int);
        bool getStatus()
            {return status;}
        int getBet()
            {return betAmt;}
        int getChips()
            {return chipsWon;}
         int getTot()
            {return totChips;}
        unsigned int nGames()
            {return games;}
        unsigned int getWins()
            {return wins;}
        unsigned int getLosses()
            {return losses;}
        void stats(Player *);
};

#endif /* PLAYER_H */

