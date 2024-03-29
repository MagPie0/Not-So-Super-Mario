#ifndef FILETAKEIN_H
#define FILETAKEIN_H

#include <iostream>
#include <fstream>
using namespace std;

class FileTakeIn
{
private:
    int *fileNumbers;
public:
    FileTakeIn();
    ~FileTakeIn();
    void ProcessInFile(string inputFile);
    bool CheckIfPercentagesAddUp();
    int GetCoinPercentage();
    int GetMarioLives();
    int GetGoombaPercentage();
    int GetKoopaPercentage();
    int GetDimension();
    int GetNothingPercentage();
    int GetMushroomPercentage();
    int GetNumberOfLevels();
};

#endif