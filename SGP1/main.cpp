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
list<int> Liste = {9,6,3,7,5,4,8};
list<int> Liste1;
list<int> Liste2;

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
    cout << endl;
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
    
    if(pid1==0)
    {
        cout<<"S"<<endl;
        int tmp = -INT_MAX;
        for(const auto &s:Liste1)
        {
            if(s>tmp)
            {
                tmp = s;
            }
        }
        cout<<tmp<<endl;
        //write()
        
    }
    else if(pid2==0)
    {
        cout<<"T"<<endl;
        int tmp = INT_MAX;
        for(const auto &t:Liste1)
        {
            if(t<tmp)
            {
                tmp = t;
            }
        }
        cout<<tmp<<endl;
    }
     else
    {   
        Affichage(Liste1);
        Affichage(Liste2);
    
        int res;
        read(tubes[0][0],&res,sizeof(res));
    }
    return 0;
}

