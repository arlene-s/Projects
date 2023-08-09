/* 
 * File:   Hand.h
 * Author: Arlene Sagaoinit
 * Created on December 10, 2021, 6:40 PM
 * Purpose: Hand Class Specification
 */

#include "Hand.h"

//Sets hand
Hand::Hand(int n){
    hndSize=n<2?2:n;
    cards=new int[hndSize];
    indx=0;
    handTot=0;
    aceElem=-1;
}

Hand::~Hand(){
    delete []cards;
}

//Calculates total of players hand
void Hand::calcTot(){
    int sum=0;      //Variable to hold sum of players hand
    for(int i=0; i<indx;i++)   //Loop through hand
        sum+=cards[i];          //Add each value in hand to sum
    handTot=sum;                //Return sum
}

int Hand::total(){
    calcTot();
    return handTot;
}

void Hand::dealCrd(int n){
    //Record ace index for possible change later
    aceElem=(n==11)?indx:aceElem;
    cards[indx++]=n;
    calcTot();
    chckAce();
}

void Hand::chckAce(){
    //If player has an ace and goes over, set value to 1
    if(handTot>21&&aceElem!=-1){
        cards[aceElem]=1;
        calcTot();//Recalculate total with ace as 1
    }
}

