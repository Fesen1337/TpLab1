#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "Fabric.hpp"

class Keeper
{
public:
    Keeper();
    void push(Fabric*);
    void clear();
    std::vector<std::string>allToString();
private:
    int size;
    Fabric* els[1000];
};

void Keeper::clear()
{
    for(int i = 0; i < 100; i++)
    {
        els[i] = NULL;
    }
    this -> size = 0;
}

std::vector<std::string> Keeper::allToString()
{
    std::vector<std::string>ans;
    for(int i =0 ; i < 100; i++)
    {
        if(els[i] != NULL)
        {
            ans.push_back(els[i]->allToString());
        }
    }
    return ans;
}

Keeper::Keeper()
{
    this->size = 0;
}

void Keeper::push(Fabric * el)
{
    els[size] = el;
    this->size++;
}
