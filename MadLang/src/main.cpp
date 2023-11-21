#include "main.h"

config MainConfig;

int main(int argc, char* argv[]){
    parseArgs(argc-1, argv);

    if(MainConfig.inFile.length() <= 0 || MainConfig.outFile.length() <= 0){
        cout << "Input/Output file not specified! Aborting." << endl;
        return 1;
    }

    lexer();

    return 0;
}