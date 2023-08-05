/* 
 * File:   Hand.h
 * Author: Arlene Sagaoinit
 * Created on December 10, 2021, 6:40 PM
 * Purpose: Hand Class Specification
 *          -Holds an array of players card values
 *          -Modified deal function, utilizes dealer's
 *          -removed hit function
 */

#ifndef HAND_H
#define HAND_H

#include "Deck.h"

//Hand class inherited from Deck class
class Hand{
    private:
        int hndSize;    //Size of hand
        int *cards;     //Array holding values of player's hand
        int indx;       //Index of cards array
        int handTot;    //Total of player's hand
        int aceElem;    //Index of Ace card in hand
    public:
        Hand(int);
        ~Hand();
        void dealCrd(int);
        void calcTot();
        int total();
        void chckAce();
};

#endif /* HAND_H */

