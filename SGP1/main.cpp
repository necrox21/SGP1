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

int S(vector<int> *tabS,int tubes[][2])
{
    int envoi = -1;
    int lecture = -1;
    int posS;
    vector<int> echangeS;
    while(true)
    {
        posS = PosMax(*tabS);
        envoi = tabS->at(posS);
        tabS->erase(tabS->begin()+posS);
        write(tubes[2][1],&envoi,sizeof(int));
        cout<<"S envoi :"<<envoi<<endl;
        echangeS.push_back(envoi);
        read(tubes[3][0],&lecture,sizeof(int));
        cout<<"S lit :"<<lecture<<endl;
        tabS->push_back(lecture);
        if(echangeS.size()>2)
        {
           if(echangeS[echangeS.size()-1]==echangeS[echangeS.size()-3])
           {   
               int final = tabS->size();
               write(tubes[0][1],&final,sizeof(int));
               for(int i=0;i<tabS->size();i++)
               {
                   final = tabS->at(i);
                   write(tubes[0][1],&final,sizeof(int));
               }
               return 0;
           }
        }
    }
    return -1;
}

int T(vector<int> *tabT,int tubes[][2])
{
    int envoi = -1;
    int lecture = -1;
    int posT;
    vector<int> echangeT;
    while(true)
    {
        posT = PosMin(*tabT);
        envoi = tabT->at(posT);
        tabT->erase(tabT->begin()+posT);
        write(tubes[3][1],&envoi,sizeof(int));
        cout<<"T envoi :"<<envoi<<endl;
        echangeT.push_back(envoi);
        read(tubes[2][0],&lecture,sizeof(int));
        cout<<"T lit :"<<lecture<<endl;
        tabT->push_back(lecture);
        if(echangeT.size()>2)
        {
           if(echangeT[echangeT.size()-1]==echangeT[echangeT.size()-3])
           {
               int final = tabT->size();
               write(tubes[1][1],&final,sizeof(int));
               for(int i=0;i<tabT->size();i++)
               {
                   final = tabT->at(i);
                   write(tubes[1][1],&final,sizeof(int));
               }
               return 0;
           }
        }
    }
    return -1;
}

void Affichage(vector<int> res)
{
    for(auto &r : res)
    {
        cout<<r<<" ";
    }
    cout<<endl<<endl;
}
int main(int argc, char** argv) {
    vector<int> *tab= new vector<int>();
    tab->insert(tab->end(),{1,8,6,9,8,6,2,4,9});
    
    vector<int> *tabS = new vector<int>();
    vector<int> *tabT = new vector<int>();
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
    
    Affichage(*tab);
    Separator(tab,tabS,tabT);
    Affichage(*tabS);
    Affichage(*tabT);
    
    pid_t pidS = fork();
    pid_t pidT =-1;
    
    if(pidS != 0)
         pidT = fork();
    
    
    /*TesMoche(tabS,tabT);*/
    
    if(pidS == 0)
    {
        //Affichage(*tabS);
        S(tabS,tubes);
    }
    else if (pidT == 0)
    {
        //Affichage(*tabT);
        T(tabT,tubes);
    }
    else
    {
       /* Union(tab,tabS,tabT);
        Affichage(*tab);*/

        read(tubes[0][0],&size1,sizeof(int));

        read(tubes[1][0],&size2,sizeof(int));

        tabS->clear();

        for(int i = 0;i<size1-1;i++)
        {
            read(tubes[0][0],&lecture1,sizeof(int));
            tabS->push_back(lecture1);
        }
                tabT->clear();
        for(int i = 0;i<size2-1;i++)
        {
            read(tubes[1][0],&lecture2,sizeof(int));
            tabT->push_back(lecture2);
        }

        Union(tab,tabS,tabT);
        Affichage(*tab);
    }
    return 0;
}


