#include "lib/Game.hpp"
#include <Windows.h>
#include <string>

/*
This game is under the GNU GPL Software License
feel free to modify and distribute =D.
*/

int main(){
    std::string title = "\n-Deathly Hollow-"; //game title =D

    //save the original console output for later
    HANDLE originCons = GetStdHandle(STD_OUTPUT_HANDLE);

    //declare a new buffer for the game -_-
    HANDLE nbuff = CreateConsoleScreenBuffer(GENERIC_WRITE | GENERIC_READ,
    FILE_SHARE_READ | FILE_SHARE_WRITE,
    NULL,
    CONSOLE_TEXTMODE_BUFFER,
    NULL
    );

    //if new screen buffer cannot be made/allocated we throw a warning and exit with a 1 return code
    if(nbuff == INVALID_HANDLE_VALUE){
        std::cerr << "\033[91mConsole Cannot be made!\n";
        return 1;
    }

    //we set our new buffer as the active screen buffer to render our game in
    SetConsoleActiveScreenBuffer(nbuff);

    //also we grab the screen info
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(nbuff,&csbi);

    //lock the console so it doesnt overwrite
    csbi.dwSize.X = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    csbi.dwSize.Y = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    SetConsoleScreenBufferSize(nbuff,csbi.dwSize); //set the new console size to lock it =D

    //we enable virtual term proc to parse advanced ansi commandsss
    DWORD cmode; //declare our consolemode buffer
    GetConsoleMode(nbuff,&cmode);
    cmode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING; //we turn it on
    SetConsoleMode(nbuff,cmode); //and set it

    //hide the cursor for now, see what happens
    CONSOLE_CURSOR_INFO curinf;
    GetConsoleCursorInfo(nbuff,&curinf);
    curinf.bVisible = false;
    SetConsoleCursorInfo(nbuff,&curinf);





    //footer and header has been moved to game.hpp

    //set game to render under the header.
    COORD spos = {0,2};
    SetConsoleCursorPosition(nbuff,spos);

        //scroll declaration        

    std::string scroll = "\033[2;" + std::to_string(csbi.dwSize.Y - 1) + "r"; 

    DWORD cbuf3; //scroll buffer

    WriteConsoleA(
        nbuff,
        scroll.c_str(),
        scroll.size(),
        &cbuf3,
        NULL
    );


    // star the main game loop and pass our screen buffer to the game
    Game game;
    game.Main(nbuff,csbi.dwSize.X,csbi.dwSize.Y); //games main loop

    //after the game we return the original screen buffer and free memory

    SetConsoleActiveScreenBuffer(originCons);
    CloseHandle(nbuff);

    return 0;

}