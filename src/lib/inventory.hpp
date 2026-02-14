#ifndef INVENTORY_HPP
#define INVENTORY_HPP

//standard headers

#include <iostream>
#include <vector>
#include <algorithm>

//My headers 

#include "items.hpp"

struct inventory{ //self explenatory like sybau bro -_-
        std::vector<item> bag;
        int limit = 10; //inv size

        template <class tl,typename T>
        tl find(tl first,tl end,T& value){ //get first and last elem
            for(;first != end;++first){ //iterate through the entire container 0(n)
                if(*first == value){ //if found return
                    return first;
                }
            }
            return end;
        }

        bool addItem(item& thing){
            if(this->bag.size() < limit){ //if not full then store
                this->bag.push_back(thing);
                return true; //report success
            }else{ //if player inven is at full size then we warn and dont store
                std::cout << "\033[92m" << "Your bag is at full capacity\n";
                return false; //report failure
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