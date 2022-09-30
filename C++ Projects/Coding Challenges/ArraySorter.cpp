#include <iostream>
#include <cstring>
#include <string>

using namespace std;

int main()
{
    string input;
    std::cout << "Input a list of numbers: ";
    std::cin >> input;
    int n = input.length();
    char array[n+1];
    strcpy(array, input.c_str());
    int num = stoi(array);
    int p = 1;
    for(int i; i < n; i++)
    {

    }

}