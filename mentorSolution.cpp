#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;
// constant game data:
enum enGameChoice
{
    stone = 1,
    paper = 2,
    scissors = 3
};

enum enWinner
{
    player1 = 1,
    computer2 = 2,
    draw = 3
};

// changabe game data:
struct stRoundInfo
{
    short RoundNumber = 0;
    enGameChoice player1Choice;
    enGameChoice computer2Choice;
    enWinner RoundWinner;
    string WinnerName = "";
};

struct stGameResult
{
    short RoundsNumber;
    short Player1WinsTime;
    short Computer2WinsTime;
    short DrawTimes;
    enWinner GameWinner;
    string WinnerName = "";
};

// get random number in range:
int RandomNumber(int from, int to)
{
    int random = rand() % (to - from + 1) + from;

    return random;
};

// ask the user how many Round he want to play:
short ReadHowManyRounds()
{
    short RoundNumber = 0;

    do
    {
        cout << "Enter How Many Rount 1 To 10: " << endl;
        cin >> RoundNumber;

    } while (RoundNumber < 1 || RoundNumber > 10);

    return RoundNumber;
};

// clear the screen And return to the main color (black):
void RestScreen()
{
    // clear the screen
    system("cls");
    // return the color to black color:
    system("color 0F");
}

enGameChoice ReadPlayer1Choice()
{
    short Choice = 1;

    do
    {

        cout << "\nYour Choice: [1]:Stone, [2]:Paper, [3]:Scissors ? ";
        cin >> Choice;

    } while (Choice > 3 || Choice < 1);

    return (enGameChoice)Choice;
}

enGameChoice GetComputerChoice()
{
    return (enGameChoice)RandomNumber(1, 3);
}

enWinner HowWinTheRound(stRoundInfo RoundInfo)
{
    if (RoundInfo.player1Choice == RoundInfo.computer2Choice)
    {
        return enWinner::draw;
    };

    switch (RoundInfo.player1Choice)
    {
    case enGameChoice::paper:
        if (RoundInfo.computer2Choice == enGameChoice::scissors)
        {
            return enWinner::computer2;
        }
        break;

    case enGameChoice::scissors:
        if (RoundInfo.computer2Choice == enGameChoice::stone)
        {
            return enWinner::computer2;
        }
        break;

    case enGameChoice::stone:
        if (RoundInfo.computer2Choice == enGameChoice::paper)
        {
            return enWinner::computer2;
        }
        break;
    }

    return enWinner::player1;
}

string WinnerName(enWinner winner)
{
    string arrWinnerName[3] = {
        "player1",
        "computer2",
        "Draw",
    };

    return arrWinnerName[winner - 1];
};

string ChoiceName(enGameChoice choice)
{
    string arrPlayersName[3] = {"stone", "paper", "scissor"};

    return arrPlayersName[choice - 1];
}

void setWinnerScreenColor(enWinner winner)
{
    switch (winner)
    {
    case enWinner::player1:
        system("color 2F"); // turn screen to Green
        break;

    case enWinner::computer2:
        system("color 4F"); // turn screen to Red
        cout << "\a";
        break;

    default:
        system("color 6F"); // turn screen to Yellowbreak;
    }
}

void PrintRoundResult(stRoundInfo RoundInfo)
{
    cout << "\n____________Round [" << RoundInfo.RoundNumber << "] ____________\n\n";
    cout << "Player1  Choice  : " << ChoiceName(RoundInfo.player1Choice) << endl;
    cout << "Computer2  Choice: " << ChoiceName(RoundInfo.computer2Choice) << endl;
    cout << "Round Winner   : [" << RoundInfo.WinnerName << "] \n";
    cout << "__________________________________\n"
         << endl;

    setWinnerScreenColor(RoundInfo.RoundWinner);
}

enWinner GameWinner(short Player1WinsTime, short Computer2WinsTime)
{
    if (Player1WinsTime > Computer2WinsTime)
    {
        return enWinner::player1;
    }
    else if (Player1WinsTime < Computer2WinsTime)
    {
        return enWinner::computer2;
    }
    else

    {
        return draw;
    };
}

stGameResult FillGameResult(int GameRound, short Player1WinTimes, short ComputerWinTime, short DrawTime)
{
    stGameResult GameResult;

    GameResult.Computer2WinsTime = ComputerWinTime;
    GameResult.RoundsNumber = GameRound;
    GameResult.DrawTimes = DrawTime;
    GameResult.Player1WinsTime = Player1WinTimes;
    GameResult.GameWinner = GameWinner(Player1WinTimes, ComputerWinTime);
    GameResult.WinnerName = WinnerName(GameResult.GameWinner);

    return GameResult;
}

stGameResult PlayGame(short HowManyRound)
{
    stRoundInfo RoundInfo;

    short player1WinTime = 0, ComputerWinTime = 0, DrawTime = 0;

    for (short GameRound = 1; GameRound <= HowManyRound; GameRound++)
    {
        cout << "\nRound [" << GameRound << "] begins: \n";

        // fill the RoundInfo Struc:
        RoundInfo.RoundNumber = GameRound;
        RoundInfo.player1Choice = ReadPlayer1Choice();
        RoundInfo.computer2Choice = GetComputerChoice();
        RoundInfo.RoundWinner = HowWinTheRound(RoundInfo);
        RoundInfo.WinnerName = WinnerName(RoundInfo.RoundWinner);

        // incress win/draw counter:
        if (RoundInfo.RoundWinner == enWinner::player1)
        {
            player1WinTime++;
        }
        else if (RoundInfo.RoundWinner == enWinner::computer2)
        {
            ComputerWinTime++;
        }
        else
        {
            DrawTime++;
        }

        // show the round result on the screen :
        PrintRoundResult(RoundInfo);
    }

    return FillGameResult(HowManyRound, player1WinTime, ComputerWinTime, DrawTime);
}

string Tabs(short TabNumber)
{
    string tab = "";

    for (int i = 0; i < TabNumber; i++)
    {
        tab = tab + "\t";
    }

    return tab;
}

void ShowGameOverScreen()
{
    cout << Tabs(2) << "__________________________________________________________\n\n";
    cout << Tabs(2) << "                 +++ G a m e  O v e r +++\n";
    cout << Tabs(2) << "__________________________________________________________\n\n";
}

void ShowFinalGameResults(stGameResult GameResults)
{
    cout << Tabs(2) << "_____________________ [Game Results ]_____________________\n\n";
    cout << Tabs(2) << "Game Rounds        : " << GameResults.RoundsNumber << endl;
    cout << Tabs(2) << "Player1 won times  : " << GameResults.Player1WinsTime << endl;
    cout << Tabs(2) << "Computer won times : " << GameResults.Computer2WinsTime << endl;
    cout << Tabs(2) << "Draw times         : " << GameResults.DrawTimes << endl;
    cout << Tabs(2) << "Final Winner       : " << GameResults.WinnerName << endl;
    cout << Tabs(2) << "___________________________________________________________\n";
    setWinnerScreenColor(GameResults.GameWinner);
}

void StartGame()
{
    char PlayAgain = 'y';

    do
    {
        RestScreen();

        stGameResult GameResult = PlayGame(ReadHowManyRounds());

        ShowGameOverScreen();

        ShowFinalGameResults(GameResult);

        cout << "\nDo you want to play again? Y/N? \n";
        cin >> PlayAgain;

    } while (PlayAgain == 'y' || PlayAgain == 'Y');
}

int main()
{

    // Seeds the random number generator in C++, called only once
    srand((unsigned)time(NULL));

    StartGame();
    return 0;
};