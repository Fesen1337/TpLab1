#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cstring>

#include "Keeper.hpp"
#include "Creator.hpp"

class Database
{
public:
    Database();
    bool isGood(std::vector<std::string>&, std::vector<std::string>&);
    std::string doQuery(Keeper*, std::vector<std::string>&);
    void get(Keeper*, std::vector<std::string>&);
    void rm(Keeper*, std::vector<std::string>&);
    std::string add(std::vector<std::string>&);
    void parseLine(std::string q, std::vector<std::string>&ans);
private:
    Creator cr;
};

Database::Database()
{
}

bool Database::isGood(std::vector<std::string>&query, std::vector<std::string>&ans)
{
    bool flag = false;
    for(int i = 1; i < query.size(); i++)
    {
        flag = false;
        for(int j = 0; j < ans.size(); j++)
        {
            if(ans[j] == query[i])
                flag = true;
        }
        if(!flag)
            return 0;
    }
    return 1;
}

void Database::rm(Keeper *k, std::vector<std::string>&query)
{
    std::ifstream in;
    std::ofstream out;

    in.open("data.txt");
    out.open("tmp.txt");

    std::string a;
    std::vector<std::string>ans;
    
    while(getline(in, a))
    {
        ans.clear();
        this->parseLine(a, ans);
        if(this->isGood(query, ans))
        {
            k -> push(cr.create(ans));
        }else{
            out << a << "\n";
        }
    }
    out.close();
    in.close();

    in.open("tmp.txt");
    out.open("data.txt");

    while(getline(in, a))
    {
        out << a << "\n";
    }
    in.close();
    out.close();
    remove("tmp.txt");
}

std::string Database::add(std::vector<std::string>&query)
{
    reverse(query.begin(), query.end());
    query.pop_back();
    reverse(query.begin(), query.end());
    Fabric* ptr = cr.create(query);
    
    std::ofstream out("data.txt", std::ios::app);
    if(ptr != NULL)
    {
        out << ptr->allToString() + "\n";
        return "Line was added";
    }
    return "Invalid input data";
    out.close();
}



void Database::get(Keeper*k, std::vector<std::string>&query)
{
    std::ifstream in;
    in.open("data.txt");
    std::string a;
    std::vector<std::string>ans;
    
    while(getline(in, a))
    {
        ans.clear();
        this->parseLine(a, ans);
        if(this->isGood(query, ans))
        {
            k -> push(cr.create(ans));
        }
    }
    in.close();
}

std::string Database::doQuery(Keeper * k, std::vector<std::string>&query)
{
    std::string commentary;
    if(query.size() == 0)
    {
        commentary = "there is no query";
    }else{
        if(query[0] == "get")
        {   
            commentary = "get result:";
            this->get(k, query);
        }else if(query[0] == "rm")
        {
            commentary = "removed lines:";
            this->rm(k, query);
        }else if(query[0] == "add")
        {
            commentary = this->add(query);
        }else if(query[0] == "info")
        {
            commentary = "";
        }else{
            commentary = "Unknown query";
        }

    }
    return commentary;
}

void Database::parseLine(std::string q, std::vector<std::string>&ans)
{
    std::string flag;
    for(int i =0 ; i < q.size(); i++)
    {
        if(q[i] == ' ' && flag.size() > 0)
        {
            ans.push_back(flag);
            flag.clear();
        }else{
            if(q[i] != ' ')
                flag.push_back(q[i]);
        }
    }
    if(flag.size() > 0)
        ans.push_back(flag);
}
