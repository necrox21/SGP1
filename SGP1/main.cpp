/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: bt479917
 *
 * Created on 21 novembre 2018, 12:12
 */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <list>
#include <limits.h>
#include <vector>

using namespace std;

int tubes[2][2];
int procesus[2];
vector<int> tab{1,8,6,9,8,6,2,4,9};
vector<int> tabS;
vector<int> tabT;

int S()
{
    return 0;
}

int T()
{
    return 0;
}

int Separator()
{
    int size = tab.size()/2+tab.size()%2;
    int i = 0;
    for(auto &r : tab)
    {
        if(i<size)
        {
            tabS.push_back(r);
        }
        else
            tabT.push_back(r);
        
        i++;
    }
    return 0;

}

void Affichage(vector<int> res)
{
    for(auto &r : res)
    {
        cout<<r<<" ";
    }
    cout<<endl;
}
int main(int argc, char** argv) {
    Affichage(tab);
    Separator();
    return 0;
}


