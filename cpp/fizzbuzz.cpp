#include <iostream>

using namespace std;

string & multiMod(int i)
{
    string str;
    if (i % 3 == 0)
    {
        str += "fizz";
    }
    if (i % 5 == 0)
    {
        str += "buzz";
    }
    if (i % 7 == 0)
    {
        str += "baz";
    }

    if (str != "")
    {
        str[0] = char(int(str[0]) - 32);
    }

    static string* retrunVal;
    retrunVal = new string;
    *retrunVal = str;

    return *retrunVal;
}

int main()
{
    int n = 1000;
    for (int i = 1; i <= n; i++)
    {
        cout << i << " " << multiMod(i) << "\n";
    }
    return 0;
}