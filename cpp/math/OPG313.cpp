#include "Header.h"

void OPG313()
{
	double Timeløn, Timer, Dager, Utgifter;

	cout << "Timeløn: ";
	cin >> Timeløn;
	cout << endl << "Timer: ";
	cin >> Timer;
	cout << endl << "Dager: ";
	cin >> Dager;
	cout << endl << "Utgifter: ";
	cin >> Utgifter;
	cout << "\n\n";

	cout << "Ho arbeider " << Timer << " timer gjennom " << Dager << 
		" dager og tjener " << Timeløn * Timer - Utgifter * Dager << " kr.\n"
	 << "Det er " << Utgifter * Dager << " kr betalt i utgifter.\n////////////////////////\n";
}