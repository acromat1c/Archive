#include "Header.h"

void OPG322()
{
	double Timeløn, Timer, Salg, Salgløn;

	cout << "Timeløn: ";
	cin >> Timeløn;
	cout << endl << "Timer: ";
	cin >> Timer;
	cout << endl << "Salg: ";
	cin >> Salg;
	cout << endl << "Salgløn: ";
	cin >> Salgløn;
	cout << "\n\n";

	cout << "Ho arbeider " << Timer << " timer og selger " << Salg <<
		" ting. Ho tjener " << Timeløn * Timer + Salg * Salgløn << " kr.\n////////////////////////\n";
}