#include "include/process.h"

void PrintSwimmingGameIntroduction() {
    cout << "+==============================+" << endl;
    cout << "| Welcome to the Olympics Game!|" << endl;
    cout << "+==============================+" << endl;
    cout << "Instructions:" << endl;
    cout << "- Swimmers start at the left, swim to the right end" << endl;
    cout << "- Then they turn around and swim back to the start" << endl;
    cout << "- First swimmer to return to the starting point wins!" << endl;
    cout << "- You are represented by '0', other swimmers by 'X'" << endl;
    cout << endl;
}

Character::Character(bool chosen_player, const string& name) {
    ChosenPlayer = chosen_player;
    Progression = 0;
    MovingRight = true;  // Start by moving right
    Name = name;         // Set character name
}

int Character::RandomSwimDistance() {
    return rand() % 2 + 1;
}

void Character::Move() {
    int distance = RandomSwimDistance();

    // If moving right, add the distance
    if (MovingRight) {
        Progression += distance;
    }
    // If moving left, subtract the distance
    else {
        Progression -= distance;
        // Make sure we don't go below 0
        if (Progression < 0) {
            Progression = 0;
        }
    }
}

void PrintSwimmingPoolAndPlayerProgress(Character& Player, vector<Character>& Swimmers, int PoolMeters, int PlayerLane, int NumSwimmers) {
    cout << "Swimming Pool Race Status:" << endl;
    cout << "Start" << string(PoolMeters - 5, ' ') << "End" << endl;

    for (int i = 0; i < NumSwimmers; i++) {
        cout << "Lane " << i + 1 << " ";
        if (i + 1 < 10) cout << " ";
        cout << "|";

        for (int j = 0; j < PoolMeters; j++) {
            if (i + 1 == PlayerLane && j == Player.Progression) {
                cout << "0";  // Player character
            } else if (i + 1 != PlayerLane && j == Swimmers[i].Progression) {
                cout << "X";  // AI swimmers
            } else {
                cout << " ";  // Empty water
            }
        }
        cout << "|";

        // Show name and direction indicators
        if (i + 1 == PlayerLane) {
            cout << " " << Player.Name << " " << (Player.MovingRight ? "->" : "<-");
        } else {
            cout << " " << Swimmers[i].Name << " " << (Swimmers[i].MovingRight ? "->" : "<-");
        }

        cout << endl;
    }
    cout << string(PoolMeters + 30, '*') << endl;  // Make line longer to accommodate names
}
