#pragma once

#include <iostream>
#include "Fabric.hpp"

class Car: public Fabric
{
public:
    Car(std::vector<std::string>res);
    std::string getBrend();
    std::string getModel();
    std::string getStateNum();
    std::string allToString();
    std::string getTypeOf();
private:
    std::string brend;
    std::string model;
    std::string stateNum;
};

Car::Car(std::vector<std::string>res)
{
    brend = res[1];
    model = res[2];
    stateNum = res[3];
}

std::string Car::allToString()
{
    return  getTypeOf() + " " + getBrend()+ " " + getModel() + " " + getStateNum();
}

std::string Car::getBrend()
{
    return brend;
}
std::string Car::getModel()
{
    return model;
}
std::string Car::getStateNum()
{
    return stateNum;
}

std::string Car::getTypeOf()
{
    return "Car";
}
