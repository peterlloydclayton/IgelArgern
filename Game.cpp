/*
a. File Name: Game.h
b. Author: Harika Para, Sereysathia Luy, Peter Clayton
c. Date: 03/27/2020
d. Compiler Used: Visual Studio 2019
e. Brief Description of the file: implementation file for the Game

*/

#include <cstdlib>
#include <stdlib.h>
#include <functional>
#include <ctime>
#include "Game.h"
#include "Color.h"

using namespace std;

// Constructor
Game::Game(int numOfPlayers, int currentPID) {
    numberOfPlayers = numOfPlayers;
    players.resize(numberOfPlayers);
    board.setNumberofPlayers(numberOfPlayers);
    currentPlayerId = currentPID;
}

// Destructor
Game::~Game() {
    delete winner;
    //for_each(players.begin(), players.end(), [](Player* p) {delete p;});
    //for_each(playerResults.begin(), playerResults.end(), [](pair<Player*,int> p) {delete p.first;});
}

// Main Game Logic
 void Game::start(bool verbose) {
    bool continueGame = true;
    char testModeResponse = 'n';
    bool isGameOver = false;
    // Turns on or off c++ display functionality
    if(!verbose) cout.setstate(ios_base::failbit);

    if (verbose) {
        cout << "\nWould you like to Enter Test Mode? (y/n)";
        cin >> testModeResponse;
    }
    testModeResponse = tolower(testModeResponse);

    setupPlayerHedgehogs();

    cout << "Total Hedgehogs added to the board!: " << hedgehogCreationCount << endl;


    // loop through players. Break Loop when the first player has three hedgehogs on the final square
    // Keep track of other players' hedgehogs on the square at that time
    while (!isGameOver) {
        // We continually loop through all players until there is a winner
        for (auto iter = players.begin();iter != players.end();iter++) {
            int hedgeHogId = (**iter).GetId();
            string hedgeHogColor = (**iter).GetColorString();

            int currentTrack;
            int takeSideStep;
            pair<int, int> sideStepDestination, playerMoveDestination;

            cout << "\n++++++++++++++++++++++++++++" << endl;
            cout << "NEW ROUND" << endl;
            cout << "++++++++++++++++++++++++++++" << endl;

            //----------------------
            // PART 1: ROLL THE DICE
            //----------------------
            cout << endl<<"**************" << endl;
            cout << "1.  Rolling Dice..." << endl;
            currentTrack = rollDice();      // CORE LOGIC
            cout << "Player "<<(**iter).GetId() <<" rolled a " << currentTrack << endl;
            cout << "The current track is Track " << currentTrack << endl << endl;;
            board.display();

            //------------------------------------------------------------------
            // PART TWO: OPTIONAL SIDE STEP: Can only move the player's hedgehog
            //------------------------------------------------------------------
            cout << "**************" << endl;
            cout << "2.  Side Step" << endl;
            cout << "Evaluating Side Step Move For "<< hedgeHogColor <<" Hedgehog"<< endl;
            sideStepDestination = processSideStep((*iter)); // CORE LOGIC

            // If processSideStep returns -1 there are no sidestep moves available
            if ((sideStepDestination.first != -1) && (sideStepDestination.second != -1)) {
                cout << "Player: " << Color::getColor((int)(**iter).GetColor()) << " Has Moved To Track: " << sideStepDestination.first + 1 << " Column: " << sideStepDestination.second+1 << endl;
            }else
                cout << "No Available Hedgehogs to Move: MAIN PROGRAM LOOP: PROCESS SIDE STEP" << endl;
            board.display();

            //------------------------
            // PART THREE: PLAYER MOVE
            //------------------------
            cout << "**************" << endl;
            cout << "3. Player: "<<hedgeHogId<<", Color: " << hedgeHogColor <<" will choose the next move for track: "<<currentTrack<< endl;
            playerMoveDestination = processPlayerMove(**iter,currentTrack); // CORE LOGIC

            // If processPlayerMove returns -1 there are no moves available
            if (playerMoveDestination.first == -1 || playerMoveDestination.second == -1) {
                continue;
            }
            board.display();

            if (testModeResponse=='y') {
                int test;
                cout << "Enter any number: " << endl;
                cin >> test;
            }

            //------------------------------------------
            // PART FOUR: DETERMINE IF THEIR IS A WINNER
            //------------------------------------------
            cout << "\n...Evaluating Game Progress Before the next round...\n" << endl;
            isGameOver = processLastColumn();
        }
    }
    
    displayResults();
    if (!verbose) {
        cout.clear(); // reactivate cout for displaying text to the console
        cout << "WINNER: " << winner->GetId() << ": " << winner->GetColorString() << endl;
    }
}

// logic for initial hedgehog placement per player
void Game::setupPlayerHedgehogs()
{
    setupHedgehogPlacementMatrix();                         // create a matrix to coordinate the appropriate placement of hedgehogs on the board
    int hedgehogLayer = 0;
    for (int i = 0; i < board.getHedgeHogsPerPlayer();i++) {        // Loop through each available layer for hedgehog placement
        for (auto iter = players.begin(); iter != players.end(); iter++) {  // loop through each player based on the number of hedgehogs per player
            cout << "\n*******************" << endl;
            cout << "\nCurrent Round of Hedgehogs: " << i + 1 << endl;
            availablePositions = displayAvailableStartTracks(hedgehogLayer);             // display vector positions that are empty
            chooseHedgehogTrack(*iter, hedgehogLayer);
            if (!hasEmptySpaces(hedgehogLayer))                     // stop looping through players if there are no more empty spaces
                hedgehogLayer++;
        }
    }
}

// Create matrix to store initial hedgehog positions
void Game::setupHedgehogPlacementMatrix() {
    // Calculate how many layers of hedgehogs are needed based on the amount of players and hedgehogs per player
    int totalHedgehogs = players.size() * board.getHedgeHogsPerPlayer();
    int baseTracks = totalHedgehogs / board.getRows();
    int remainingHedgehogs = totalHedgehogs % board.getRows();
    int totalHedgehogLayersNeeded;
    (remainingHedgehogs > 0) ? (totalHedgehogLayersNeeded = baseTracks + 1) : (totalHedgehogLayersNeeded = baseTracks);
    hedgeHogLayers.resize(totalHedgehogLayersNeeded);       // This sets up a vector of total hedgehog layers
    for (auto iter = hedgeHogLayers.begin(); iter != hedgeHogLayers.end(); iter++) {
        (*iter).resize(board.getRows());                    // This resizes the hedgehog layer to match the number of rows on the board
    }
}

// check if there are available spaces on the board to place hedgehogs
bool Game::hasEmptySpaces(int row) {
    auto it = find(hedgeHogLayers[row].begin(), hedgeHogLayers[row].end(), 0);      // check to see if there is a 0 value in the current layer
    if (it != hedgeHogLayers[row].end()) // if a 0 value is found there are still empty spaces remaining on that layer
        return true;
    else
        return false;
}

// display all available and unavailble tracks for hedgehog placement
vector<int> Game::displayAvailableStartTracks(int row) {
    int i = 0;
    vector<int> availableStartTracks;

    //display unavailable positions
    cout << "Unavailable Tracks: " << endl;
    for (auto iter = hedgeHogLayers[row].begin(); iter != hedgeHogLayers[row].end(); iter++) {
        if (*iter != 0)
            cout << "Track " << i + 1 << ": " << " has hedgehog " << *iter << endl;
        i++;
    };
    int j = 0;

    //display available positions
    cout << "Available Tracks: " << endl;
    for (auto iter = hedgeHogLayers[row].begin(); iter != hedgeHogLayers[row].end(); iter++) {
        if (*iter == 0){
            availableStartTracks.push_back(j);
            cout << "Track " << j + 1 << ": " << " is available.  Current Value: " << *iter << endl;
        }
        j++;
    };
    cout << endl;

    return availableStartTracks;
}

// Within the hedgehog placement matrix layers/tracks are used as 'holding containers' for the hedgehogs
// Once a track is chosen we then add the hedgehog to the board on that row and first column
void Game::chooseHedgehogTrack(Player * p, int row) {
    bool chooseAnotherTrack = true;
    vector<Hedgehog*> hh = p->getHedgehogs();

    auto hhIter = hh.begin();               // get hedgehog vector to rotate through player hedgehogs

    while (chooseAnotherTrack) {
        bool trackInRange = false;
        int chosenTrack;

        // validate track selection
        while (!trackInRange){
            chosenTrack = p->chooseTrack(availablePositions); // Tracks are zero based so we subtract 1 from the player's choice
            cout <<"Track chosen: "<<chosenTrack+1 << endl;
            (chosenTrack < board.getRows()) ? trackInRange = true : trackInRange = false;
        }

        // add hedgehog to board if the location in the hedgehog placement matrix is 0 (empty)
        if (hedgeHogLayers[row][chosenTrack] == 0) {
            hedgeHogLayers[row][chosenTrack] = p->GetId();      
            board.addHedgehog(chosenTrack,0,*hhIter);
            hedgehogCreationCount++;    // keep track of all the hedgehogs created
            hhIter++; // increment through player hedgehogs
            chooseAnotherTrack = false;
            cout << "Great Choice! You have chosen track " << chosenTrack+1 << endl;
        }else {
            cout << chosenTrack <<" is not available. Already occupied by player: "<< hedgeHogLayers[row][chosenTrack] <<"  Please choose another Track "<< endl;
            chooseAnotherTrack = true;
        }
    }
}

// First player move: Rolle the dice
int Game::rollDice()
{
    int roll;
    roll = rand() % board.getRows() + 1;
    return roll;
}

// Second Player Move: Process Optional Sidestep
pair<int, int> Game::processSideStep(Player * currentPlayer) {
    pair<int, int> destinationSquare;
    pair<int, int> currentLocation;
    vector<Hedgehog*> availablePlayerHedeghogs;
    int sideStepDirection;
    int randomHedgehogIndex;

    // determine if hedgehog is on the top of the stack
    int currentPlayerHedgehogSize = currentPlayer->getHedgehogs().size();
    cout << " Hedgehogs for SideStep consideration for Player: " << currentPlayer->GetId() << ", Color: " << currentPlayer->GetColorString()<< endl;

    for(int i = 0; i < currentPlayerHedgehogSize;i++) {       // cycle through all of the players hedgehogs
        Hedgehog * currentPlayerHedgehog = currentPlayer->getHedgehogs()[i];
 
        cout << "Current Hedgehog Number: "<<currentPlayer->GetColorString()<<": "<<i << endl;

        int hhRow = (*currentPlayer->getHedgehogs()[i]).getLocation().first;
        int hhColumn = (*currentPlayer->getHedgehogs()[i]).getLocation().second;
        if (((hhRow-1)>=0)&&((hhColumn-1)>=0)) {
            if (board.getSquare(hhRow-1, hhColumn-1)->getTopHedgehog() != nullptr) {
                int targetSquareTopHedgehogID = board.getSquare(hhRow-1, hhColumn-1)->getTopHedgehog()->getPlayerId(); // target square top hedgehog
                // if the hedgehog at location x,y is the same color/id/ as the top hedgehog at that location add to available hedgehog vector
                if ((currentPlayerHedgehog)->getPlayerId() == targetSquareTopHedgehogID) {
                    availablePlayerHedeghogs.push_back(currentPlayerHedgehog);
                }
            }
        }
    }
    // If all hedgehogs are trapped return -1 for the locations
    if (availablePlayerHedeghogs.size() == 0) {
        cout << "Game::processSideStep: Not available" << endl;
        pair<int, int> p;
        p.first = -1;
        p.second = -1;
        return p;
    }

    // randomly select one of the available hedgehogs to move
    randomHedgehogIndex = rand() % availablePlayerHedeghogs.size();      // generates a random index for available hedgehogs
    Hedgehog *chosenHedgehog = availablePlayerHedeghogs[randomHedgehogIndex];      // use a random index to select Hedgehog.  Must initialize chosenHedgehogs with value inorder to invoke copy constructor
    currentLocation = chosenHedgehog->getLocation();
    
    // Decide whether to stay, move up, or move down
    sideStepDirection = rand() % 3;
    if (sideStepDirection == 0) {                                                       // Stay at the current location
        cout << "Player Has Chosen Not To Side Step" << endl;
        destinationSquare.first = currentLocation.first;
    }
    else if(sideStepDirection == 1 && (currentLocation.first < board.getRows()-2)){     // hedgehog is not in the bottom row
        cout << "Player Has Chosen To Side Step DOWN" << endl;
        cout << "Value of Board.GetRows(): "<< board.getRows() - 2 << endl;
        cout << "Value of currentLocation.first: " << currentLocation.first << endl;
        destinationSquare.first = currentLocation.first +1;                             // Move hedgehog down
    }
    else if (sideStepDirection == 2 && (currentLocation.first >= 1)) {                  // hedgehog is not in the top row
        cout << "Player Has Chosen To Side Step UP" << endl;
        destinationSquare.first = currentLocation.first - 1;                            // Move hedgehog up
    }

    destinationSquare.second = currentLocation.second;                                  // remain in the same column
    // if the player has chosen to sidestep, move the hedgehog to the new destination
    if (sideStepDirection != 0) {
        board.addHedgehog(destinationSquare, chosenHedgehog);
        pair<int, int> zCurrentLocation;        // adjusts the values of current location to match board's 0 based positioning system
        zCurrentLocation.first = currentLocation.first - 1;
        zCurrentLocation.second = currentLocation.second - 1;
        board.removeHedgehog(zCurrentLocation);
    }

    return destinationSquare;
}

// Third Player Move: Process forward move
pair<int, int> Game::processPlayerMove(Player& currentPlayer, int currentTrack) {
    pair<int, int> destinationLocation;
    pair<int, int> currentLocation;
    bool isValidTrack = false;
    bool isValidHedgehog = false;
    Player* player = &currentPlayer;
    Hedgehog* chosenHedgehog = 0;

    // validate track selection, make sure the row is not empty
    while (!isValidTrack) {
        isValidTrack = validateTrackSelection(currentTrack);
        if (!isValidTrack) {
            cout << "Empty track selected. Please roll again " << endl;
            currentTrack = rollDice();
            cout << "New track selected: " << currentTrack << endl;
        }
    }


    while (!isValidHedgehog) {
        // get chosenHedgehog
        chosenHedgehog = getChosenHedgehog(currentTrack);
        if (chosenHedgehog == nullptr) {
            isValidHedgehog = false;
            cout << "No Available Hedgehogs To Move: GET CHOSEN HEDGEHOG" << endl;
            pair<int, int> temp;
            temp.first = currentTrack;
            temp.second = board.getColumns();
            if (CheckPreviousSpacesForHedghogs(temp)) { // verify that there are previous hedgehogs available to choose from
                currentTrack = rollDice();
                cout << "New track selected: " << currentTrack << endl;
            }else {
                temp.first = -1;
                temp.second = -1;
                return temp;
            }
        }else {
            isValidHedgehog = true;
        }
    }
    
    //note: getlocation is not zero based
    currentLocation = chosenHedgehog->getLocation();
    cout<<"Chosen Hedgehog: Location: "<<currentLocation.first<<","<<currentLocation.second<<endl;

    // implementing destinationLocation as 0 Based
    destinationLocation.first = currentLocation.first-1;
    destinationLocation.second = currentLocation.second;

    // Board::getSquare is 0 Based
    Square* destinationSquare = board.getSquare(destinationLocation.first, (destinationLocation.second));

    // For a wormhole relocation
    if (destinationSquare->getSquareType()=="Wormhole") {
        destinationLocation.first = rand() % board.getRows();
        destinationLocation.second = rand() % board.getColumns();
        cout << "<<<<-------WORMHOLE WARP------->>>>" << endl;
        cout << "zero based: Moving to Track: "<<destinationLocation.first+1<<", Column: "<<destinationLocation.second+1 << endl;
    }
    // add&remove Hedgehog are 0 based!
    board.addHedgehog(destinationLocation, chosenHedgehog);
    pair<int, int> zCurrentLocation; // zero based current location
    zCurrentLocation.first = currentLocation.first - 1;
    zCurrentLocation.second = currentLocation.second - 1;
    board.removeHedgehog(zCurrentLocation);
    cout << "Player " << player->GetId() << " Has chosen to move Hedgehog ID: " << chosenHedgehog->getPlayerId() << " Color: " << chosenHedgehog->getColor()<<endl;
    cout << "Moving from: (" << currentLocation.first << "," << currentLocation.second << ") to (" << destinationLocation.first+1 << "," << destinationLocation.second+1 << ")" << endl;

    // free the trapped hedgehog on shallow trap if there are no previous spaces and there are no hedgehogs above
    Square* currentSquare = board.getSquare(currentLocation.first-1, currentLocation.second-1);
    if (currentSquare->getSquareType() == "Shallow") {
        cout << "FREE HEDGEHOG FROM SHALLOW TRAP!!!" << endl;
        ShallowTrap* shallow = dynamic_cast<ShallowTrap*>(board.getSquare(currentLocation.first-1, currentLocation.second-1));
        shallow->removeTrappedHedgehog();
    }

    return destinationLocation;
}

// validate track selection
bool Game::validateTrackSelection(int track) {
    for (int i = 0; i < board.getColumns();i++) {
        if (board.getSquare(track-1, i)->getTopHedgehog() != nullptr){
            return true;
        } else{
            continue;
        }
    }
    return false;
}

// Choose a random movable hedgehog from the current track
Hedgehog* Game:: getChosenHedgehog(int track)
{
    vector<Hedgehog*> availableHedgehogs;
    vector<Square*> currentTrack = board.getRow(track-1);  // get all the squares from the current track

    // main logic for getting movable hedgehogs
    availableHedgehogs = getMovableHedgehogs(currentTrack);
    if (availableHedgehogs.size() == 0) {
        cout << "NO AVAILABLE: GET CHOSEN HEDGEHOGS FOR CURRENT TRACK: "<<track << endl;
        return nullptr;
    }

    // display all available hedgehogs to potentially move
    for_each (availableHedgehogs.begin(), availableHedgehogs.end(), [](Hedgehog* hh) {
        cout << "ALL AVAILABLE HEDGEHOGS FROM GET MOVABLE HEDGEHOGS" << endl;
        (*hh).displayHedgehog();
        });

    // select a random Hedgehog from the vector
    int randHHToMove = rand() % availableHedgehogs.size();
    return availableHedgehogs[randHHToMove];
}

// get movable hedgehogs
vector<Hedgehog*> Game::getMovableHedgehogs(vector<Square*> &track){
    vector<Hedgehog*> movableHedgehogs;
    Hedgehog* currentHedgehog = 0;

    // CORE QUESTION: IS THE TOP HEDGEHOG MOVABLE
    // iterate through all the squres of the current track
    for (auto iter = track.begin(); iter != track.end(); iter++) {
        Square* currentSquare = (*iter);
        currentHedgehog = currentSquare->getTopHedgehog();
        string squareType = currentSquare->getSquareType();
        bool arePreviousSquaresEmpty;

        // ensure that the current hedgehog is not null and not in the last column of the board
        if ((currentHedgehog != nullptr) && (currentSquare->getLocation().second != board.getColumns())){
            currentHedgehog->setLocation(currentSquare->getLocation().first, currentSquare->getLocation().second);

            if (squareType == "Regular") {            //TOP HH MOVABLE: YES
                cout << "Processing Regular Square: " << endl;
                movableHedgehogs.push_back(currentHedgehog);
            }
            else if (squareType == "Normal") {        //TOP HH MOVABLE: IF PREVIOUS TRACKS ARE CLEAR
                cout << "Processing Normal Trap:  " << endl;
                arePreviousSquaresEmpty = CheckPreviousSpacesForHedghogs(currentSquare->getLocation());
                if (arePreviousSquaresEmpty)   // the board behind the current hedge hog is clear!
                    movableHedgehogs.push_back(currentHedgehog);
            }
            else if (squareType == "Shallow") {       //TOP HH MOVABLE: YES, UNLESS THERE'S ONLY ONE HEDGE HOG. IF SO UPDATE IN THE MOVE PORTION
                cout << "Processing Shallow Trap:  " << endl;
                movableHedgehogs.push_back(currentHedgehog); // **********must make sure remove hedgehog*********
            }
            else if (squareType == "Deep") {           //TOP HH MOVABLE: YES, UNLESS THERE'S ONLY ONE HEDGE HOG or has regained senses
                cout << "Processing Deep Trap:  " << endl;
                arePreviousSquaresEmpty = CheckPreviousSpacesForHedghogs(currentSquare->getLocation());
                if (arePreviousSquaresEmpty)   // the board behind the current hedge hog is clear!
                    movableHedgehogs.push_back(currentHedgehog);
            }
        }
    }

    return movableHedgehogs;
}

// Check all the previous squares the presence of hedgehogs
bool Game::CheckPreviousSpacesForHedghogs(pair<int, int> currentLocation) {
    // loop through the entire board up through the current column to find hedgehogs

    bool emptyRegion = true;
    for (int i = 0; i < board.getRows();i++) {
        for (int j = 0; j < currentLocation.second; j++) {
            if (board.getSquare(i, j)->getTopHedgehog() != nullptr) // Hedgehog found
                emptyRegion = false;
        }
    }
    return emptyRegion;
}

// Fourth Game Move: Process the last column on the board to identify if there is a winner
bool Game::processLastColumn() {
    // Check for 3 hedgehogs of one player in the last row
    
    //map<int,int> currentRoundLastColumnStats;
    map<Player*,int> currentRoundLastColumnStats;

    bool isGameOver = false;
    pair<Player*, int> currentPlayerLastColumnHedgeHogs;
    Player* currentHedgehogsPlayer = 0;
    vector<Square*> lastColumn = board.getColumn(board.getColumns()-1);

    // loop through all squares in the last column
    for (auto squareIter = lastColumn.begin();squareIter != lastColumn.end();squareIter++) {
        vector<Hedgehog*> hh = (*squareIter)->getAllHedgehogs();    // get all the hedgehogs on the current square
        if (hh.size() != 0) {
            // loop through all hedgehogs on the current square
            for (auto hhIter = hh.begin();hhIter != hh.end();hhIter++) {
                int playerId=(*hhIter)->getPlayerId();      // get the current playerId

                // find the player pointer corresponding to the current id
                for (auto iter = players.begin();iter != players.end();iter++) { 
                    if ((*iter)->GetId() == playerId) // currentHedgehog Id matches the current player in the loop
                    {
                        currentHedgehogsPlayer = (*iter);    
                        break;
                    }
                }

                if (currentRoundLastColumnStats.find(currentHedgehogsPlayer) != currentRoundLastColumnStats.end()) // check to see if current hedgehog/playerId is present within map of hedgehogs/players
                {
                    (currentRoundLastColumnStats.find(currentHedgehogsPlayer)->second)++; // increment the total of hedgehogs for the current player
                    if (currentRoundLastColumnStats.find(currentHedgehogsPlayer)->second >= hedgehogsNeededToWin) {   // see who has the total number of winning hedgehogs in the last column
                        winner = currentHedgehogsPlayer;
                        isGameOver = true;
                    }
                }else { // add the current playerId to the map of playerIds
                    currentPlayerLastColumnHedgeHogs.first = currentHedgehogsPlayer;
                    currentPlayerLastColumnHedgeHogs.second = 1;
                    currentRoundLastColumnStats.insert(currentPlayerLastColumnHedgeHogs);
                }
            }
        }
    }


    if (isGameOver) {
        playerResults = currentRoundLastColumnStats;
    }

    return isGameOver;
}

// add a vector of pre-created Players to the current vector<Player*>
void Game::addPlayers(vector<Player*> & newPlayers)
{
    int i = 0;

    players.resize(newPlayers.size());

    for(auto iter = newPlayers.begin(); iter != newPlayers.end(); iter++){
        players[i] = (*iter);
        i++;
    }
}

// Set/update one player to the game
void Game::setPlayer(int index, int iD, COLORS c) {
    players[index] = new Player(iD, c);
}

// display the game results
void Game::displayResults() {

    cout << "*************************" << endl;
    cout << "*************************" << endl;
    cout << "GAME STATS: " << endl;

    cout << "\nAND THE WINNER IS: \nID:" << winner->GetId()
        << "\nCOLOR: " << winner->GetColorString()
        << "\nWINNING HEDGEHOG TOTAL: " << playerResults[winner] << endl<<endl;

    cout << "\nADDITIONAL RESULTS" << endl;     // Show all the stats of players who have hedgehogs in the last column
        for(auto playerResultsIter = playerResults.begin(); playerResultsIter != playerResults.end(); playerResultsIter++){
            cout << "Player ID: " << (*playerResultsIter).first->GetId()
                <<", COLOR: " << (*playerResultsIter).first->GetColorString()
                << ", NUMBER OF HEDGEHOGS: " << (*playerResultsIter).second
                <<endl;
        }

    cout << "*************************" << endl;
    cout << "*************************" << endl<<endl;

}