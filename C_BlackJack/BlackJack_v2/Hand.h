/* 
 * File:   Hand.h
 * Author: Arlene Sagaoinit
 * Created on November 14, 2021, 6:40 PM
 * Purpose: Structure holding players hand info
 *          -Dynamic array holding players hand
 *          -Index to keep track of amount of cards in hand
 *          -Total sum of cards
 *          -aceElem to hold ace element of card if pulled
 */

#ifndef HAND_H
#define HAND_H

struct Hand{             //Structure containing players hand details
    int *cards;          //Array holding players hand
    int index;           //Current index/size of array
    int handTot;         //Current sum of players hand
    int aceElem;         //Ace card index, val to change when total>21
};

#endif /* HAND_H */
