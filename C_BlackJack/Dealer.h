/* 
 * File:   Dealer.h
 * Author: Arlene Sagaoinit
 * Created on December 15, 2021, 7:56 PM
 * Purpose: Dealer class specification
 *          -Inherited from player class
 *          -Moved deal function from hand class to here
 *          -Separated display function from deal function
 */

#ifndef DEALER_H
#define DEALER_H

#include "Card.h"
#include "Deck.h"
#include "Player.h"

#include <iostream>
using namespace std;

class Dealer:public Player{
    private:
        static int cardNum;
        Deck *deck;
    public:
        Dealer(int n){
            deck=new Deck(n);
            deck->shuffle();
            cardNum=0;
        }
        ~Dealer(){delete deck;}
        int deal(){
            //When delt all cards in deck, shuffle
            //Reset card number
            if(cardNum>51){
                deck->shuffle();
                cardNum=0;
            }
            return deck->val(cardNum++);
        }
        void shuffle(){deck->shuffle();}
        string display(){return deck->face(cardNum-1)+deck->suit(cardNum-1);}
        static int getCardNum(){return cardNum;}
};

int Dealer::cardNum=0;

#endif /* DEALER_H */

