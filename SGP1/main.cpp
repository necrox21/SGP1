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
#include <wait.h>
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

int testrec(vector<int> *tab,int ppid,vector<int> *test)
{ 
    int status;
    if(tab->size()>1)
    {
        pid_t pid = fork();

        if(pid == 0)
        {
            
            tab->erase(tab->begin());
            testrec(tab,ppid,test);           
        }
        else 
        {   
            
            waitpid(pid,&status,0);
            if(getpid()==ppid)
                Affichage(*tab);
        }
    }
    
    
}

int main(int argc, char** argv) {
    vector<int> tab;
    vector<int> test;
    tab.insert(tab.end(),{1,8,6,9,8,6,2,4,9}); 
    int a = getpid();
    testrec(&tab,a,&test);
    return 0;
}


