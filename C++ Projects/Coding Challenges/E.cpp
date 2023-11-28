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
