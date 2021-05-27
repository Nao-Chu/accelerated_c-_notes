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

#include "main11.hpp"

using namespace std;

class Str{
public:
        typedef Vec<char>::size_type size_type;
        Str() {}
        Str(size_type n, char c) : data (n, c) {}
        Str(const char* cp) {
                copy(cp, cp+strlen(cp), back_inserter(data));
        }
        template<class In> 
        Str(In b, In e) {
                copy(b, e, back_inserter(data));
        }

        char& operator() (size_type i) { return data[i]; }
        const char& operator() (size_type i) const { return data[i]; }
        
        friend istream& operator>> (istream& is, Str& s) ;
        Str& operator+= (const Str& s) {
                copy(s.data.begin(), s.data.end(), back_inserter(data));
                return *this;
        }
        

        size_type size() const { return data.size(); }
private:
        Vec<char> data;
};
ostream& operator<< (ostream& os, const Str& s) 
{
        
}
Str& operator+ (const Str&s, const Str& t)
{
        //Str r = s;
        //r += t;
        //return r;
}

int main(int argc, char ** argv)
{
        char x,y;
        //scanf("%c",&x);
       // scanf("%c",&y);
        //cin.get(x);
        //cin.get(y);
        cin >> x;
        cin >> y;
        cout << x << y << endl;
        return 0;
}
