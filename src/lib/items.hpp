#ifndef ITEMS_HPP
#define ITEMS_HPP

#include <string>
#include <utility>
#include <iostream>

using std::string;

struct item{
    string name,desc; //name and description of an item
    int amt; //item amount

    bool isKey,isObj,isConsumable; //identifier on what type of item, if key type, interactible object or consumable
    item(const string& x = "",const string& y = "",const bool& isKey = false,const bool& isObj = false,const bool& isCons = false,const int& amt = 1) : name(x),desc(y),isKey(isKey),isObj(isObj),isConsumable(isCons),amt(amt){} //initialize item

    //define conditional operators for item =D
    bool operator==(const item& other) const{ //equal to opeerator
        return name == other.name && amt == other.amt;
    }

    bool operator<(const item& other) const{ //lesser 
        return amt < other.amt;
    }

    bool operator>(const item& other) const{ //greater
        return amt > other.amt;
    }

    bool operator>=(const item& other) const{ //greater than or equal to
        return amt >= other.amt;
    }

    bool operator<=(const item& other) const{ //lesser than or equal to
        return amt <= other.amt;
    }
};

#endif