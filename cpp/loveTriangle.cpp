#include <iostream>

using std::cout;
using std::cin;

void BuildPyramid(int layers)
{
    if (layers > 0)
    {
        cout << '#';
        BuildPyramid(layers - 1);
    }
}

int main()
{
    BuildPyramid(20);
}