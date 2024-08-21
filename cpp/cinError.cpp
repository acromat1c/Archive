#include <iostream>

using namespace std;

int main()
{
	int A;
	
	Aa:

		cin >> A;

	if (cin.fail())
	{
		cout << "invalid answer\n";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		goto Aa;
	}

	cout << "\n" << A << "\n";
}