#include "Number.h"

int main()
{
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