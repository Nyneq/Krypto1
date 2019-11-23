//
// Created by szkola on 23/11/2019.
//

#ifndef KRYPTO1_TESTS_H
#define KRYPTO1_TESTS_H

#include <vector>

using namespace std;

void does_work(bool value);
bool array_to_block(bool array[], vector< vector <bool> >& vec);
bool reduc_perm(vector <bool>& base_key);

#endif //KRYPTO1_TESTS_H
