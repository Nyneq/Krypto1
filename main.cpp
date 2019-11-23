#include "functions.h"

using namespace std;

int main()
{
    // manual setup for testing
    bool array[] = {0,1,1,0,0,0,0,1,0,1,1,0,0,0,0,1,0,1,1,0,0,0,0,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    vector<bool> base_key = {0,1,1,0,0,0,0,1,0,1,1,0,0,0,0,1,0,1,1,0,0,0,0,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

    // end of manual setup for testing
    vector<bool> all_data (array, array + sizeof(array) / sizeof(bool) );  // changing array to vector

    int number_of_blocks = get_blocks_number(all_data);                         // number of blocks our plain text contains
    vector< vector <bool> > blocks (number_of_blocks);                          // vector that will contain 64 element vectors
    edit_base_vector(all_data, get_blocks_number(all_data));                // make our vector's length be multiple of 64
    separate_into_blocks(all_data, blocks);                                 // splitting all the data into vector that contains vectors of 64 elements

    DES_algorithm(blocks, base_key, number_of_blocks);
    DES_algorithm_decryption(blocks, base_key, number_of_blocks);

    for ( int i = 0; i < 64; i++)
    {
        cout << blocks[0][i] << " " << all_data[i] << endl;
    }

    //Zrob deszyfrowanie, tak samo jak szyfrowanie tylko w roundach kolejność od tyłu i rotujesz w prawo dodatkowo za pierwszym razem nie rotujesz.
    // Zrób rotacje kluczy do deszyfrowania

    return 0;
}