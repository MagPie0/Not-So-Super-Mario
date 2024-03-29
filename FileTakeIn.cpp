#include "FileTakeIn.h"

FileTakeIn::FileTakeIn()
{
    //I hard code the array size since it is a fixed amount of data the program will be reading
    fileNumbers = new int [8];
}

FileTakeIn::~FileTakeIn()
{
    delete[] fileNumbers;
}

void FileTakeIn::ProcessInFile(string inputFile){
    ifstream inFS;

    inFS.open(inputFile);

    if (!inFS.is_open())
    {
        cerr << "Couldn't open file, sorry";
        return;
    }

    while (!inFS.fail())
    {
        for (int i = 0; i < 8; ++i)
        {
            inFS >> fileNumbers[i];
        }
    }
    
    inFS.close();
}
bool FileTakeIn::CheckIfPercentagesAddUp(){
    if (fileNumbers[3] + fileNumbers[4] + fileNumbers[5] + fileNumbers[6] + fileNumbers[7] == 100)
    {
        return true;
    } else {
        return false;
    }
    
}

//accessor methods
int FileTakeIn::GetNumberOfLevels(){
    return fileNumbers[0];
}
int FileTakeIn::GetDimension(){
    return fileNumbers[1];
}
int FileTakeIn::GetMarioLives(){
    return fileNumbers[2];
}
int FileTakeIn::GetCoinPercentage(){
    return fileNumbers[3];
}
int FileTakeIn::GetNothingPercentage(){
    return fileNumbers[4];
}
int FileTakeIn::GetGoombaPercentage(){
    return fileNumbers[5];
}
int FileTakeIn::GetKoopaPercentage(){
    return fileNumbers[6];
}
int FileTakeIn::GetMushroomPercentage(){
    return fileNumbers[7];
}
