#include "args.h"

bool compare(char* in, const char* cmp){
    while (*in && *cmp) {
        if (*in != *cmp) {
            return false;
        }
        in++;
        cmp++;
    }
    return (*in == '\0' && *cmp == '\0');
}

void help(){
    cout << "MadLang Help" << endl;
}

void parseArgs(int argc, char* argv[]){
    if(argc == 0) return;
    for(int i=1; i<=argc; i++){
        if(compare(argv[i], "-help") || compare(argv[i], "-h")) help();
        if(compare(argv[i], "-o")) MainConfig.outFile = argv[i+1];
        if(compare(argv[i], "-i")) MainConfig.inFile = argv[i+1];
    }
}