#ifndef GAME_HPP
#define GAME_HPP

//standard headers
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <Windows.h>
#include <string>
#include <conio.h>

//my headers
#include "player.hpp"
#include "items.hpp"
#include "rooms.hpp"
#include "inventory.hpp"

//for easy access
using std::string;

enum Display{ //display size in map 5x5
    X1 = 5,
    Y1 = 5
};

const std::pair <int,int> start = {2,2};

//main game class
class Game{
    private:
        Player* main; //player init
        bool isRUnning = true; //running by default
        tile* current = nullptr;
        Map* world = new Map;
        HANDLE scrbuff; //declare a screen buffer to pass the buffer from main
        int scrsizeW,scrsizeH;

        void DrawUI(){
            COORD hc = {0,0}; //set headers coords to top left
            COORD fc = {0,(short)scrsizeH - 1}; //set the footer coords to the screens height -1 since its a coord
            DWORD cbuff; //declare our buffer for header and fooder
            WORD bg = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY; //set the background of header and footer to white

            std::string title = "-Deathly Hollows-",ftitle = "A Game made by Patrick Andrew Cortez";
            
            if(scrsizeW > title.size()){
                title.append(scrsizeW - title.size(),' ');
            }

            //finally we render our header

            WriteConsoleOutputCharacterA( //write the header text to screen buffer
                scrbuff,
                title.c_str(),
                title.size(),
                hc,
                &cbuff
            );

            FillConsoleOutputAttribute( //we then fill the headers background with white that we set in fg
                scrbuff,
                bg,
                scrsizeW,
                hc,
                &cbuff
            );

            WORD fg = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY; //set footer background to white
            DWORD cbuff2; //declare our buffer for footer
            //set up our footer
            WriteConsoleOutputCharacterA(scrbuff,ftitle.c_str(),ftitle.size(),fc,&cbuff2); //write footer text
            FillConsoleOutputAttribute(scrbuff,fg,scrsizeW,fc,&cbuff2); //set up footer backgroudn


    }
        

    void init(){ //inititialize the player
            string name,desc;
            item* none = new item("none","none");
            print("\033[93m\n\t\t[Deathly Hollow]\n");
            print("\n Whats your name? "); name = in(); //get player name with input handler
            print("\n Alittle background? ");
            
            desc = in(); //get player description using our input handler

            main = new Player(name,desc,100); //initialize player
            main->current = none; //set player item to none, we cant have the player item uninitialized
        
    }

        void print(const std::string& msg){ //new Console output handler since we are declaring a new scr buffer
            DWORD Charbuff; //declare our character buffer
            WriteConsoleA( // write the msg to screen buffer
                scrbuff,
                msg.c_str(),
                msg.size(),
                &Charbuff,
                NULL
            );
        }

        void printHelp(){ //for user convenience and serves as a guide
            print("Actions: \n");
            print("\ntest - test action\n");
            print("leave - exit the game\n");
            print("move <location> - move to the desired location\n");
            print("display - show the map\n");
            print("where - show current coordinates\n");
            print("look - show items in the room\n");
            print("take - take an item in room\n");
            print("use <item> - equip an item\n");
        }

        void InitRooms(){ //initialize room before game begins
            tile* kitchen = new tile("kitchen","A lovely simple kitchen");
            tile* lr = new tile("Living Room","A simple living room w/ a tv, couch and a window");
            tile* br = new tile("Bathroom","A simple bathroom w/ a toilet and a shower");
            
            lr->coords = start; //starting coord

            //loot setup

            item apple("Apple","A red delicious Apple",false,false,false,3);
            lr->addLoot(apple);

            //join tiles
            lr->CreateTile(kitchen,br);
            br->CreateTile(lr,nullptr);
            kitchen->CreateTile(nullptr,lr);

            this->current = lr; //set living room as the current

            world->fillMap(lr); //fill map to display

        }

        string in(){ //input handler for control, will be useful later.
            string data = "";
            char ch;

            while(true){
                ch = _getch();

                if(ch == '\r'){
                    print("\n");
                    break;
                }else if(ch == '\b'){
                    if(!data.empty()){
                        data.pop_back();
                        print("\b \b");
                    }
                }else if(isprint(ch)){
                    data += ch;
                    string s(1,ch);
                    print(s);
                }

            }

            return data;
        }

        void displayMap(std::pair<int,int>& coords,const int& Xaxis = 0,const int& Yaxis = MapSize::Y){ //for now we only have players coords as the
            bool isDone = false;
            std::pair<int,int> MapSize = world->getMapSize(); //get Map Size

            print("--------------------------------------------\n");
            for(int posY = main->coords.second - 2;posY < Yaxis; posY++){
                for(int posX = main->coords.first - 2;posX < Xaxis;posX++){

                 //   std::print << "PosX: " << posX << " PosY: " << posY << " "; //debug the map display for future bugs and shi

                    if(world->tiles[posX][posY] != nullptr && (posX != coords.first || posY != coords.second)){
                        print(" "); // if populated we display as space.
                    }else if(posX == coords.first && posY == coords.second){
                        print("O"); //display player position
                    }else{
                        print("#"); //display null elements as #  to simulate walls or borders
                    }
                }
                print("\n"); //new line after a row is done
            }
            print("\n");
        }

        void traverse(const string& location){
            //traverse to loc if not nullf
            if(current->North != nullptr && location == current->North->name){
                current = current->North;
            }else if(current->South != nullptr && location == current->South->name){
                current = current->South;
            }else if(current->East != nullptr && location == current->East->name){
                current = current->East;
            }else if(current->West != nullptr && location == current->West->name){
                current = current->West;
            }else{
                print("\033[91m" + location + " does not exist!\n");
                return;
            }

        }

        void displayTiles(){ //display adjacent tiles to player

            print("Nearby Tiles:\n");

            if(current->North != nullptr){
                print(current->North->name + " | " + current->North->desc + "\n");
            }

            if(current->South != nullptr){
                print(current->South->name + " | " + current->South->desc + "\n");
            }

            if(current->East != nullptr){
                print( current->East->name + " | " + current->East->desc + "\n");
            }

            if(current->West != nullptr){
                print( current->West->name + " | " + current->West->desc + "\n");
            }

            print("\n");
        }

        string remchar(string& origin,const char& target){
            for(int x = 0; x < origin.size();x++){
                if(origin[x] == target){
                    origin.erase(x,1);
                    return origin;
                    break;
                }
            }
        }

        void clearscreen(){ //clear screen
            print("\033[2J\033[H");
        }



    public:


        void Main(HANDLE buff,const short& X,const short& Y){
            scrbuff = buff;
            //pass our screen buffer size from main
            scrsizeH = Y;
            scrsizeW = X;

            DrawUI(); 
            init(); //initiate start of game
            InitRooms(); //initiate rooms
            string action; //Player action 


            while(isRUnning){ //main game loop
                clearscreen(); //clear screen so its clean
                DrawUI(); //start rendering our UI.
                displayTiles(); //display adjacent tiles so players knows where to travert next
                main->coords = current->coords;
                print("Item Equipped: " + main->current->name + "\n"); //display current item of player 
                print("\033[93m" + main->getname() +  "@" + current->name + ">: "); //prompt
                action = in(); //player action
                std::stringstream ss(action); //init tokenizer
                string cmd;
                ss >> cmd;
                
                if(cmd.compare("test")==0){
                    print("Hello From mars, your code is working!\n");
                }else if(cmd.compare("help")==0){ //for user convenience
                    printHelp();
                }else if(cmd.compare("leave")==0){
                    exit(0); //exit on quit
                }else if(cmd.compare("display")==0){
                    displayMap(main->coords,Display::X1,Display::Y1);
                }else if(cmd.compare("move")==0){
                    string location;
                    std::getline(ss,location);
                    location = remchar(location,' '); 

                    traverse(location); //make players traverse
                }else if(cmd.compare("where")==0){
                    print(std::to_string(main->coords.first) + "," + std::to_string(main->coords.second) + "\n"); //display curr pos to player
                }else if(cmd.compare("inventory")==0){ //display inventory of player
                    main->main.displayItems(scrbuff); 
                }else if(cmd.compare("look")==0){
                    current->displayLoot(scrbuff);
                }else if(cmd.compare("take")==0){
                    string thing;
                    ss >> thing;
                    current->giveLoot(main->main,thing,1);
                }else if(cmd.compare("use")==0){
                    string thing;
                    ss >> thing;
                    print(thing + "\n"); //debug
                    main->current = main->main.useItem(thing,scrbuff); 
                }else if(cmd.compare("shout")==0){
                    string sentence;
                    std::getline(ss,sentence);
                    print(sentence + "\n");
                } else if (cmd.compare("drop")==0){
                    std::string item;
                    ss >> item;
                    bool found = false;

                    for(auto& x:main->main.bag){
                        if(x.name == item){
                            main->main.delItem(x,scrbuff);
                            break;
                        }
                    }
                } else {
                    print("\033[91mGame: " + cmd + " is not an Action\n");
                }
                print("\n");
            }
        }

};

#endif