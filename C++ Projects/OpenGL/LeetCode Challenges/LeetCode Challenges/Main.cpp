#include <iostream>
#include <string>

class Solution {
public:
    char nextGreatestLetter(char letters[], char target) {
        for(char character : letters)
        {
            if (target < character)
            {
                return(character);
            }
        }

        return(letters[0]);
    }
};