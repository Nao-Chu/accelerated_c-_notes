#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <cctype>
#include <numeric>

using namespace std;
/*find word*/
bool space(char c)
{
        return isspace(c);
}

bool not_space(char c)
{
        return !isspace(c);
}

vector<string> split(const string& str)
{
        typedef string::const_iterator iter;
        vector<string> ret;

        iter i = str.begin();
        while (i != str.end() ) {
                i = find_if(i, str.end(), not_space);

                iter j = find_if (i, str.end(), space);

                if (i != str.end()) {
                        ret.push_back(string(i,j));
                }

                i = j;
        }
        return ret;
}

/* Rever */
bool is_palidrome(const string& s)
{
        return equal(s.begin(),  s.end(),  s.rbegin());
}

/* URL */
string::const_iterator url_end(string::const_iterator b, string::const_iterator e);

bool not_url_char(char c)
{
        static const string url_ch = "~:/?:@=&$-_.+!*(),'";
        return !( isalnum(c) || 
                        find(url_ch.begin(), url_ch.end(), c)  != url_ch.end( ) );
}

string::const_iterator url_end(string::const_iterator b, string::const_iterator e)
{
        return find_if(b, e, not_url_char);
}

string::const_iterator url_brg(string::const_iterator b, string::const_iterator e)
{
        static const string sep = "://";
        typedef string::const_iterator iter;
        iter i = b;

        while ( (i = search(i, e, sep.begin(), sep.end()) ) != e) {
                if (i != b && i + sep.size() != e) {
                        iter beg = i;
                        while (beg != b && isalpha(beg[-1]))
                                --beg;

                        if ( beg != i && i + sep.size() != e 
                                && !not_url_char(i[sep.size()]))
                                return beg;
                }

                if (i != e)
                        i += sep.size();
        }

        return e;
}

vector<string> find_urls(const string& s)
{
        vector<string> ret;
        typedef string::const_iterator iter;
        iter b = s.begin(),  e = s.end();
        while (b != e) {
                b = url_brg(b,e);
                if (b != e) {
                        iter after = url_end(b,e);
                        ret.push_back(string(b,after));
                        b = after;
                }
                
        }
        return ret;
}

/*Student */
typedef struct Student_info
{
        string name;
        double midterm,final;
        vector<double> homework;
}Student_info;
double median (vector<double>& students);

bool did_all_hw(const Student_info& s)
{
        return find(s.homework.begin(), s.homework.end(), 0)
                        == s.homework.end();
}

istream& read_hw(istream& in,vector<double>& hw)
{
        if (in) {
                hw.clear();

                double x;
                while (in >> x)
                        hw.push_back(x);
                in.clear();
        }
        return in;
}

istream& read(istream& is,Student_info& s)
{
        is >> s.name >> s.midterm >> s.final;

        read_hw(is, s.homework);
        return is;
}

double grade(double midterm, double final, double homework)
{
        return 0.2 * midterm + 0.4 * final + 0.4 * homework;
}

double grade(double midterm, double final, vector<double>& hw)
{
        if (hw.size() == 0)
                throw domain_error("student has done no homework");
        return grade(midterm, final, median(hw));
}

double grade(Student_info&s)
{
        return grade(s.midterm, s.final, s.homework);
}

double grade_aux(Student_info& s)
{
        try {
                return grade(s);
        } catch (domain_error) {
                return grade(s.midterm, s.final, 0);
        }
}

double median (vector<double>& students)
{
        typedef vector<double>::size_type vec_sz;

        vec_sz size = students.size();

        if (size == 0) 
                throw domain_error("median of an empty vector");

        sort (students.begin(), students.end());

        vec_sz mid = size / 2;
        return size % 2 == 0 ? (students[mid] + students[mid-1] / 2) : students[mid];
}

double median_analysis(vector<Student_info>& students)
{
        vector<double> grades;

        transform(students.begin(), students.end(),
                        back_inserter(grades),grade_aux);

        return median(grades);
}

double average (vector<double>& v)
{
        return accumulate(v.begin(), v.end(), 0.0) / v.size();
}

double averge_grade(Student_info& s)
{
        return grade(s.midterm, s.final, average(s.homework));
}

double average_analysis(vector<Student_info>& students)
{
        vector<double> grades;
        transform(students.begin(), students.end(),
                        back_inserter(grades), averge_grade);
        return median(grades);
}

double optimistic_median(Student_info& s)
{
        vector<double> nonzero;
        remove_copy(s.homework.begin(), s.homework.end(),
                                        back_inserter(nonzero), 0);
        
        if (nonzero.empty())
                return grade(s.midterm, s.final, 0);
        else
                return grade(s.midterm, s.final, median(nonzero));
}

double optimistic_median_analysis(vector<Student_info>& students)
{
        vector<double> grades;
        
        return median(grades);
}

void write_analysis(ostream& out, const string& name,
                                        double analysis(vector<Student_info>&),
                                        vector<Student_info>& did,
                                        vector<Student_info>& didnt)
{
        out << name << ": median(did) = " << analysis(did) << 
                        ", median(didnt) = " << analysis(didnt) << endl;
}

int student_analysis () 
{
        vector<Student_info> did, didnt;
        Student_info student;
        while (read(cin, student)) {
                if (did_all_hw(student))
                        did.push_back(student);
                else
                        didnt.push_back(student);
        }

        if (did.empty() ) {
                cout << "No student did all the homework!" << endl;
                return 1;
        }

        if (didnt.empty() ) {
                cout << "Every student did all the homework!" << endl;
                return 1;
        }

        write_analysis(cout, "median", median_analysis, did ,didnt );
        write_analysis(cout, "average", average_analysis, did ,didnt );
        write_analysis(cout, "median of homework turned in", 
                                        optimistic_median_analysis, did ,didnt );
        return 0;
}

int main()
{
        string str = "I love you";
        vector<string> ret = split(str);
        for (size_t  i = 0; i < ret.size(); i++)
                cout << ret[i] << endl;
        
        string s0 = "revaer";
        string s1 = "rever";
        cout << is_palidrome(s0) << endl;
        cout << is_palidrome(s1) << endl;

        string url = "://123http://www.baidu.com http://www.sougu.com";
        cout << find_urls(url)[0] <<endl;
        cout << find_urls(url)[1] <<endl;
}

// page:128