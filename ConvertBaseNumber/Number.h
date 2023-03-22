#pragma once
#include <iostream>
#include <string>

using namespace std;

class Number
{
protected:
	bool sign;
	string digitsSrc;
	int baseSrc;
	long long valueBase10;
	string digitsDes;
	int baseDes;

	static bool checkBase(const int& base);

	bool isValid();
	void getSign();

	bool isNumChar(const char& x);
	//check if a character is a number
	bool isAlphabetChar(const char& x);
	//check if a character is a number

	int charToNum(const char& x);
	char NumTochar(const int& x);

	void upperCase();
};

class Integer :Number
{
public:
	Integer();
	Integer(const string& digitsSrc, const  int& baseSrc, const  int& baseDes);
	void setValue(const string& digitsSrc, const  int& baseSrc, const  int& baseDes);
	friend istream& operator>>(istream& is, Integer& number);
	friend ostream& operator<<(ostream& os, const Integer& number);

	void convertTobase10();
	void convertTobaseDes();
	void convert();

	string getDigitsDes();
};

class RealNumber :Number
{
	static const int numberDecDigit = 32; // the number of digits after comma
	string decPartSrc;
	double decPartValue;
	string decPartDes;
public:
	RealNumber();

	friend istream& operator>>(istream& is, RealNumber& number);
	friend ostream& operator<<(ostream& os, const RealNumber& number);

	void calculateDecPartValue();
	void convertDecPart();
	void convert();
};