#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

int RandomNumber(int from, int to)
{
    int random = rand() % (to - from + 1) + from;

    return random;
};

int ReadRaoundNumber(string messages)
{
    int number = 0;

    do
    {
        cout << messages << endl;
        cin >> number;

    } while (number < 0 || number > 10);

    return number;
};

string RoundResult(int playerChoice, int computerChoice, int &ComputerWins, int &PlayerWins)
{
    string result;
    // draw
    if (playerChoice == 1 && computerChoice == 1 || playerChoice == 2 && computerChoice == 2 || playerChoice == 3 && computerChoice == 3)
    {
        result = "no winner";
    }
    else if (playerChoice == 2 && computerChoice == 1 || playerChoice == 3 && computerChoice == 2 || playerChoice == 1 && computerChoice == 3)
    {
        result = "player win";
        PlayerWins++;
    }
    else
    {
        result = "computer win";
        ComputerWins++;
    }
    return result;
}

void PrintRoundResult(int RoundNumber, int PlayerChoice, int ComputerChoice, string Result)
{
    cout << "\n\t\t\t\t----------------- round "
         << "[" << RoundNumber << "]"
         << "-----------------\t\t\t\t";

    cout << "\n\t\t\t\tPlayer Choice: " << PlayerChoice;
    cout << "\n\t\t\t\tComputer Choice: " << ComputerChoice;
    cout << "\n\t\t\t\tRound winner: " << Result;

    cout << "\n\t\t\t\t----------------------------------\t\t\t\t";
}

string FinalReult(int ComputerWinsTimes, int PlayerWinsTimes)
{
    string FinalResult;
    if (ComputerWinsTimes > PlayerWinsTimes)
    {
        FinalResult = "Computer Wins";
    }
    else if (ComputerWinsTimes == PlayerWinsTimes)
    {
        FinalResult = "No Winner";
    }
    else
    {
        FinalResult = "Player Wins";
    }
    return FinalResult;
}

void PrintFinalResult(int ComputerWinsTimes, int PlayerWinsTimes, int GameRounds)
{
    cout << "\n\t\t\t\t____________________________________________\n";

    cout << "\n\t\t\t\t\t\t\t++++ G A M E O V E R ++++ "
         << "\t\t\t\t";
    cout << "\n\t\t\t\t____________________________________________\n";

    cout << "\n\t\t\t\tGame Rounds       : " << GameRounds << endl;
    cout << "\n\t\t\t\tPlayer win times  : " << PlayerWinsTimes << endl;
    cout << "\n\t\t\t\tComputer win times: " << ComputerWinsTimes << endl;
    cout << "\n\t\t\t\tFinalResult       : " << FinalReult(ComputerWinsTimes, PlayerWinsTimes) << endl;
}

void AskUserTochoice()
{
    // take the number from user and save it in global virable
    int RoundNumber = ReadRaoundNumber("how many round 1 to 10  ");

    // take the user to choise
    int PlayerChoice = 0;
    int CoumputerChoice = 0;

    int PlayerWins = 0;
    int ComputerWins = 0;

    for (int i = 0; i < RoundNumber; i++)
    {
        cout << "\n\t\t\t\tRound"
             << "[" << i + 1 << "]"
             << "begins";

        // player choice
        cout << "\n\t\t\t\tyour choice : [1]:stone ,[2]:paper ,[3]:scissors ?";
        cin >> PlayerChoice;

        // computer choice randomlay
        CoumputerChoice = RandomNumber(1, 3);

        // print the Round result
        PrintRoundResult(i + 1, PlayerChoice, CoumputerChoice, RoundResult(PlayerChoice, CoumputerChoice, ComputerWins, PlayerWins));
    }

    // print all rounds result
    PrintFinalResult(ComputerWins, PlayerWins, RoundNumber);
}

// ask the user is he want play again
bool PlayAgain()
{
    char PlayAgain;
    cout << "Do Want To Play Again ? y/n ? ";
    cin >> PlayAgain;

    // errer: the function don't declear in this scop ;
    if (PlayAgain == 'y')
    {
        return true;
    }
    else
    {
        return false;
    }
}

void startGame()
{

    bool playAgainCheck = false;
    do
    {

        AskUserTochoice();

        playAgainCheck = PlayAgain();

    } while (playAgainCheck);
};
int main()
{

    // Seeds the random number generator in C++, called only once
    srand((unsigned)time(NULL));

    startGame();

    return 0;
};