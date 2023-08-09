/* 
 * File:   Hand.h
 * Author: Arlene Sagaoinit
 * Created on December 10, 2021, 8:00 PM
 * Purpose: Hand Class Specification
 */

#include "Hand.h"

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

string Hand::dealCrd(Deck &deck,int &n){
    int elem=n;
    cards[indx]=deck.val(elem);
    if(deck.face(elem)=="A")
        aceElem=indx;
    indx++;
    n++;
    return deck.face(elem)+deck.suit(elem);
}

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

void Hand::hit(Deck &deck, int &n){
    bool quit=false;    //Set to true when user wants to stop hitting
    //Prompt user to hit while quit is false and hand total < 21
    while(quit==false&&handTot<21){
        cout<<"Hit? (y/n): ";
        char hit;
        cin>>hit;
        //If input is uppercase, convert to lowercase 
        //Only two options: 'y' or 'n' if not chosen, prompt until one of the two chosen
        while(tolower(hit)!='y'&&tolower(hit)!='n'){
            cout<<"Invalid please enter 'y' or 'n'"<<endl;
            cin>>hit;
        }
        if(tolower(hit)=='y'){  //If yes
            cout<<"card: "<<dealCrd(deck,n)<<endl;
            calcTot();
            chckAce();
        }else{
            quit=true;          //If no, set quit to true and exit loop
        }
    }
}

void Hand::chckAce(){
    //If player has an ace and goes over, set value to 1
    if(handTot>21&&aceElem!=-1){
        cards[aceElem]=1;
        calcTot();//Recalculate total with ace as 1
    }
}