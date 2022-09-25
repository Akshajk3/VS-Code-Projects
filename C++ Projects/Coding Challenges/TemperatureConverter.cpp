#include <iostream>

int main()
{
    int tempf;
    std::cout << "What is the temperatuer in C: ";
    std::cin >> tempf;
    float tempc = (tempf * 1.8) + 32;
    std::cout << "The temperature in F is ";
    std::cout << tempc;
    std::cout << "\n";

    return 0;
}