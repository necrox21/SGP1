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

int tubes[2][2];
int procesus[2];
list<int> Liste = {9,6,3,7,5,4,8};
list<int> Liste1;
list<int> Liste2;

int S()
{
    pipe(tubes[0]);
    int tmp=INT_MAX;
    while(procesus[0]==0)
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
    while(procesus[1]==0)
    {

    }
    return 0;
}

int Separator()
{

    auto middle = next( Liste.begin(), Liste.size() / 2 +1 );

    Liste1= list<int>( Liste.begin(), middle );

    Liste2= list<int>( middle, Liste.end() );

    Affichage(Liste1);
    Affichage(Liste2);

}

void Affichage(list<int> L)
{
    for (const auto &l : L ) 
        cout << l << ' ';
    cout << endl;
}

int main(int argc, char** argv) {
    Separator();
    //S();
    //T();
    return 0;
}

