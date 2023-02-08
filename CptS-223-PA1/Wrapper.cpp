#include "Wrapper.h"

/*************************************************************
 * Function: run ()                                          *
 * Description: runs the program wrapper, opening files and  *
 *        allowing user to interact with the game            *
 *************************************************************/
void Wrapper::run() {
	int option, score = 0;
	bool exit = false;

    // import initial list of commands from csv
    importCmdList();
	// import previous game scores
	importProfiles();

	// on first run: as long as files were opened successfully
	// thereafter: as long as user doesn't enter exit function
	while (!exit) {
		// display menu and prompt user for a menu option to execute
		printMenu();
		option = promptIntInRange(1, 6, "Enter an option : ");
		// clear the screen
		clrscr();

		switch (option) {
		case 1:
			printRules();
			break;
		case 2:
			playGame(score);
			break;
		case 3:
			loadPreviousGame(score);
			break;
		case 4:
			addCmd();
			break;
		case 5:
			removeCmd();
			break;
		case 6:
			exit = true;
			if (this->modified) {
				saveCmds();
			}
			saveProfiles();
			break;
		}
	}
}

/*************************************************************
 * Function: printMenu ()                                    *
 * Description: displays program options to the sceen        *
 *************************************************************/
void Wrapper::printMenu() {
	string options[6] = { "Game Rules", "Play Game", "Load Previous Game",
        "Add Command", "Remove Command", "Exit"};

	// iterate over options and print to screen with corresponding option number
	for (int i = 1; i < 7; i++) {
		cout << "[" << i << "] " << options[i - 1] << std::endl;
	}
}

/*************************************************************
 * Function: printRules ()                                   *
 * Description: print game rules to the screen               *
 *************************************************************/
void Wrapper::printRules() {
	cout << "The objective is to match Linux commands to descriptions of those commands. If a command guess, the player earns 1 point. If the guess is incorrect, the player loses a point. Negative point totals are possible. The player selects between five and thirty questions at the beginning of the game.";
	cout << endl;
}

/*************************************************************
 * Function: importCmdList ()                                *
 * Description: iterate over command list file and parse     *
 *        each line into cmdData struct, add to list         *
 *************************************************************/
void Wrapper::importCmdList() {
	string line;
	mCmds.clearList();
	cmdData newData;

	// open command file for reading
	std::ifstream cmdStream;
	cmdStream.open(mCommandsFile);

	// with help from https://stackoverflow.com/questions/5343173/
	cmdStream.clear();
	cmdStream.seekg(0);
	
	// iterate over each line of file
	while (getline(cmdStream, line)) {
		newData = parseCmdLine(line);
		mCmds.insertAtFront(newData);
	}

	cmdStream.close();
}

/*************************************************************
 * Function: importProfiles ()                               *
 * Description: iterate over previous games file and parse   *
 *        each line into profile struct, add to array        *
 *************************************************************/
void Wrapper::importProfiles() {
	string line;
	// clear player profile array
	for (int i = 0; i < 16; i++) {
		players[i].name = "";
		players[i].score = 0;
	}
	playerCount = 0;

	// open player file for reading
	std::ifstream gameStream;
	gameStream.open(mGameFile);

	// with help from https://stackoverflow.com/questions/5343173/
	gameStream.clear();
	gameStream.seekg(0);
	
	// iterate over each line of file or until profile limit
	while (getline(gameStream, line) && playerCount < 16) {
		players[playerCount] = parseProfile(line);
		playerCount++;
	}

	gameStream.close();
}

/*************************************************************
 * Function: parseCmdLine ()                                 *
 * Description: parse csv lines from command pairs into      *
 *        cmdData struct                                     *
 *************************************************************/
cmdData Wrapper::parseCmdLine(string line) {
	string item;
	std::stringstream lineStream;
	cmdData newData;

	// load line into string stream
	lineStream.str(line);

	// name
	getline(lineStream, item, ',');
	newData.name = item;

	// next portion is quoted to allow commas within description
	if (lineStream.peek() == '"') {
		// ingest first quotation mark
		getline(lineStream, item, '"');
		// actually get description
		getline(lineStream, item, '"');
	} else {
		getline(lineStream, item, ',');
	}
	newData.description = item;

	return newData;
}

/*************************************************************
 * Function: parseProfile ()                                 *
 * Description: parse csv lines from previous games file     *
 *        into profile struct                                *
 *************************************************************/
profile Wrapper::parseProfile(string line) {
	string item;
	std::stringstream lineStream;
	profile newData;

	// load line into string stream
	lineStream.str(line);

	// name
	getline(lineStream, item, ',');
	newData.name = item;

	// score
	getline(lineStream, item, ',');
	newData.score = stoi(item);

	return newData;
}

/*************************************************************
 * Function: playGame ()                                     *
 * Description: allows user to play game defined in earlier  *
 *        in printRules ()                                   *
 *************************************************************/
void Wrapper::playGame(int startScore) {
	int score = startScore;
	int totalGuesses = 0;
	string name;
	// prompt user for name
	cout << "What is your name? ";
	cin >> name;

	// prompt user for questions score to end game
	int questions = promptIntInRange(5, 30, "How many questions will you answer? ");
	int cmdList[3];
	int printOrder[3];
	int usedCmds[mCmds.getLength()] = {0};

	// game loop
	for (int i = 0; i < questions; i++) {
		// get three random commands
		do {
			randomizeIntArray(cmdList, 3, 0, mCmds.getLength() - 1);
		} while (usedCmds[ cmdList[0] ]);
		
		// update list of used commands
		usedCmds[ cmdList[0]] = 1;

		// print in random order to screen
		randomizeIntArray(printOrder, 3, 0, 2);

		// print command to guess for
		int correct = cmdList[0];
		cout << mCmds.getNodeAtPosition(correct)->data.name << endl;

		int desc;
		// print each description to the screen
		for (int i = 0; i < 3; i++) {
			desc = printOrder[i];
			cout << "[" << i << "] ";
			cout << mCmds.getNodeAtPosition( cmdList[desc] )->data.description << endl;
		}

		// get user guess and check adjust score
		int guess = promptIntInRange(0, 2, "Which command does this correspond to? ");
		totalGuesses++;

		clrscr();
		// indicate whether guess was correct, and update score
		if (printOrder[guess] == 0) {
			score++;
			cout << "Correct! Your score is now " << score << endl;
		}
		else {
			score--;
			cout << "Wrong! Your score is now " << score << endl;
			// show correct answer
			cout << mCmds.getNodeAtPosition(0)->data.name << " - " << mCmds.getNodeAtPosition(0)->data.description << endl;
		}
	}

	// save score to user profile
	updateProfile(name, score);
}

/*************************************************************
 * Function: loadPreviousGame ()                             *
 * Description: loads previous game scores from scores.csv   *
 *************************************************************/
void Wrapper::loadPreviousGame(int &score) {
	string name;
	bool found = false;
	// get name from user
	cout << "Enter your name: ";
	cin >> name;

	// find match for player profile
	for (int i = 0; i < playerCount; i++) {
		if (players[i].name == name) {
			score = players[i].score;
			found = true;
			break;
		}
	}

	if (found) {
		cout << "Welcome back " << name << ". Your score is " << score << "." << endl; 
	} else {
		cout << "Unable to find matching profile for '" << name << "'." << endl;
	}
}

/*************************************************************
 * Function: addCmd ()                                       *
 * Description: allows user to add command to quiz list      *
 *************************************************************/
void Wrapper::addCmd() {
	cmdData newData;
	bool valid = false;
	node<cmdData>* pCurrent;

	while (!valid) {
		cout << "Enter the command name to add [or 'quit']: ";
		cin >> newData.name;

		valid = true;
		pCurrent = mCmds.getHead();
		// ensure command isn't a duplicate
		while (pCurrent != nullptr) {
			// allow user to quit
			if (newData.name == "quit") {
				return;
			}
			if (pCurrent->data.name == newData.name) {
				valid = false;
				break;
			}
			pCurrent = pCurrent->next;
		}

		if (!valid) {
			cout << "Duplicate command entered. Please try again." << endl;
		}
	}
	
	cout << "Enter the command description: ";
	// ingest newline in first
	getline(cin, newData.description);
	getline(cin, newData.description);
	cout << "Command '" << newData.name << "' successfully added." << endl;

	mCmds.insertAtFront(newData);
	this->modified = true;
}

/*************************************************************
 * Function: removeCmd ()                                    *
 * Description: allows user to remove command from quiz list *
 *************************************************************/
void Wrapper::removeCmd() {
	// list must not be empty to remove any commands
	if (!mCmds.isEmpty()) {
		string name;
		bool removed = false;
		// get command to remove from user
		cout << "Enter the command name to remove: ";
		cin >> name;

		node<cmdData>* pCurrent = mCmds.getHead();
		// iterate over list to find match
		while (pCurrent != nullptr) {
			if (pCurrent->data.name == name) {
				removed = mCmds.removeNode(pCurrent);
				break;
			}
			pCurrent = pCurrent->next;
		}

		// inform user whether command was successfully removed
		if (removed) {
			this->modified = true;
			cout << "Command '" << name << "' successfully removed." << endl;
		}
		else {
			cout << "Unable to find command '" << name << "' to remove." << endl;
		}
	}
	else {
		cout << "Command list is empty, unable to remove." << endl;
	}
}

void Wrapper::updateProfile(string name, int score) {
	// see if name matches in existing array
	for (int i = 0; i < playerCount; i++) {
		// match found, update score
		if (players[i].name == name) {
			players[i].score = score;
			return;
		}
	}

	// else, need to create new profile
	if (playerCount < 16) {
		players[playerCount].name = name;
		players[playerCount].score = score;
		playerCount++;
	} else {
		// player array is out of memory
		cout << "Player profile array is full. Score will not be saved." << endl;
	}
}

/*************************************************************
 * Function: saveCmds ()                                     *
 * Description: saves command data to commands.csv           *
 *************************************************************/
void Wrapper::saveCmds() {
	// open commands file for writing, and overwrite data
	std::ofstream cmdStream;
	cmdStream.open(mCommandsFile, std::ofstream::trunc);

	// iterate over command linked list and print each entry to file
	node<cmdData>* pCurrent = mCmds.getHead();
	while (pCurrent != nullptr) {
		cmdStream << pCurrent->data.name << ",\"" << pCurrent->data.description << "\"\n";
		pCurrent = pCurrent->next;
	}

	cmdStream.close();
}

/*************************************************************
 * Function: saveProfiles ()                                 *
 * Description: saves game data to scores.csv                *
 *************************************************************/
void Wrapper::saveProfiles() {
	// open games file for writing, and overwrite data
	std::ofstream gameStream;
	gameStream.open(mGameFile);

	// iterate over player profiles array and print each to file
	for (int i = 0; i < playerCount; i++) {
		gameStream << players[i].name << "," << players[i].score << "\n";
	}

	gameStream.close();
}

/*************************************************************
 * Function: randomizeIntArray ()                            *
 * Description: randomizes integer array with unique ints    *
 *        within the range provided                          *
 * Preconditions: min <= max, length is len of intArray[]    *
 * Postconditions: min <= ints <= max                        *
 *************************************************************/
void Wrapper::randomizeIntArray(int intArray[], int length, int min, int max) {
	int fill = 0;
	int newInt;
	bool valid;

	// fill array with random integers in range
	while (fill < length) {
		// generate new int
		newInt = randomIntInRange(min, max);
		
		valid = true;
		// ensure newInt isn't in array already
		for (int i = 0; i < fill; i++) {
			// found in array
			if (intArray[i] == newInt) {
				valid = false;
			}
		}

		// add newInt to end of array
		if (valid) {
			intArray[fill] = newInt;
			fill++;
		}
	}
}

/*************************************************************
 * Function: randomIntInRange ()                             *
 * Description: returns random int in the range provided     *
 * Preconditions: min <= max                                 *
 * Postconditions: min <= int <= max                         *
 *************************************************************/
int randomIntInRange(int min, int max) {
	return (rand()%(max-min+1))+min;
}

/*************************************************************
 * Function: promptIntInRange ()                             *
 * Description: prompts user with given message for an int   *
 *        within the range provided                          *
 * Preconditions: min <= max                                 *
 * Postconditions: min <= int <= max                         *
 *************************************************************/
int promptIntInRange(int min, int max, string message) {
    int prompt;

    do {
        // requires cin to load an int, clears input stream if it is not
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1024, '\n');
        }

        // print message to user and get their option input
        cout << message;
        cin >> prompt;

        // check that input is an int and is between min and max
    } while (cin.fail() || (prompt < min || prompt > max));

    return prompt;
}

/*************************************************************
 * Function: clrscr ()                                       *
 * Description: clears the screen                            *
 *************************************************************/
void clrscr() {
    // cross platform special characters that represent the clear screen cmd
    // with help from https://stackoverflow.com/questions/17335816/clear-screen-using-c
    cout << "\033[2J\033[1;1H";
}

/*************************************************************
 * Function: operator==                                      *
 * Description: comparison operator overload for cmdData     *
 *************************************************************/
bool operator==(const cmdData& lhs, const cmdData& rhs) {
    return (lhs.name == rhs.name && lhs.description == rhs.description);
}
