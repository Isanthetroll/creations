#ifndef PROCESS_H_INCLUDED
#define PROCESS_H_INCLUDED
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <windows.h>
#include <string>
#include <vector>
using namespace std;

class Character {
public:
    bool ChosenPlayer;
    int Progression;
    bool MovingRight;  // Add direction tracking
    string Name;       // Add name for each character

    Character(bool chosen_player, const string& name = "Swimmer");
    int RandomSwimDistance();
    void Move();  // Method to handle movement with direction
};

void PrintSwimmingPoolAndPlayerProgress(Character& Player, vector<Character>& Swimmers, int PoolMeters, int PlayerLane, int NumSwimmers);
void PrintSwimmingGameIntroduction();

#endif // PROCESS_H_INCLUDED
