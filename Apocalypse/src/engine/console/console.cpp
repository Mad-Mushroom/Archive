/*
 * Mad2D - MadEngine
 * Made by MadMushroom
 * 
 * licensed under GNU Generic Public License
 * <https://www.gnu.org/licenses/gpl-3.0.en.html>
 */

#include "console.h"

void ConsoleClass::Print(const char* text){
    cout << text << endl;
}
        
void ConsoleClass::Log(const char* message){
    TotalLogs++;
    cout << "Log " << TotalLogs << ": " << message << endl;
}
void ConsoleClass::Warning(const char* message){
    TotalWarnings++;
    cout << "Warning " << TotalWarnings << ": " << message << endl;
}
void ConsoleClass::Error(const char* message){
    TotalErrors++;
    cout << "ERROR " << TotalErrors << ": " << message << endl;
}