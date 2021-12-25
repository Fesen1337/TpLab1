#pragma once

#include <vector>

#include "Furniture.hpp"
#include "Car.hpp"
#include "Worker.hpp"

class Creator
{
public:
    Creator();
    Fabric *create(std::vector<std::string>);
private:

};

Creator::Creator()
{

}

Fabric* Creator::create(std::vector<std::string>res)
{
    if(res.size() == 0)
        return NULL;
    
    if(res[0] == "Furniture")
    {
        if(res.size() == 8)
        {
            
            return new Furniture(res);
        }
    }
    if(res[0] == "Car")
    {
        if(res.size() == 4)
        {
            return new Car(res);
        }
    }
    if(res[0] == "Worker")
    {
        if(res.size() == 8)
        {
            return new Worker(res);
        }
    }
    return NULL;
}
