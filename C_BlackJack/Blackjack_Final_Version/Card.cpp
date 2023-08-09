/* 
 * File:   Card.h
 * Author: Arlene Sagaoinit
 * Created on December 6, 2021, 3:25 PM
 * Purpose: Card class Implementation
 */

#include "Card.h"
#include <iostream>
using namespace std;

Card::Card(){
    face="";
    suit=' ';
    val=-1;
}
//takes an index from deck and sets the face of card
void Card::setFace(int n){
    string faces[]={"2","3","4","5","6","7","8","9","10","J","K","Q","A"};
    face=faces[n];
}

//takes an index from deck and sets suit of card
void Card::setSuit(int n){
    char suits[]={"DSHC"};
    suit=suits[n];
}

//takes an index from deck and sets int value of card
void Card::setVal(int n){
    int cardVals[]={2,3,4,5,6,7,8,9,10,10,10,10,11};
    val=cardVals[n];
}