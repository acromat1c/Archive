#include "Header.h"

void OPG313()
{
	double Timel�n, Timer, Dager, Utgifter;

	cout << "Timel�n: ";
	cin >> Timel�n;
	cout << endl << "Timer: ";
	cin >> Timer;
	cout << endl << "Dager: ";
	cin >> Dager;
	cout << endl << "Utgifter: ";
	cin >> Utgifter;
	cout << "\n\n";

	cout << "Ho arbeider " << Timer << " timer gjennom " << Dager << 
		" dager og tjener " << Timel�n * Timer - Utgifter * Dager << " kr.\n"
	 << "Det er " << Utgifter * Dager << " kr betalt i utgifter.\n////////////////////////\n";
}