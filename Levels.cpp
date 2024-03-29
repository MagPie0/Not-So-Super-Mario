#include "Levels.h"

Levels::Levels(int levels, int dimension, int lives, int nothingPercent, int coinPercent, int mushroomPercent, int goombaPercent, int koopaPercent)
{
    //sets variables
    m_numberOfLevels  = levels;
    m_dimension = dimension;
    m_marioLives = lives;
    m_percentageOfNothing = nothingPercent;
    m_percentageOfCoins = coinPercent;
    m_percentageOfMushrooms = mushroomPercent;
    m_percentageOfGoombas = goombaPercent;
    m_percentageOfKoopas = koopaPercent;

    //creates Mario
    m_Mario = new Mario(lives, dimension);
    m_marioRowPlacement = m_Mario->getRowForMario();
    m_marioColumnPlacement = m_Mario->getColumnForMario();

    //creates the 3D array to create a 2D level for each level
    levelSize = new char **[dimension];
    for (int i = 0; i < m_numberOfLevels; ++i)
    {
        levelSize[i] = new char *[dimension];
        for (int j = 0; j < dimension; ++j)
        {
            levelSize[i][j] = new char [dimension];
        }
    }
    
    srand(time(NULL)); //generates a new seed everytime so that it can actually call a random number
}

Levels::~Levels() //deconstructor
{
    for (int i = 0; i < m_dimension; ++i) {
        for (int j = 0; j < m_dimension; ++j) {
            delete[] levelSize[i][j]; // Delete each row
        }
        delete[] levelSize[i]; // Delete each column
    }
    delete[] levelSize;
    delete m_Mario;
}


char Levels::CreateLevel(int levelNumber){
        for (int j = 0; j < m_dimension; ++j)
        {
            for (int k = 0; k < m_dimension; ++k)
            {
            int random = 1 + (rand() % 100); //creates the random probability each loop

            if (random <= m_percentageOfCoins)
            {
                levelSize[levelNumber][j][k] = 'c';
            } else if (random <= (m_percentageOfMushrooms + 
                m_percentageOfCoins))
            {
                levelSize[levelNumber][j][k] = 'm';
            } else if (random <= (m_percentageOfGoombas + 
                m_percentageOfMushrooms + m_percentageOfCoins))
            {
                levelSize[levelNumber][j][k] = 'g';
            }  else if (random <= (m_percentageOfKoopas +
                 m_percentageOfGoombas + m_percentageOfMushrooms + m_percentageOfCoins))
            {
                levelSize[levelNumber][j][k] = 'k';
            } else if (random <= 100)
            {
                levelSize[levelNumber][j][k] = 'x';
            } else {
                cerr << "error" << endl << endl;
            } 
            }
        }
        PlaceWarp(levelNumber); 
        AddFinalBoss(levelNumber);
        return ***levelSize; 
}


void Levels::DisplayLevel(int level, int xCord, int yCord){
    //Kalin Richardson helped me by recommending I put in parameters for the method
    // so that I can controll what level gets shown and when Mario gets shown
    cout << endl << "==============" << endl;

        for (int j = 0; j < m_dimension; ++j)
        {
            for (int k = 0; k < m_dimension; ++k)
            {
             if (j == xCord && k == yCord) //places Mario into the world
                {
                  cout << 'H'; 
                } else {
                   cout << levelSize[level][j][k];
                }
            }
        cout << endl;
        }
    cout << "==============";
}

void Levels::PlaceWarp(int levelNumber){
    int row = rand() % m_dimension;
    int column = rand() % m_dimension;

    if (levelNumber < m_numberOfLevels - 1) //Doesn't place the warp on the last level
    {
        levelSize[levelNumber][row][column] = 'W';
    }

}

void Levels::AddFinalBoss(int levelNumber){
    if (levelNumber == m_numberOfLevels - 1) //Only places Boss/Bowser on the last level
    {
        int row = rand() % m_dimension;
        int column = rand() % m_dimension;

        levelSize[levelNumber][row][column] = 'B';
    }
}

char Levels::getMariosCurrentPosition(int currentLevel, int row, int column){
    //I use this to track the next char in his next position
    return levelSize[currentLevel][row][column];
}

void Levels::MarioHasBeen(int currentLevel, int row, int column){
    //This makes it so that Mario doesn't constantly pick up coins or fight while he finds the warp/boss
    levelSize[currentLevel][row][column] = 'x';
}