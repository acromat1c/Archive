#include "Header.h"

void OPG345()
{
	double num;
	cin >> num;
	if (num >= 100) { num *= 1.2; }
	else { num *= 1.1; }
	cout << num << "\n\n";
}