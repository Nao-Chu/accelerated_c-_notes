#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <cctype>
#include <numeric>
#include <map>
#include <iterator>
#include <iomanip>

using namespace std;

class  Student_info{
private:
        string n;
        double midterm, final;
        vector<double> homework;

public:
        istream& read(istream&);
        double grade() const;
        string name() const { return n; }
        bool valid() const { return !homework.empty();}

public:
        Student_info();
        Student_info(istream&);
};

void read_hw(istream& in, vector<double> hw)
{
}

istream& Student_info::read(istream& in)
{
        in >> n >> midterm >> final ;
        read_hw(in, homework);
        return in;
}

double grade(double m, double f, vector<double> hw)
{
        
}
double Student_info::grade() const
{
        return ::grade(midterm, final, homework);
}

bool compare(const Student_info& x, const Student_info& y)
{
        return x.name() < y.name();
}

Student_info::Student_info() : midterm(0) , final(0)
{

}

Student_info::Student_info(istream& is) 
{
        read(is);
}

int main()
{
        vector<Student_info> students;
        Student_info record;
        string::size_type maxlen = 0;

        while (record.read(cin)) {
                maxlen = max(maxlen, record.name().size());
                students.push_back(record);
        }

        sort(students.begin(), students.end(), compare);

        for (vector<Student_info>::size_type i = 0; 
                i != students.size(); ++i) 
        {
                cout << setw(maxlen + 1) << students[i].name();
                try{
                        double final_grade = students[i].grade();
                        streamsize prec = cout.precision();
                        cout << setprecision(3) << final_grade 
                                 << setprecision(prec) << endl;
                } catch (domain_error e) {
                        cout << e.what() << endl;
                }
        }
        return 0;
}

// Page : 190