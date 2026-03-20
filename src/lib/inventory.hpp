#ifndef INVENTORY_HPP
#define INVENTORY_HPP

//standard headers

#include <iostream>
#include <vector>

//My headers 
#include "items.hpp"
#include "utility.hpp"
#include "Cstream.hpp"

struct inventory{ //self explenatory like sybau bro -_-
        std::vector<item> bag;
        int limit = 10; //inv size


        bool addItem(item& thing,HANDLE scrbuff){
            if(this->bag.size() < limit || isPresent(bag.begin(),bag.end(),thing)==true){ //if not full then store

                for(auto& x: bag){ //check if thing already exists in bag
                
                    if(x == thing){
                        x.amt++; //only increment if the item already exists
                        return true; //report success
                    }
                }

                this->bag.push_back(thing); 
                return true;
            }else{ //if player inven is at full size then we warn and dont store
                CS::outp(scrbuff,"\033[92m Your bag is at full capacity\n");
                return false; //report failure
            }
        }

        item* useItem( const string& target,HANDLE scrbuff){ //to set the current item of the plager
            bool found = false;
            for(item& x: this->bag){ //for each until we find the desired item by name
                if(target == x.name && &x != nullptr){
                    found = true;
                    CS::outp(scrbuff,"Item: " + x.name + "\n");
                    return& x; //if found we return 
                    break;
                }
            }

            if(found == false){ //if not then we warn the player
                CS::outp(scrbuff,"\033[91m" + target + " Not found in bag!\n");
            }
        }

        void displayItems(HANDLE scrbuff){ //display items of the player

            CS::outp(scrbuff,"Bag:\n");

            for(const auto& x: bag){ //for each, so we can loop through all the contents of the vector
                CS::outp(scrbuff,x.name + "|" + std::to_string(x.amt) +"\n");
            }
        }

        bool delItem(item& thing,HANDLE scrbuff){ //delete item from fukin inven gives player freedom
            SetConsoleActiveScreenBuffer(scrbuff); //test for redirecting cout to my screen buffer
            if(this->bag.size() == 0){
                std::cout << "\033[92m" << "Your bag is empty!\n";
                return false; 
            }else{ 
                auto pos = find(this->bag.begin(),this->bag.end(),thing); //find desired fuckin item
                this->bag.erase(pos); //erase item from vector
                return true;
            }
        }
};

#endif