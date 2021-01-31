#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <windows.h>
#include <ctype.h> 
#include <stdio.h> 
#include <iterator>
#include <stdlib.h>
#include <time.h>

using namespace std;
// Tic Tac Toe
// https://github.com/BandomasisGithub/ticitactoe/edit/main/main.cpp
// https://vk.com/doc13926071_415928574?hash=2a5c94421dceea8969&dl=ea3692e5b8dce423d8
// https://github.com/id-Software/Quake-III-Arena/commit/dbe4ddb10315479fc00086f08e25d968b4b43c49

//To do next:

// + Mark change
// + Starting first/secon
// + Fixing winning loops and loosing loops when i loose nothing hapens
// + Fixing the game loop it doesnt work there is no win or loose and the board is bs
// + After game end return a number and outside a gameLoop() function write a if statement which will decide what you do 
// + Shoul make that after winning or loosing you are shown the board and the only two options play again or go back to main menu
// + Stat tracker(how many win/ loose depending difficulty)

// - Possible impossible dificulty
// - One vs One(possibility to play againts othe players)


enum ParametersPlace {Difficulty = 0, MoveOrder = 1, Mark = 2};

enum StatsPlace{FirstDifficulty = 0, FirstDifficultyWins = 2, 
           FirstDifficultyLosses = 4, FirstDifficultyDraw = 6, 
           SecondDifficulty = 7, SecondDifficultyWins = 9,
           SecondDifficultyLosses = 11, SecondDifficultyDraw = 13};

void mainMenu();
void help();
void clearScreen();
string gameLoop(vector<string> parameters);
string gameOneVsOneLoop(vector<string> &parameters);
void parametersText();
vector<string> readingParameterFile();

void writingParameterFile(ParametersPlace parametersKey,
                          vector<string> &parameters,
                          string changeValue);

string writingParameterMenu(string parameterNumber, 
                            vector<string> &parameters);

string boardDataVisualRepresantation(const string& boardData);

string& dataRowConversionToBoard(string& board, 
                                const string& boardData, 
                                int rowsFirstPlace);

void gameLoopBoardOptions(bool const& boardHelpStatus,
                        string& boardData);

string gameEndConditions(int winingCombinationKey,
                            const string& boardData,
                            char playersMark,
                            char opponentMark);

void winingCombinationsCreation(int firstFieldKey, 
                                int secondFieldKey, 
                                int thirdFieldKey);

int computersTurn(string &boardData,
                    string &boardDataWithSpaces,
                    string &boardView,
                    char playersMark,
                    char opponentsMark,
                    string difficulty);

int impossibleDifficutlyComputer(string &boardData,
                    string &boardDataWithSpaces,
                    string &boardView,
                    char playersMark,
                    char opponentsMark);

int possibleDifficutlyComputer(string &boardData,
                    string &boardDataWithSpaces,
                    string &boardView,
                    char playersMark,
                    char opponentsMark);

int possibleModeLevel(const vector<int> &winingCombination, 
                    string boardData, 
                    int checkSpaceKey);

void saveFileExistence();
void statsFileExistence();
vector<string> readingStatsFile();
void writingToStatsFile(string gameResult,
                        string difficulty);
string endGameMessage(string endGameMessage, string &boardData);
void statsPage();
//vektoriu vektoriu vektorius reiktu pasiziuret alternatyva sitam 
// nes gaunas kaip masinu masinu masina
vector<vector<vector<int>>> GLOBAL_winningCombinations(9);
vector<string> GLOBAL_boardPlaces;
vector<int> GLOBAL_boardSpaceCordinates;
vector<string> GLOBAL_emptyBoard;




int main()
{

    //THIS FUNCTION CHANGES GLOBAL STATE BE AWARE
    saveFileExistence();
    statsFileExistence();
    
    //first field's wining combinations
    winingCombinationsCreation(0, 3, 6);
    winingCombinationsCreation(0, 1, 2);
    winingCombinationsCreation(0, 4, 8);

    //second field's wining combinations
    winingCombinationsCreation(1, 0, 2);
    winingCombinationsCreation(1, 4, 7);

    //third field's wining combinations
    winingCombinationsCreation(2, 0, 1);
    winingCombinationsCreation(2, 5, 8);
    winingCombinationsCreation(2, 4, 6);

    //fourth field's wining combinations
    winingCombinationsCreation(3, 0, 6);
    winingCombinationsCreation(3, 4, 5);

    //fifth field's wining combinations
    winingCombinationsCreation(4, 3, 5);
    winingCombinationsCreation(4, 1, 7);
    winingCombinationsCreation(4, 0, 8);
    winingCombinationsCreation(4, 2, 6);
    
    //sixth field's wining combinations
    winingCombinationsCreation(5, 2, 8);
    winingCombinationsCreation(5, 3, 4);

    //seventh field's wining combinations
    winingCombinationsCreation(6, 0, 3);
    winingCombinationsCreation(6, 7, 8);
    winingCombinationsCreation(6, 2, 4);

    //eighth field's wining combinations
    winingCombinationsCreation(7, 6, 8);
    winingCombinationsCreation(7, 4, 1);

    //ninth field's wining combinations
    winingCombinationsCreation(8, 4, 0);
    winingCombinationsCreation(8, 2, 5);
    winingCombinationsCreation(8, 6, 7);
    
    mainMenu();

    return 0;
};

void mainMenu()
{
    string playersChoise;
    int firstInfiniteLoopStatement = 0;
    int secondInfiniteLoopStatement = 1;
    string parameterMessage = "";

    do {
        //clearScreen();
        std::cout << "Welcome Tic Tac Toe" << std::endl;
        std::cout << std::endl;
        std::cout << "Press 1 to play the main game" << std::endl;
        std::cout << "Press 2 to play 1 Vs 1 (Local)" << std::endl;
        std::cout << "Press 3 to see the rules of the game" << std::endl;
        std::cout << "Press 4 to see game parameters" << std::endl;
        std::cout << "Press 5 to see your stats" << std::endl;
        std::cout << "Press 6 to exit" << std::endl;

        std::cin >> playersChoise;

        if (playersChoise == "1")
        {
            string menuFromGameLoop = "1";

            while(menuFromGameLoop == "1"){
            
                vector<string> parameters = readingParameterFile();
                string gameExitCode = gameLoop(parameters);
            
                if (gameExitCode != menuFromGameLoop) {

                    break;
                };
            };
        } else if(playersChoise == "2") {
            clearScreen();

            string menuFromGameLoop = "1";

            while(menuFromGameLoop == "1"){
            
                vector<string> parameters = readingParameterFile();
                string gameExitCode = gameOneVsOneLoop(parameters);
            
                if (gameExitCode != menuFromGameLoop) {

                    break;
                };
            };


        } else if (playersChoise == "3") {
            clearScreen();
            help();

        } else if(playersChoise == "4")
        {
            string playersParameterChoise;
            while(playersParameterChoise != "0") 
            {
                clearScreen();
                
                vector<string> parameters = readingParameterFile();

                std::cout << "Write 0 to return to previous menu" << std::endl;
                std::cout << "Write 1 to change difficulty" << std::endl;
                std::cout << "Write 2 to change move order" << std::endl;
                std::cout << "Write 3 to change mark" << std::endl;
                std::cout << std::endl;

                std::cout << "Difficulty: " << parameters[Difficulty] << std::endl;
                std::cout << "Move order: " << parameters[MoveOrder] << std::endl;
                std::cout << "Mark: " << parameters[Mark] << std::endl;
                std::cout << std::endl;

                if(parameterMessage != "")
                {
                    std::cout << std::endl;
                    std::cout << parameterMessage << std::endl;
                };

                std::cin >> playersParameterChoise;
                
                if(playersParameterChoise == "0")
                {
                    clearScreen();
                    break;

                } else {
                    
                    parameterMessage = writingParameterMenu(playersParameterChoise, parameters);
                    
                };
            };
                //changingParameters();
                
                //to check status
        } else if(playersChoise == "5")
        {
            statsPage();
            clearScreen();
            continue;
        } else if (playersChoise == "6") {

            return;
        } else {
            clearScreen();
            std::cout << "There is no such comand try to retype the comand" << std::endl;
        };
    } while (firstInfiniteLoopStatement != secondInfiniteLoopStatement);

    return;
};

string gameLoop(vector<string> parameters)
{

    vector<string> choosableBoardSpaces;
    int boardSpacesAmmount = 9;
    bool boardHelpStatus = false;
    string boardView;
    ParametersPlace parameterKey = Mark;
    char playersMark = parameters[parameterKey][0];
    char opponentMark;
    int pcChosenMarkKey;

    choosableBoardSpaces.push_back("1");
    choosableBoardSpaces.push_back("2");
    choosableBoardSpaces.push_back("3");
    choosableBoardSpaces.push_back("4");
    choosableBoardSpaces.push_back("5");
    choosableBoardSpaces.push_back("6");
    choosableBoardSpaces.push_back("7");
    choosableBoardSpaces.push_back("8");
    choosableBoardSpaces.push_back("9");


    // return 1 if I want to exit the program return 0 if I want to go back to menu

    //Ask To choose who starts 
    string playersInput;
    string boardSpaces = "123456789";
    string boardData = "         ";
    string boardDataWithSpaces = "123456789";
    boardView = boardDataWithSpaces;
    string playersChoise;
    clearScreen();
    
    //first HERE IT SHOULD BE REDIRECT TO A FUNCTION

    //if(first -> go to where the player starts first)
    //else -> go to where the player starts second

    if(playersMark == 'X') 
    {
        opponentMark = 'O';
    } else 
    {
        opponentMark = 'X';
    };

    parameterKey = MoveOrder;

    if(parameters[MoveOrder] == "Second")
    {
        computersTurn(boardData,
                        boardDataWithSpaces,
                        boardView,
                        playersMark,
                        opponentMark,
                        parameters[Difficulty]);      
        clearScreen();
        gameLoopBoardOptions(boardHelpStatus, boardView);
    };   



    // this should be one of jumping points

 
    clearScreen();
    gameLoopBoardOptions(boardHelpStatus, boardView);

    while (1 != 0)
    {
        //clearScreen();
        //gameLoopBoardOptions(boardHelpStatus, boardView);
        std::cin >> playersChoise;
        
        if (playersChoise == "0")
        {
            clearScreen();
            return "0";
        }
        else if (playersChoise == "h") {

            clearScreen();
            boardHelpStatus = !boardHelpStatus;
            gameLoopBoardOptions(boardHelpStatus, boardView);

            continue;
        }
        else if (playersChoise == "m")
        {
            clearScreen();
            std::cout << "The board was change to show places and marks" << std::endl;
            boardView = boardDataWithSpaces;
            gameLoopBoardOptions(boardHelpStatus, boardView);

            continue;
        }
        else if (playersChoise == "e")
        {
            clearScreen();
            std::cout << "The board was change to show only marks" << std::endl;
            boardView = boardData;
            gameLoopBoardOptions(boardHelpStatus, boardView);

            continue;

        }
        else if (playersChoise == "p")
        {
            clearScreen();
            std::cout << "The board was change to show only places" << std::endl;
            boardView = boardSpaces;
            gameLoopBoardOptions(boardHelpStatus, boardView);

            continue;
        };

        for (int i = 0; i < boardSpacesAmmount; i++)
        {
            if (choosableBoardSpaces[i] == playersChoise) {

                if (boardData[i] == 'X' || boardData[i] == 'O')
                {
                    clearScreen();
                    gameLoopBoardOptions(boardHelpStatus, boardView);
                    std::cout << "Choose a FREE space" << std::endl;

                    break;
                    //Return to guess again
                };

                boardData[i] = playersMark;
                boardDataWithSpaces[i] = playersMark;
                boardView[i] = playersMark;

                clearScreen();
                gameLoopBoardOptions(boardHelpStatus, boardView);

                //tikrinti ar yra laimintis variantas
                string gameEndStatus = gameEndConditions(
                                            i,
                                            boardData,
                                            playersMark,
                                            opponentMark);

                if(gameEndStatus == "Win") 
                {
                    writingToStatsFile(gameEndStatus, parameters[Difficulty]);

                    return endGameMessage("Congrats, you win", boardData);

                    // wining message and going back to the main menu
                }else if(gameEndStatus == "Draw")
                {
                    writingToStatsFile(gameEndStatus, parameters[Difficulty]);

                    return endGameMessage("Draw", boardData);
                };

                pcChosenMarkKey = computersTurn(boardData,
                                                boardDataWithSpaces,
                                                boardView,
                                                playersMark,
                                                opponentMark,
                                                parameters[Difficulty]);

                clearScreen();

                gameLoopBoardOptions(boardHelpStatus, boardView);

                gameEndStatus = gameEndConditions(
                                        pcChosenMarkKey,
                                        boardData,
                                        playersMark,
                                   
                                        opponentMark);

                if(gameEndStatus == "Loose")
                {

                    writingToStatsFile(gameEndStatus, parameters[Difficulty]);
                    
                    return endGameMessage("You loose", boardData);
                    
                } else if(gameEndStatus == "Draw")
                {
                    writingToStatsFile(gameEndStatus, parameters[Difficulty]);

                    return endGameMessage("Draw", boardData);
                };
    
                break;
            };

            clearScreen();
            gameLoopBoardOptions(boardHelpStatus, boardView);
            std::cout << "Choose an existing space" << std::endl;
        };
    };
    //should reloop to the start with changed board


    return "0";

    /*
    std::cout << boardDataVisualRepresantation(boardData);
    std::cout << std::endl;
    std::cout << boardDataVisualRepresantation(boardDataWithSpaces);
    std::cout << std::endl;
    std::cout << boardDataVisualRepresantation(boardS paces);
    */

    //should reloop to let a player input the required place of the board 


    //how to get Whole number part in c++
    //https://stackoverflow.com/questions/47837838/get-decimal-part-of-a-number
    //https://en.cppreference.com/w/cpp/numeric/math/modf
    //i should get whole number of i/3 which would be 1, 2 or 3
    // then give that number to determine which row is let say
    // GLOBAL_emptyBoard
    //1 should be 0, 2 should be 2, 3 should be 4
    //try to count smartly somehow or instead vector use map
    // and call that number lets say COF

    // after that save(example): 
    //GLOBAL_emptyBoard[COF][GLOBAL_boardSpaceCordinates[spaceCordinate]] = playersMark;


    // move to pc move and end this function



    //std::cout << "Choose an existing space" << std::endl;
    // return back to players choise

};

void help()
{
    string playersInput;

    std::cout << "1. You choose who starts first (you or pc)" << std::endl;
    std::cout << "2. The main goal is to get all your chosen 3 symbols in a line" << std::endl;
    std::cout << "3. You choose one free place (unmarked by your or your opents symbol) to mark " << std::endl;
    std::cout << "from the given board. After the choise your oponent gets to choose  and the cycle repeats " << std::endl;
    std::cout << "as long as the is no free spaces on the board or someone wins" << std::endl;
    std::cout << "4. Free spaces on the board are marked by numbers to choose a free space " << std::endl;
    std::cout << "wright the number of it" << std::endl;
    std::cout << "5. Wining combinations on the board:" << std::endl;
    std::cout << std::endl;
    std::cout << "X | X | X    O | O | O" << std::endl;
    std::cout << "---------    ---------" << std::endl;
    std::cout << "  |   |   Or   |   |  " << std::endl;
    std::cout << "---------    ---------" << std::endl;
    std::cout << "  |   |        |   |  " << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "  |   |        |   |  " << std::endl;
    std::cout << "---------    ---------" << std::endl;
    std::cout << "X | X | X Or O | O | O" << std::endl;
    std::cout << "---------    ---------" << std::endl;
    std::cout << "  |   |        |   |  " << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "  |   |        |   |  " << std::endl;
    std::cout << "---------    ---------" << std::endl;
    std::cout << "  |   |   Or   |   |  " << std::endl;
    std::cout << "---------    ---------" << std::endl;
    std::cout << "X | X | X    O | O | O" << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "  |   | X      |   | O" << std::endl;
    std::cout << "---------    ---------" << std::endl;
    std::cout << "  | X |   Or   | O |  " << std::endl;
    std::cout << "---------    ---------" << std::endl;
    std::cout << "X |   |      O |   |  " << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "X |   |      O |   |  " << std::endl;
    std::cout << "---------    ---------" << std::endl;
    std::cout << "  | X |   Or   | O |  " << std::endl;
    std::cout << "---------    ---------" << std::endl;
    std::cout << "  |   | X      |   | O" << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "  | X |        | O |  " << std::endl;
    std::cout << "---------    ---------" << std::endl;
    std::cout << "  | X |   Or   | O |  " << std::endl;
    std::cout << "---------    ---------" << std::endl;
    std::cout << "  | X |        | O |  " << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "X |   |      O |   |  " << std::endl;
    std::cout << "---------    ---------" << std::endl;
    std::cout << "X |   |   Or O |   |  " << std::endl;
    std::cout << "---------    ---------" << std::endl;
    std::cout << "X |   |      O |   |  " << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "  |   | X      |   | O" << std::endl;
    std::cout << "---------    ---------" << std::endl;
    std::cout << "  |   | X Or   |   | O" << std::endl;
    std::cout << "---------    ---------" << std::endl;
    std::cout << "  |   | X      |   | O" << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;

    std::cout << "To go back to previous menu press 0" << std::endl;

previousMenu:

    std::cin >> playersInput;
    if (playersInput == "0")
    {
        clearScreen();

        return;
    }
    else
    {
        std::cout << "There is no such comand try retype the comand" << std::endl;

        goto previousMenu;
    };

    return;
};

//clearScreen function is stackOwerfloaw magic 
void clearScreen()
{
    HANDLE                     hStdOut;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD                      count;
    DWORD                      cellCount;
    COORD                      homeCoords = { 0, 0 };

    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hStdOut == INVALID_HANDLE_VALUE) return;

    // Get the number of cells in the current buffer 
    if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
    cellCount = csbi.dwSize.X * csbi.dwSize.Y;

    // Fill the entire buffer with spaces 
    if (!FillConsoleOutputCharacter(
        hStdOut,
        (TCHAR)' ',
        cellCount,
        homeCoords,
        &count
    )) return;

    // Fill the entire buffer with the current colors and attributes 
    if (!FillConsoleOutputAttribute(
        hStdOut,
        csbi.wAttributes,
        cellCount,
        homeCoords,
        &count
    )) return;

    // Move the cursor home 
    SetConsoleCursorPosition(hStdOut, homeCoords);
};

string& dataRowConversionToBoard(string& board, const string& boardData, int rowsFirstPlace)
{
    int nextPlace = 1;

    board = board + " "
        + boardData[rowsFirstPlace] + " | "
        + boardData[rowsFirstPlace + nextPlace] + " | "
        + boardData[rowsFirstPlace + nextPlace + nextPlace] + " ";
    board += '\n';

    return board;
};

string boardDataVisualRepresantation(const string& boardData)
{

    string visualBoard;
    int firstFirstRowPlace = 0;
    int firstSecondRowPlace = 3;
    int firstThirdRowPlace = 6;

    vector<string> board;
    visualBoard = dataRowConversionToBoard(visualBoard, boardData, firstFirstRowPlace);
    visualBoard += "-----------";
    visualBoard += '\n';
    visualBoard = dataRowConversionToBoard(visualBoard, boardData, firstSecondRowPlace);
    visualBoard += "-----------";
    visualBoard += '\n';
    visualBoard = dataRowConversionToBoard(visualBoard, boardData, firstThirdRowPlace);
    visualBoard += '\n';

    return visualBoard;
};

void gameLoopBoardOptions(bool const& boardHelpStatus, string& boardData)
{
    if (boardHelpStatus == false)
    {
        std::cout << "Write 0 to exit the game" << std::endl;
        std::cout << "See more board options write h" << std::endl;
        std::cout << "Mark a free space by typing its number" << std::endl;
        std::cout << std::endl;
        std::cout << "The board view" << std::endl;
        std::cout << std::endl;
        std::cout << boardDataVisualRepresantation(boardData);
        std::cout << std::endl;

        return;
    };

    std::cout << "Write 0 to exit the game" << std::endl;
    std::cout << "To exit more board options write h" << std::endl;
    std::cout << "Mark a free space by typing its number" << std::endl;
    std::cout << "To change board view:" << std::endl;
    std::cout << "Board places with marks write m" << std::endl;
    std::cout << "Empty board with marks write e" << std::endl;
    std::cout << "Board places write p" << std::endl;
    std::cout << "Mark a free space by typing its number" << std::endl;
    std::cout << std::endl;
    std::cout << "The board view" << std::endl;
    std::cout << std::endl;
    std::cout << boardDataVisualRepresantation(boardData);
    std::cout << std::endl;

    return;
};


// below boardData should be given as reference
int computersTurn(string &boardData,
                    string &boardDataWithSpaces,
                    string &boardView,     
                    char playersMark,
                    char computersMark,
                    string difficulty)
{
    if(difficulty == "Impossible")
    {
        return impossibleDifficutlyComputer(boardData, boardDataWithSpaces,
                                            boardView, playersMark,
                                            computersMark); 
    };

    return possibleDifficutlyComputer(boardData, boardDataWithSpaces,
                                        boardView, playersMark,
                                        computersMark);
};

string gameEndConditions(int winingCombinationKey,
                            const string& boardData,
                            char playersMark,
                            char pcMark)
{
    for(vector<int> winingCombination : GLOBAL_winningCombinations[winingCombinationKey])
    {
        int playersMarkAmountInARow = 0;
        int pcMarkAmountInARow = 0;

        for(int winingCombinationPlace : winingCombination)
        {
            if(boardData[winingCombinationPlace] == playersMark)
            { 
                playersMarkAmountInARow++;
                continue;

            } else if (boardData[winingCombinationPlace] == pcMark)
            {
                pcMarkAmountInARow++;
                continue;
            };
        };

        if(playersMarkAmountInARow == 3)
        {

            return "Win";

        } else if(pcMarkAmountInARow == 3)
        {
            
            return "Loose";
        };
    };

    int freeSpaces = 0;

    for(int i = 0; i < 9; i++)
    {
        if(boardData[i] != ' ')
        {
            freeSpaces++;
        };
    };

    if(freeSpaces == 9)
    {
        return "Draw";
    };

    //Draw bullshit and continue to play i guess
    return "";
};

void winingCombinationsCreation(int firstFieldKey, 
                                int secondFieldKey, 
                                int thirdFieldKey)
{
    // firstFieldKey is also the key by which 
    // i figure out two which outer vector key it should belong
    vector<int> winingCombination;
    winingCombination.push_back(firstFieldKey);
    winingCombination.push_back(secondFieldKey);
    winingCombination.push_back(thirdFieldKey);

    GLOBAL_winningCombinations[firstFieldKey].push_back(winingCombination);

    return;
};

int possibleModeLevel(const vector<int> &winingCombination, 
                    string boardData, 
                    int checkSpaceKey)
{
    for (int placeToCheck : winingCombination)
    {
        if(placeToCheck == 4 && boardData[placeToCheck] == ' ')
        {

            checkSpaceKey = placeToCheck;
            break;

        } else if(checkSpaceKey != 4 &&   
            (placeToCheck == 0 || placeToCheck == 2 ||
            placeToCheck == 8 || placeToCheck == 6) && 
            boardData[placeToCheck] == ' ')
        {

            checkSpaceKey = placeToCheck;

        } else if(checkSpaceKey == 100 && 
            boardData[placeToCheck] == ' ')
        {

            checkSpaceKey = placeToCheck; 

        };   
    };

    return checkSpaceKey;
};

vector<string> readingParameterFile()
{   
    ifstream parameterFile;
    parameterFile.open("C:\\Users\\sm\\Desktop\\laikiniaIskelti\\truktUzVadziuIrVelIsPradziu\\games\\ticTacToe\\parameters.txt");
    vector<string> parameters;
    string parameter;

    while(std::getline(parameterFile, parameter))
    {
        parameters.push_back(parameter);
    };
    
    //https://stackoverflow.com/questions/55977686/how-to-read-text-file-lines-into-vectors/55977797
    parameterFile.close();

    return parameters;
    //file()

    //std::ofstream parameterFile;
    //std::ofstream file; 
    //file.open("C:\\Users\\sm\\Desktop\\laikiniaIskelti\\truktUzVadziuIrVelIsPradziu\\games\\ticTacToe\\parameters.txt", ios::out); 
};

void writingParameterFile(ParametersPlace parametersKey,
                          vector<string> &parameters,
                          string changeValue)
{
    parameters[parametersKey] = changeValue;
    string filePath = "C:\\Users\\sm\\Desktop\\laikiniaIskelti\\truktUzVadziuIrVelIsPradziu\\games\\ticTacToe\\parameters.txt";
    std::ofstream saveFile ("C:\\Users\\sm\\Desktop\\laikiniaIskelti\\truktUzVadziuIrVelIsPradziu\\games\\ticTacToe\\parameters.txt", std::ios::out | std::ios::trunc);
    std::ostream_iterator<std::string> output_iterator(saveFile, "\n");
    std::copy(parameters.begin(), parameters.end(), output_iterator);
    saveFile.close();

    return;
};

vector<string> readingStatsFile()
{
    ifstream statFile;
    statFile.open("C:\\Users\\sm\\Desktop\\laikiniaIskelti\\truktUzVadziuIrVelIsPradziu\\games\\ticTacToe\\stats.txt");
    vector<string> stats;
    string stat;

    while(std::getline(statFile, stat))
    {
        stats.push_back(stat);
    };
    
    statFile.close();

    return stats;
};

void writingToStatsFile(string gameResult,
                        string difficulty)
{
    vector<string> stats = readingStatsFile();
    /*
    for(string stat : stats)
    {
        std::cout << stat << std::endl;
    };
    */
    string filePath = "C:\\Users\\sm\\Desktop\\laikiniaIskelti\\truktUzVadziuIrVelIsPradziu\\games\\ticTacToe\\stats.txt";
    std::ofstream statsFile (filePath, std::ios::out | std::ios::trunc);
    int statCount;
    StatsPlace statsKey;

    if(difficulty == "Impossible")
    {

        if(gameResult == "Win")
        {
            statCount = std::stoi(stats[FirstDifficultyWins]);
            statCount++;
            stats[FirstDifficultyWins] = std::to_string(statCount);

        } else if(gameResult == "Loose")
        {
            statCount = std::stoi(stats[FirstDifficultyLosses]);
            statCount++;
            stats[FirstDifficultyLosses] = std::to_string(statCount);

        }else if(gameResult == "Draw")
        {
            statCount = std::stoi(stats[FirstDifficultyDraw]);
            statCount++;
            stats[FirstDifficultyDraw] = std::to_string(statCount);
        };

    }else
    {
        if(gameResult == "Win")
        {
            statCount = std::stoi(stats[SecondDifficultyWins]);
            statCount++;
            stats[SecondDifficultyWins] = std::to_string(statCount);

        } else if(gameResult == "Loose")
        {
            statCount = std::stoi(stats[SecondDifficultyLosses]);
            statCount++;
            stats[SecondDifficultyLosses] = std::to_string(statCount);

        }else if(gameResult == "Draw")
        {
            statCount = std::stoi(stats[SecondDifficultyDraw]);
            statCount++;
            stats[SecondDifficultyDraw] = std::to_string(statCount);
        };
    };

    std::ostream_iterator<std::string> output_iterator(statsFile, "\n");
    std::copy(stats.begin(), stats.end(), output_iterator);
    statsFile.close();

    return;
};

string writingParameterMenu(string parameterNumber,
                            vector<string> &parameters)
{   

    string feedbackMessage;
    string savedLine;
    ParametersPlace key;

    clearScreen();

    if(parameterNumber == "1")
    {
        key = Difficulty;        
        if(parameters[key] == "Possible")
        {

            writingParameterFile(key,
                                 parameters,
                                 "Impossible");
            /*
            //parameters[difficulty] = "Impossible";
            //"Impossible
            //std::ofstream saveFile ("C:\\Users\\sm\\Desktop\\laikiniaIskelti\\truktUzVadziuIrVelIsPradziu\\games\\ticTacToe\\parameters.txt", std::ios::out | std::ios::trunc);
            //std::ostream_iterator<std::string> output_iterator(saveFile, "\n");
            //std::copy(parameters.begin(), parameters.end(), output_iterator);
            //saveFile.close();
            */
            /*
            std::ostream_iterator<std::string> output_iterator(parameterFile, "\n");
            std::copy(parameters.begin(), parameters.end(), output_iterator);
            parameterFile.close();
            */
                   


            return "Your difficulty was change to Impossible";
        };

        writingParameterFile(key,
                            parameters,
                            "Possible");

        return "Your difficulty was change to Possible";
        // change dificulty
    } else if(parameterNumber == "2")
    {
        key = MoveOrder;
        
        if(parameters[key] == "First")
        {
            //"Second"
            writingParameterFile(key,
                                parameters,
                                "Second");

            return "You will start second";
        };

        writingParameterFile(key,
                            parameters,
                            "First");

        return "You will start first";
        // change your move order
    } else if(parameterNumber == "3")
    {
        key = Mark;
        
        if(parameters[key] == "X")
        {
            //"O"
            writingParameterFile(key,
                                parameters,
                                "O");

            return "Your mark is O";
        };

        writingParameterFile(key,
                            parameters,
                           "X");

        return "Your mark is X";
        //"X"
    };

    return "There is no such command. Choose an existing command";
};


void statsFileExistence()
{
    std::ifstream statsFile;
    statsFile.open("C:\\Users\\sm\\Desktop\\laikiniaIskelti\\truktUzVadziuIrVelIsPradziu\\games\\ticTacToe\\stats.txt", ios::out);
    vector<string> stats;

    if(!statsFile)
    {
        std::fstream statsFile;
        statsFile.open("C:\\Users\\sm\\Desktop\\laikiniaIskelti\\truktUzVadziuIrVelIsPradziu\\games\\ticTacToe\\stats.txt", ios::out);

        stats.push_back("Possible");
        stats.push_back("Win: ");
        stats.push_back("0");
        stats.push_back("Losses: ");
        stats.push_back("0");
        stats.push_back("Draw: ");
        stats.push_back("0");
        stats.push_back("Impossible");
        stats.push_back("Win: ");
        stats.push_back("0");
        stats.push_back("Losses: ");
        stats.push_back("0");
        stats.push_back("Draw: ");
        stats.push_back("0");

        std::ostream_iterator<std::string> output_iterator(statsFile, "\n");
        std::copy(stats.begin(), stats.end(), output_iterator);
        statsFile.close();

        return;
    };

    return;
};

void saveFileExistence()
{    
    std::ifstream parameterFile;
    parameterFile.open("C:\\Users\\sm\\Desktop\\laikiniaIskelti\\truktUzVadziuIrVelIsPradziu\\games\\ticTacToe\\parameters.txt", ios::out);
    vector<string> parameters;

    if(!parameterFile)
    {
        std::fstream parameterFile;
        parameterFile.open("C:\\Users\\sm\\Desktop\\laikiniaIskelti\\truktUzVadziuIrVelIsPradziu\\games\\ticTacToe\\parameters.txt", ios::out);
        
        parameters.push_back("Impossible"); // Dificulty
        parameters.push_back("First"); // Who starts first and who second
        parameters.push_back("O"); // Mark O or X

        std::ostream_iterator<std::string> output_iterator(parameterFile, "\n");
        std::copy(parameters.begin(), parameters.end(), output_iterator);
        parameterFile.close();

        return;
    };

    return;
};

string endGameMessage(string endGameMessage, string& boardData)
{
    string playersChoise;
    char firstLoopControler = 'a';

    do 
    {
        clearScreen();
        std::cout << std::endl;
        std::cout << boardDataVisualRepresantation(boardData);
        std::cout << std::endl;
        std::cout << endGameMessage << std::endl;
        std::cout << std::endl;
        std::cout << "To return to menu press 0";
        std::cout << std::endl;
        std::cout << "To play again press 1";
        std::cout << std::endl;
        //std::cin >> playersChoise;

        if(playersChoise == "0")
        {
            clearScreen();

            return "0";
        } else if(playersChoise == "1")
        {
            clearScreen();

            return "1";
        } else if(firstLoopControler == 'b')
        {
            std::cout << "There is no \"" << playersChoise 
            << "\" comand, please try to retype the comand";
        };

        firstLoopControler = 'b';
        std::cout << std::endl;
        std::cin >> playersChoise;

    } while(playersChoise != "0" || playersChoise != "1");

    return "0";
};

void statsPage()
{
    vector<string> stats = readingStatsFile();
    std::cout << std::endl;
    string playersChoise;
    char firstLoopControler = 'a';

    while(playersChoise != "0")
    {
        clearScreen();
        std::cout << "Write 0 to return to previous menu" << std::endl;
        std::cout << std::endl;
        std::cout << stats[FirstDifficulty] << " diffiuculty: " << std::endl;
        std::cout << "Wins: " << stats[FirstDifficultyWins] << std::endl;
        std::cout << "Losses: " << stats[FirstDifficultyLosses] << std::endl;
        std::cout << "Draws: " << stats[FirstDifficultyDraw] << std::endl;
        std::cout << std::endl;
        std::cout << stats[SecondDifficulty] << " diffiuculty: " << std::endl;
        std::cout << "Wins: " << stats[SecondDifficultyWins] << std::endl;
        std::cout << "Losses: " << stats[SecondDifficultyLosses] << std::endl;
        std::cout << "Draws: " << stats[SecondDifficultyDraw] << std::endl;

        if(playersChoise != "0" && firstLoopControler == 'b')
        {
            std::cout << std::endl;
            std::cout << "There is no \"" << playersChoise 
            << "\" comand, please try to retype the comand";  
        };

        firstLoopControler = 'b';
        std::cout << std::endl;
        std::cin >> playersChoise;
    };

    return;     
};

int impossibleDifficutlyComputer(string &boardData,
                                string &boardDataWithSpaces,
                                string &boardView,     
                                char playersMark,
                                char computersMark)
{
    std::cout << std::endl;
    std::cout << "Please wait for opponents move";
    std::cout << std::endl;
    //Should get string with data

    //I should make GLOBAL_winningCombinations
    //vector<vector<int>> and than push 0 1 2
    //should change every now exisitng number -1
    // 0 1 2 from 123
    // and to make checking for within for loop
    //for start at least 
    // should start reading algorithms book again 
    // from changed GLOBAL_winningCombinations take 
    int boardSpacesAmmount = 9;
    int playersMarksAmountInRow;
    int pcMarksAmountInRow;


    // below variables should be given into the function
    // depending if the players go first or second
    // or i can hardCode the value and the player could always be X
    int firstCheckSpaceKey = 100;
    int secondCheckSpaceKey = 100;
    int thirdCheckSpaceKey = 100;
    int forthCheckSpaceKey = 100;
    
    //vector<int>* pcWinningCombinationPointer;

    for (int i = 0; i < boardSpacesAmmount; i++)
    {

        for (vector<int> winingCombination : GLOBAL_winningCombinations[i])
        {
            
            playersMarksAmountInRow = 0;
            pcMarksAmountInRow = 0;

            for(int placeToCheck : winingCombination)
            {
                if (boardData[placeToCheck] == playersMark)
                {
                    playersMarksAmountInRow++;

                } else if (boardData[placeToCheck] == computersMark)
                {
                    pcMarksAmountInRow++;
                };
            };

            //first check all plausible pc wins posibilities
            //than check oponents pausible wins 
            //look for posibilities to win:
            //1. if it is posibble to have three in a row 
            //2. if there is already mark put pc simbol already

            if (pcMarksAmountInRow == 2 && playersMarksAmountInRow == 0)
            {


                for (int placeToCheck : winingCombination)
                {
                    //sita nk neirasineti i variable nes jei yra tai pabaigt tikrinima
                    // bet tiktai neirasineti jei playersMarksAmountInRow == 3
                    // tikrinu po player  

                    if (boardData[placeToCheck] != computersMark)
                    {
                        boardData[placeToCheck] = computersMark;
                        boardDataWithSpaces[placeToCheck] = computersMark;
                        boardView[placeToCheck] = computersMark;
                        
                        return placeToCheck;
                        // print loosing message for the player
                        // add to statistics if i make them
                    };
                };

                // Only should be possible if playersMarksAmountInRow is = 0
                // Put there and win

            } else if (playersMarksAmountInRow == 2 && pcMarksAmountInRow == 0)
            {

                // tureciau irasyti i vector<int> key arba
                // memory adress vector
                //teoriskai tai uztenka int variable tiktai nes jei yra tai nereikia nk daugiau tikrint


                // Sita dalis turetu eit po for each ir tada patikrint 
                for (int placeToCheck : winingCombination)
                {
                    if (boardData[placeToCheck] != playersMark)
                    {
                        firstCheckSpaceKey = placeToCheck;
                        //boardData[placeToCheck] = computersMark;
                        // print loosing message for the player
                        // add to statistics if i make them
                        //return;
                    };
                };
                // Save to a variable which is a pointer and points 
                // To vector value 
                // Let's say playersWinningMove
            }
            else if (pcMarksAmountInRow == 1 && playersMarksAmountInRow == 0)
            {
                
                secondCheckSpaceKey = possibleModeLevel(winingCombination, 
                                boardData,
                                secondCheckSpaceKey);

                // Only should be possible if playersMarksAmountInRow is = 0
                // Save to a pointer vector
                // Let's say vectorOFOnes
            }
            else if (pcMarksAmountInRow == 0 && playersMarksAmountInRow == 0)
            {
                thirdCheckSpaceKey = possibleModeLevel(winingCombination, 
                                boardData,
                                thirdCheckSpaceKey);
                // Save to another vector of pointers
                // What the fuck i am doing with my life
                // Lets say vectorsOfTwo
            } else 
            {
                forthCheckSpaceKey = possibleModeLevel(winingCombination, 
                                boardData,
                                forthCheckSpaceKey);
            };
            //check if there is playersWinningMove
            // put mark acording 
            // check vectorOFOnes put there
            // put mark acording
            // check vectorOfTwo put there
            // put mark acording
        };
    };
    
    if(firstCheckSpaceKey != 100)
    {
        boardData[firstCheckSpaceKey] = computersMark;
        boardDataWithSpaces[firstCheckSpaceKey] = computersMark;
        boardView[firstCheckSpaceKey] = computersMark;

        return firstCheckSpaceKey;

    } else if (secondCheckSpaceKey != 100)
    {
        boardData[secondCheckSpaceKey] = computersMark;
        boardDataWithSpaces[secondCheckSpaceKey] = computersMark;
        boardView[secondCheckSpaceKey] = computersMark;

        return secondCheckSpaceKey;

    }  else if (thirdCheckSpaceKey != 100)
    {
        boardData[thirdCheckSpaceKey] = computersMark;
        boardDataWithSpaces[thirdCheckSpaceKey] = computersMark;
        boardView[thirdCheckSpaceKey] = computersMark;

        return thirdCheckSpaceKey;

    } else {
        boardData[forthCheckSpaceKey] = computersMark;
        boardDataWithSpaces[forthCheckSpaceKey] = computersMark;
        boardView[forthCheckSpaceKey] = computersMark;
        
        return forthCheckSpaceKey;
    };

    std::cout << "Well this is unexpected something went wrong in computersTurn" << std::endl;
};

int possibleDifficutlyComputer(string &boardData,
                                string &boardDataWithSpaces,
                                string &boardView,     
                                char playersMark,
                                char computersMark)
{
    vector<int> freeBoardSpaces;
    int freeBoardKey;
    int boardSpacesAmount = 9;

    std::cout << std::endl;
    std::cout << "Please wait for opponents move";
    std::cout << std::endl;

    for(int i = 0; i < boardSpacesAmount; i++)
    {
        if(boardData[i] == ' ')
        {
            freeBoardSpaces.push_back(i);
        };
    };

    std::srand(time(NULL));
    int randomBoardKey = rand() % freeBoardSpaces.size();
    freeBoardKey = freeBoardSpaces[randomBoardKey];

    boardData[freeBoardKey] = computersMark;
    boardDataWithSpaces[freeBoardKey] = computersMark;
    boardView[freeBoardKey] = computersMark;
                        
    return randomBoardKey;
    std::cout << "Well this is unexpected something went wrong in computersTurn" << std::endl;
};

string gameOneVsOneLoop(vector<string> &parameters)
{
    char firstPlayersMark = parameters[Mark][0];
    char secondPlayersMark;
    int boardSpacesAmmount = 9;
    bool boardHelpStatus = false;
    string boardView;
    ParametersPlace parameterKey = Mark;
    char playersMark = firstPlayersMark;
    string playersInput;
    string boardSpaces = "123456789";
    string boardData = "         ";
    string boardDataWithSpaces = "123456789";
    boardView = boardDataWithSpaces;
    string playersChoise;



    if(firstPlayersMark == 'X')
    {
        secondPlayersMark = 'O';
    } else {
        secondPlayersMark = 'X';
    };

 vector<string> choosableBoardSpaces;

    choosableBoardSpaces.push_back("1");
    choosableBoardSpaces.push_back("2");
    choosableBoardSpaces.push_back("3");
    choosableBoardSpaces.push_back("4");
    choosableBoardSpaces.push_back("5");
    choosableBoardSpaces.push_back("6");
    choosableBoardSpaces.push_back("7");
    choosableBoardSpaces.push_back("8");
    choosableBoardSpaces.push_back("9");

 
    clearScreen();
    gameLoopBoardOptions(boardHelpStatus, boardView);

    while (1 != 0)
    {
        //clearScreen();
        //gameLoopBoardOptions(boardHelpStatus, boardView);
        std::cin >> playersChoise;
        
        if (playersChoise == "0")
        {
            clearScreen();
            return "0";
        } else if (playersChoise == "h") {

            clearScreen();
            boardHelpStatus = !boardHelpStatus;
            gameLoopBoardOptions(boardHelpStatus, boardView);

            continue;
        } else if (playersChoise == "m")
        {
            clearScreen();
            std::cout << "The board was change to show places and marks" << std::endl;
            boardView = boardDataWithSpaces;
            gameLoopBoardOptions(boardHelpStatus, boardView);

            continue;
        } else if (playersChoise == "e")
        {
            clearScreen();
            std::cout << "The board was change to show only marks" << std::endl;
            boardView = boardData;
            gameLoopBoardOptions(boardHelpStatus, boardView);

            continue;

        } else if (playersChoise == "p")
        {
            clearScreen();
            std::cout << "The board was change to show only places" << std::endl;
            boardView = boardSpaces;
            gameLoopBoardOptions(boardHelpStatus, boardView);

            continue;
        };

        for (int i = 0; i < boardSpacesAmmount; i++)
        {
            if (choosableBoardSpaces[i] == playersChoise) {

                if (boardData[i] != ' ')
                {
                    clearScreen();
                    gameLoopBoardOptions(boardHelpStatus, boardView);
                    std::cout << "Choose a FREE space" << std::endl;

                    break;
                    //Return to guess again
                };

                boardData[i] = playersMark;
                boardDataWithSpaces[i] = playersMark;
                boardView[i] = playersMark;

                clearScreen();
                gameLoopBoardOptions(boardHelpStatus, boardView);

                //tikrinti ar yra laimintis variantas
                string gameEndStatus = gameEndConditions(
                                            i,
                                            boardData,
                                            firstPlayersMark,
                                            secondPlayersMark);

                if(gameEndStatus == "Win") 
                {
                    return endGameMessage("First players wins", boardData);

                }else if(gameEndStatus == "Draw")
                {
                    return endGameMessage("Draw", boardData);

                }else if(gameEndStatus == "Loose")
                {
                    return endGameMessage("Second players wins", boardData);
                };

                if(playersMark == firstPlayersMark)
                {
                    playersMark = secondPlayersMark;
                }else {
                    playersMark = firstPlayersMark;
                };    
                    
                break;
            };


            clearScreen();
            gameLoopBoardOptions(boardHelpStatus, boardView);
            std::cout << "Choose an existing space" << std::endl;
        };
    };

    return "0";
};
