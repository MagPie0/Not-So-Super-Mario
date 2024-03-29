#include "OutFile.h"

OutFile::OutFile(string inputFile, string outputFile)
{
    fileTakeIn = new FileTakeIn();
    //I process the input file from argv in main.cpp to gather all of the data I need for the game
    fileTakeIn->ProcessInFile(inputFile); 

    //I put in all the data into levels
    level = new Levels(fileTakeIn->GetNumberOfLevels(), fileTakeIn->GetDimension(), fileTakeIn->GetMarioLives(),
        fileTakeIn->GetNothingPercentage(), fileTakeIn->GetCoinPercentage(), fileTakeIn->GetMushroomPercentage(),
        fileTakeIn->GetGoombaPercentage(), fileTakeIn->GetKoopaPercentage());

    dimension = fileTakeIn->GetDimension();

    //I create Mario with some of the data from inputFile
    marioInWorld = new Mario(fileTakeIn->GetMarioLives(), fileTakeIn->GetDimension());
    amountOfLevels = fileTakeIn->GetNumberOfLevels();

    //create the array of levels
    m_levels = new int[amountOfLevels];
    //then create the 2D array for each level
    levelSize = new char *[dimension];
    for (int i = 0; i < dimension; ++i)
    {
        levelSize[i] = new char [dimension];
    }

    CheckFileNumbers(inputFile, outputFile);
}

OutFile::~OutFile()
{
    delete fileTakeIn;
    delete marioInWorld;
    delete[] m_levels;
    delete[] levelSize;
}

void OutFile::CheckFileNumbers(string inputFile, string outputFile){
    //I check to see if the percentages in the file add up to 100 or else this will fail
    if (fileTakeIn->CheckIfPercentagesAddUp())
    {
        StartGame(outputFile);
    } else {
        cout << "incorrect percentages" << endl;
        return;
    }
}

void OutFile::StartGame(string outputFile){
    /*I got help from Kaye in regards to logging in the game into the output file.
    Lines 57-63 and 158-159
    I had originally tried using the file processing method used for A1, however
    was very unsuccessful
    */
    ofstream loggerFile(outputFile);
    if (!loggerFile.is_open()) {
        cerr << "Failed to open output file: " << outputFile << endl;
        return; // Exit function if file opening fails
    }
    streambuf* coutToLogger = cout.rdbuf(); 
    cout.rdbuf(loggerFile.rdbuf()); //redirects all couts to the logger file

    int currentLevelPlayed = 0;
    bool isGameOver = false;

    //create the levels
    for (int i = 0; i < amountOfLevels; ++i)
    {
        m_levels[i] = level->CreateLevel(i);
        level->DisplayLevel(i, -1, -1);
        cout << endl;
    }

    cout << "Mario is currently at (" << marioInWorld->getRowForMario() << ", "
        << marioInWorld->getColumnForMario() << ")" << endl;
    /*The game itself is a while loop,
    While Mario has lives and the game isn't over, mario will move around randomly in the level using move(),
    the switch statement will check to see what mario has landed on and determine the next move and what other methods to call
    from the Mario class.
    */
    while (marioInWorld->getMarioLives() > 0 && !isGameOver)
    {
        int rowOfMario = marioInWorld->getRowForMario();
        int columnOfMario = marioInWorld->getColumnForMario();
        level->DisplayLevel(currentLevelPlayed, marioInWorld->getRowForMario(), marioInWorld->getColumnForMario());

       cout << endl << "Level: " << currentLevelPlayed << ""
        << endl << "Mario is at (" << rowOfMario << ", " << columnOfMario << ")"
        << endl << "Mario is at Power Level: " << marioInWorld->getPowerLevel()
        << endl << "Mario has " << marioInWorld->getMarioLives() << " lives left"
        << endl << "Mario has " << marioInWorld->getCoins() << " coins";

        //tracks the char in the 2D array that mario is going to go on
        char nextPosition = level->getMariosCurrentPosition(currentLevelPlayed, rowOfMario, columnOfMario);
        switch (nextPosition)
        {
        case 'c':
            cout << "\nMario found a coin!";
            marioInWorld->FindsCoin();
            level->MarioHasBeen(currentLevelPlayed, rowOfMario, columnOfMario);
            break;
        case 'm':
            cout << "\nMario found a mushroom!";
            marioInWorld->FindsMushroom();
            level->MarioHasBeen(currentLevelPlayed, rowOfMario, columnOfMario);
            break;
        case 'g':
            cout << "\nMario will fight a goomba";
            if (marioInWorld->fightGoomba())
            {
                level->MarioHasBeen(currentLevelPlayed, rowOfMario, columnOfMario);
            }
            if (marioInWorld->emptyLives())
            {
                    cout << "Mario has lost D:";
                    return;
            }
            break;
        case 'k':
            cout << "\nMario will fight a koopa";
            if (marioInWorld->fightKoopa())
            {
                level->MarioHasBeen(currentLevelPlayed, rowOfMario, columnOfMario);
            }
            if (marioInWorld->emptyLives())
            {
                    cout << "Mario has lost the whole game D:";
                    return;
            }
            break;  
        case 'W':
            cout << "\nMario has found a warp pipe!";
            currentLevelPlayed++;
            level->DisplayLevel(currentLevelPlayed, marioInWorld->getRowForMario(), marioInWorld->getColumnForMario());
            break;  
        case 'B':
        // Mario will continue to fight bowser/boss once they have interacted in the last level to see if he wins of loses
            cout << "\nMario is fighing the BOSS";
            while (!marioInWorld->fightBowser())
            {
                if (marioInWorld->emptyLives())
                {
                    cout << "\nMario has lost D:";
                    return;
                } else if (marioInWorld->fightBowser()) //if fightBowser is true then mario wins
                {
                    cout << "\nMario has won the whole game!! :D";
                    return;
                }
            }
            break;                
        default:
            cout << "\nMario is on an empty space";
            break;
        }
        
        if (currentLevelPlayed != (amountOfLevels))
        {        
                cout << endl;
                marioInWorld->MarioMove();
        } else {
            isGameOver = true;
        }
    }

    cout.rdbuf(coutToLogger);
    loggerFile.close();
}