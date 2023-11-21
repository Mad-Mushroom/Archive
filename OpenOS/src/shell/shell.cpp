/* OpenOS Shell
 *
 * Made by MadMushroom
 * 
 * Copyright (c) 2023 MadMushroom
 */

#pragma once

#include "../Kernel.h"

struct command {
    const char* commandString;
    void action(char args[][32]);
};

class Shell {
    public:
        const char* Username;
        char commandBuffer[512];
        uint_16 bufferSize;
        command commands[1] = {
            {"clear"},
        };
};
Shell shell;

void initShell(){
    //malloc(sizeof(shell));
    shell.Username = "user";
}

void RunShell(){
    PrintString(shell.Username);
    PrintString("> ");
}

void ParseCommand(){
    char arguments[16][32];
    uint_16 index;
    uint_16 index2;
    uint_8 args;

    while(shell.commandBuffer[index] != 0){
        if(shell.commandBuffer[index] == ' '){ args++; index++; index2 = 0; }
        arguments[args][index2] = shell.commandBuffer[index];
        index++;
        index2++;
    }

    PrintString(arguments[0]);    
}

void Shell_EnterPressed(){
    PrintString("\n");
    //ParseCommand();
    RunShell();
}

void Shell_AddChar(char chr){
    shell.commandBuffer[shell.bufferSize] = chr;
    shell.bufferSize++;
    PrintChar(chr);
}