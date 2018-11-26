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
#include <algorithm>

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


int PosMax()
{
    int pos=-1;
    int tmp = -INT_MAX;
    
    for(int i = 0;i<tabS.size();i++)
    {
        if(tabS[i]>tmp)
        {
            tmp = tabS[i];
            pos = i;
        }
    }
    
    return pos;
}

int PosMin()
{
    int pos=-1;
    int tmp = INT_MAX;
    
    for(int i = 0;i<tabT.size();i++)
    {
        if(tabT[i]<tmp)
        {
            tmp = tabT[i];
            pos = i;
        }
    }
    
    return pos;
}


void TesMoche()
{
    bool arrete = false;
    int tmpS=-1;
    int tmpT=-1;
    int posS;
    int posT;
    vector<int> echangeS;
    vector<int> echangeT;
    
    while(!arrete)
    {
        posS = PosMax();
        posT = PosMin();
        
        tmpS = tabT[PosMin()];
        tmpT = tabS[PosMax()];
        tabS.erase(tabS.begin()+posS);
        cout<<"S envoi :"<<tmpT<<endl;
        echangeS.push_back(tmpS);
        tabT.erase(tabT.begin()+posT);
        cout<<"T envoi :"<<tmpS<<endl;
        echangeT.push_back(tmpT);
        tabS.push_back(tmpS);
        tabT.push_back(tmpT);
        cout<<endl;
        if(echangeS.size()>2&&echangeT.size()>2)
        {
           if(echangeS[echangeS.size()-1]==echangeS[echangeS.size()-3]&&echangeT[echangeT.size()-1]==echangeT[echangeT.size()-3])
            arrete=true;
        }
    }
    
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
     Affichage(tabS);
    Affichage(tabT);
    cout<<endl;
    TesMoche();
    Affichage(tabS);
    Affichage(tabT);
    return 0;
}


