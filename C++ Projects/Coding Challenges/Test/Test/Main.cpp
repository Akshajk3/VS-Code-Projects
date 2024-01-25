#include "NewMap.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
     Map a(1000);   // a can hold at most 1000 key/value pairs
     Map b(5);      // b can hold at most 5 key/value pairs
     Map c;         // c can hold at most DEFAULT_MAX_ITEMS key/value pairs
     KeyType k[6] = { "Jack", "Bob", "Joe", "Jill", "Mary", "Anne" };
     ValueType v  = 10;

       // No failures inserting pairs with 5 distinct keys into b
     for (int n = 0; n < 5; n++)
         assert(b.insert(k[n], v));

       // Failure if we try to insert a pair with a sixth distinct key into b
     assert(!b.insert(k[5], v));

       // When two Maps' contents are swapped, their capacities are swapped
       // as well:
     a.swap(b);
     assert(!a.insert(k[5], v)  &&  b.insert(k[5], v));
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
