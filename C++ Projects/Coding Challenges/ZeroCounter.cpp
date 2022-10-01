#include <iostream>
#include <cstring>

using namespace std;

int main()
{
    string input;
    int num_zeros = 0;
    std::cout << "Input a Number: ";
    std::cin >> input;
    int n = input.length();
    char array[n+1];
    strcpy(array, input.c_str());
    for(int i; i < n; i++)
    {
        if(array[i] == '0')
        {
            num_zeros++;
        }
    }
    std::cout << num_zeros;
    std::cout << "\n";
    return 0;
}