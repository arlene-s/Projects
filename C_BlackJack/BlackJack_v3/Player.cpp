/* 
 * File:   Player.h
 * Author: Arlene Sagaoinit
 * Created on December 10, 2021, 8:00 PM
 * Purpose: Player Class implementation
 */

#include "Player.h"
#include <iostream>
using namespace std;

Player::Player(){
    betAmt=0;
    chipsWon=0;
    totChips=0;
    games=0;
    wins=0;
    losses=0;
    status=false;
}

void Player::setHand(Hand *hand)
    {plyrHnd=hand;}

void Player::setBet(int bet)
    {betAmt=bet;}

void Player::setChips(int chips)
    {chipsWon=chips;}

void Player::stats(Player *dealr){
    if(plyrHnd->total()>21){ //user goes over, display loss
        //Subtract bet amount from total chips won
        //totChips can't be negative, set to 0 if totChips-betAmt < 0
        if(totChips-betAmt<0)totChips=0;
        else totChips-=betAmt;
        games++;     //Increment games played
        losses++;    //Increment losses
        status=false;    //Status false for loss

        //Display stats
        cout<<"You Lose!"<<endl;
        cout<<"Chips Won: "<<chipsWon<<endl;
    }else if(plyrHnd->total()<21){
        //If user total and dealer total < 21
        if(dealr->plyrHnd->total()<21){
            //and user total > dealer total, display win
            if(plyrHnd->total()>dealr->plyrHnd->total()){
                totChips+=betAmt;  //Add bet amount to chip total
                chipsWon+=betAmt;
                games++; 
                wins++;          //Incrememnt wins
                status=true;     //True for win

                cout<<"You win!"<<endl;
                cout<<"Chips Won: "<<chipsWon<<endl;
            //user total < dealer total, display loss
            }else{
                if(totChips-betAmt<0)totChips=0;
                else totChips-=betAmt;
                games++;
                losses++;
                status=false;

                cout<<"You Lose!"<<endl;
                cout<<"Chips Won: "<<chipsWon<<endl;
            }
        //user total < 21 and dealer total > 21, display win
        }else if(dealr->plyrHnd->total()>21){
            totChips+=betAmt;
            chipsWon+=betAmt;
            games++;
            wins++;
            status=true;

            cout<<"You Win!"<<endl;
            cout<<"Chips Won: "<<chipsWon<<endl;
        //user total < 21 and dealer total = 21, display loss
        }else{
            if(totChips-betAmt<0)totChips=0;
            else totChips-=betAmt;
            games++;
            losses++;
            status=false;

            cout<<"You Lose!"<<endl;
            cout<<"Chips Won: "<<chipsWon<<endl;
        }
    //User total ==21
    }else{
        //If dealer total != 21, display win
        if(plyrHnd->total()!=dealr->plyrHnd->total()){
            totChips+=betAmt;
            chipsWon+=betAmt;
            games++;
            wins++;
            status=true;

            cout<<"You Win!"<<endl;
            cout<<"Chips Won: "<<chipsWon<<endl;
        //Dealer total = 21, display loss
        }else{
            if(totChips-betAmt<0)totChips=0;
            else totChips-=betAmt;
            games++;
            losses++;
            status=false;

            cout<<"Tie You Lose"<<endl;
            cout<<"Chips Won: "<<chipsWon<<endl;
        }
    }
};