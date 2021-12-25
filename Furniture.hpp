#pragma once

#include <iostream>
#include "Fabric.hpp"

class Furniture: public Fabric
{
public:
    Furniture(std::vector<std::string>res);
    std::string getTypeOf();
    std::string getType();
    std::string getHeight();
    std::string getWidth();
    std::string getDepth();
    std::string getColour();
    std::string getMaterial();
    std::string getCost();
    std::string allToString();
private:
    std::string type;
    std::string height;
    std::string width;
    std::string depth;
    std::string colour;
    std::string material;
    std::string cost;
};

Furniture::Furniture(std::vector<std::string>res)
{
    type = res[1];
    height = res[2];
    width = res[3];
    depth = res[4];
    colour = res[5];
    material = res[6];
    cost = res[7];
}

std::string Furniture::allToString()
{
    return getTypeOf() + " " + getType() + " " + getHeight() + " " + getWidth() + " " + getDepth() + " " + getColour() + " " + getMaterial() + " " + getCost(); 
}

std::string Furniture::getColour()
{
    return colour;
}

std::string Furniture::getCost()
{
    return cost;
}
std::string Furniture::getDepth()
{
    return depth;
}

std::string Furniture::getHeight()
{
    return height;
}

std::string Furniture::getMaterial()
{
    return material;
}

std::string Furniture::getType()
{
    return type;
}

std::string Furniture::getTypeOf()
{
    return "Furniture";
}

std::string Furniture::getWidth()
{
    return width;
}