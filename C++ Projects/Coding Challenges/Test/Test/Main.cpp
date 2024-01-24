#include "Map.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    Map m;  // maps ints to strings
    assert(m.empty());
    ValueType v = "Ouch";
    assert( !m.get(42, v)  &&  v == "Ouch"); // v unchanged by get failure
    m.insert(123456789, "Wow!");
    assert(m.size() == 1);
    KeyType k = 9876543;
    assert(m.get(0, k, v)  &&  k == 123456789  &&  v == "Wow!");
    cout << "Passed all tests" << endl;
}















//#include <iostream>
//using namespace std;
//
//// This function searches through str for the character chr.
//// If the chr is found, it returns a pointer into str where
//// the character was first found, otherwise nullptr (not found).
//
//const char* findTheChar(const char* str, char chr)
//{
//    for (int k = 0; *str != 0; k++)
//        if (*(str + k) == chr)
//            return (str + k);
//
//    return nullptr;
//}
//
//int main()
//{
//    const char myString[] = "Hello, World!";
//    char searchChar = 'l';
//
//    const char* result = findTheChar(myString, searchChar);
//    
//    cout << result << endl;
//
//    if (result != nullptr)
//    {
//        std::cout << "Character '" << searchChar << "' found at position: " << result - myString << std::endl;
//    }
//    else
//    {
//        std::cout << "Character '" << searchChar << "' not found in the string." << std::endl;
//    }
//
//    return 0;
//}

// QUESTION 5
/*
 #include <cstdint>
 #include <iostream>

 using namespace std;

 void removeS(char* message)
 {
     size_t len = strlen(message);
     int writeIndex = 0;
     
     for(int i = 0; i < len; i++)
     {
         if(message[i] != 'S' && message[i] != 's')
         {
             message[writeIndex] = message[i];
             writeIndex++;
         }
     }
     
     message[writeIndex] = '\0';
 }

 int main()
 {
     char msg[50] = "She'll blossom like a massless princess.";
     removeS(msg);
     cout << msg << endl;  // prints   he'll bloom like a male prince.
 }
 */

// QUESTION 3

/*
#include <cstdint>
#include <iostream>

using namespace std;

double mean(const double* scores, int numScores)
{
    const double* ptr = scores;
    int tot = 0;
    for(int i = 0; i < numScores; i++)
    {
        tot += ptr[i];
    }
    return tot/numScores;
}

int main()
{
    double scores[] = {20.2, 15.5, 18.0, 22.8, 25.3};
    int numScores = 5;
    double x = mean(scores, numScores);
    
    cout << x << endl;
}
 */

// QUESTION 2
/*
 #include <cstdint>
 #include <iostream>

 using namespace std;

 int main()
 {
     double* cat;
     double mouse[5];
     
     cat = &mouse[4];
     
     *cat = 25.0;
     
     *(cat - 1) = 17;
     
     cat -= 3;
     
     cat[1] = 42;
     
     cat[0] = 54;
     
     bool d = cat == &mouse[0];
     
     bool b = *cat == *(cat + 1);
     
     return 0;
 }

 */
