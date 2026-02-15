#ifndef INVENTORY_HPP
#define INVENTORY_HPP

//standard headers

#include <iostream>
#include <vector>

//My headers 
#include "items.hpp"
#include "utility.hpp"

struct inventory{ //self explenatory like sybau bro -_-
        std::vector<item> bag;
        int limit = 10; //inv size


        bool addItem(item& thing){
            if(this->bag.size() < limit){ //if not full then store
                this->bag.push_back(thing);
                return true; //report success
            }else{ //if player inven is at full size then we warn and dont store
                std::cout << "\033[92m" << "Your bag is at full capacity\n";
                return false; //report failure
            }
        }

        item* useItem( const string& target){ //to set the current item of the plager
            bool found = false;
            for(item x: bag){ //for each until we find the desired item by name
                if(target == x.name){
                    found = true;
                    return &x; //if found we return 
                    break;
                }
            }

            if(found == false){ //if not then we warn the player
                std::cout << "\033[91m" << target << " Not found in bag!\n";
            }
        }

        void displayItems(){ //display items of the player

            std::cout << "Bag:\n";

            for(const auto& x: bag){ //for each, so we can loop through all the contents of the vector
                std::cout << x.name << "|" << x.amt <<"\n";
            }
        }

        bool delItem(item& thing){ //delete item from fukin inven gives player freedom
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