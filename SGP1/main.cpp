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

int tubes[2][2];
int procesus[2];
list<int> Liste = {9,6,3,7,5,4,8};
list<int> Liste1;
list<int> Liste2;

int S()
{

    return 0;
}

int T()
{
    return 0;
}

int Separator()
{

    auto middle = next( Liste.begin(), Liste.size() / 2 +1 );

    Liste1= list<int>( Liste.begin(), middle );

    Liste2= list<int>( middle, Liste.end() );

    for (const auto &s : Liste1 ) cout << s << ' ';
    cout << endl;

    for (const auto &t : Liste2 ) cout << t << ' ';
    cout << endl;
    return 0;

}

int main(int argc, char** argv) {
    return 0;
}

