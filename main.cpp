#include "functions.h"

using namespace std;

int main()
{
    // manual setup for testing
    bool array[] = {true,false,false,true,true,false,false,true,true,true,true,true,false,true,true,true,true,false,false,true,true,true,false,true,true,false,false,true,true,false};
    // end of manual setup for testing
    vector<bool> plain_text(array, array + sizeof(array) / sizeof(bool) );
    print_vector(plain_text);

    


    return 0;
}