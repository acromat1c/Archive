#include "Header.h"

void OPG3122()
{
	double L�n, �r, L�n�r;

	cout << "L�n: ";
	cin >> L�n;
	cout << endl << "Ned betaling: ";
	cin >> L�n�r;
	cout << endl << "�r: ";
	cin >> �r;
	cout << "\n\n";

	cout << "Etter " << �r << " �r er l�ne redusert med " << L�n�r * �r << 
		" kr og " << L�n - L�n�r * �r << " kr gjenst�r av l�ne"
		<< "\n////////////////////////\n";
}