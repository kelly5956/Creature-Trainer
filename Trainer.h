//
//  Trainer.h
//  CreatureTrainer
//
//  Created by Jeremy Gibson on 11/4/14.
//  Copyright (c) 2014 Jeremy Richard Gibson. All rights reserved.
//

#ifndef __CreatureTrainer__Trainer__
#define __CreatureTrainer__Trainer__

#include <stdio.h>
#include <string>
#include <sstream>
#include <vector>
#include "Class1.h"


using namespace std;

class Trainer {
public:
    /**
     * Requires: Nothing.
     * Modifies: Nothing.
     * Effects:  returns 'a' or 's#' given the situation.
                 This is where the bulk of your code will go. The implementation
                 of your AI goes here.
     */
    string makeMove(stringstream& situation);

    /**
     * Requires: Nothing.
     * Modifies: Nothing.
     * Effects:  Prints out the final situation
     */
    void finalSituation(stringstream& situation);
    
    
    /**
     * Requires: Nothing.
     * Modifies: Nothing.
     * Effects:  Splits a string into a vector of strings
     */
    vector<string> splitString(string inString, string splitOn=" ");
    
    Trainer();
    
private:
    // vvvvvv Your changes to Trainer.h go between this line…
    Class1 ourInfo;
    int pickCreature(int activeCreature, int activeLevel,
                     int enemyCreature, int enemyLevel);
    int captureCreature(int enemyCreature, int enemyLevel);
    int returnLowest();
    char throwScroll(int enemyNumber);
 //   bool checkBench();
    
    
    
    
    // ^^^^^^ And this line. That's it!
    
};

#endif /* defined(__CreatureTrainer__Trainer__) */
