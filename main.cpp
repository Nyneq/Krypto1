#include "functions.h"

using namespace std;

int main()
{
    // manual setup for testing
    bool array[] = {1,0,0,1,1,1,1,0,1,1,0,0,1,1,1,1,1,0,1,1,0,0,1,0,1,0,1,1,0,0,1,1,1,1,1,1,1,1,0,0,1,1,0,0,1,1,1,0,0,1,1,1,0,0,0,0,1,0,1,1,0,1,0,0,0,1,1,0,0,1,1,1,0,0,1,0,1};
    // end of manual setup for testing
    vector<bool> all_data (array, array + sizeof(array) / sizeof(bool) );   // changing array to vector
    vector< vector <bool> > blocks (get_blocks_number(all_data));                // vector that will contain 64 element vectors
    print_vector(all_data);
    cout << "\n\nSize of vector: " << all_data.size() << endl;
    edit_base_vector(all_data, get_blocks_number(all_data));                //make our vector's length be multiple of 64

    separate_into_blocks(all_data, blocks);                             // splitting all the data into vector that contains vectors of 64 elements



    return 0;
}