#pragma once

#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

#include "Keeper.hpp"
#include "Database.hpp"

class Parser
{
public:
    Parser();
    void getQuery(std::string);
    std::vector<std::string> getAns();
    void parseQuery(std::string);
private:
    std::vector<std::string>ans;
    std::vector<std::string>query;
    Keeper k;
    Database db;
};

void Parser::parseQuery(std::string q)
{
    std::string flag;
    flag.clear();
    query.clear();
    for(int i =0 ; i < q.size(); i++)
    {
        if(q[i] == ' ' && flag.size() > 0)
        {
            query.push_back(flag);
            flag.clear();
        }else{
            if(q[i] != ' ')
                flag.push_back(q[i]);
        }
    }
    if(flag.size() > 0)
        query.push_back(flag);
    
}


Parser::Parser()
{
    ans.clear();
}

void Parser::getQuery(std::string q)
{
    ans.clear();
    this->parseQuery(q);

    q = db.doQuery(&k, query);
    
    ans = k.allToString();
    ans.push_back(q);
    std::reverse(ans.begin(), ans.end());
    k.clear();
}

std::vector<std::string> Parser::getAns()
{
    return ans;
}