#include <iostream>
#include <cstdlib>  // for rand() and srand()
#include <ctime>    // for time()
#include <windows.h> // for Sleep()
#include <string>
#include <vector>
#include "include/process.h"
#include "process.cpp"
using namespace std;

int main()
{
    srand(static_cast<unsigned int>(time(0)));
    bool gamestart = true;
    int PlayerLane;
    int NumSwimmers;
    string PlayerName;

    PrintSwimmingGameIntroduction();

    // Get number of swimmers (between 2 and 10)
    cout << "Enter number of swimmers (2-10): ";
    while (true) {
        cin >> NumSwimmers;
        if (cin.fail() || NumSwimmers < 2 || NumSwimmers > 10) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid number! Please enter a number between 2 and 10: ";
        } else {
            break;
        }
    }

    // Get player name
    cout << "Enter your name: ";
    cin.ignore(); // Clear buffer
    getline(cin, PlayerName);

    // Get player lane
    cout << "Choose your lane (1-" << NumSwimmers << "): ";
    while (gamestart) {
        cin >> PlayerLane;
        if (cin.fail() || PlayerLane < 1 || PlayerLane > NumSwimmers) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid Number! Please choose a lane between 1 and " << NumSwimmers << ": ";
        } else {
            break;
        }
    }

    // Create player with chosen name
    Character Player(true, PlayerName);

    // Create vector of swimmers with custom names
    vector<Character> Swimmers;
    cin.ignore(); // Clear buffer before getting names

    for (int i = 0; i < NumSwimmers; i++) {
        string swimmerName;

        // If this is the player's lane, add a placeholder (we'll use the Player object instead)
        if (i + 1 == PlayerLane) {
            Swimmers.push_back(Character(false, "PLACEHOLDER"));
        } else {
            // Get custom name for this swimmer
            cout << "Enter name for swimmer in lane " << i + 1 << ": ";
            getline(cin, swimmerName);

            // If name is empty, provide a default name
            if (swimmerName.empty()) {
                swimmerName = "Swimmer " + to_string(i+1);
            }

            Swimmers.push_back(Character(false, swimmerName));
        }
    }

    int PoolMeters = 20;
    bool gameOver = false;
    bool playerWon = false;
    int winnerLane = 0;
    string winnerName = "";

    cout << "\nAll swimmers ready! Press Enter to start the race...";
    cin.get();

    // Game loop
    while (!gameOver) {
        system("cls");
        PrintSwimmingPoolAndPlayerProgress(Player, Swimmers, PoolMeters, PlayerLane, NumSwimmers);

        // Handle player movement with direction change
        Player.Move();

        // Check if player reached the right end
        if (Player.Progression >= PoolMeters && Player.MovingRight) {
            Player.Progression = PoolMeters - 1;
            Player.MovingRight = false;  // Start moving left
            cout << Player.Name << " turns around!" << endl;
        }
        // Check if player returned to start
        else if (Player.Progression <= 0 && !Player.MovingRight) {
            Player.Progression = 0;
            gameOver = true;
            playerWon = true;
        }

        // Handle all swimmers movement
        for (int i = 0; i < NumSwimmers; i++) {
            // Skip the player's lane
            if (i + 1 == PlayerLane) continue;

            Swimmers[i].Move();

            // Check if swimmer reached the right end
            if (Swimmers[i].Progression >= PoolMeters && Swimmers[i].MovingRight) {
                Swimmers[i].Progression = PoolMeters - 1;
                Swimmers[i].MovingRight = false;  // Start moving left
                cout << Swimmers[i].Name << " turns around!" << endl;
            }
            // Check if swimmer returned to start
            else if (Swimmers[i].Progression <= 0 && !Swimmers[i].MovingRight) {
                Swimmers[i].Progression = 0;
                gameOver = true;
                winnerLane = i + 1;
                winnerName = Swimmers[i].Name;
                break;
            }
        }

        if (!gameOver) {
            Sleep(200);
        }
    }

    // Display the final race result
    system("cls");
    PrintSwimmingPoolAndPlayerProgress(Player, Swimmers, PoolMeters, PlayerLane, NumSwimmers);

    if (playerWon) {
        cout << "===============================================" << endl;
        cout << "  CONGRATULATIONS! " << PlayerName << " WON THE SWIMMING RACE!" << endl;
        cout << "===============================================" << endl;
    } else {
        cout << "=================================================" << endl;
        cout << "  GAME OVER! " << winnerName << " IN LANE " << winnerLane << " WON THE RACE!" << endl;
        cout << "=================================================" << endl;
        cout << "Better luck next time, " << PlayerName << "!" << endl;
    }

    return 0;
}
