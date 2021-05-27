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

#include <stdio.h>

using namespace std;

class Core{
public:
        Core();
        Core(istream& );
        string name() const;
        istream& read(istream&);
        double grade() const;

protected:
        istream& read_common(istream&);
        double midterm, final;
        vector<double> homework;

private:
        string n;    
};

class Grad : public Core {
public:
        Grad();
        Grad(istream&);
        double grade() const;
        istream& read(istream&);

private:
        double thesis;
};

string Core::name() const
{
        return n;
}

double Core::grade() const
{
        //reutrn  ::grade(midterm, final, homework);
}

istream& Core::read_common(istream& in)
{
        in >> n >> midterm >> final;
        return in;
}

istream& Core::read(istream& in)
{
        read_common(in);
       // read_hw(in, homework);
        return in;

}

istream& Grad::read(istream& in)
{
        Core::read_common(in);
        in>>thesis;
       // read_hw(in, homework);
        return in;
        
}
int main(int argc, char ** argv)
{
        return 0;
}