#pragma once 

#include <iostream>
#include <string>
#include <cstring>

class Fabric
{
public:
    virtual std::string getTypeOf() = 0;
    virtual std::string allToString() = 0;
};
