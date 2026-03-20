#ifndef CSTREAM_HPP
#define CSTREAM_HPP

#include <windows.h> //for WriteConsoleA, Handle and DWORD
#include <conio.h> //for getch
#include <cctype> //for isprint()
#include <string> //for string

namespace CS{

    /*
        TODO's:
            - Universal Input handler to handle boolean, int, float, double, char, and more
            - handle arrow keys
            - handle sig int with signal
    */

    //Universal Output handler
    void outp(HANDLE scbuff,const std::string& msg){ //pass the screen buffer and string input as args
        DWORD cbuff;
        WriteConsoleA( //write to console
            scbuff,
            msg.c_str(),
            msg.size(),
            &cbuff,
            NULL
        );
    }

    //Universal Input Handler
    std::string inp(HANDLE scbuff){ //input handler w/ a scrbuffer as args
        std::string data = ""; //declare our buffer for our input

        while(true){
            char ch = _getch(); // to capture all key events

            if(ch == '\r'){ //capture enter key
                outp(scbuff,"\n");
                break;
            }else if(ch == '\b'){ //capture backspace key
                if(!data.empty()){
                    data.pop_back(); //erase characters
                    outp(scbuff,"\b \b");
                }
            }else if(isprint(ch)){ //Capture the rest of the keys as input
                data += ch;
                std::string s(1,ch); //store the key captured in a temporary buffer to display
                outp(scbuff,s); //display said key
            }
        }

        return data; //return what was typed
    }



}

#endif