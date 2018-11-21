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

int S()
{
    pipe(tubes[0]);
    int tmp=INT_MAX;
    while(processus[0]==0)
    {
        for (const auto &s : Liste1)
            if(s<tmp)
                tmp = s;

        close(tubes[0][0]);
        write(tubes[0][1],&tmp,sizeof(tmp));
        Liste1.remove(tmp);


        close(tubes[1][1]);
        read(tubes[1][0],&tmp,sizeof(tmp));
        Liste1.push_back(tmp);


    }
    return 0;
}

int T()
{
    pipe(tubes[1]);
    int tmp=-INT_MAX;
    while(processus[1]==0)
    {

    }
    return 0;
}

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

void testS()
{
    pipe(tubes[2]);
    int tmp = INT_MAX;
    processus[0]=0;
    while(processus[0]==0)
    {
        for(const auto &s : Liste1)
        {
            if(s<tmp)
                tmp = s;
        }
        
        close(tubes[2][0]);
        write(tubes[2][1],&tmp,sizeof(tmp));
        Liste1.remove(tmp);
        tmp = atoi("null");
        while(tmp == atoi("null"))
        {
            close(tubes[2][1]);
            read(tubes[2][0],&tmp,sizeof(tmp));
            cout<<"S: "<<tmp<<endl;
        }
        Liste1.push_back(tmp);
        
    }
}

void testT()
{
    pipe(tubes[3]);
    int tmp = -INT_MAX;
    
}

int main(int argc, char** argv) {
    Separator();
    Affichage(Liste1);
    Affichage(Liste2);
    testS();
    return 0;
}

