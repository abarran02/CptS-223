#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <string.h>

#include "List.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;

// stores name and description pair of a Linux command
struct cmdData {
    string name;
    string description;
};

// stores name and score pair of a player profile
struct profile {
    string name;
    int score;
};

class Wrapper {
public:
    Wrapper(string commandsFile, string gameFile) {
        mCommandsFile = commandsFile;
        mGameFile = gameFile;

        modified = false;
    }

    Wrapper(const Wrapper& app) {
        mCommandsFile = app.mCommandsFile;
        mGameFile = app.mGameFile;

        modified = false;
    }

    void run();
    
private:
    List<cmdData> mCmds;
    profile players[16];
    int playerCount;
    string mCommandsFile;
    string mGameFile;

    void importCmdList();
    void importProfiles();
    cmdData parseCmdLine(string line);
    profile parseProfile(string line);
    void printMenu();
    
    void printRules();
    void playGame(int startScore);
    void loadPreviousGame(int &score);
    void addCmd();
    void removeCmd();

    bool modified;
    void updateProfile(string name, int score);
    void saveCmds();
    void saveProfiles();

    void randomizeIntArray(int intArray[], int length, int min, int max);
};

int randomIntInRange(int min, int max);
int promptIntInRange(int min, int max, string message);
void clrscr();
bool operator==(const cmdData& lhs, const cmdData& rhs);
