#ifndef KRYPTO1_FUNCTIONS_H
#define KRYPTO1_FUNCTIONS_H

#include <iostream>
#include <vector>

void edit_base_vector(std::vector<bool>& vec, int blocks_number);
int get_blocks_number(const std::vector<bool>& vec);
void print_vector(const std::vector<bool>& vec);
void separate_into_blocks(std::vector<bool>& base_vec, std::vector< std::vector<bool> >& blocks);
//void initial_permutation(std::vector<bool>& vec);

#endif //KRYPTO1_FUNCTIONS_H
