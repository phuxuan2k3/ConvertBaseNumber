#include "Number.h"

int main()
{
	char choice;

	do
	{
		system("cls");
		RealConverter a;
		cout << "***************************************************************" << endl;
		cout << "\t\t\t=== BASE CONVERTER ===" << endl;
		cout << endl;
		cout << "Enter i: Show Introductions" << endl;
		cout << "Enter q: Quit Program" << endl;
		cout << "Enter any other character: Convert Number" << endl;
		cout << "---------------------------------------------------------------" << endl;
		cout << "Your choice: ";
		cin >> choice;
		ignoreLine();
		cout << "***************************************************************" << endl;
		cout << endl;

		if (choice == 'i') {
			show_guide();
		}
		else if (choice == 'q') {
			system("cls");
			cout << endl;
			cout << "Good bye!" << endl;
			cout << endl;
			break;
		}
		else {
			a.input();
			a.convert();
			a.display();
			cout << endl;
			cout << endl;
			cout << "***************************************************************" << endl;
			cout << "Continue...";
			system("pause");
		}
		system("cls");

	} while (true);

	system("pause");
	return 0;
}