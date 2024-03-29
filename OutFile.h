#ifndef OUTFILE_H
#define OUTFILE_H

#include <fstream>
#include "Mario.h"
#include "FileTakeIn.h"
#include "Levels.h"

class OutFile
{
private:
    Levels *level;
    FileTakeIn *fileTakeIn;
    Mario *marioInWorld;
    char **levelSize;
    int amountOfLevels;
    int dimension;
    int* m_levels;
public:
    OutFile(string inputFile, string outputFile);
    ~OutFile();
    void StartGame(string outputFile);
    void CheckFileNumbers(string inputFile, string outputFile);
};

#endif
