/* 
 * File:   AbsPlayer.h
 * Author: Arlene Sagaoinit
 * Created on December 14, 2021, 7:00 PM
 * Purpose: Abstract class specification
 *          -Object defined from class -> Player
 *          -Sets and returns name
 *          -Pure virtual setHand function
 */

#ifndef ABSPLAYER_H
#define ABSPLAYER_H

#include <iostream>
using namespace std;

class AbsPlayer{
    protected:
        string name;
    public:
        void setName(string nam){name=nam;}
        string getName(){return name;}
        virtual void setHand(Hand *)=0;
};

#endif /* ABSPLAYER_H */

