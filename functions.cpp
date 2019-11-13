#include "functions.h"
#include <iostream>


void print_vector(const std::vector<bool>& vec)
{
    std::cout << "Content of the vector:  ";
    for (auto && i : vec)
    {
        std::cout << " " << i;
    }
}

void print_block(const std::vector< std::vector <bool> >& vec, int block_number)
{
    std::cout << "\nContent of the block number " << block_number << " :";
    for ( int i = 0; i < 64; i++ )
    {
        std:: cout << " " << vec[block_number][i];
    }
}

int get_blocks_number(const std::vector<bool>& vec)
{
    int size = vec.size(), number = 0;

    do
    {
        size -= 64;
        number++;
    }while(size > 0 );
    return number;
}

void edit_base_vector(std::vector<bool>& vec, int blocks_number)
{
    int last_block_start = (blocks_number - 1) * 64;
    int last_block_count = vec.size() % 64;
    if ( last_block_count == 0 ) return;
    else
    {
        last_block_start = last_block_start + last_block_count;
        while( last_block_start % 64 != 0 )
        {
            vec.push_back(false);
            last_block_start++;
        }
    }
}

void separate_into_blocks(std::vector<bool> base_vec, std::vector< std::vector<bool> >& blocks)
{
    int len = base_vec.size();
    for ( int i = 0; i < len; i++)
    {
        blocks[i / 64].push_back(base_vec[i]);
    }
}

void initial_permutation(std::vector< std::vector <bool> >& vec, int block_number)
{
    int swap_positions[64] = {58, 50, 42, 34, 26, 18, 10, 2,
                              60, 52, 44, 36, 28, 20, 12, 4,
                              62, 54, 46, 38, 30, 22, 14, 6,
                              64, 56, 48, 40, 32, 24, 16, 8,
                              57, 49, 41, 33, 25, 17, 9, 1,
                              59, 51, 43, 35, 27, 19, 11, 3,
                              61, 53, 45, 37, 29, 21, 13, 5,
                              63, 55, 47, 39, 31, 23, 15, 7};
    std::vector<bool> tmp_vec = vec[block_number];

    for( int i = 0; i < 64; i++)
    {
        vec[block_number][i] = tmp_vec [swap_positions[i] - 1];
    }
}

void DES_algorithm(std::vector< std::vector <bool> >& vec, std::vector<bool>& key, int number_of_blocks)
{
    reduce_and_permute_choice1(key);
    std::vector<bool> left_key(28), right_key(28);
    mk_half_key(key, left_key, 0);
    mk_half_key(key, right_key, 28);

    for ( int block_number = 0; block_number < number_of_blocks; block_number++ )
    {
        initial_permutation(vec, block_number);
        std::vector <bool> left_vec(32);
        std::vector <bool> right_vec(32);
        mk_half_vector(vec, left_vec, 0, block_number);         // splitting vector in half for the algorithm
        mk_half_vector(vec, right_vec, 32, block_number);       // splitting vector in half for the algorithm

        // from here it will be in round function
        for (int round_count = 1; round_count < 17; round_count++)             // do the 16 rounds
        {
            std::vector <bool> short_key;
            round(left_key, right_key, left_vec, right_vec, short_key, round_count);
        }

        combine_halves(vec, left_vec, right_vec, block_number);     // combining left and right part swapped
        final_permutation(vec, block_number);                              // inverse initial permutation

    }
}

void round(std::vector <bool>& left_key, std::vector <bool>& right_key, std::vector <bool>& left_vec, std::vector <bool>& right_vec, std::vector <bool>& short_key, int round_count)
{
    if (round_count == 1 || round_count == 2 || round_count == 9 || round_count == 16 )     // rotate left 1 or 2 depending on the round number
    {
        rotate_left(left_key);
        rotate_left(right_key);
    }
    else
    {
        for (int i = 0; i < 2; ++i)
        {
            rotate_left(left_key);
            rotate_left(right_key);
        }
    }

    std::vector <bool> right_vec_copy = right_vec;                              // creating copy to save right side for next iteration, copy is eddited
    right_vec_copy.resize(48);                                         // resize copy for the expansion permutation
    short_key.insert(short_key.end(), left_key.begin(), left_key.end());        // combining left and right
    short_key.insert(short_key.end(), right_key.begin(), right_key.end());      // part of the key into one
    reduce_and_permute_choice2(short_key);                                  // permute 2 and reduction to 48 elements
    expansion_permutation(right_vec_copy);                                  // expansion permutation
    vectors_XOR(right_vec_copy, short_key);                             // xor right side and key, we use right side for next steps
    s_box(right_vec_copy);                                                  // doing the s-boxes
    post_box_permutation(right_vec_copy);                                   // permutation after doing xbox
    vectors_XOR(right_vec_copy, left_vec);                              // xor of changed right part of plain txt and left part
    left_vec = right_vec;                                                       // assignment of vectors for the next round
    right_vec = right_vec_copy;                                                 // assignment of vectors for the next round
                                                                                // no need to change anything in keys
}

void rotate_left(std::vector <bool>& vec)
{
    vec.push_back(vec[0]);
    vec.erase(vec.begin());
}

void mk_half_vector(std::vector< std::vector <bool> > base_vec, std::vector <bool>& half_vec, int start_point, int block_number)
{
    for( int i = 0; i < 32; i++ )
    {
        half_vec[i] = base_vec[block_number][i + start_point];
    }
}

void mk_half_key(std::vector<bool> base_vec, std::vector <bool>& half_vec, int start_point)
{
    for( int i = 0; i < 28; i++ )
    {
        half_vec[i] = base_vec[i + start_point];
    }
}

void expansion_permutation(std::vector <bool>& vec)
{
    int positions[48] = {32,  1,  2,  3,  4,  5,
                         4,   5,  6,  7,  8,  9,
                         8,   9, 10, 11, 12, 13,
                         12, 13, 14, 15, 16, 17,
                         16, 17, 18, 19, 20, 21,
                         20, 21, 22, 23, 24, 25,
                         24, 25, 26, 27, 28, 29,
                         28, 29, 30, 31, 32, 1};

    std::vector <bool> tmp_vec = vec;

    for ( int i = 0; i < 48; i++ )
    {
        vec[i] = tmp_vec[positions[i]];
    }
}

void reduce_and_permute_choice1(std::vector <bool>& key)
{
    for ( int position = 7; position < 64; position += 8 )
    {
        key.erase(key.begin() + position);
    }
}

void reduce_and_permute_choice2(std::vector <bool>& vec)
{
    int positions[48] = {14, 17, 11, 24,  1,  5,  3, 28, 15,  6, 21, 10,
                         23, 19, 12,  4, 26,  8, 16,  7, 27, 20, 13,  2,
                         41, 52, 31, 37, 47, 55, 30, 40, 51, 45, 33, 48,
                         44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32};
    std::vector <bool> tmp_vec = vec;
    vec.resize(48);
    for (int i = 0; i < 48; i++ )
    {
        vec[i] = tmp_vec[positions[i]];
    }
}

void vectors_XOR(std::vector <bool>& vec1, std::vector <bool>& vec2)
{
    for (int i = 0; i < vec1.size(); i++)
    {
        vec1[i] = vec1[i] ^ vec2[i];
    }
}

void bin_to_int(rep &box)
{
    int tmp_int_row = 0, tmp_int_column = 0;
    for (int i = 0, pow =1; i > 2; i++, pow << 1 )
    {
        tmp_int_row = tmp_int_row + (pow * box.row_bin[i]);
    }
    for (int i = 0, pow = 1; i > 4; i++, pow << 1 )
    {
        tmp_int_column = tmp_int_column + (pow * box.column_bin[i]);
    }
    box.row_int = tmp_int_row;
    box.column_int = tmp_int_column;
}

void int_to_bin(rep &box, std::vector <bool>& vec, int s_box_number)
{
    std::vector <bool> tmp_vec(4);
    int values[8][4][16] = {{
                                    14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7,
                                    0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8,
                                    4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0,
                                    15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13
                            },
                            {
                                    15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10,
                                    3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5,
                                    0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15,
                                    13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9
                            },


                            {
                                    10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8,
                                    13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1,
                                    13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7,
                                    1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12
                            },
                            {
                                    7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15,
                                    13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9,
                                    10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4,
                                    3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14
                            },
                            {
                                    2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9,
                                    14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6,
                                    4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14,
                                    11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3
                            },
                            {
                                    12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11,
                                    10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8,
                                    9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6,
                                    4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13
                            },
                            {
                                    4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1,
                                    13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6,
                                    1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2,
                                    6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12
                            },
                            {
                                    13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7,
                                    1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2,
                                    7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8,
                                    2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11
                            }};
    int tmp;
    tmp = values[s_box_number][box.row_int][box.column_int];

    int i = 0;
    while (tmp > 0)
    {
        tmp_vec[i] = tmp % 2;
        tmp = tmp / 2;
        i++;
    }
    for ( int j = 0, k = 3; j < 4; j++, k-- )
    {
        vec[j + s_box_number * 4] = tmp_vec[k];
    }
}

void s_box(std::vector <bool>& vec)
{
    std::vector <bool> tmp_vec(32);
    rep box = rep();
    box.row_bin.resize(2);
    box.column_bin.resize(4);
    for (int s_box_number = 0; s_box_number < 8; s_box_number++ )
    {
        box.row_bin[1] = vec[s_box_number * 6];
        box.row_bin[0] = vec[s_box_number * 6 + 5];
        for (int i = 1, j = 5 ; i < 5; i++, j-- )
        {
            box.column_bin[j - 1] = vec[s_box_number * 6 + i];
        }
        bin_to_int(box);
        int_to_bin(box, vec, s_box_number);
    }
    vec.resize(32);
}

void post_box_permutation(std::vector <bool>& vec)
{
    int position[32] = {16, 7 , 20, 21, 29, 12, 28, 17,
                        1, 15, 23, 26, 5, 18, 31, 10,
                        2, 8, 24, 14, 32, 27, 3, 9,
                        19, 13, 30, 6, 22, 11, 4, 25};
    std::vector <bool> tmp_vec(32);
    tmp_vec = vec;
    for ( int i = 0; i < 32; i++ )
    {
        vec[i] = tmp_vec[position[i] - 1];
    }
}

void combine_halves(std::vector <std::vector <bool> >& vec, std::vector <bool>& left_vec, std::vector <bool>& right_vec, int block_number)
{
    for ( int i = 0; i < 32; i++ )
    {
        vec[block_number][i] = right_vec[i];
        vec[block_number][i + 32] = left_vec[i];
    }
}

void final_permutation(std::vector <std::vector <bool> >& vec, int block_number)
{
    int positions[64] = {    40,8,48,16,56,24,64,32,
                             39,7,47,15,55,23,63,31,
                             38,6,46,14,54,22,62,30,
                             37,5,45,13,53,21,61,29,
                             36,4,44,12,52,20,60,28,
                             35,3,43,11,51,19,59,27,
                             34,2,42,10,50,18,58,26,
                             33,1,41,9,49,17,57,25 };
    std::vector <bool> tmp_vec(64);
    tmp_vec = vec[block_number];
    for (int i = 0; i < vec.size(); i++)
    {
        vec[block_number][i] = tmp_vec[positions[i] - 1];
    }
}