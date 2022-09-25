#include <iostream>
#include <cstring>

int main()
{
    char input[10];
    int num_zeros;
    std::cout << "Input a Number: ";
    std::cin >> input;
    for(int i; i < 10; i++)
    {
        if(input[i] == 0)
        {
            num_zeros++;
        }
    }
    std::cout << num_zeros;
}