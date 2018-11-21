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

void testS()
{
    pipe(tubes[2]);
    pipe(tubes[3]);

}

void testT()
{
    pipe(tubes[2]);
    pipe(tubes[3]);
   
}

int main(int argc, char** argv) {
    Separator();

    int pid1 = fork();
    int pid2 = fork();


    if(pid1==0)
    {
    testS();
    }
    else if(pid2==0)
    {
    testT();
    }
    else if (pid2!=0 && pid1!=0)
    {
        while(true)
        {}
    Affichage(Liste1);
    Affichage(Liste2);
    }
    return 0;
}

