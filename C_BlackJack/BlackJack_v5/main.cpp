/*
 * File:   main.cpp
 * Author: Arlene Sagaoinit
 * Created on December 14, 2021, 7:00 PM
 * Purpose: Fifth version of blackjack class conversion
 *          -Added abstract class
 */

//System Libraries
#include <iostream>   //Input/Output Library
#include <ctime>      //srand()
#include <iomanip>    //setw()
#include <cstring>    //strlen()
#include <fstream>    //read/write to file
using namespace std;  //STD Name-space where Library is compiled

//User Libraries
#include "Deck.h"
#include "Player.h"     //Struct holding players gameplay stats
#include "Hand.h"       //Struct holding players hand info

//Global Constants not Variables
//Math/Physics/Science/Conversions/Dimensions

//Enumerators to hold suits and faces 

//Function Prototypes
void wrtBin(fstream &,Player *); //Write to binary file
Player *readBin(fstream &);      //Read from binary file
void print(Player *);            //Print records read from binary file
void endStats(Player *);         //Print overall gameplay stats at the end

//Code Begins Execution Here with function main
int main(int argc, char** argv) {
    //Set random number seed once here
    srand(static_cast<unsigned int>(time(0)));
    
    //Declare variables here
    int size=10;                 //Size of player's hand
    int deckSiz=52;              //Size of card deck
    int index=0;
    char input;                  //User input to play game again (y/n)
    int betAmnt;                 //User's bet amount
    fstream binFile;             //Binary file
    
    //Initialize variables here
    binFile.open("stats.bin",ios::out|ios::binary);
    Player *user=new Player;        //Create a player struct for user
    Player *dealer=new Player;     //Create a player struct for dealer
    
    //Create deck of cards
    Deck deck(deckSiz);
    deck.shuffle();

    //Map inputs to outputs here, i.e. the process
    cout<<"Play Blackjack!"<<endl;
    cout<<"Beat the dealer by gaining a hand total close to 21 without going over. "<<endl
        <<"If you have an ace card, its value is 11 until you go over 21. When "
        <<"you go over, your ace will change to 1 and you can continue hitting "
        <<"until you go over again."<<endl
        <<"Min bet: $20"<<endl<<"Max bet: $500"<<endl;
    do{
        //When end of deck reached (all 52 cards used),reset index back to 0
        cout<<"--------------------------------------"<<endl;
        
        if(index>51){
            deck.shuffle();
            index=0;
        }
        
        Hand *usrHnd=new Hand(size);
        Hand *dealHnd=new Hand(size);
        
        cout<<"Place your bet: ";
        cin>>betAmnt;           //Collect users bet amount
        
        //Error check, amount cant be less than 20 or greater than 100
        
        while(betAmnt<20 || betAmnt>500){
            cout<<"Invalid bet amount"<<endl;
            cout<<"Min: $20 "<<"Max: $500"<<endl;
            cin>>betAmnt;
        }
        user->setBet(betAmnt);
        
        //Pull cards and display them
        cout<<"Your cards: "<<usrHnd->dealCrd(deck,index)<<" "<<usrHnd->dealCrd(deck,index)<<endl;
        usrHnd->calcTot();
        usrHnd->chckAce();
        
        //Display users total
        cout<<"Total: "<<usrHnd->total()<<endl<<endl;

        cout<<"Dealers first card: "<<dealHnd->dealCrd(deck,index)<<endl;
        //If users hand total < 21, call function to prompt user to hit
        //prompt user while total<21 and until they want to stop
        if(usrHnd->total()<21){
            usrHnd->hit(deck,index);
            cout<<"Total: "<<usrHnd->total()<<endl<<endl;
        }
        user->operator=(usrHnd);
        
        //Grab second card for dealer
        cout<<"Dealers second card: "<<dealHnd->dealCrd(deck,index)<<endl;
        dealHnd->calcTot();
        
        while(dealHnd->total()<17){//Dealer pulls cards until the total is 17 or greater
            cout<<"Dealer hits: "<<dealHnd->dealCrd(deck,index)<<endl;
            dealHnd->calcTot();
            dealHnd->chckAce();
        }
        //Display dealers total
        cout<<"Dealers total: "<<dealHnd->total()<<endl<<endl;
        dealer->operator=(dealHnd);
        
        //Display the results
        user->stats(dealer);
        
        //Deallocate memory
        //Delete only the player's hand info inside do while loop to reset their hand
        //but keep players stats -> betAmt, chipTot, num games, wins, losses
        delete usrHnd;
        delete dealHnd;
        
        //Write to binary file
        wrtBin(binFile, user);
        
        //Reset bet amount and chips won for next round
        user->setBet(0);
        user->setChips(0);
        
        //Prompt user for next game or to end game
        cout<<"Would you like to play again? (y/n) ";
        cin>>input;
        //If input uppercase, convert to lowercase
        //User can only enter 'y' or 'n', loop while input invalid
        while(tolower(input)!='y'&&tolower(input)!='n'){
            cout<<"Invalid please enter 'y' or 'n"<<endl;
            cin>>input;
        }
    }while(tolower(input)=='y');     //Start game again if input == 'y'
    cout<<endl;
    
    //Close file
    binFile.close();
    
    //End of game, display records of each round played
    //Open file again for input
    //If file open successful, read from beginning of file
    binFile.open("stats.bin",ios::in|ios::binary);
    Player *recrd;
    if(binFile){
        //Read first record
        recrd=readBin(binFile);
        cout<<"***************************************"<<endl;
        //While end of file not reached, read next record and print
        while(!binFile.eof()){
            print(recrd);
            cout<<"***************************************"<<endl;
            recrd=readBin(binFile);
        }
        binFile.close();    //Close file
    }else{
        cout<<"Error opening file"<<endl;
    }
    
    //Print overall gameplay stats
    endStats(user);
    
    //Deallocate memory
    //Now when user is done playing
    //delete struct containing players stats -> chipTot, num games, wins, losses
    delete user;
    delete dealer;
    delete recrd;
    
    return 0;
}

//Write to binary file
void wrtBin(fstream &bin, Player *plyr){
    //Write user structure to binary file
    bin.write(reinterpret_cast<char *>(plyr),sizeof(Player));
}

//Read from binary file
Player *readBin(fstream &bin){
    Player *record=new Player;
    bin.read(reinterpret_cast<char *>(record),sizeof(Player));
    return record;
}

void print(Player *plyr){
    cout<<"Game #: "<<plyr->nGames()<<endl;
    cout<<"Status: "<<(plyr->getStatus()==true?"Win":"Loss")<<endl;
    cout<<"Bet Amount: "<<plyr->getBet()<<endl;
    cout<<"Chips Won: "<<plyr->getChips()<<endl;
}

void endStats(Player *plyr){
    cout<<"\tTotal Games Played: "<<setw(5)<<plyr->nGames()<<endl;
    cout<<"\tTotal Wins: "<<setw(13)<<plyr->getWins()<<endl;
    cout<<"\tTotal Losses: "<<setw(11)<<plyr->getLosses()<<endl;
    cout<<"\tOverall chips won: "<<setw(6)<<plyr->getTot()<<endl;
}

