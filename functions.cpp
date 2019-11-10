#include "functions.h"



void print_vector(const std::vector<bool>& vec)
{
    std::cout << "Content of the vector:";
    for (auto && i : vec)
    {
        std::cout << " " << i;
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

void separate_into_blocks(std::vector<bool>& base_vec, std::vector< std::vector<bool> >& blocks)
{
    int len = base_vec.size();
    for ( int i = 0; i < len; i++)
    {
        blocks[i / 64].push_back(base_vec[i]);
    }
}

/*void initial_permutation(std::vector<bool>& vec)
{
    for( int i = 0; i < block_number; i++)
    {

    }
}*/