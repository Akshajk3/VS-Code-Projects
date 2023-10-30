#include <iostream>

using namespace std;

int main() {
/*    int x=10;
    int y=25;
    int z=x+y; */

    string input_1 = "H-12v-14";
    string input_2 = "H-1v-14";
    string input_3 = "H1v14";
    string input_4 = "H1v4";

    string input = input_1;
    string key = "";
   
    for ( int i = 0; i < input.length( ); i++ ){
        if ( input.at(0) != 'H' || input.at(0) != 'h' )
        {
            cout << "Bad String. Exit Code: -1" << endl;
            return -1;
        }
    }

    return 0;
}