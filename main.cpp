#include "FileTakeIn.h"
#include "Levels.h"
#include "OutFile.h"

int main(int argc, char **argv){
    //sets the command line into their respective variables
    string inputFile = argv[1];
    string outFile = argv[2];
    OutFile *fileOutPut = new OutFile(inputFile, outFile);

    delete fileOutPut;
    return 0;
}