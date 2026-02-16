#ifndef ROOMS_HPP
#define ROOMS_HPP

//standard headers
#include <string>
#include <vector>
#include <utility>

//my headers
#include "items.hpp"
#include "inventory.hpp"

//map size, 64x64 by default
enum MapSize{
    X=64,
    Y=64
};

struct tile{
    std::string name,desc; //name and desc of tile
    std::vector<item> loot;
    //directions to nav
    tile* North;
    tile* South;
    tile* East;
    tile* West;
    std::pair<int,int> coords; //store coords in a int pair(utility)

    tile(const std::string& name,const std::string& desc) : name(name),desc(desc){
        North = nullptr;
        South = nullptr;
        East =  nullptr;    
        West =  nullptr; 
    }

    void setCoord(const int& X,const int& Y){ //set coordinates of a tile
        if((X >=0 && Y >= 0) && (X <= MapSize::X && Y <= MapSize::Y)){  //make sure coords is not in negatives and over the mapsize
            this->coords = {X,Y};
        }
    }

    void CreateTile (tile* N = nullptr,tile* S = nullptr,tile* E = nullptr,tile* W = nullptr) { //Construtor that inits the tile and sets if a direction is null or not
        if(N != nullptr){
            N->coords = this->coords;
            N->coords.second += 1;
            this->North = N;
            
        }

        if(S != nullptr){
            S->coords = this->coords;
            S->coords.second -= 1;
            this->South = S;
        }

        if(E != nullptr){
            E->coords = this->coords;
            E->coords.first -= 1;
            this->East = E;
        }

        if(W != nullptr){
            W->coords = this->coords;
            W->coords.first += 1;
            this->West = W;
        }
    }

    void addLoot(item& xloot){ //add items to tile for player to pick up
        this->loot.push_back(xloot);
    }

    void remLoot(const item& xloot){ //remove tile once the player picks up the item

        for(auto& x: loot){
            if(x == xloot && x.amt > 0){
                x.amt -= 1; //remove 1 amount from the given item

                if(x.amt == 0){ //if amount is 0 then we remove the item from the vector
                    this->loot.erase(find(loot.begin(),loot.end(),xloot));
                    return;
                }
                return;
            }
        }
    }

    void giveLoot(inventory& bag,std::string& xloot,const int& amt){
        bool found = false;
        for(auto& x: loot){
            if(x.name == xloot && x.amt > 0){

                if(amt > x.amt){
                    std::cout << "You can't have that much";
                    return;
                }

                found = true;
                item newOne = x; //create new instance to store the fkin
                newOne.amt = amt;
                if( bag.addItem(newOne)){
                    remLoot(x);
                    return;
                }
            }            
        }

            if(found == false){
                std::cout << xloot << " Doesnt Exist!\n";
            }
    }
    

    void displayLoot(){ //display loot in current tile
        std::cout << "Items around the room: \n";
        for(const auto& x:loot){
            std::cout << x.name << "|" << x.amt << "\n";
        }
    }
};

class Map{ //game map T_T this took alot of thinking
    public:
        tile* tiles[MapSize::X][MapSize::Y] = {nullptr}; //64x64 2d array for map

    std::pair<int,int> getMapSize(){
        return {MapSize::X,MapSize::Y};
    }

    

    void fillMap(tile* origin){
        if(origin == nullptr){
            return;
        }

        //return if the coords is less than 0 or over map limit to avoid seg fault
        if(origin->coords.first < 0 || origin->coords.first > MapSize::X
        || origin->coords.second < 0 || origin->coords.second > MapSize::Y){
            return; //return if 
        }

        //also return if the coord is alread on the 2D array
        if(tiles[origin->coords.first][origin->coords.second] != nullptr){
            return;
        }

        this->tiles[origin->coords.first][origin->coords.second] =  origin; //save the current tile in the 2d array with its coords

        //recurse to fill the entire 2d array
        fillMap(origin->North);
        fillMap(origin->South);
        fillMap(origin->East);
        fillMap(origin->West);
    }
    

};

#endif