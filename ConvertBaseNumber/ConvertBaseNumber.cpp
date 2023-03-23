#include "Number.h"

int main()
{
	cout << "*note: In this program, we use the symbols:\n";
	cout << "\t'0','1',... '9' to represent numbers 0,1,...,9\n";
	cout << "\t'A','B',... 'Z' to represent numbers 10,11,...,35\n";
	cout << "\t'a','b',... 'z' to represent numbers 36,37,...,62\n";
	cout << "Similarly, we can EASILY represent even larger bases, as long as we find the appropriate symbols.\nHowever, in this program, the largest base that can be converted is 62.\n\n";

	char choice;

	do
	{
		RealNumber a;
		cin >> a;
		a.convert();
		cout << a;
		cout << "\n\nContinue? (y/n)";
		cin >> choice;
	} while (choice == 'y');

	return 0;
}