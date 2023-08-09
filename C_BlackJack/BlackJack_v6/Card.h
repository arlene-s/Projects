/* 
 * File:   Card.h
 * Author: Arlene Sagaoinit
 * Created on December 6, 2021, 3:25 PM
 * Purpose: Card class specification
 *          -Used to create an array of Card objects
 *          -Contains the info of a card: face, suit, value
 */

#ifndef CARD_H
#define CARD_H

#include <iostream> //string
using namespace std;

//Class to hold the data of a single card in the deck of 52
class Card{
    private:
        string face;        //Face of card
        char suit;          //Suit
        int val;            //Card value
    public:
        Card();             //Default constructor
        void setFace(int);  //Mutator functions
        void setSuit(int);
        void setVal(int);
        string getFace()    //Accessor functions
            {return face;}
        char getSuit()
            {return suit;}
        int getVal()
            {return val;}
};

#endif /* CARD_H */

