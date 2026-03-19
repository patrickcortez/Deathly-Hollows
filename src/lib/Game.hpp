#ifndef GAME_HPP
#define GAME_HPP

//standard headers
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <string>

//my headers
#include "player.hpp"
#include "items.hpp"
#include "rooms.hpp"
#include "inventory.hpp"

//for easy access
using std::cout;
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
        

        void init(){
            string name,desc;
            item* none = new item("none","none");
            cout << "\033[93m" << "\t\t[Deathly Hollow]\n";
            cout << "\n Whats your name? "; std::getline(std::cin,name); //get username
            cout << "\n Alittle background? ";std::getline(std::cin,desc);

            main = new Player(name,desc,100); //initialize player
            main->current = none;
        }

        void printHelp(){ //for user convenience
            cout << "\n" << "Actions: \n";
            cout << "\n" << "test - test action\n";
            cout << "leave - exit the game\n";
            cout << "move <location> - move to the desired location\n";
            cout << "display - show the map\n";
            cout << "where - show current coordinates\n";
            cout << "look - show items in the room\n";
            cout << "take - take an item in room\n";
            cout << "use <item> - equip an item\n";
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

        void displayMap(std::pair<int,int>& coords,const int& Xaxis = 0,const int& Yaxis = MapSize::Y){ //for now we only have players coords as the
            bool isDone = false;
            std::pair<int,int> MapSize = world->getMapSize(); //get Map Size

            cout << "--------------------------------------------\n";
            for(int posY = main->coords.second - 2;posY < Yaxis; posY++){
                for(int posX = main->coords.first - 2;posX < Xaxis;posX++){

                 //   std::cout << "PosX: " << posX << " PosY: " << posY << " "; //debug the map display for future bugs and shi

                    if(world->tiles[posX][posY] != nullptr && (posX != coords.first || posY != coords.second)){
                        cout << " "; // if populated we display as space.
                    }else if(posX == coords.first && posY == coords.second){
                        cout << "O"; //display player position
                    }else{
                        cout << "#"; //display null elements as #  to simulate walls or borders
                    }
                }
                cout << "\n"; //new line after a row is done
            }
            std::cout << std::endl;
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
                cout << "\033[91m" << location << " does not exist!\n";
                return;
            }

        }

        void displayTiles(){ //display adjacent tiles to player

            cout << "Nearby Tiles:\n";

            if(current->North != nullptr){
                cout << current->North->name << " | " << current->North->desc << "\n";
            }

            if(current->South != nullptr){
                cout << current->South->name << " | " << current->South->desc << "\n";
            }

            if(current->East != nullptr){
                cout << current->East->name << " | " << current->East->desc << "\n";
            }

            if(current->West != nullptr){
                cout << current->West->name << " | " << current->West->desc << "\n";
            }

            cout << "\n";
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



    public:


        void Main(){
            init(); //initiate start of game
            InitRooms(); //initiate rooms
            string action; //Player action 


            while(isRUnning){ //main game loop
                displayTiles(); //display adjacent tiles so players knows where to travert next
                main->coords = current->coords;
                std::cout << "Item Equipped: " << main->current->name << "\n"; //display current item of player 
                std::cout << "\033[93m" << main->getname() <<  "@" << current->name << ">: "; //prompt
                std::getline(std::cin,action); //player action
                std::stringstream ss(action); //init tokenizer
                string cmd;
                ss >> cmd;
                
                if(cmd.compare("test")==0){
                    std::cout << "Hello From mars, your code is working!\n";
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
                    cout << main->coords.first << "," << main->coords.second << "\n"; //display curr pos to player
                }else if(cmd.compare("inventory")==0){ //display inventory of player
                    main->main.displayItems(); 
                }else if(cmd.compare("look")==0){
                    current->displayLoot();
                }else if(cmd.compare("take")==0){
                    string thing;
                    ss >> thing;
                    current->giveLoot(main->main,thing,1);
                }else if(cmd.compare("use")==0){
                    string thing;
                    ss >> thing;
                    cout << thing << "\n"; //debug
                    main->current = main->main.useItem(thing); 
                }else if(cmd.compare("shout")==0){
                    string sentence;
                    std::getline(ss,sentence);
                    std::cout << sentence << "\n";
                }else{
                    std::cerr << "\033[91mGame: " << cmd << " is not an Action\n";
                }
                cout << "\n";
            }
        }

};

#endif