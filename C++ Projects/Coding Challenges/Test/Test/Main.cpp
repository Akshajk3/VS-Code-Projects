#include <iostream>
#include <fstream>
#include <istream>
#include <string>
#include <cstring>

using namespace std;

int render(int lineLength, istream& inf, ostream& outf)
{
    if (lineLength < 1) return 2;

    string s;
    int counter = 0;
    getline(inf, s);
    cout << s << endl;
    for (char c : s)
    {
        if (!isspace(c))
            counter++;
        if (counter > lineLength)
        {
            return 1;
        }
    }
    return 0;
}

int main()
{
    const int MAX_FILENAME_LENGTH = 100;
    for (;;)
    {
        cout << "Enter input file name (or q to quit): ";
        char filename[MAX_FILENAME_LENGTH];
        cin.getline(filename, MAX_FILENAME_LENGTH);
        if (strcmp(filename, "q") == 0)
            break;
        ifstream infile(filename);
        if (!infile)
        {
            cerr << "Cannot open " << filename << "!" << endl;
            continue;
        }
        cout << "Enter maximum line length: ";
        int len;
        cin >> len;
        cin.ignore(10000, '\n');
        int returnCode = render(len, infile, cout);
        cout << "Return code is " << returnCode << endl;
    }
	return 0;
}
