#include "functions.h"

void print_vector(std::vector<bool> vec)
{
    std::cout << "Content of the vector:";
    for ( unsigned int i = 0; i < vec.size(); i++)
    {
        std::cout << " " << vec[i];
    }
}
