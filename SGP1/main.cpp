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

void Write(int mes,int tubes[2])
{
    write(tubes[1],&mes,sizeof(mes));
}

void Write(vector<int> *mes,int tubes[2])
{
    int fin = mes->size();
    Write(fin,tubes);
    for(int i=0;i<mes->size();i++)
    {
        fin = mes->at(i);
        Write(fin,tubes);
    }
}

int Read(int tubes[2])
{
    int res;
    read(tubes[0],&res,sizeof(res));
    return res;
}

void Read(vector<int> *res,int tubes[2])
{
    int taille = Read(tubes);
    res->clear();
    for(int i=0;i<taille;i++)
    {
        int val = Read(tubes);
        res->push_back(val);
    }
}

int Exchange(vector<int> *e,int tubesE[2],int tubesL[2],int tubesP[2],char type)
{
    int envoi = -1;
    int lecture = -1;
    int pos;
    vector<int> echange;
    bool work = true;
    while(work)
    {
        if(type == 'S'||type == 's')
        {
            pos = PosMax(*e);
        }
        else if(type == 'T'||type == 't')
        {
            pos = PosMin(*e);
        }
        else
        {
            work = false;
        }
        
        envoi = e->at(pos);
        e->erase(e->begin()+pos);
        Write(envoi,tubesE);
        printf("%c envoi : %d\n",type,envoi);
        echange.push_back(envoi);
        lecture = Read(tubesL);
        printf("%c lit : %d\n",type,lecture);
        e->push_back(lecture);
        if(echange.size()>2)
        {
            if(echange[echange.size()-1]==echange[echange.size()-3])
            {
                Write(e,tubesP);
                return 0;
            }
        }
    }
    return -1;
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
    int lecture2;
    
    Affichage(tab);
    Separator(&tab,&tabS,&tabT);
    Affichage(tabS);
    Affichage(tabT);
    
    pid_t pidS = fork();
    pid_t pidT =-1;
    
    if(pidS != 0)
         pidT = fork();
    
        
    if(pidS == 0)
    {
        Exchange(&tabS,tubes[2],tubes[3],tubes[0],'S');
    }
    else if (pidT == 0)
    {
        Exchange(&tabT,tubes[3],tubes[2],tubes[1],'T');
    }
    else
    {

        Read(&tabS,tubes[0]);
        Read(&tabT,tubes[1]);
        Union(&tab,&tabS,&tabT);
        Affichage(tab);
    }
    return 0;
}


