#include "functions.h"

using namespace std;

int main()
{
    // manual setup for testing

    bool array[] = {0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0};
    vector<bool> base_key = {0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1};
    vector<bool> all_data (array, array + sizeof(array) / sizeof(bool) );  // changing array to vector
    int number_of_blocks = get_blocks_number(all_data);                         // number of blocks our plain text contains
    vector< vector <bool> > blocks (number_of_blocks);                          // vector that will contain 64 element vectors
    edit_base_vector(all_data, get_blocks_number(all_data));                // make our vector's length be multiple of 64
    separate_into_blocks(all_data, blocks);                              // splitting all the data into vector that contains vectors of 64 elements

    // end of manual setup, it is fine to delete after completing the program

    /*
     * For this to work we need to pass to function DES_algorithm / DES_algorithm_decryption 3 things:
     *      1. "vec" which is vector that contains vectors of 64 boolean type elements, it is necesary to make sure
     *          that every "block" is 64 bits long. If data from file is shorter you need to fill it with zeros (boolean false).
     *      2. "base_key" which is boolean type vector that contains 64 elements that are our key for encryption / decryption,
     *          it is also necesary for the base_key to be 64 bit long, if user gives longer key cut anything past 8th character,
     *          if user gives too short key fill it with zeros (boolean false).
     *      3. "number_of_blocks" which as the name suggests tells us how many blocks our base vector from point 1 has.
     *          If vector of vectors is already prepared you can use vec.size() method to get it.
     */

    DES_algorithm(blocks, base_key, number_of_blocks);
    DES_algorithm_decryption(blocks, base_key, number_of_blocks);


    return 0;
}