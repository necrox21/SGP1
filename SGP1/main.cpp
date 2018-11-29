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


int Separator(vector<int> *tab,vector<int> *tabS,vector<int> *tabT)
{
    int size = tab->size()/2+tab->size()%2;
    int i = 0;
    for(auto &r : *tab)
    {
        if(i<size)
        {
            tabS->push_back(r);
        }
        else
            tabT->push_back(r);
        
        i++;
    }
    return 0;

}

int Union(vector<int> *tab,vector<int> *tabS,vector<int> *tabT)
{
    tab->clear();
    tab->insert(tab->end(),tabS->begin(),tabS->end());
    tab->insert(tab->end(),tabT->begin(),tabT->end());
    return 0;
}


int PosMax(vector<int> tabS)
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

int PosMin(vector<int> tabT)
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
    
void Affichage(vector<int> res)
{
    for(auto &r : res)
    {
        cout<<r<<" ";
    }
    cout<<endl<<endl;
}


int test(vector<int> tab,int tubes[][2])
{
    cout<<tab.at(0)<<endl;
    tab.erase(tab.begin());
    int fin = tab.size();
    write(tubes[0][1],&fin,sizeof(int));
    for(int i = 0;i<fin;i++)
    {
        int envoi = tab.at(i);
        cout<<envoi<<endl<<endl;
        write(tubes[0][1],&envoi,sizeof(int));
    }
    
}


int main(int argc, char** argv) {
    vector<int> tab;
    tab.insert(tab.end(),{1,8,6,9,8,6,2,4,9});
    
    vector<int> tabS;
    vector<int> tabT;
    vector<int> resS;
    vector<int> resT;
    int tubes[4][2];
    pipe(tubes[0]);
    pipe(tubes[1]);
    pipe(tubes[2]);
    pipe(tubes[3]);
    int size1;
    int size2;
    int lecture1;
    
    Affichage(tab);
    Separator(&tab,&tabS,&tabT);
    Affichage(tabS);
    Affichage(tabT);
    
    pid_t pid = fork();
   
    if(pid == 0)
    {
        test(tab,tubes);
    }
    else 
    {
        tab.clear();
        read(tubes[0][0],&size1,sizeof(int));
        
        for(int i=0;i<size1;i++)
        {
            read(tubes[0][0],&lecture1,sizeof(tab));
            tab.push_back(lecture1);
        }
        //cout<<tab.at(0);
        //Affichage(tab);
    }
    return 0;
}


