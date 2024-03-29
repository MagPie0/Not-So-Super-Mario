#include "Mario.h"

Mario::Mario(int lives, int dimension)
{
    amountOfLives = lives;
    dimensionForMario = dimension;
    powerLevel = 0;
    coins = 0;
    //automatically place Mario in the level once he is created
    placeMarioInLevel();
}

Mario::~Mario(){}

void Mario::MarioMove(){
    //There are 4 different directions he can face so we use rand() to calculate the probability of the next direction
    int randomDirection = (rand() % 4);

    if (randomDirection == 0)
    {
        if (rowOfMario == 0)
        {
            rowOfMario = dimensionForMario - 1;
        } else {
            rowOfMario--;
        }
        cout << "Mario is moving up";
    } else if (randomDirection == 1) {
        if (rowOfMario == dimensionForMario - 1)
        {
            rowOfMario = 0;
        } else {
            rowOfMario++;
        }
        cout << "Mario is moving down";
    } else if (randomDirection == 2) {
        if (columnOfMario == 0)
        {
            columnOfMario = dimensionForMario - 1;
        } else {
            columnOfMario--;
        }
        cout << "Mario is moving left";
    } else {
        if (columnOfMario == dimensionForMario - 1)
        {
            columnOfMario = 0;
        } else {
            columnOfMario++;
        }
        cout << "Mario is moving right";
    }
}

bool Mario::fightGoomba(){
    //mario wins with an 80% probability
    if (FightResult(80))
    {
        cout << "\nMario has won the fight against a Goomba!" << endl;
        return true;
    } else {
        cout << "\nMario has lost the fight!";
        if (powerLevel != 0) //if he has power levels then he loses them
        {
            TakeAwayPowerLevel();
            cout << "\nMario has lost a power level from his fight with a Goomba" << endl;
        } else if (amountOfLives != 0) //no power levels mean that he loses a life
        {
            TakeAwayMarioLife();
            cout << "\nMario has lost a life from his fight with a Goomba" << endl;
        }
    }
    return false;
}

bool Mario::fightKoopa(){
    //mario wins with 65% probability
    if (FightResult(65))
    {
        cout << "\nMario has won the fight against a Koopa!" << endl;
        return true;
    } else {
        cout << "\nMario has lost the fight!";
        if (powerLevel != 0)
        {
            TakeAwayPowerLevel();
            cout << "\nMario has lost a power level from his fight with a Koopa" << endl;
        } else if (amountOfLives != 0)
        {
            TakeAwayMarioLife();
            cout << "\nMario has lost a life from his fight with a Koopa" << endl;
        }
    }
    return false;
}

bool Mario::fightBowser(){
    //mario wins with 50% probability
    if (FightResult(50))
    {
        cout << "\nMario has beat Bowser!!!" << endl;
        return true;
    } else {
        cout << "\nMario has lost the fight!";
        if (powerLevel != 0)
        {
            TakeAwayPowerLevel();
            cout << "\nMario has lost a power level from his fight with the Boss" << endl;
        } else if (amountOfLives != 0)
        {
            TakeAwayMarioLife();
            cout << "\nMario has lost a life from his fight with the Boss" << endl;
        }
    }
    
    return false;
}

bool Mario::emptyLives(){
    if (amountOfLives == 0)
    {
        return true;
    } else {
        return false;
    }
}

void Mario::placeMarioInLevel(){
    srand(time(NULL)); //generates a new seed everytime so that it can actually call a random number
    rowOfMario = rand() % dimensionForMario;
    columnOfMario = rand() % dimensionForMario;
}

//accessor methods
int Mario::getColumnForMario(){
    return columnOfMario;
}

int Mario::getRowForMario(){
    return rowOfMario;
}

int Mario::getMarioLives(){
    return amountOfLives;
}

int Mario::getPowerLevel(){
    return powerLevel;
}

int Mario::getCoins(){
    return coins;
}

void Mario::TakeAwayMarioLife(){
    if (powerLevel > 0)
    {
        powerLevel--;
    } else {
        amountOfLives--;
    }  
}

void Mario::TakeAwayPowerLevel(){
    powerLevel--;
}

void Mario::FindsCoin(){
    coins++;
}

void Mario::FindsMushroom(){
    if (powerLevel == 2) //doesn't get more than 2 power levels
    {
        return;
    } else {
        powerLevel++;
    }
    
}

bool Mario::FightResult(int probabilityOfWinning){
    int WinRate = 1 + (rand() % 100 );
    if (WinRate <= probabilityOfWinning) //from 0 to whatever probability of winning is a win
    {
        return true;
    } else if (WinRate <= 100) // anything else from the probability is a loss
    {
        return false;
    } 
}