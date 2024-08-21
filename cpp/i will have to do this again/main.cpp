#include "header.h"

using namespace std;

float errorfloat()
{
	float f;
tryagain:
	try {
		cin >> f;
		if (!cin)
		{
			throw (f);
		}
	}
	catch (float bmi)
	{
		cout << "enter a valid number!" << endl;
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		goto tryagain;
	}
	return f;
}

void calculatebmi(float bmi)
{
	bmi = floor(bmi);

	int underwaight = 18, healthy = 25,
		overwaight = 30, gethelp = 40;
	if (bmi < underwaight)
		{ cout << "you have an eating disorder\n"; }
	else if (bmi < healthy)
		{ cout << "you good\n"; }
	else if (bmi < overwaight)
		{ cout << "hit the gym\n"; }
	else if (bmi < gethelp)
		{ cout << "hit the gym, NOW!\n"; }
	else
		{ cout << "may god have mercy on your wreched soul\n"; }
}

int main()
{
	float bmi;

	bmi = errorfloat();
	calculatebmi(bmi);
}