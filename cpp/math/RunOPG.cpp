#include "Header.h"

string Run;

void RunOPG(string Run2)
{
	if (Run2 == "OPG313")
	{
		OPG313();
	}
	else if (Run2 == "OPG322")
	{
		OPG322();
	}
	else if (Run2 == "OPG3122")
	{
		OPG3122();
	}
	else if (Run2 == "OPG330")
	{
		OPG330();
	}
	else if (Run2 == "OPG331")
	{
		OPG331();
	}
	else if (Run2 == "OPG333")
	{
		OPG333();
	}
	else if (Run2 == "OPG340")
	{
		OPG340();
	}
	else if (Run2 == "OPG345")
	{
		OPG345();
	}
	else
	{
		cout << "\nXXXXX\nerror\nXXXXX\n";
	}
}

int main()
{
	while (true)
	{
		cin >> Run;
		if (Run == "close") { break; }
		else { RunOPG(Run); }
	}
}