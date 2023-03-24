#include "Number.h"

void ignoreLine()
{
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

double inputDouble(const char* inputMessage,const char* errMessage, bool (*check) (const double))
{
	while (true)
	{
		std::cout << inputMessage;
		double x{};
		std::cin >> x;

		if (!std::cin)
		{
			std::cin.clear();
			ignoreLine();
			std::cerr << errMessage << endl;
			continue;
		}
		if (check(x) == false) {
			ignoreLine();
			std::cerr << errMessage << endl;
		}
		else
		{
			ignoreLine();
			return x;
		}
	}
	// Never reach
	return 0;
}

int inputInt(const char* inputMessage, const char* errMessage, bool (*check) (const int))
{
	while (true)
	{
		std::cout << inputMessage;
		int x{};
		std::cin >> x;

		if (!std::cin)
		{
			std::cin.clear();
			ignoreLine();
			std::cerr << errMessage << endl;
			continue;
		}
		if (check(x) == false) {
			ignoreLine();
			std::cerr << errMessage << endl;
		}
		else
		{
			ignoreLine();
			return x;
		}
	}
	// Never reach
	return 0;
}



bool Converter::checkBase(const int base)
{
	if (base < 2)
	{
		return false;
	}
	return true;
}

IntConverter::IntConverter()
{
	this->sign = false;
	this->baseDes = 0;
	this->baseSrc = 0;
	this->digitsDes = "";
	this->digitsSrc = "";
	this->valueBase10 = 0;
}

IntConverter::IntConverter(const string& digitsSrc, const  int& baseSrc, const  int& baseDes)
{
	this->digitsSrc = digitsSrc;
	this->baseSrc = baseSrc;
	this->digitsDes = "";
	this->baseDes = baseDes;
	this->valueBase10 = 0;
}

void IntConverter::setValue(const string& digitsSrc, const  int& baseSrc, const  int& baseDes)
{
	this->digitsSrc = digitsSrc;
	this->baseSrc = baseSrc;
	this->digitsDes = "";
	this->baseDes = baseDes;
	this->valueBase10 = 0;
}

void IntConverter::input() {
	do
	{
		cout << "Enter the base of source number: ";
		cin >> this->baseSrc;
	} while (Converter::checkBase(this->baseSrc) == false);
	do
	{
		cout << "Enter the source number: ";
		cin >> this->digitsSrc;
	} while (this->isValid() == false);
	do
	{
		cout << "Enter the destination base: ";
		cin >> this->baseDes;
	} while (Converter::checkBase(this->baseDes) == false);
}

void IntConverter::display() {
	cout << (this->sign == true ? "-" : "") << this->digitsSrc << "(" << this->baseSrc << ") = " 
		<< (this->sign == true ? '-' : '\0') << this->digitsDes << "(" << this->baseDes << ")";
}

//istream& operator>>(istream& is, IntConverter& number)
//{
//	do
//	{
//		cout << "Enter the base of source number: ";
//		cin >> number.baseSrc;
//	} while (Converter::checkBase(number.baseSrc) == false);
//	do
//	{
//		cout << "Enter the source number: ";
//		cin >> number.digitsSrc;
//	} while (number.isValid() == false);
//	do
//	{
//		cout << "Enter the destination base: ";
//		cin >> number.baseDes;
//	} while (Converter::checkBase(number.baseDes) == false);
//
//	return is;
//}
//
//ostream& operator<<(ostream& os, const IntConverter& number)
//{
//	cout << (number.sign == true ? "-" : "") << number.digitsSrc << "(" << number.baseSrc << ") = " << (number.sign == true ? '-' : '\0') << number.digitsDes << "(" << number.baseDes << ")";
//
//	return os;
//}

bool Converter::isValid()
{
	int numDot = 0;
	int temDigitValue_baseDiff = 0;

	for (int i = 0; i < this->digitsSrc.size(); i++)
	{
		// Value part
		if (this->isNumChar(this->digitsSrc[i]) == true or
			this->isUpperAlphabetChar(this->digitsSrc[i]) == true or
			this->isLowerAlphabetChar(this->digitsSrc[i]) == true)
		{
			if (this->charToNum(this->digitsSrc[i]) + temDigitValue_baseDiff >= this->baseSrc)
			{
				return false;
			}
			temDigitValue_baseDiff = 0;
		}

		// Sign part
		else if (this->isUnderScore(this->digitsSrc[i]) == true) {
			temDigitValue_baseDiff += MAX_BASE_DIGIT;
		}
		else if (this->digitsSrc[i] == '.')
		{
			if (numDot >= 1) return false;
			if (temDigitValue_baseDiff != 0) return false;
			numDot++;
		}
		else if ((this->digitsSrc[i] == '+' or this->digitsSrc[i] == '-') and i == 0)
		{
		}
		else
		{
			return false;
		}
	}
	return (temDigitValue_baseDiff == 0 ? true : false);
}

void Converter::getSign()
{
	if (this->digitsSrc[0] == '-')
	{
		this->sign = true;
		this->digitsSrc.erase(0, 1);
	}
	else if (this->digitsSrc == "+")
	{
		this->digitsSrc.erase(0, 1);
	}
}

bool Converter::isNumChar(const char& x)
{
	if (x >= '0' and x <= '9')
	{
		return true;
	}
	return false;
}
//check if a character is a number

bool Converter::isUpperAlphabetChar(const char& x)
{
	if ((x >= 'A' and x <= 'Z'))
	{
		return true;
	}
	return false;
}
//check if a character is a upper-case alphabet

bool Converter::isLowerAlphabetChar(const char& x)
{
	if ((x >= 'a' and x <= 'z'))
	{
		return true;
	}
	return false;
}
//check if a character is a lower-case alphabet

bool Converter::isUnderScore(const char& x) {
	if (x == '_') return true;
	return false;
}
//check if a character is a lower-case alphabet


void Converter::upperCase()
{
	for (int i = 0; i < this->digitsSrc.size(); i++)
	{
		if (this->digitsSrc[i] >= 'a' and this->digitsSrc[i] <= 'z')
		{
			(this->digitsSrc[i]) -= 32;
		}
	}
}

//=============================================================================================================
//=============================================================================================================

int Converter::charToNum(const char& x)
{
	if (this->isUnderScore(x) == true) {
		// unwanted case
		return 0;
	}
	else if (this->isNumChar(x) == true)
	{
		return int(x) - 48;
	}
	else if (this->isUpperAlphabetChar(x) == true)
	{
		return int(x) - 55;
	}
	else
	{
		return int(x) - 61;
	}
}

string Converter::NumTochar(const int& x)
{
	if (x >= 0 and x <= 9)
	{
		return string(1, char(x + 48));
	}
	else if (x >= 10 and x <= 35)
	{
		return string(1, char(x + 55));
	}
	else if (x >= 36 and x <= 61)
	{
		return string(1, char(x + 61));
	}
	else if (x >= 62) {
		string tem = "";
		int tem2 = x;
		while (tem2 >= 62) {
			tem += "_";
			tem2 -= 62;
		}
		tem = tem + this->NumTochar(tem2);
		return tem;
	}
	else {
		cout << "ERROR\n";
		return "\0";
	}
}

// Reversal read
void IntConverter::convertTobase10() {
	int n = this->digitsSrc.size();
	long long pre = 0;
	int base_value_diff = 0;
	int power = 0;
	int pre_pos = -1;

	for (int i = 0; i < n; i++)
	{
		if (this->isUnderScore(this->digitsSrc[n - 1 - i]) == true) {
			if (i == 0) {
				cout << "ERROR";
				return;
			}

			this->valueBase10 = pre;
			if (pre_pos == -1) {
				pre_pos = i - 1;
			}
			base_value_diff += MAX_BASE_DIGIT;

			if (i == n - 1) {
				power--;
				this->valueBase10 = pre + (this->charToNum(this->digitsSrc[n - 1 - pre_pos]) + base_value_diff) * pow(this->baseSrc, power);
				pre_pos = -1;
				base_value_diff = 0;
				power++;
			}
		}
		else if (base_value_diff != 0) {
			power--;
			this->valueBase10 = pre + (this->charToNum(this->digitsSrc[n - 1 - pre_pos]) + base_value_diff) * pow(this->baseSrc, power);
			pre_pos = -1;
			base_value_diff = 0;
			power++;
			i--;
		}
		else {
			pre_pos = -1;
			pre = this->valueBase10;
			this->valueBase10 += this->charToNum(this->digitsSrc[n - 1 - i]) * pow(this->baseSrc, power);
			power++;
		}
	}
}

// Reversal write
void IntConverter::convertTobaseDes()
{
	long long value = this->valueBase10;
	while (value != 0)
	{
		string x = this->NumTochar(value % this->baseDes);
		this->digitsDes = x + this->digitsDes;
		value /= this->baseDes;
	}
}

void IntConverter::convert()
{
	this->getSign();
	this->convertTobase10();
	this->convertTobaseDes();
}

string IntConverter::getDigitsDes()
{
	return this->digitsDes;
}

RealConverter::RealConverter()
{
	this->sign = false;
	this->baseDes = 0;
	this->baseSrc = 0;
	this->digitsDes = "";
	this->digitsSrc = "";
	this->valueBase10 = 0;

	this->decPartSrc = "";
	this->decPartDes = "";
	this->decPartValue = 0;
}

void RealConverter::input() {
	this->baseSrc = inputInt(
		"Enter the base of source number (base >= 2): ", 
		"Invalid input, try again!", 
		Converter::checkBase);

	do
	{
		cout << "Enter the source number(digits must be exist in above base): ";
		cin >> this->digitsSrc;
	} while (this->isValid() == false);
	
	this->baseDes = inputInt(
		"Enter the base of destination number (base >= 2): ",
		"Invalid input, try again!",
		Converter::checkBase);
}

void RealConverter::display() {
	cout << (this->sign == true ? "-" : "") << this->digitsSrc
		<< "(" << this->baseSrc << ") = " << (this->sign == true ? '-' : '\0')
		<< this->digitsDes << "(" << this->baseDes << ")";
}

//istream& operator>>(istream& is, RealConverter& number)
//{
//	do
//	{
//		cout << "Enter the base of source number(integer number in [2,62]): ";
//		cin >> number.baseSrc;
//	} while (Converter::checkBase(number.baseSrc) == false);
//	cout << "\n";
//	do
//	{
//		cout << "Enter the source number(digits must be exist in above base): ";
//		cin >> number.digitsSrc;
//	} while (number.isValid() == false);
//	cout << "\n";
//	do
//	{
//		cout << "Enter the destination base(integer number in [2,62]): ";
//		cin >> number.baseDes;
//	} while (Converter::checkBase(number.baseDes) == false);
//
//	return is;
//}


//ostream& operator<<(ostream& os, const RealConverter& number)
//{
//	cout << (number.sign == true ? "-" : "") << number.digitsSrc 
//		<< "(" << number.baseSrc << ") = " << (number.sign == true ? '-' : '\0') 
//		<< number.digitsDes << "(" << number.baseDes << ")";
//
//	return os;
//}


// Order read
void RealConverter::calculateDecPartValue()
{
	int power = 0;
	int base_diff = 0;
	for (int i = 0; i < this->decPartSrc.size(); i++)
	{
		if (this->isUnderScore(this->decPartSrc[i]) == true) {
			base_diff += MAX_BASE_DIGIT;
			continue;
		}
		this->decPartValue += ((this->charToNum(this->decPartSrc[i]) + base_diff) * pow(this->baseSrc, (-1) * power - 1));
		base_diff = 0;
		power++;
	}
	if (base_diff != 0) {
		cout << "ERROR\n";
	}
}

// Order write
void RealConverter::convertDecPart()
{
	int i = 0;
	double value = this->decPartValue;
	while (value != 0.0 && i <= RealConverter::numberDecDigit)
	{
		value *= this->baseDes;
		long long integerPart = (long long)value;
		this->decPartDes = this->decPartDes + this->NumTochar(integerPart);
		value -= integerPart;
		i++;
	}
	if (i == RealConverter::numberDecDigit + 1 && (long long)(value * this->baseDes) >= round(this->baseDes / double(2)))
	{
		int j = this->decPartDes.size() - 1;
		this->decPartDes[j]++;
	}
}

void RealConverter::convert()
{
	this->getSign();
	IntConverter a;
	int posDot = this->digitsSrc.find('.');
	if (posDot != string::npos)
	{
		a.setValue(this->digitsSrc.substr(0, posDot), this->baseSrc, this->baseDes);
		this->decPartSrc = this->digitsSrc.substr(posDot + 1, this->digitsSrc.size() - posDot - 1);
	}
	else
	{
		a.setValue(this->digitsSrc, this->baseSrc, this->baseDes);
	}
	a.convert();

	this->calculateDecPartValue();
	this->convertDecPart();

	this->digitsDes = a.getDigitsDes() + (this->decPartDes == "" ? "" : "." + this->decPartDes);
}

IntConverter ::~IntConverter() {

}

RealConverter::~RealConverter() {

}

//==============================================================================
//==============================================================================


void show_guide() {
	system("cls");

	cout << "***************************************************************" << endl;
	cout << "\t\t\t=== INTRODUCTION ===" << endl;
	cout << endl;
	cout << "In this program, we use these symbols with their corresponding value:\n";
	cout << "0 = 0;" << "\t";
	cout << "1 = 1;" << "\t";
	cout << "2 = 2;" << "\t";
	cout << "3 = 3;" << "\n";
	cout << "4 = 4;" << "\t";
	cout << "5 = 5;" << "\t";
	cout << "6 = 6;" << "\t";
	cout << "7 = 7;" << "\n";
	cout << "8 = 8;" << "\t";
	cout << "9 = 9;" << "\t";
	cout << "A = 10;" << "\t";
	cout << "B = 11;" << '\n';
	cout << "C = 12;" << '\t';
	cout << "D = 13;" << '\t';
	cout << "E = 14;" << '\t';
	cout << "F = 15;" << '\n';
	cout << "G = 16;" << '\t';
	cout << "H = 17;" << '\t';
	cout << "I = 17;" << '\t';
	cout << "J = 19;" << '\n';
	cout << "K = 20;" << '\t';
	cout << "L = 21;" << '\t';
	cout << "M = 22;" << '\t';
	cout << "N = 23;" << '\n';
	cout << "O = 24;" << '\t';
	cout << "P = 25;" << '\t';
	cout << "Q = 26;" << '\t';
	cout << "R = 27;" << '\n';
	cout << "S = 28;" << '\t';
	cout << "T = 29;" << '\t';
	cout << "U = 30;" << '\t';
	cout << "V = 31;" << '\n';
	cout << "W = 32;" << '\t';
	cout << "X = 33;" << '\t';
	cout << "Y = 34;" << '\t';
	cout << "Z = 35;" << '\n';
	cout << "a = 36;" << '\t';
	cout << "b = 37;" << '\t';
	cout << "c = 38;" << '\t';
	cout << "d = 39;" << '\n';
	cout << "e = 40;" << '\t';
	cout << "f = 41;" << '\t';
	cout << "g = 42;" << '\t';
	cout << "h = 43;" << '\n';
	cout << "i = 44;" << '\t';
	cout << "j = 45;" << '\t';
	cout << "k = 46;" << '\t';
	cout << "l = 47;" << '\n';
	cout << "m = 48;" << '\t';
	cout << "n = 49;" << '\t';
	cout << "o = 50;" << '\t';
	cout << "p = 51;" << '\n';
	cout << "q = 52;" << '\t';
	cout << "r = 53;" << '\t';
	cout << "s = 54;" << '\t';
	cout << "t = 55;" << '\n';
	cout << "u = 56;" << '\t';
	cout << "v = 57;" << '\t';
	cout << "w = 58;" << '\t';
	cout << "x = 59;" << '\n';
	cout << "y = 60;" << '\t';
	cout << "z = 61;" << '\t';
	cout << endl;
	cout << "Inorder to use higher representation of symbols (like 62) we use underscore\n" 
		<< "symbol (\"_\"). Then, a value of a number will be represented by: 62 * n + g\n"
		<< "With:\n"
		<< "+ n: the number of underscore symbol (\"_\") in front of a valid digit\n"
		<< "+ g: the value of a digit after n underscore (\"_\")\n"
		;
	cout << "Example: _0 = 62, __k = 62 * 2 + 46 = 170" << endl;
	cout << endl;
	cout << "***************************************************************" << endl;
	cout << "Return...";
	system("pause");
}




