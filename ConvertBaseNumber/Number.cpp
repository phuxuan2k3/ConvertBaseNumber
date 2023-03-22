#include "Number.h"

bool Number::checkBase(const int& base)
{
	if (base < 2 or base >36)
	{
		return false;
	}
	return true;
}
Integer::Integer()
{
	this->sign = false;
	this->baseDes = 0;
	this->baseSrc = 0;
	this->digitsDes = "";
	this->digitsSrc = "";
	this->valueBase10 = 0;
}

Integer::Integer(const string& digitsSrc, const  int& baseSrc, const  int& baseDes)
{
	this->digitsSrc = digitsSrc;
	this->baseSrc = baseSrc;
	this->digitsDes = "";
	this->baseDes = baseDes;
	this->valueBase10 = 0;
}

void Integer::setValue(const string& digitsSrc, const  int& baseSrc, const  int& baseDes)
{
	this->digitsSrc = digitsSrc;
	this->baseSrc = baseSrc;
	this->digitsDes = "";
	this->baseDes = baseDes;
	this->valueBase10 = 0;
}

istream& operator>>(istream& is, Integer& number)
{
	do
	{
		cout << "Enter the base of source number: ";
		cin >> number.baseSrc;
	} while (Number::checkBase(number.baseSrc) == false);
	do
	{
		cout << "Enter the source number: ";
		cin >> number.digitsSrc;
	} while (number.isValid() == false);
	do
	{
		cout << "Enter the destination base: ";
		cin >> number.baseDes;
	} while (Number::checkBase(number.baseDes) == false);

	return is;
}

ostream& operator<<(ostream& os, const Integer& number)
{
	cout << (number.sign == true ? "-" : "") << number.digitsSrc << "(" << number.baseSrc << ") = " << (number.sign == true ? '-' : '\0') << number.digitsDes << "(" << number.baseDes << ")";

	return os;
}

bool Number::isValid()
{
	this->upperCase();
	int numDot = 0;
	for (int i = 0; i < this->digitsSrc.size(); i++)
	{
		if (this->isNumChar(this->digitsSrc[i]) == true or this->isAlphabetChar(this->digitsSrc[i]) == true)
		{
			if (this->charToNum(this->digitsSrc[i]) >= this->baseSrc)
			{
				return false;
			}
		}
		else if (this->digitsSrc[i] == '.')
		{
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
	return (numDot < 2 ? true : false);
}

void Number::getSign()
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

bool Number::isNumChar(const char& x)
{
	if (x >= '0' and x <= '9')
	{
		return true;
	}
	return false;
}
//check if a character is a number

bool Number::isAlphabetChar(const char& x)
{
	if ((x >= 'A' and x <= 'Z') or (x >= 'a' and x <= 'z'))
	{
		return true;
	}
	return false;
}

void Number::upperCase()
{
	for (int i = 0; i < this->digitsSrc.size(); i++)
	{
		if (this->digitsSrc[i] >= 'a' and this->digitsSrc[i] <= 'z')
		{
			(this->digitsSrc[i]) -= 32;
		}
	}
}


int Number::charToNum(const char& x)
{
	if (this->isNumChar(x) == true)
	{
		return int(x) - 48;
	}
	return int(x) - 55;
}

char Number::NumTochar(const int& x)
{
	if (x >= 0 and x <= 9)
	{
		return char(x + 48);
	}
	return char(x + 55);
}

void Integer::convertTobase10()
{
	int n = this->digitsSrc.size();
	for (int i = 0; i < n; i++)
	{
		this->valueBase10 += this->charToNum(this->digitsSrc[n - 1 - i]) * pow(this->baseSrc, i);
	}
}

void Integer::convertTobaseDes()
{
	long long value = this->valueBase10;
	while (value != 0)
	{
		char x = this->NumTochar(value % this->baseDes);
		this->digitsDes = x + this->digitsDes;
		value /= this->baseDes;
	}
}

void Integer::convert()
{
	this->getSign();
	this->upperCase();
	this->convertTobase10();
	this->convertTobaseDes();
}

string Integer::getDigitsDes()
{
	return this->digitsDes;
}

RealNumber::RealNumber()
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

istream& operator>>(istream& is, RealNumber& number)
{
	do
	{
		cout << "Enter the base of source number: ";
		cin >> number.baseSrc;
	} while (Number::checkBase(number.baseSrc) == false);
	do
	{
		cout << "Enter the source number: ";
		cin >> number.digitsSrc;
	} while (number.isValid() == false);
	do
	{
		cout << "Enter the destination base: ";
		cin >> number.baseDes;
	} while (Number::checkBase(number.baseDes) == false);

	return is;
}

ostream& operator<<(ostream& os, const RealNumber& number)
{
	cout << (number.sign == true ? "-" : "") << number.digitsSrc << "(" << number.baseSrc << ") = " << (number.sign == true ? '-' : '\0') << number.digitsDes << "(" << number.baseDes << ")";

	return os;
}

void RealNumber::calculateDecPartValue()
{
	for (int i = 0; i < this->decPartSrc.size(); i++)
	{
		this->decPartValue += (this->charToNum(this->decPartSrc[i]) * pow(this->baseSrc, (-1) * i - 1));
	}
}

void RealNumber::convertDecPart()
{
	int i = 0;
	double value = this->decPartValue;
	while (value != 0.0 && i <= RealNumber::numberDecDigit)
	{
		value *= this->baseDes;
		long long integerPart = (long long)value;
		this->decPartDes += this->NumTochar(integerPart);
		value -= integerPart;
		i++;
	}
	if (i == RealNumber::numberDecDigit + 1 && (long long)(value * this->baseDes) >= round(this->baseDes / double(2)))
	{
		int j = this->decPartDes.size() - 1;
		this->decPartDes[j]++;
	}
}

void RealNumber::convert()
{
	this->getSign();
	this->upperCase();
	Integer a;
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
