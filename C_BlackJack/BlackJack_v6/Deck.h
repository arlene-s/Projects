/* 
 * File:   Deck.h
 * Author: Arlene Sagaoinit
 * Created on December 6, 2021, 4:13 PM
 * Purpose: Deck class specification
 *          -Creates an array of Card objects
 *          -Contains shuffle function
 */

#ifndef DECK_H
#define DECK_H

#include "Card.h"

//Enumerators to hold suits and faces 
enum Suit {D,S,H,C};
enum Face {TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE};

//Class to create a deck of 52 cards from Card class
class Deck{
    private:
        int nCards;         //Size of deck
        Card *crdDeck;      //Array of Card objects
        void setDeck();     //Utility function to create deck
    public:
        Deck(int);          //Constructor
        ~Deck()             //Deconstructor
            {delete []crdDeck;}
        string face(int n)  //Accessor functions
            {return crdDeck[n].getFace();}
        char suit(int n)
            {return crdDeck[n].getSuit();}
        int val(int n)
            {return crdDeck[n].getVal();}
        void shuffle();     //Shuffles deck
};

#endif /* DECK_H */

