#ifndef MARIO_H
#define MARIO_H

#include <iostream>
#include <cstdlib>
using namespace std;
class Mario
{
private:
    int amountOfLives;
    int powerLevel;
    int coins;
    int dimensionForMario;
    int rowOfMario;
    int columnOfMario;
public:
    Mario(int lives, int dimension); //takes in lives and dimension from input file
    ~Mario();
    void placeMarioInLevel();
    int getRowForMario();
    int getColumnForMario();
    int getMarioLives();
    int getPowerLevel();
    int getCoins();
    bool fightGoomba();
    bool fightKoopa();
    bool fightBowser();
    bool emptyLives();
    void TakeAwayMarioLife();
    void TakeAwayPowerLevel();
    void FindsCoin();
    void FindsMushroom();
    void MarioMove();
    bool FightResult(int probabilityOfWinning);
};

#endif