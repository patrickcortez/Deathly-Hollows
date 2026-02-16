#ifndef UTILITY_HPP
#define UTILITY_HPP





template <class tl,typename T>
    tl find(tl first,tl end,T& value){ //get first and last elem
        for(;first != end;++first){ //iterate through the entire container 0(n)
            if(*first == value){ //if found return
                return first;
            }
        }
            return end;
    }

template <class tl,typename T>
    bool isPresent(tl first,tl end,T& value){
        for(;first != end;++first){
            if(*first == value){
                return true;
            }
        }
        return false;
    }

#endif