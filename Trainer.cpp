
//  Trainer.cpp
//  CreatureTrainer
//
//  You may NOT #include any .h files we provide you (Battle, Creature, CreatureType,
//  EECSRandom, Party, PrintHelper)
//  other than the ones name "ClassX.h" and "Trainer.h"
//  You may #include other <> libraries if you wish to
//
//  Created by Jeremy Gibson on 11/4/14.
//  Copyright (c) 2014 Jeremy Richard Gibson. All rights reserved.
//

/**
 * Alex Intner, waintner@umich.edu
 * Kelly Fischer, kjfisch@umich.edu
 * Alex Cayford, acay@umich.edu
 * Lynn Chou, lynnchou@umich.edu
 *
 * Runs an AI that plays a game of Pokemon
 */


#include <iostream>
#include <sstream>
#include "Trainer.h"
#include "Class1.h"
#include "Class3.h"
#include "Class4.h"
#include "Class5.h"
#include "CreatureType.h"


using namespace std;

Trainer::Trainer() {
    ourInfo = Class1();
}

int Trainer::pickCreature(int activeCreature, int activeLevel,
                          int enemyCreature, int enemyLevel) {
    bool case1 = false;
    bool case2 = false;
    bool case3 = false;
    int returnCreature = 0;
    CreatureType e = CreatureType::TYPES[enemyCreature];
    
    
    for (int i = 0; i < 4; i++) {
        char x = ourInfo.name[i][0];
        x = x - 'A';
        CreatureType c = CreatureType::TYPES[x];
        if ((c.getElementalAttackType() == e.getElementalWeakness()) &&
            (c.getElementalStrength() == e.getElementalAttackType()) &&
            (ourInfo.healthAvail[i] >
             ((e.getAttackPerLevel()  + enemyLevel * e.getAttackPerLevel()) / 2))
            && c.getElementalWeakness() != e.getElementalAttackType()) {
            if (i != activeCreature) {
                case1 = true;
                returnCreature = i;
                break;
            }
        }
        
    }
    
    if (case1) {
        return returnCreature;
    }
    
    for (int i = 0; i < 4; i++) {
        char x = ourInfo.name[i][0];
        x = x - 'A';
        CreatureType c = CreatureType::TYPES[x];
        if ((c.getElementalAttackType() == e.getElementalWeakness()) &&
            (ourInfo.healthAvail[i] >
             (e.getAttackPerLevel() + enemyLevel * e.getAttackPerLevel()))
            && e.getElementalAttackType() != c.getElementalWeakness()) {
            if (i != activeCreature) {
                case2 = true;
                returnCreature = i;
                break;
            }
        }
        
    }
    
    if (case2 && ourInfo.numSwaps < 3) {
        return returnCreature;
    }
    
    for (int i = 0; i < 4; i++) {
        char x = ourInfo.name[i][0];
        x = x - 'A';
        CreatureType c = CreatureType::TYPES[x];
        if ((c.getElementalStrength() == e.getElementalAttackType()) &&
            (ourInfo.healthAvail[i] >
             ((e.getAttackPerLevel()  + enemyLevel * e.getAttackPerLevel()) / 2))
            && c.getElementalWeakness() != e.getElementalAttackType()) {
                if (i != activeCreature) {
                    case3 = true;
                    returnCreature = i;
                    break;
                }
            }
        
    }

    
    if (case3) {
        return returnCreature;
    }

    
    int max = ourInfo.healthAvail[activeCreature];
    int maxNumber = activeCreature;
    bool hasEntered = false;
    for (int i = 0; i < 4; i++) { //Check place 0?
        char x = ourInfo.name[i][0];
        x = x - 'A';
        CreatureType c = CreatureType::TYPES[x];
        if (i == activeCreature) {
            continue;
        }
        if (ourInfo.healthAvail[i] >= max &&
            c.getElementalWeakness() != e.getElementalAttackType()) {
            max = ourInfo.healthAvail[i];
            maxNumber = i;
            hasEntered = true;
        }
    }
    if (!hasEntered || ourInfo.healthAvail[maxNumber] == 0) {
        maxNumber = 0;
        max = ourInfo.healthAvail[0];
        for (int i = 1; i < 4; i++) {
            if (ourInfo.healthAvail[i] > max) {
                max = ourInfo.healthAvail[i];
                maxNumber = i;
            }
        }
    }
    if (ourInfo.healthAvail[activeCreature] == max) {
        return -1;
    }
    return maxNumber;
}

int Trainer::captureCreature(int enemyCreature, int enemyLevel) {
    for (int i = 0; i < 4; i++) {
        char firstCharInName = ourInfo.name[0][0];
        int typeNum = firstCharInName - 'A';
        if (typeNum == enemyCreature) {
            return -1;
        }
        
    }
    
    bool deadCreature[4] = {false};
    
    for (int i = 0; i < 4; i++) {
        if (ourInfo.healthAvail[i] == 0) {
            deadCreature[i] = true;
        }
    }
    
    for (int i = 0; i < 4; i++) {
        if (deadCreature[i]) {
            return i;
        }
    }
    
    char firstCharInName = ourInfo.name[0][0];
    int typeNum = firstCharInName - 'A';
    int minHealth = CreatureType::TYPES[typeNum].getHealthMaxBase() + ourInfo.level[0] * CreatureType::TYPES[typeNum].getHealthMaxPerLevel();
    int minHealthCreature = 0;
    
    for (int i = 1; i < 4; i++) {
        firstCharInName = ourInfo.name[i][0];
        typeNum = firstCharInName - 'A';
        int tempHealth = CreatureType::TYPES[typeNum].getHealthMaxBase() + ourInfo.level[i] * CreatureType::TYPES[typeNum].getHealthMaxPerLevel();
        if (tempHealth < minHealth) {
            minHealth = tempHealth;
            minHealthCreature = i;
        }
            
    }
    
    int enemyMaxHealth = CreatureType::TYPES[enemyCreature].getHealthMaxBase() + enemyLevel
                        * CreatureType::TYPES[enemyCreature].getHealthMaxPerLevel();
    
    if (minHealth + 4 <= enemyMaxHealth) {
        return minHealthCreature;
    }
    else {
        return -1;
    }
    
}

int Trainer::returnLowest() {
    return -1;
}

char Trainer::throwScroll(int enemyNumber) {
    CreatureType enemy = CreatureType::TYPES[enemyNumber];
    int weakness = enemy.getElementalWeakness();
    char weakChar = weakness + 'a';
    if (ourInfo.scrollsAvail[weakness] > 0) {
        return weakChar;
    }
    for (int i = 0; i < 8; i++) {
        char typeChar = i + 'a';
        if (ourInfo.scrollsAvail[i] > 0 && i != enemy.getElementalStrength()) {
            return typeChar;
        }
    }
    return 'z';
}

string Trainer::makeMove(stringstream& situation) {

    
    // pull the entire string out of stringStream& situation
    string situationString = situation.str();
    // situationString now includes ALL of the lines that will be sent to cout
    
    // Here's how to use the stringSplit function
    vector<string> lines = splitString(situationString, "\n");
    // This splits situationString into a vector of individual lines.
    // (it splits on the new line character "\n")
    // To access the 3rd line (as in 0, 1, 2, 3), you would use bracket access
    //   as in: lines[3]
    
    // This loop will iterate through all the lines
    int pipeLine = -1;
    // lines.size() tells us how many elements are in the vector<string> lines
    // In this case, it tells us how many lines we pulled in
    for (int i=0; i<lines.size(); i++) {
        // Store each line in the string line
        string line = lines[i];
        // Store the first char of line in the char c
        char c = line[0];
        // If c is a pipe ('|'), then this is the line that tells us about our
        //    party and the health of each Creature we own.
        if (c == '|') {
            // Store which line number this is
            pipeLine = i;
        }
    }
    
    // Now that we know which line has the health, do something with it
    //cout << lines[pipeLine] << "\n"; // Output for testing only
    
    // Split the party health line by pipes "|"
    vector<string> creatureHealthBits = splitString(lines[pipeLine], "|");
    // This gives us something like the vector description below
    /* { "",
     " *Jackal     10/10",
     " Yaminon    17/17",
     " Megapode   13/13",
     " Jackal     10/10",
     "" } */
    // You can see that the first and last pipe caused empty strings
    
    // Now, go through this information and pull out info for each entry
    // We do 1 to <creatureHealthBits.size()-1 because we only need the middle
    //    four elements (and are skipping the empty ones.
    int activeNum = 0;
    int typeNum = 0;

    for (int i=1; i<creatureHealthBits.size()-1; i++) {
        // cout just for testing
        //cout << creatureHealthBits[i] << "\n";
        
        // We are putting the string into a stringStream so we can use >>
        stringstream ss;
        ss << creatureHealthBits[i];
        
        // For example, we have a stringstream ss containing " *Jackal   10/10 "
        // pull the name as a string

        string name;
        ss >> name; // name = "*Jackal"
        ourInfo.level[i-1] = name[name.length() - 1] - '0';
        
        char firstCharInName = ' ';
        if (name[0] == '*') {
            activeNum = i-1;
            firstCharInName = name[1];
        }
        else {
            firstCharInName = name[0];
        }
        
        typeNum = firstCharInName - 'A';
        string fullName = CreatureType::typeName(typeNum, 0);
        ourInfo.name[i-1] = fullName;

        
        // pull the health
        int health;
        ss >> health; // health = 10
        ourInfo.healthAvail[i-1] = health;
        
        // Get rid of the slash char
        char slash;
        ss >> slash; // slash = '/'
        
        // get max health
        int maxHealth;
        ss >> maxHealth; // maxHealth = 10
        
        // cout this info for testing purposes
        //cout << "Name: " << name << " health: " << health << "\n";
    }
    
    char firstCharInActiveName = ourInfo.name[activeNum][0];
    
    typeNum = firstCharInActiveName - 'A';
    
    
    int exLine = -1;
    // lines.size() tells us how many elements are in the vector<string> lines
    // In this case, it tells us how many lines we pulled in
    for (int i=0; i<lines.size(); i++) {
        // Store each line in the string line
        string line = lines[i];
        // Store the first char of line in the char c
        char c = line[0];
        // If c is a pipe ('|'), then this is the line that tells us about our
        //    party and the health of each Creature we own.
        if (c == '!') {
            // Store which line number this is
            exLine = i;
            break;
        }
    }
    
    // Now that we know which line has the health, do something with it
    //cout << lines[pipeLine] << "\n"; // Output for testing only
    
    // Split the party health line by pipes "|"
    vector<string> itemBits = splitString(lines[exLine], "!");
    vector<string>scrollBits = splitString(lines[exLine+1], "!");

    // This gives us something like the vector description below
    /* { "",
     " *Jackal     10/10",
     " Yaminon    17/17",
     " Megapode   13/13",
     " Jackal     10/10",
     "" } */
    // You can see that the first and last pipe caused empty strings
    
    for (int i=1; i<itemBits.size()-1; i++) {
        vector <string> itemNums = splitString(itemBits[i], ":");
        stringstream ss;
        ss << itemNums[1];
        int numAvail = 0;
        ss >> numAvail;
        if (i-1 < 5)
            ourInfo.itemsAvail[i-1] = numAvail;
    }

    for (int i = 2; i < scrollBits.size() - 1; i++) {
        vector <string> scrollNums = splitString(scrollBits[i], ":");
        stringstream ss;
        ss << scrollNums[1];
        int numAvail = 0;
        ss >> numAvail;
        if (i-1 < 8)
            ourInfo.scrollsAvail[i-1] = numAvail;

    }
    
    
    
    
    // This is something else you can do ONLY for testing.
    // In a previous post, I recommended #including CreatureType.h so that you
    //    can make a Trainer::decide() function that will make the right
    //    decision if you have perfect data about creature types.
    // While developing, you can use the static vector<CreatureType> TYPES to
    //    get that perfect information, though you will eventually need to write
    //    your own function to learn that information from the data that is sent
    //    in via stringstream& situation.
    
    
    /*    // This makes ct a copy of the CreatureType for Creature 0 (the Axolotyl).
     // All CreatureType and Element names start with a different letter of the
     //    alphabet (CreatureType is A-Z, Element is A-H).
     CreatureType ct = CreatureType::TYPES[0];
     // You can then get the type of ct, which is 0 because it's the Axolotyl
     int type = ct.getType();
     // You can also directly get info from CreatureTypes::TYPES elements.
     int elementalWeakness3 = CreatureType::TYPES[3].getElementalWeakness();
     */
    
    // Output for human player
    // Instead of doing this, you will need to replace the code of Trainer
    // to parse the input situation and create a proper response,
    // (like "a" for attack or "s3" to swap to the creature in slot 3).
      cout << situationString;
    
    int underscoreLine = -1;
    
    for (int i=0; i<lines.size(); i++) {
        // Store each line in the string line
        string line = lines[i];
        // Store the first char of line in the char c
        char c = line[0];
        // If c is a underscore ('_'), then this is the line that tells us about our
        //    party and the health of each Creature we own.
        if (c == '_') {
            // Store which line number this is
            underscoreLine = i;
        }
    }
    string enemyName = "";
    int enemyLevel = 0;
    bool enemyHasFainted = false;
    
    if (underscoreLine != -1) {
        vector<string>enemyAttackInfo = splitString(lines[underscoreLine + 3], " ");
        for (int i = 0; i < enemyAttackInfo.size(); i++) {
            if (enemyAttackInfo[i] == "faints!") {
                enemyHasFainted = true;
                break;
            }
        }
        

        if (enemyAttackInfo.size() > 1)
            enemyName = enemyAttackInfo[1];
    }
    char e = enemyName[enemyName.size()-1];
    char O = '0';
    enemyLevel = e - O;
    char firstCharInEnemyName = enemyName[0];
    int enemyTypeNum = firstCharInEnemyName - 'A';
    string fullName = CreatureType::typeName(enemyTypeNum, 0);
    enemyName = fullName;

    
    //  ourInfo.getInfo();

    
    if (enemyHasFainted) {
        if (ourInfo.healthAvail[activeNum] < 4) {
            ourInfo.numMoves++;
            return "r";
        }
        if (ourInfo.itemsAvail[4] > 0) {
            int n = captureCreature(enemyTypeNum, enemyLevel);
            switch (n) {
                case 0:
                    ourInfo.prevMove = "co1";
                    ourInfo.numSwaps = 0;
                    ourInfo.numMoves++;
                    return "co1";
                case 1:
                    ourInfo.prevMove = "co2";
                    ourInfo.numSwaps = 0;
                    ourInfo.numMoves++;
                    return "co2";
                case 2:
                    ourInfo.prevMove = "co3";
                    ourInfo.numSwaps = 0;
                    ourInfo.numMoves++;
                    return "co3";
                case 3:
                    ourInfo.prevMove = "co4";
                    ourInfo.numSwaps = 0;
                    ourInfo.numMoves++;
                    return "co4";
                default:
                    ourInfo.prevMove = "r";
                    ourInfo.numSwaps = 0;
                    ourInfo.numMoves++;
                    return "r";
            }

        }
        ourInfo.numMoves++;
        return "r";
    }
    
    
    
    if (ourInfo.healthAvail[activeNum] == 0) {
        int number = pickCreature(activeNum, ourInfo.level[activeNum],
                                  enemyTypeNum, enemyLevel);
        switch (number) {
            case 0:
                ourInfo.prevMove = "s1";
                ourInfo.numSwaps++;
                ourInfo.numMoves++;
                return "s1";
            case 1:
                ourInfo.prevMove = "s2";
                ourInfo.numSwaps++;
                ourInfo.numMoves++;
                return "s2";
            case 2:
                ourInfo.prevMove = "s3";
                ourInfo.numSwaps++;
                ourInfo.numMoves++;
                return "s3";
            case 3:
                ourInfo.prevMove = "s4";
                ourInfo.numSwaps++;
                ourInfo.numMoves++;
                return "s4";
            
        }
    }
    if ((activeNum == 0 && ourInfo.healthAvail[1] == 0
         && ourInfo.healthAvail[2] == 0
         && ourInfo.healthAvail[3] == 0) ||
        (activeNum == 1 && ourInfo.healthAvail[0] == 0
         && ourInfo.healthAvail[2] == 0
         && ourInfo.healthAvail[3] == 0) ||
        (activeNum == 2 && ourInfo.healthAvail[1] == 0
         && ourInfo.healthAvail[0] == 0
         && ourInfo.healthAvail[3] == 0) ||
        (activeNum == 3 && ourInfo.healthAvail[1] == 0
         && ourInfo.healthAvail[2] == 0
         && ourInfo.healthAvail[0] == 0)) {
            ourInfo.prevMove = "a";
            ourInfo.numSwaps = 0;
            ourInfo.numMoves++;
            return "a";
        }
    

    int newEnemyLine = -1;
    
    for (int i=0; i<lines.size(); i++) {
        // Store each line in the string line
        string line = lines[i];
        // Store the first char of line in the char c
        char c = line[1];
        // If c is a pipe ('|'), then this is the line that tells us about our
        //    party and the health of each Creature we own.
        if (c == 't') {
            // Store which line number this is
            newEnemyLine = i;
        }
    }
    
    if (newEnemyLine != -1) {
        vector<string>ourAttackInfo = splitString(lines[newEnemyLine], " ");
        string newEnemyName = ourAttackInfo[3];
        string newNewEnemyName = "";
        if (newEnemyName[newEnemyName.size() - 1] == '!') {
            for (int k = 0; k < newEnemyName.size() - 1; k++) {
                newNewEnemyName[k] = newEnemyName[k];
            }
        }

        if (newNewEnemyName != "") {
            newEnemyName = newNewEnemyName;
        }
        
        char e = newEnemyName[newEnemyName.size()-2];
        char O = '0';
        int nEnemyLevel = e - O;
        char firstCharInNEnemyName = newEnemyName[0];
        int nEnemyTypeNum = firstCharInNEnemyName - 'A';
        string nEFullName = CreatureType::typeName(nEnemyTypeNum, 0);
        newEnemyName = nEFullName;
        
        int nEnemyAttackNum = 0;
        
        nEnemyAttackNum = CreatureType::TYPES[nEnemyTypeNum].getAttackBase() +
        CreatureType::TYPES[nEnemyTypeNum].getAttackPerLevel()
        * nEnemyLevel;
        
        int nEnemyAttack = CreatureType::TYPES[nEnemyTypeNum].getElementalAttackType();
        int ourWeakness = CreatureType::TYPES[typeNum].getElementalWeakness();
        
        if (nEnemyAttack == ourWeakness) {
            nEnemyAttackNum *= 2;
        }
        
        
        if (ourWeakness != nEnemyAttack && ourInfo.healthAvail[activeNum] > nEnemyAttackNum) {
            ourInfo.prevMove = "a";
            ourInfo.numSwaps = 0;
            ourInfo.numMoves++;
            return "a";
        }
        else {
            int n = pickCreature(activeNum, ourInfo.level[activeNum],
                                      nEnemyTypeNum, nEnemyLevel);;
            switch (n) {
                case 0:
                    ourInfo.prevMove = "s1";
                    ourInfo.numSwaps++;
                    ourInfo.numMoves++;
                    return "s1";
                case 1:
                    ourInfo.prevMove = "s2";
                    ourInfo.numSwaps++;
                    ourInfo.numMoves++;
                    return "s2";
                case 2:
                    ourInfo.prevMove = "s3";
                    ourInfo.numSwaps++;
                    ourInfo.numMoves++;
                    return "s3";
                case 3:
                    ourInfo.prevMove = "s4";
                    ourInfo.numSwaps++;
                    ourInfo.numMoves++;
                    return "s4";
                default:
                    ourInfo.prevMove = "a";
                    ourInfo.numSwaps = 0;
                    ourInfo.numMoves++;
                    return "a";
            }

        }
    }
    
    if (ourInfo.numSwaps >= 3) {
        char scroll = throwScroll(enemyTypeNum);
        switch (scroll) {
                case 'a':
                    ourInfo.prevMove = "sa";
                    ourInfo.numSwaps = 0;
                    ourInfo.numMoves++;
                    return "sa";
                case 'b':
                    ourInfo.prevMove = "sb";
                    ourInfo.numSwaps = 0;
                    ourInfo.numMoves++;
                    return "sb";
                case 'c':
                    ourInfo.prevMove = "sc";
                    ourInfo.numSwaps = 0;
                    ourInfo.numMoves++;
                    return "sc";
                case 'd':
                    ourInfo.prevMove = "sd";
                    ourInfo.numSwaps = 0;
                    ourInfo.numMoves++;
                    return "sd";
                case 'e':
                    ourInfo.prevMove = "se";
                    ourInfo.numSwaps = 0;
                    ourInfo.numMoves++;
                    return "se";
                case 'f':
                    ourInfo.prevMove = "sf";
                    ourInfo.numSwaps = 0;
                    ourInfo.numMoves++;
                    return "sf";
                case 'g':
                    ourInfo.prevMove = "sg";
                    ourInfo.numSwaps = 0;
                    ourInfo.numMoves++;
                    return "sg";
                case 'h':
                    ourInfo.prevMove = "sh";
                    ourInfo.numSwaps = 0;
                    ourInfo.numMoves++;
                    return "sh";
                default:
                    ourInfo.prevMove = "a";
                    ourInfo.numSwaps = 0;
                    ourInfo.numMoves++;
                    return "a";
        }
    }
    
    
    int enemyAttackNum = CreatureType::TYPES[enemyTypeNum].getAttackBase() +
                        CreatureType::TYPES[enemyTypeNum].getAttackPerLevel()
                        * enemyLevel;
    
    int enemyAttackType = CreatureType::TYPES[enemyTypeNum].getElementalAttackType();
    int ourWeakness =  CreatureType::TYPES[typeNum].getElementalWeakness();
    int ourStrength = CreatureType::TYPES[typeNum].getElementalStrength();
    
    if (enemyAttackType == ourWeakness) {
        enemyAttackNum *= 2;
    }
    if (enemyAttackType == ourStrength) {
        enemyAttackNum /= 2;
    }
    
    
    if (ourInfo.healthAvail[activeNum] > enemyAttackNum) {
        // changed the condition to potentially fix the 6 threshold problem
        ourInfo.prevMove = "a";
        ourInfo.numSwaps = 0;
        ourInfo.numMoves++;
        return "a";
    }
    
    else {
        int number = pickCreature(activeNum, ourInfo.level[activeNum],
                                  enemyTypeNum, enemyLevel);;
        switch (number) {
            case 0:
                ourInfo.prevMove = "s1";
                ourInfo.numSwaps++;
                ourInfo.numMoves++;
                return "s1";
            case 1:
                ourInfo.prevMove = "s2";
                ourInfo.numSwaps++;
                ourInfo.numMoves++;
                return "s2";
            case 2:
                ourInfo.prevMove = "s3";
                ourInfo.numSwaps++;
                ourInfo.numMoves++;
                return "s3";
            case 3:
                ourInfo.prevMove = "s4";
                ourInfo.numSwaps++;
                ourInfo.numMoves++;
                return "s4";
            default:
                ourInfo.prevMove = "a";
                ourInfo.numSwaps = 0;
                ourInfo.numMoves++;
                return "a";
        }
    }
    
    
    
    /*
     * This line is basically what your AI chooses to do
     * When first playing, you may type in your move.
     * For both the core and reach portions, however, you need to
     * comment out "cin >> response" and instead have this function
     * generate a response string.
     */
    //string response;
    //cin >> response;
    
    
    //return response;
}


void Trainer::finalSituation(stringstream& situation) {
//    cout << "We survived " << ourInfo.numMoves << "moves..." << endl;
       cout << situation.str();
    
}



vector<string> Trainer::splitString(string inString, string splitOn) {
    vector<string> elements;
    string substring;
    
    size_t splitIndex = inString.find(splitOn),
    substrStart = 0;
    
    // keep searching until no spaces remain
    while (splitIndex != string::npos) {
        substring = inString.substr(substrStart, splitIndex - substrStart);
        elements.push_back(substring);
        substrStart = splitIndex + 1;
        // start at next character after finding substring
        splitIndex = inString.find(splitOn, substrStart);
    }
    // add last element to vector
    substring = inString.substr(substrStart, inString.length() - substrStart);
    elements.push_back(substring);
    
    return elements;
}