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
#include <limits.h>
#include <vector>
#include <algorithm>
#define TAILLE 500
#define MIN 0
#define MAX 100
#define MODE 1

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

void Affichage(vector<int> res,string name)
{
    cout<<name<<" : [";
    for(auto &r : res)
    {
        cout<<" "<<r<<" ";
    }
    cout<<"]\n\n"<<flush;
}

void Write(int mes,int tubes[2])
{
    close(tubes[0]);
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
    close(tubes[1]);
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

int Exchange(vector<int> *e,int tubeE[2],int tubeL[2],int tubeP[2],char type,string c)
{
    int envoi = -1;
    int lecture = -1;
    int pos;
    while(true)
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
            return -1;
        }
        
        envoi = e->at(pos);
       
        Write(envoi,tubeE);
        lecture = Read(tubeL);
        //cout<<c<<" envoi : "<<envoi<<" et lit : "<<lecture<<"\n\n"<<flush;
        
        
        if(((type == 'T'||type == 'T')&&envoi<lecture)||((type == 'S'||type == 's')&&envoi>lecture))
        {
            e->erase(e->begin()+pos);
            e->push_back(lecture);
            
        }
        else
        {
            if(MODE==0)
            {
                Affichage(*e,c);
                Write(e,tubeP);
            }
            else
            {
                Affichage(*e,c);
            }

        return 0;
        }
    }
    return -1;
}

int TriST(vector<int> *tab,int tubeE[2],int tubeL[2],int tubeP[2],char type,string recu)
{
    vector<int> tabS;
    vector<int> tabT;
    Exchange(tab,tubeE,tubeL,tubeP,type,recu);
    if(tab->size()==1)
    {
        Write(tab,tubeP);
    }
    else
    {
        
        Separator(tab,&tabS,&tabT);
        int tubes[4][2];
        pipe(tubes[0]);
        pipe(tubes[1]);
        pipe(tubes[2]);
        pipe(tubes[3]);
        
        pid_t pidS = fork();
        pid_t pidT =-1;

        if(pidS != 0)
             pidT = fork();
                
        if(pidS == 0)
        {
            TriST(&tabS,tubes[2],tubes[3],tubes[0],'S',recu+'S');
        }
        else if (pidT == 0)
        {
            TriST(&tabT,tubes[3],tubes[2],tubes[1],'T',recu+'T');
        }
        else
        {
            Read(&tabS,tubes[0]);
            Read(&tabT,tubes[1]);    
            Union(tab,&tabS,&tabT);
            Write(tab,tubeP);
        }
    }
    
    return -1;
}

int TriST(vector<int> *tab)
{
    vector<int> tabS;
    vector<int> tabT;
    int tubes[4][2];
    pipe(tubes[0]);
    pipe(tubes[1]);
    pipe(tubes[2]);
    pipe(tubes[3]);
    
    Affichage(*tab,"tabTri");
    Separator(tab,&tabS,&tabT);
    
    pid_t pidS = fork();
    pid_t pidT =-1;
    
    if(pidS != 0)
         pidT = fork();
    
        
    if(pidS == 0)
    {
        TriST(&tabS,tubes[2],tubes[3],tubes[0],'S',"S");
    }
    else if (pidT == 0)
    {
        TriST(&tabT,tubes[3],tubes[2],tubes[1],'T',"T");
    }
    else
    {
        Read(&tabS,tubes[0]);
        Read(&tabT,tubes[1]);        
        Union(tab,&tabS,&tabT);
        Affichage(*tab,"tabTriee");
    }
}

int Partition(vector<int> *tab)
{
        vector<int> tabS;
    vector<int> tabT;
    int tubes[4][2];
    pipe(tubes[0]);
    pipe(tubes[1]);
    pipe(tubes[2]);
    pipe(tubes[3]);
    
    Affichage(*tab,"tabPartition");
    Separator(tab,&tabS,&tabT);
    
    pid_t pidS = fork();
    pid_t pidT =-1;
    
    if(pidS != 0)
         pidT = fork();
    
        
    if(pidS == 0)
    {
        Exchange(&tabS,tubes[2],tubes[3],tubes[0],'S',"S");
    }
    else if (pidT == 0)
    {
        Exchange(&tabT,tubes[3],tubes[2],tubes[1],'T',"T");
    }
    else
    {
        Read(&tabS,tubes[0]);
        Read(&tabT,tubes[1]);        
        Union(tab,&tabS,&tabT);
        Affichage(*tab,"tabPartitione");
    }
}

int Aleatoire(int min, int max)
{
 
    return rand()%(max-min+1) + min;
}

int main(int argc, char** argv) {
    srand(time(NULL));
    vector<int> tab;
    if(TAILLE>=2)
    {
        if(MODE!=0)
        {
            for(int i = 0 ; i < TAILLE ; i++)
            {
            int a = Aleatoire(MIN,MAX);
            tab.insert(tab.end(),a);
            }
            TriST(&tab);
        }
        else
        {
            for(int i = 0 ; i < 10 ; i++)
            {
            int a = Aleatoire(MIN,MAX);
            tab.insert(tab.end(),a);
            }
            Partition(&tab);
        }
    }
    return 0;
}


