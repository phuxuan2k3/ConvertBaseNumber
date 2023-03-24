#pragma once
#include <iostream>
#include <string>
#include <limits>

#define MAX_BASE_DIGIT 62

using namespace std;


void ignoreLine();
double inputDouble(const char* inputMessage = "Enter a double value: ", const char* errMessage = "Invalid input, try again!", bool (*check) (double) = nullptr);
int inputInt(const char* inputMessage = "Enter an Integer value: ", const char* errMessage = "Invalid input, try again!", bool (*check) (int) = nullptr);

void show_guide();

class Converter
{
protected:
	bool sign;
	string digitsSrc;
	int baseSrc;
	long long valueBase10;
	string digitsDes;
	int baseDes;

	static bool checkBase(const int base);

	bool isValid();
	void getSign();

	bool isNumChar(const char& x);
	//check if a character is a number
	bool isUpperAlphabetChar(const char& x);
	//check if a character is a upper-case alphabet
	bool isLowerAlphabetChar(const char& x);
	//check if a character is a lower-case alphabet
	bool isUnderScore(const char& x);
	//check if a character is a lower-case alphabet

	int charToNum(const char& x);
	string NumTochar(const int& x);

	void upperCase();
};

class IntConverter : private Converter
{
public:
	IntConverter();
	IntConverter(const string& digitsSrc, const  int& baseSrc, const  int& baseDes);
	void setValue(const string& digitsSrc, const  int& baseSrc, const  int& baseDes);

	void input();
	void display();
	//friend istream& operator>>(istream& is, IntConverter& number);
	//friend ostream& operator<<(ostream& os, const IntConverter& number);

	void convertTobase10();
	void convertTobaseDes();
	void convert();

	string getDigitsDes();
	~IntConverter();
};

class RealConverter : private Converter
{
	static const int numberDecDigit = 32; // the number of digits after comma
	string decPartSrc;
	double decPartValue;
	string decPartDes;

public:
	RealConverter();
	void input();
	void display();
	//friend istream& operator>>(istream& is, RealConverter& number);
	//friend ostream& operator<<(ostream& os, const RealConverter& number);

	void calculateDecPartValue();
	void convertDecPart();
	void convert();

	~RealConverter();
};