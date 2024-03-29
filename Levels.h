#ifndef LEVELS_H
#define LEVELS_H

#include <iostream>
#include "Mario.h"
using namespace std;

class Levels
{
private:
    int m_numberOfLevels;
    int m_dimension;
    int m_marioLives;
    int m_percentageOfNothing;
    int m_percentageOfCoins;
    int m_percentageOfMushrooms;
    int m_percentageOfGoombas;
    int m_percentageOfKoopas;
    int m_marioColumnPlacement;
    int m_marioRowPlacement;
    char ***levelSize;
    Mario *m_Mario;
public:
    Levels(int levels, int dimension, int lives, int nothingPercent, int coinPercent, int mushroomPercent, int goombaPercent, int koopaPercent);
    ~Levels();
    char CreateLevel(int levelNumber);
    void DisplayLevel(int level, int xCord, int yCord);
    void PlaceWarp(int levelNumber);
    void AddFinalBoss(int levelNumber);
    char getMariosCurrentPosition(int currentLevel, int row, int column);
    void MarioHasBeen(int currentLevel, int row, int column);
};

#endif
