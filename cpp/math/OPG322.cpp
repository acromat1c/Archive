#include "Header.h"

void OPG322()
{
	double Timel�n, Timer, Salg, Salgl�n;

	cout << "Timel�n: ";
	cin >> Timel�n;
	cout << endl << "Timer: ";
	cin >> Timer;
	cout << endl << "Salg: ";
	cin >> Salg;
	cout << endl << "Salgl�n: ";
	cin >> Salgl�n;
	cout << "\n\n";

	cout << "Ho arbeider " << Timer << " timer og selger " << Salg <<
		" ting. Ho tjener " << Timel�n * Timer + Salg * Salgl�n << " kr.\n////////////////////////\n";
}