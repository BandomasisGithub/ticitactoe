#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <ctype.h> 
#include <stdio.h> 

using namespace std;
// Tic Tac Toe

// Main menu again(play, help, exit)
// Welcoming message
// Choosing does the player goes first(and ability for random decision)
// Board
// PlayerInput
// Pc input
// End Game state(win loose)
// Togle boards(only space numbers, space numbers with made moves, moves without space numbers)

void mainMenu();
void help();
void clearScreen();
int gameLoop(); 
string boardDataVisualRepresantation(const string &boardData);
string& dataRowConversionToBoard(string &board, const string &boardData, int rowsFirstPlace);
void gameLoopBoardOptions(bool const &boardHelpStatus, string &boardData);



vector<string> GLOBAL_winningCombinations;
vector<string> GLOBAL_boardPlaces;
vector<int> GLOBAL_boardSpaceCordinates;
vector<string> GLOBAL_emptyBoard;


int main() 
{

    //BoardPlaces

    // To change board space (numbers) into marked places
    // The push order matters it is reletated to bardSpaceCordinateKey
    // The function later is using with % operator
    //All winning lines combinations 

    GLOBAL_winningCombinations.push_back("123");
    GLOBAL_winningCombinations.push_back("456");
    GLOBAL_winningCombinations.push_back("789");
    GLOBAL_winningCombinations.push_back("147");
    GLOBAL_winningCombinations.push_back("258");
    GLOBAL_winningCombinations.push_back("369");
    GLOBAL_winningCombinations.push_back("159");
    GLOBAL_winningCombinations.push_back("357");

    mainMenu();

    return 0;
};

void mainMenu()
{
    string playersChoise;
    int firstInfiniteLoopStatement = 0;
    int secondInfiniteLoopStatement = 1;

    do {
        //clearScreen();
        std::cout << "Welcome Tic Tac Toe" << std::endl;
        std::cout << std::endl;
        std::cout << "Press 1 to play the main game" << std::endl;
        std::cout << "Press 2 to see the rules of the game" << std::endl;
        std::cout << "Press 3 to exit" << std::endl;
        std::cin >> playersChoise;

        if(playersChoise == "1")
        {
            int menuFromGameLoop = 1;
            int gameExitCode = gameLoop();

            if(gameExitCode != menuFromGameLoop) {

                return;
            };
        } else if(playersChoise == "2") {
            clearScreen();
            help();
            
        } else if(playersChoise == "3") {

            return;
        } else {
            std::cout << "There is no such comand try retype the comand" << std::endl;
        };
    } while(firstInfiniteLoopStatement != secondInfiniteLoopStatement);
    
    return;
};

int gameLoop()
{   
    // using vector rather than a string because when you take a string[i]
    // it becomes a char which complicates check for me latter

    vector<string> choosableBoardSpaces;
    int boardSpacesAmmount = 9;
    bool boardHelpStatus = false;
    string boardView;


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
    string exitMainMenuValue = "1";

    //string boardData = "---------";
    string boardSpaces = "123456789";
    string boardData = "         ";
    string boardDataWithSpaces = "123456789";
    boardView = boardDataWithSpaces;
    string playersChoise;
    clearScreen();
    std::cout << "To go back to previous menu press 1" << std::endl;
    std::cout << std::endl;
    std::cout << "Type \"first\" if you want to go first or type \"second\" if you want to go second" << std::endl;
    std::cin >> playersInput;

    int playersGuessLength = playersInput.length();
    char playersMark = 'X';
    char opponentMark = 'O';
    // playersChoise
    // check if a place exists
    clearScreen();
    std::cout << "Write 0 to exit the game" << std::endl;
    std::cout << "See more board options write h" << std::endl;
    std::cout << "Mark a free space by typing its number" << std::endl;
    std::cout << std::endl;
    std::cout << "The board view" << std::endl;
    std::cout << std::endl;
    std::cout << boardDataVisualRepresantation(boardView);
    std::cout << std::endl;

        // this should be one of jumping points
    while(1 != 0)
    {

        std::cin >> playersChoise;

        if(playersChoise == "0") 
        {
            clearScreen();
            return 1;
        } else if(playersChoise == "h") {   

            clearScreen();
            boardHelpStatus = !boardHelpStatus;
            gameLoopBoardOptions(boardHelpStatus, boardView);
            
            
 
        } else if(playersChoise == "m") 
        {
            clearScreen();
            std::cout << "The board was change to show places and marks" << std::endl;
            boardView = boardDataWithSpaces;
            gameLoopBoardOptions(boardHelpStatus, boardView);

            continue;

        } else if(playersChoise == "e") 
        {
            clearScreen();
            std::cout << "The board was change to show only marks" << std::endl;
            boardView = boardData; 
            gameLoopBoardOptions(boardHelpStatus, boardView);

            continue;

        } else if(playersChoise == "p")
        {
            clearScreen();
            std::cout << "The board was change to show only places" << std::endl;
            boardView = boardSpaces;
            gameLoopBoardOptions(boardHelpStatus, boardView);

            continue;
        };

        for(int i = 0; i < boardSpacesAmmount; i++) 
        {
            if(choosableBoardSpaces[i] == playersChoise) {

                if(boardData[i] == 'X' || boardData[i] == 'O') 
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
                
                break;
            }; 

            clearScreen();
            gameLoopBoardOptions(boardHelpStatus, boardView);
            std::cout << "Choose an existing space" << std::endl; 
        };
    };
    //should reloop to the start with changed board




    /*
    std::cout << boardDataVisualRepresantation(boardData);
    std::cout << std::endl;
    std::cout << boardDataVisualRepresantation(boardDataWithSpaces);
    std::cout << std::endl;
    std::cout << boardDataVisualRepresantation(boardS paces);
    */
    
    //should reloop to let a player input the required place of the board 
    return 1;


        
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



    std::cout << "Choose an existing space" << std::endl;
    // return back to players choise







    return 1;
    // Below chek for later
    /*
    if(playersInput == exitMainMenuValue) 
    {
        return 1;
    } else if(playersInput == "first") 
    {
        
        // get the board view
        // choose a number
        // chekc if its legal
        // mark if legal warning if not
        // give pc a turn 
    } else if(playersInput == "second") 
    {
        //pc checks only empty space
        //if check empty space doesn't make the win for other player
        // check if it is possible to win with that space
        //Values of spaces
        // empty/ oponent doesnt win/ possible win outcomes
        //return made move on the board
    };
    */

    return 0;
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

    std::cout << "To go back to previous menu press 1" << std::endl;

    previousMenu:

    std::cin >> playersInput;
    if(playersInput == "1")
    {
        
        return;
    } else 
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

    hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
    if (hStdOut == INVALID_HANDLE_VALUE) return;

    // Get the number of cells in the current buffer 
    if (!GetConsoleScreenBufferInfo( hStdOut, &csbi )) return;
    cellCount = csbi.dwSize.X *csbi.dwSize.Y;

    // Fill the entire buffer with spaces 
    if (!FillConsoleOutputCharacter(
        hStdOut,
        (TCHAR) ' ',
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
    SetConsoleCursorPosition( hStdOut, homeCoords );
};

string& dataRowConversionToBoard(string &board,const string &boardData, int rowsFirstPlace)
{
    int nextPlace = 1;

    board = board + " " 
        + boardData[rowsFirstPlace] + " | " 
        + boardData[rowsFirstPlace + nextPlace] + " | "  
        + boardData[rowsFirstPlace + nextPlace + nextPlace] + " ";
    board += '\n'; 

    return board; 
};

string boardDataVisualRepresantation(const string &boardData)
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

void gameLoopBoardOptions(bool const &boardHelpStatus, string &boardData)
{
    if(boardHelpStatus == false)
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

void computersTurn( string boardData,
                    int boardSpacesAmmount,
                    vector<vector<int>> winingCombinations)
{
    //Should get string with data

    //I should make GLOBAL_winningCombinations
    //vector<vector<int>> and than push 0 1 2
    //should change every now exisitng number -1
    // 0 1 2 from 123
    // and to make checking for within for loop
    //for start at least 
    // should start reading algorithms book again 
    // from changed GLOBAL_winningCombinations take 

    int playersMarksAmountInRow;
    int pcMarksAmountInRow;

    for(int i = 0; i < boardSpacesAmmount; i++)
    {
        if(boardData[i] == 'X')
        {
            playersMarksAmountInRow = 0;
            pcMarksAmountInRow = 0;
            for(vector<int> winingCombination : winingCombinations[i])
            {
                for(int existingMarkKey : winingCombination)
                {
                    if(boardData[existingMarkKey] == 'X')
                    {
                        playersMarksAmountInRow++;
                    } else if(boardData[existingMarkKey] == 'O')
                    {
                        pcMarksAmountInRow++;
                    };
                };

                //first check all plausible pc wins posibilities
                //than check oponents pausible wins 
                //look for posibilities to win:
                //1. if it is posibble to have three in a row 
                //2. if there is already mark put pc simbol already



                if(playersMarksAmountInRow == 3)
                {
                    //Print the message of victory for the player
                } else if(pcMarksAmountInRow == 2) 
                {
                    //Only should be possible if playersMarksAmountInRow is = 0
                    //Put there and win
                } else if (playersMarksAmountInRow == 2)
                {
                    // save to a variable which is a pointer and points 
                    // to vector value 
                    //lets say playersWinningMove
                } else if(pcMarksAmountInRow == 1) 
                {
                    //Only should be possible if playersMarksAmountInRow is = 0
                    //save to a pointer vector
                    // lets say vectorOFOnes
                } else if(pcMarksAmountInRow == 0)
                {
                    //save to another vector of pointers
                    //what the fuck i am doing with my life
                    //lets say vectorsOfTwo
                };

                //check if there is playersWinningMove
                // put mark acording 
                // check vectorOFOnes put there
                // put mark acording
                // check vectorOfTwo put there
                // put mark acording


            };
            

        };
    };
    


    //Should check if there is space if put pc wins
    //(if there is put there)
    //Should check if there is space if put the player wins
    //(if there is put there)
    //Check if there is a possibility for a straight 3
    //(if there is put there)
    //If none of the obove is avaivble put to the firs possible place



}

