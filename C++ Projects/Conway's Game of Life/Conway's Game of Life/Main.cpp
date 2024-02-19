#include <iostream>
#include <cmath>

float ln(float x, int terms = 100)
{
    float result = 0.0;
    for (int i = 1; i < terms + 1; i++)
    {
        result += (pow((-1), (i - 1))) * pow((x - 1), i) / i;
    }
    return result;
}

int main()
{
    float x = 2.0;
    float result = ln(x);
    std::cout << "The Natural Log of " << x << " is " << result << std::endl;
}