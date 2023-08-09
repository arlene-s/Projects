/* 
 * File:   Player.h
 * Author: Arlene Sagaoinit
 * Created on November 14, 2021, 6:41 PM
 * Purpose: Structure holding players gameplay stats
 *          -Nested structure, pointer to Hand struct to hold players hand
 *          -Bet amount
 *          -Chips collected each round, resets each round
 *          -Total chips collected for whole gameplay
 *          -Number of games
 *          -Number of wins
 *          -Number of losses
 *          -Status for win or loss, win=true;
 */

#ifndef PLAYER_H
#define PLAYER_H
#include "Hand.h"

struct Player{           //Structure containing players card details, bet amount, total chips
    Hand *plyrHnd;       //Pointer to hand structure for holding players hand info
    int betAmt;          //Players bet amount
    int chipsWon;        //Amount of chips player won for each round, resets
    int totChips;        //Total chips won for whole gameplay
    unsigned int games;  //Number of games 
    unsigned int wins;   //Players number of wins
    unsigned int losses; //Number of losses
    bool status;         //Players current game status, win? status=true;
};

#endif /* PLAYER_H */

