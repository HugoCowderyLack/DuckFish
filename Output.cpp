#include "Output.hpp"

void SetBackColour(int bgColour) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, bgColour << 4);
}