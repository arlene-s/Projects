/* 
 * File:   Deck.h
 * Author: Arlene Sagaoinit
 * Created on December 6, 2021, 4:13 PM
 * Purpose: Deck class Implementation
 */

#include "Deck.h"

//Constructor to create array of Card objects
Deck::Deck(int n){
    nCards=(n>52?52:n); //Size of deck
    crdDeck=new Card[nCards];
    setDeck();          //Create deck
}

//Uses Card class mutator functions to create deck of cards
void Deck::setDeck(){
    //Use outer for loop to represent suits (0-4)
    //Inner loop for assigning card's face, value, and suit
    int k=0;//Index of each element in deck
    for(int suitCrd=D; suitCrd<=C;suitCrd=static_cast<Suit>(suitCrd+1)){     
        for(int faceCrd=TWO;faceCrd<=ACE;faceCrd=static_cast<Face>(faceCrd+1)){
            crdDeck[k].setFace(faceCrd);  //Assign a face to card
            crdDeck[k].setSuit(suitCrd);  //Assign a suit
            crdDeck[k].setVal(faceCrd);   //Assign the face value
            k++;                          //Increment, k goes to 52 (size of deck array)
        }
    }
}

//Shuffles deck
void Deck::shuffle(){
    Card temp;
    int r;
    for(int i=0; i<nCards;i++){
        r=rand()%52;
        temp=crdDeck[i];
        crdDeck[i]=crdDeck[r];
        crdDeck[r]=temp;
    }
}
