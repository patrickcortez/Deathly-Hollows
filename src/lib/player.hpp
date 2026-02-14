#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <iostream>
#include <memory>

#include "items.hpp"
#include "inventory.hpp"

using std::string;
using std::make_unique;

class Player{


string name,desc; //player description and name
int hp;

public:

inventory main;
item* current = nullptr;

Player(string& x,string& y,int z) : name(x),desc(y),hp(z){} //initialize player

void setHP(int& amt,char& ops);

string getname(){
    return this->name; //return player name
}

string getdesc(){
    return this->desc; //return player description
}

int getHP(){
    return this->hp;
}
};

void Player::setHP(int& amt,char& ops){

    switch(ops){
        case '+': //heal player
            this->hp += amt;
        break;
        case '-': //damage
            this->hp -= amt;
        break;
        default: //error if ops not found
            std::cerr << "\033[92m" << "operation not found!\n";
        break;
    }
    
}

#endif