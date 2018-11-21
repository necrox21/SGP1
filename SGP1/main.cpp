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

using namespace std;

void Affichage(list<int> L);

int tubes[4][2];
int processus[2];
list<int> Liste = {9,5,7,5,6,2,1};
list<int> Liste1;
list<int> Liste2;
list<int> EchangeS;
list<int> EchangeT;


int Separator()
{

    auto middle = next( Liste.begin(), Liste.size() / 2 +1 );
    Liste1= list<int>( Liste.begin(), middle );
    Liste2= list<int>( middle, Liste.end() );
}


void Affichage(list<int> L)
{
    for (const auto &l : L ) 
        cout << l << ' ';
}

int main(int argc, char** argv) {
    pipe(tubes[0]);
    pipe(tubes[1]);
    pipe(tubes[2]);
    pipe(tubes[3]);
    Separator();
    pid_t pid1 = fork(); 
    pid_t pid2;
    
    if(pid1!=0)
        pid2 = fork();  
    
    if(pid1==0)//S
    {
        int tmp = -INT_MAX;
        while(processus[0]==0)
        {  
            int pos=0;
            int posReal=0;
            for(const auto &s:Liste1)
            {
                if(s>tmp)
                {
                    tmp = s;
                    pos=posReal;
                }
                posReal++;
            }
            write(tubes[2][1],&tmp,sizeof(tmp));
            list<int>::iterator a = next(Liste1.begin(),pos);
            Liste1.erase(a);
            EchangeS.push_back(tmp);
            read(tubes[3][0],&tmp,sizeof(tmp));
            Liste1.push_back(tmp);
            cout<<"S:";
            Affichage(Liste1);
            cout<<endl;
            sleep(1);
            if(EchangeS.size()>3)
            {
                
                list<int>::iterator i = next(EchangeS.begin(),EchangeS.size()-1);
                list<int>::iterator j = next(EchangeS.begin(),EchangeS.size()-3);
                if(*i==*j)
                {
                    processus[0]=-1;
                }
            }
        }
        for (const auto &l : Liste1 )
        {
            write(tubes[0][1],&l,sizeof(int));
        }
        cout<<"finS"<<endl;
    }
    else if(pid2==0)//T
    {

        int tmp = INT_MAX;
        while(processus[1]==0)
        {
            int pos=0;
            int posReal=0;
            for(const auto &t:Liste2)
            {
                if(t<tmp)
                {
                    tmp = t;
                    pos=posReal;
                }
                posReal++;
            }
            write(tubes[3][1],&tmp,sizeof(tmp));
            list<int>::iterator a = next(Liste2.begin(),pos);    
            Liste2.erase(a);
            EchangeT.push_back(tmp);
            read(tubes[2][0],&tmp,sizeof(tmp));
            Liste2.push_back(tmp);
            cout<<"T:";
            Affichage(Liste2);
            cout<<endl;
            cout<<endl;
            sleep(1);
            if(EchangeT.size()>3)
            {
                list<int>::iterator i = next(EchangeS.begin(),EchangeS.size()-1);
                list<int>::iterator j = next(EchangeS.begin(),EchangeS.size()-3);
                if(*i==*j)
                {
                    processus[1]=-1;
                }
            }
        }
        for (const auto &l : Liste2 )
        {
            write(tubes[1][1],&l,sizeof(int));
        }
        cout<<"finT"<<endl;
    }
    else//Pere
    {   
        Affichage(Liste1);
        Affichage(Liste2);
        cout<<endl;
        cout<<endl;
        int res;
        Liste.clear();
        for(int i = 0;i<Liste1.size();i++)
        {
        read(tubes[0][0],&res,sizeof(int));
        Liste.push_back(res);
        }
        for(int i = 0;i<Liste2.size();i++)
        {
        read(tubes[1][0],&res,sizeof(int));
        Liste.push_back(res);
        }
        Affichage(Liste);
        //read(tubes[1][0],&Liste2,sizeof(Liste2));
    }
    return 0;
}

