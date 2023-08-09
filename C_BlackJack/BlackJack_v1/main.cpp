/* 
 * File:   main.cpp
 * Author: Arlene Sagaoinit
 * Created on December 6, 2021, 3:35 PM
 * Purpose:  First version of Class conversion
 *           -Converted Card struct to Card class
 *           -Created an array of Cards
 */

//System Libraries
#include <iostream>   //Input/Output Library
#include <ctime>      //srand()
#include <iomanip>    //setw()
#include <cstring>    //strlen()
#include <fstream>    //read/write to file
using namespace std;  //STD Name-space where Library is compiled

//User Libraries
#include "Card.h"       //Struct holding data of single card from deck
#include "Hand.h"       //Struct holding players hand info
#include "Player.h"     //Struct holding players gameplay stats

//Global Constants not Variables
//Math/Physics/Science/Conversions/Dimensions

//Enumerators to hold suits and faces 
enum Suit {D,S,H,C};
enum Face {TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE};

//Function Prototypes
Player *playr();                 //Returns a Player struct with initialized values
Hand *hand(int);                 //Returns a Hand struct with initialized values
void crDeck(Card []);    //Create deck of 52
string card(Player *, Card [], int &);  //Assigns card to player
void calcTot(Player *);                 //Calculate total of hand
void hit(Player *, Card [], int &);     //Ask user if want another card
void stats(Player *, Player *);  //Display win or loss
void chckAce(Player *);          //Check if players hand contains an ace
void shuffle(Card []);           //Passes in deck and shuffles values in deck
void wrtBin(fstream &,Player *); //Write to binary file
Player *readBin(fstream &);      //Read from binary file
void print(Player *);            //Print records read from binary file
void endStats(Player *);         //Print overall gameplay stats at the end

//Code Begins Execution Here with function main
int main(int argc, char** argv) {
    //Set random number seed once here
    srand(static_cast<unsigned int>(time(0)));
    
    //Declare variables here
    int size;                    //Size of player's hand
    int index;                   //Index for deck of cards
    char input;                  //User input to play game again (y/n)
    Face faceCrd;                //Enumerator, face cards
    fstream binFile;             //Binary file
    
    //Initialize variables here
    binFile.open("stats.bin",ios::out|ios::binary);
    size=10;                     //Initialize hand size to 10, too big
    Player *user=playr();        //Create a player struct for user
    Player *dealer=playr();      //Create a player struct for dealer
    Card deck[52];               //Define an array of classes, each element a Card class
    
    //Create deck of cards
    crDeck(deck);
    
    //Map inputs to outputs here, i.e. the process
    cout<<"Play Blackjack!"<<endl;
    cout<<"Beat the dealer by gaining a hand total close to 21 without going over. "<<endl
        <<"If you have an ace card, its value is 11 until you go over 21. When "
        <<"you go over, your ace will change to 1 and you can continue hitting "
        <<"until you go over again."<<endl
        <<"Min bet: $20"<<endl<<"Max bet: $500"<<endl;
    do{
        //When end of deck reached (all 52 cards used),reset index back to 0
        index=index>51?0:index;
        
        cout<<"--------------------------------------"<<endl;
        user->plyrHnd=hand(size);    //Allocate memory to hand info struct
        dealer->plyrHnd=hand(size);      
        cout<<"Place your bet: ";
        cin>>user->betAmt;           //Collect users bet amount
        //Error check, amount cant be less than 20 or greater than 100
        while(user->betAmt<20 || user->betAmt>100){
            cout<<"Invalid bet amount"<<endl;
            cout<<"Min: $20 "<<"Max: $100"<<endl;
            cin>>user->betAmt;
        }
        
        shuffle(deck);               //Shuffle the deck
        //Pull cards and display them
        cout<<"Your cards: "<<card(user,deck,index)<<" "<<card(user,deck,index)<<endl;
        calcTot(user);               //Calculate total of hand
        chckAce(user);               //Check if ace card pulled, if went over change val to 1
        //Display users total
        cout<<"Total: "<<user->plyrHnd->handTot<<endl<<endl;

        cout<<"Dealers first card: "<<card(dealer,deck,index)<<endl;
        //If users hand total < 21, call function to prompt user to hit
        //prompt user while total<21 and until they want to stop
        if(user->plyrHnd->handTot<21){
            hit(user,deck,index);
            cout<<"Total: "<<user->plyrHnd->handTot<<endl<<endl;
        }

        //Grab second card for dealer
        cout<<"Dealers second card: "<<card(dealer,deck,index)<<endl;
        calcTot(dealer);             //Calculate the dealers hand total
        while(dealer->plyrHnd->handTot<17){//Dealer pulls cards until the total is 17 or greater
            cout<<"Dealer hits: "<<card(dealer,deck,index)<<endl;
            calcTot(dealer);         //Calculate new total
            chckAce(dealer);         //Check if card pulled is an ace
        }
        //Display dealers total
        cout<<"Dealers total: "<<dealer->plyrHnd->handTot<<endl<<endl;

        //Display the results
        stats(user, dealer);         //Compare user and dealer totals and display win or loss
        
        //Deallocate memory
        //Delete only the player's hand info inside do while loop to reset their hand
        //but keep players stats -> betAmt, chipTot, num games, wins, losses
        delete []user->plyrHnd->cards;      //Destroy users hand, hand total, and size
        delete user->plyrHnd;               //Destroy Hand structure
        delete []dealer->plyrHnd->cards;    
        delete dealer->plyrHnd;
        
        //Write to binary file
        wrtBin(binFile, user);
        
        //Reset bet amount and chips won for next round
        user->betAmt=0;
        user->chipsWon=0;
        
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

//Create Hand struct containing player's cards info
Hand *hand(int n){
    n=n<2?2:n;                  //Initialize size of player's hand
    Hand *hand=new Hand;        //Define struct
    hand->cards=new int[n];  //Define cards array
    hand->index=0;              //Initialize index referenced to hand array 
    hand->handTot=0;            //Initalize hand total 
    hand->aceElem=-1;     
    //Set ace element to -1 until ace card pulled
    //when pulled, set aceElem to ace card's index position in cards array
    return hand;                //Return hand struct
}

//Create a Player struct containing players game stats
Player *playr(){
    Player *playr=new Player;   //Define Player struct
    playr->betAmt=0;            //Initalize all members to 0
    playr->chipsWon=0;
    playr->games=0;
    playr->wins=0;
    playr->losses=0;
    playr->status=false;        //Win status default to false
    return playr;               //Return Player struct
}

//Create a deck of 52 cards by pulling from faces[], suits[], cardval[]
//Store into deck of Card structures
void crDeck(Card deck[]){
    //Use outer for loop to represent suits (0-4)
    //Inner loop for assigning card's face, value, and suit
    int k=0;//Index of 
    for(int suitCrd=D; suitCrd<=C;suitCrd=static_cast<Suit>(suitCrd+1)){     
        for(int faceCrd=TWO;faceCrd<=ACE;faceCrd=static_cast<Face>(faceCrd+1)){
            deck[k].setFace(faceCrd);  //Assign a face to card
            deck[k].setSuit(suitCrd);     //Assign a suit
            deck[k].setVal(faceCrd);//Assign the face value
            k++;                          //Increment, k goes to 52 (size of deck array)
        }
    }
}

//Updates players stats and displays a win or loss to user
void stats(Player *playr, Player *dealr){
    if(playr->plyrHnd->handTot>21){ //user goes over, display loss
        //Subtract bet amount from total chips won
        //totChips can't be negative, set to 0 if totChips-betAmt < 0
        if(playr->totChips-playr->betAmt<0)playr->totChips=0;
        else playr->totChips-=playr->betAmt;
        playr->games++;     //Increment games played
        playr->losses++;    //Increment losses
        playr->status=false;    //Status false for loss
        
        //Display stats
        cout<<"You Lose!"<<endl;
        cout<<"Chips Won: "<<playr->chipsWon<<endl;
    }else if(playr->plyrHnd->handTot<21){
        //If user total and dealer total < 21
        if(dealr->plyrHnd->handTot<21){
            //and user total > dealer total, display win
            if(playr->plyrHnd->handTot>dealr->plyrHnd->handTot){
                playr->totChips+=playr->betAmt;  //Add bet amount to chip total
                playr->chipsWon+=playr->betAmt;
                playr->games++; 
                playr->wins++;          //Incrememnt wins
                playr->status=true;     //True for win
                
                cout<<"You win!"<<endl;
                cout<<"Chips Won: "<<playr->chipsWon<<endl;
            //user total < dealer total, display loss
            }else{
                if(playr->totChips-playr->betAmt<0)playr->totChips=0;
                else playr->totChips-=playr->betAmt;
                playr->games++;
                playr->losses++;
                playr->status=false;
                
                cout<<"You Lose!"<<endl;
                cout<<"Chips Won: "<<playr->chipsWon<<endl;
            }
        //user total < 21 and dealer total > 21, display win
        }else if(dealr->plyrHnd->handTot>21){
            playr->totChips+=playr->betAmt;
            playr->chipsWon+=playr->betAmt;
            playr->games++;
            playr->wins++;
            playr->status=true;
            
            cout<<"You Win!"<<endl;
            cout<<"Chips Won: "<<playr->chipsWon<<endl;
        //user total < 21 and dealer total = 21, display loss
        }else{
            if(playr->totChips-playr->betAmt<0)playr->totChips=0;
            else playr->totChips-=playr->betAmt;
            playr->games++;
            playr->losses++;
            playr->status=false;
            
            cout<<"You Lose!"<<endl;
            cout<<"Chips Won: "<<playr->chipsWon<<endl;
        }
    //User total ==21
    }else{
        //If dealer total != 21, display win
        if(playr->plyrHnd->handTot!=dealr->plyrHnd->handTot){
            playr->totChips+=playr->betAmt;
            playr->chipsWon+=playr->betAmt;
            playr->games++;
            playr->wins++;
            playr->status=true;
            
            cout<<"You Win!"<<endl;
            cout<<"Chips Won: "<<playr->chipsWon<<endl;
        //Dealer total = 21, display loss
        }else{
            if(playr->totChips-playr->betAmt<0)playr->totChips=0;
            else playr->totChips-=playr->betAmt;
            playr->games++;
            playr->losses++;
            playr->status=false;
            
            cout<<"Tie You Lose"<<endl;
            cout<<"Chips Won: "<<playr->chipsWon<<endl;
        }
    }
}

//Function to allow player to hit while hand total < 21
void hit(Player *playr, Card deck[], int &idx){
    bool quit=false;    //Set to true when user wants to stop hitting
    //Prompt user to hit while quit is false and hand total < 21
    while(quit==false&&playr->plyrHnd->handTot<21){
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
            cout<<"card: "<<card(playr,deck,idx)<<endl; //Pull card
            calcTot(playr);     //Calculate total
            chckAce(playr);     //Check if card pulled is an ace
        }else{
            quit=true;          //If no, set quit to true and exit loop
        }
    }
}

//Function to check players hand for an ace card (aceElem!=-1)
//If hand total > 21, change the value of ace card to 1
void chckAce(Player *playr){
    //If player has an ace and goes over, set value to 1
    if(playr->plyrHnd->handTot>21&&playr->plyrHnd->aceElem!=-1){
        playr->plyrHnd->cards[playr->plyrHnd->aceElem]=1;
        calcTot(playr);//Recalculate total with ace as 1
    }
}

//Calculate total of players hand
void calcTot(Player *playr){
    int sum=0;      //Variable to hold sum of players hand
    for(int i=0; i<playr->plyrHnd->index;i++)   //Loop through hand
        sum+=playr->plyrHnd->cards[i];          //Add each value in hand to sum
    playr->plyrHnd->handTot=sum;                //Return sum
}

//Modified to return string instead of char
//Create a random number between 0-51 to represent an element in card deck
//Store the value of face card from deck into players hand
string card(Player *playr, Card deck[], int &index){
    int elem=index;         //Element number from 0 to 12
    //Store the value of face card from deck into players hand
    playr->plyrHnd->cards[playr->plyrHnd->index]=deck[elem].getVal();
    //If card selected is an ace, record its index in hand array
    if(deck[elem].getFace()=="A")playr->plyrHnd->aceElem=playr->plyrHnd->index;
    playr->plyrHnd->index++;    //Increment index for next card
    index++;                    //Increment index for next card choice in deck
    //Return face card and suit
    return deck[elem].getFace()+deck[elem].getSuit();
}

//Function shuffles deck by using a random number to grab a face from deck
//and swap it with deck[i] 
void shuffle(Card deck[]){
    Card temp;                 //Create a temp card to store face card contents
    int r;                     //Store random number
    for(int i=0;i<52;i++){
        r=rand()%52;           //Grab random number
        temp=deck[i];          //Store face card in temp card
        deck[i]=deck[r];       //Change face card in deck to random face card in deck
        deck[r]=temp;          //Swap random face card with temp
    }
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
    cout<<"Game #: "<<plyr->games<<endl;
    cout<<"Status: "<<(plyr->status==true?"Win":"Loss")<<endl;
    cout<<"Bet Amount: "<<plyr->betAmt<<endl;
    cout<<"Chips Won: "<<plyr->chipsWon<<endl;
}

void endStats(Player *plyr){
    cout<<"\tTotal Games Played: "<<setw(5)<<plyr->games<<endl;
    cout<<"\tTotal Wins: "<<setw(13)<<plyr->wins<<endl;
    cout<<"\tTotal Losses: "<<setw(11)<<plyr->losses<<endl;
    cout<<"\tOverall chips won: "<<setw(6)<<plyr->totChips<<endl;
}
