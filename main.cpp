#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <windows.h>
#include <ctype.h> 
#include <stdio.h> 

using namespace std;
// Tic Tac Toe


// MAYBE I SHOULD MAKE STATS TRACKING HOW MANY TIME LOOSE AND WIN
// CREATE A FILE WHERE TO SAVE NECESERY DATA (TXT FILE I WOULD GUESSAQ)
// MAYBE A POSIBILITY TO PLAY AGAINST ANOTHER PLAYER
// possible imposible dificulty


void mainMenu();
void help();
void clearScreen();
int gameLoop();
void parametersText();

string boardDataVisualRepresantation(const string& boardData);

string& dataRowConversionToBoard(string& board, 
                                const string& boardData, 
                                int rowsFirstPlace);

void gameLoopBoardOptions(bool const& boardHelpStatus,
                        string& boardData);

bool lastSquareWinningCheck(int winingCombinationKey,
                            const string& boardData,
                            char playersMark);

void winingCombinationsCreation(int firstFieldKey, 
                                int secondFieldKey, 
                                int thirdFieldKey);

void computersTurn(string &boardData);

int possibleModeLevel(const vector<int> &winingCombination, 
                    string boardData, 
                    int checkSpaceKey);

//vektoriu vektoriu vektorius reiktu pasiziuret alternatyva sitam 
//negeneliam sumanymui nes gale gaunas kaip is simpsonu
// masinu masinu masinos
vector<vector<vector<int>>> GLOBAL_winningCombinations(9);
vector<string> GLOBAL_boardPlaces;
vector<int> GLOBAL_boardSpaceCordinates;
vector<string> GLOBAL_emptyBoard;


int main()
{

    //THIS FUNCTION CHANGES GLOBAL STATE BE AWARE

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

    do {
        //clearScreen();
        std::cout << "Welcome Tic Tac Toe" << std::endl;
        std::cout << std::endl;
        std::cout << "Press 1 to play the main game" << std::endl;
        std::cout << "Press 2 to see the rules of the game" << std::endl;
        std::cout << "Press 3 to see game parameters" << std::endl;
        std::cout << "Press 4 to see your stats" << std::endl;
        std::cout << "Press 5 to exit" << std::endl;
        std::cin >> playersChoise;

        if (playersChoise == "1")
        {
            int menuFromGameLoop = 1;
            int gameExitCode = gameLoop();

            if (gameExitCode != menuFromGameLoop) {

                return;
            };
        }
        else if (playersChoise == "2") {
            clearScreen();
            help();

        } 
        else if(playersChoise == "3")
        {
            clearScreen();
            void parametersText();

            string playersChoise;
            std::cin >> playersChoise;

            if(playersChoise == "0")
            {
                
                return;

            } else if(playersChoise == "1")
            {
                clearScreen();
                //1. Difficulty(Possible) Possible/Impossible

                std::ofstream parameterFile;
                parameterFile.open("parameters.txt");
                parameterFile << "Files can be tricky, but it is fun enough!";
                parameterFile.close();
                char data[100];
                parameterFile.open("parameters.txt");

                

                std::ifstream infile; 
                infile.open("parameters.txt"); 

                cout << "Reading from the file" << endl; 
                infile >> data;                 
                // write the data at the screen.
                cout << data << endl;

                // again read the data from the file and display it.
                infile >> data; 
                cout << data << endl;               
                // close the opened file.
                infile.close();




                while(1 != 0)
                {
                    
                    
                };

            } else if(playersChoise == "2")
            {
                clearScreen();
                //2. You start(First) First/Second

            } else if(playersChoise == "3")
            {
                clearScreen();
                //3. Your mark(X) X/O
            };

            //changingParameters();
            
            //to check status
        }else if(playersChoise == "4")
        {
            clearScreen();
            help();
            //
        }else if (playersChoise == "5") {

            return;
        }
        else {
            std::cout << "There is no such comand try retype the comand" << std::endl;
        };
    } while (firstInfiniteLoopStatement != secondInfiniteLoopStatement);

    return;
};

int gameLoop()
{

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
    while (1 != 0)
    {

        std::cin >> playersChoise;

        if (playersChoise == "0")
        {
            clearScreen();
            return 1;
        }
        else if (playersChoise == "h") {

            clearScreen();
            boardHelpStatus = !boardHelpStatus;
            gameLoopBoardOptions(boardHelpStatus, boardView);



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
                bool gameWinLooseStatus = lastSquareWinningCheck(
                                            i,
                                            boardData,
                                            playersMark);
                if(gameWinLooseStatus == true) 
                {
                    std::cout << "WIN BABYYYY";
                    // wining message and going back to the main menu
                }

                computersTurn(boardData);

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
    if (playersInput == "1")
    {

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
void computersTurn(string &boardData)
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
    int boardSpacesAmmount = 9;
    int playersMarksAmountInRow;
    int pcMarksAmountInRow;


    // below variables should be given into the function
    // depending if the players go first or second
    // or i can hardCode the value and the player could always be X
    char playersMark = 'X';
    char computersMark = 'O';
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
                        
                        return;
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
        
        return;
    } else if (secondCheckSpaceKey != 100)
    {
        boardData[secondCheckSpaceKey] = computersMark;
        
        return;       
    }  else if (thirdCheckSpaceKey != 100)
    {
        boardData[thirdCheckSpaceKey] = computersMark;
        
        return;       
    } else {
        boardData[forthCheckSpaceKey] = computersMark;

        return;
    };

    std::cout << "Well this is unexpected something went wrong in computersTurn" << std::endl;

    return;
};

bool lastSquareWinningCheck(int winingCombinationKey,
                            const string& boardData,
                            char playersMark)
{
    for(vector<int> winingCombination : GLOBAL_winningCombinations[winingCombinationKey])
    {
        int markAmountInRow = 0;

        for(int winingCombinationPlace : winingCombination)
        {
            if(boardData[winingCombinationPlace] == playersMark)
            { 
                markAmountInRow++;
                continue;
            }

            break;
        };

        if(markAmountInRow == 3)
        {

            return true;
        };
    };

    return false;
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

void parametersText()
{
    std::cout << "To go back to previous menu press 0" << std::endl;
    std::cout << "To change parameter write the asociated number with it:" << std::endl << std::endl;
    std::cout << "1. Difficulty(Possible) Possible/Impossible" << std::endl;
    std::cout << "2. You start(First) First/Second" << std::endl;
    std::cout << "3. Your mark(X) X/O" << std::endl;

    return;
};

void changingParameters()
{


    return;
};

void parameterFile()
{
    std::ofstream parameterFile;
    parameterFile.open("parameters.txt");
    parameterFile.close();

    return;
}

void saveFile()
{
    std::ofstream saveFile;
    saveFile.open("saves.txt");
    saveFile.close();

    return;
};
