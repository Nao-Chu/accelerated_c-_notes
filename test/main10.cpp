#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <cctype>
#include <numeric>
#include <map>
#include <iterator>
#include <iomanip>
#include <fstream>
#include <cstring>

using namespace std;

void copyfile()
{
        ifstream infile("in");
        ofstream outfile("out");

        string s;
        while (getline(infile, s))
                outfile << s << endl;
}

int copyfile2(int argc, char ** argv)
{
        int fail_count = 0;
        for (int i = 1; i < argc; ++i) {
                ifstream in(argv[i]);
                if (in) {
                        string s;
                        while (getline(in, s))
                                cout << s << endl;
                } else {
                        cerr << "cannot open file " << argv[i] << endl;
                        ++fail_count;
                }
        }
        return fail_count;
}

char* duplicate_chars(const char* p)
{
        size_t length = strlen(p) + 1;
        char* result = new char(length);
        copy(p, p + length, result);
        return result;
}

int main(int argc, char ** argv)
{
        copyfile();
       int count = copyfile2(argc, argv);

        // return a off-the-end *p of valid and no any mean
        // we can to use it as a delete[] 
       int* p = new int(0);
        return 0;
}

// Page : 209