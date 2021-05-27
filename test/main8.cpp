#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <cctype>
#include <numeric>
#include <map>
#include <iterator>

using namespace std;

template <class T>
T median(vector<T> v)
{
        typedef typename vector<T>::size_type vec_sz;

        vec_sz size = v.size();
        sort(v.begin(), v.end());

        vec_sz mid = size / 2;
        return size % 2 == 0 ? (v[mid] + v[mid - 1]) / 2 : v[mid];
}

template<class In, class X> 
In find(In begin, In end, const X& x)
{
        while (begin != end && *begin != x)
                ++begin;
        return begin;

        // 方法2

        if (begin == end || *begin == x)
                return begin;
        begin++;
        return find(begin, end, x);
}

template<class In, class Out>
Out copy(In begin, In end, Out dest)
{
        while (begin != end)
                *dest++ = *begin++;
        return dest;
}

template<class For, class X>
void replace(For beg, For end, const X& x, const X& y)
{
        while (beg != end) {
                if (*beg == x)
                        *beg = y;
                ++beg;
        }
}

template <class Bi> 
void reverse(Bi begin, Bi end)
{
        while (begin != end) {
                --end;
                if (begin != end)
                        swap(*begin++, *end);
        }
}

template<class Ran, class X>
bool binary_search(Ran begin, Ran end, const X& x)
{
        while (begin < end) {
                Ran mid = begin + (end - begin) / 2;

                if (x < *mid)
                        end = mid;
                else if (*mid < x)
                        begin = mid + &x;
                else
                        return true;
        }
        
        return false;
}

bool not_space(char c)
{
        return !isspace(c);
}

bool space(char c)
{
        return isspace(c);
}

template <class Out>
void split(const string& str, Out os)
{
        typedef string::const_iterator iter;

        iter i = str.begin();
        while ( i != str.end())
        {
                i = find_if (i, str.end(), not_space);

                iter j = find_if(i, str.end(), space);

                if (i != str.end())
                        *os++ = string(i,j);

                i = j;
        }
        
}

int main()
{
        string s;
        while (getline(cin, s) && s != "quit")
                split(s, ostream_iterator<string>(cout, "\n"));
        return 0;
}

// Page:175