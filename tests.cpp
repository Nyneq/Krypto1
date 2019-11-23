//
// Created by szkola on 23/11/2019.
//
#include "tests.h"
#include <iostream>

void does_work(bool value)
{
    if( value ) cout << "\nIt works\n";
    else cout << "\n It doesnt work\n";
}

bool array_to_block(bool array[], vector< vector <bool> >& vec)
{
    for( int i = 0; i < 64; i++ )
    {
        if( array[i] != vec[0][i] ) return false;
    }
    return true;
}

bool reduc_perm(vector <bool>& base_key) {return false;}; // not tested
