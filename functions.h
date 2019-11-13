#ifndef KRYPTO1_FUNCTIONS_H
#define KRYPTO1_FUNCTIONS_H

#include <iostream>
#include <vector>

struct rep {
    int row_int;
    std::vector <bool> row_bin;
    int column_int;
    std::vector <bool> column_bin;
};

void edit_base_vector(std::vector<bool>& vec, int blocks_number);
void print_block(const std::vector< std::vector <bool> >& vec, int block_number);
int get_blocks_number(const std::vector<bool>& vec);
void print_vector(const std::vector<bool>& vec);
void separate_into_blocks(std::vector<bool> base_vec, std::vector< std::vector<bool> >& blocks);
void initial_permutation(std::vector< std::vector<bool> >& vec, int block_number);                  // part of DES algorithm
void DES_algorithm(std::vector< std::vector <bool> >&, std::vector<bool>& key, int number_of_blocks);                        // takes in vector of "blocks"
void round(std::vector <bool>& left_key, std::vector <bool>& right_key, std::vector <bool>& left_vec, std::vector <bool>& right_vec, std::vector <bool>& short_key, int round_count);
void rotate_left(std::vector <bool>& vec);
void mk_half_vector(std::vector< std::vector <bool> > base_vec, std::vector <bool>& half_vec, int start_point, int block_number);
void mk_half_key(std::vector<bool> base_vec, std::vector <bool>& half_vec, int start_point);
void expansion_permutation(std::vector<bool>& vec);
void reduce_and_permute_choice1(std::vector<bool>& key);
void reduce_and_permute_choice2(std::vector <bool>& vec);
void vectors_XOR(std::vector <bool>& vec1, std::vector <bool>& vec2);
void bin_to_int(rep &box);
void int_to_bin(rep &box, std::vector <bool>& vec, int s_box_number);
void s_box(std::vector <bool>& vec);
void post_box_permutation(std::vector <bool>& vec);
void combine_halves(std::vector <std::vector <bool> >& vec, std::vector <bool>& left_vec, std::vector <bool>& right_vec, int block_number);
void final_permutation(std::vector <std::vector <bool> >& vec, int block_number);

#endif //KRYPTO1_FUNCTIONS_H