/* 
 * File:   Hand.h
 * Author: Arlene Sagaoinit
 * Created on December 10, 2021, 8:00 PM
 * Purpose: Hand Class Specification
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
        string dealCrd(Deck &,int &);
        void calcTot();
        int total();
        void hit(Deck &,int &);
        void chckAce();
};

#endif /* HAND_H */