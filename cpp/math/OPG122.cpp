#include "Header.h"

void OPG3122()
{
	double LÂn, ≈r, LÂn≈r;

	cout << "LÂn: ";
	cin >> LÂn;
	cout << endl << "Ned betaling: ";
	cin >> LÂn≈r;
	cout << endl << "≈r: ";
	cin >> ≈r;
	cout << "\n\n";

	cout << "Etter " << ≈r << " ≈r er lÂne redusert med " << LÂn≈r * ≈r << 
		" kr og " << LÂn - LÂn≈r * ≈r << " kr gjenstÂr av lÂne"
		<< "\n////////////////////////\n";
}