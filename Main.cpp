/*
Atif Ahmad
Lab 3
*/

#include<iostream>
#include<string>
#include<fstream>

using namespace std;

int main()
{
	cout << "-------------------------------------------------------------------------------" << endl;
	cout << "|                                                                             |" << endl;
	cout << "|                   RSA Encryption/Decryption Program                         |" << endl;
	cout << "|                                                                             |" << endl;
	cout << "-------------------------------------------------------------------------------" << endl;
	cout << "The purpose of the program is to use RSA encryption/decryption to either encrypt a text message";
	cout << " into a text containing a sequence of numbers or decrpyt a text\ncontaining a sequence of numbers into";
	cout << " a text message. The user enters values for p, q, e, and d. The user also needs to enter a text file";
	cout << " to encrpt or decrypt. p and q are prime numbers. e is an arbitrary number usually prime.";
	cout << " N is equal to p*q. phi is equal to (p -1)*(q-1). d is the multiplicative inverse of e. This\nmeans that";
	cout << " e*d mod phi = 1. After the user inputs all the information, the\n\"results.txt\" file is generated, which";
	cout << " shows the encrypted or decrypted message." << endl;
	cout << "-------------------------------------------------------------------------------" << endl;

	int p;
	int q;
	int e;
	int d;
	char inputResponse;
	string inputFileName;
	bool isPPrime = true;
	bool isQPrime = true;
	bool errorOccurred = false;

	do
	{
		isPPrime = true;
		isQPrime = true;
		errorOccurred = false;
		cout << "Enter the values for p and q: ";
		cin >> p;
		cin >> q;

		if (p <= 1 || q <= 1)
			errorOccurred = true;

		if (errorOccurred == false)
		{
			// Check to see if p is prime
			for (int i = 2; i <= p / 2; i++)
			{
				if (p % i == 0)
				{
					isPPrime = false;
					break;
				}
			}

			// Check to see if q is prime
			for (int i = 2; i <= q / 2; i++)
			{
				if (q % i == 0)
				{
					isQPrime = false;
					break;
				}
			}
		}

			if (!isPPrime || !isQPrime || errorOccurred)
				cout << "p and q must be prime numbers" << endl;
		

	} while (!isPPrime || !isQPrime || errorOccurred);

	do
	{
		errorOccurred = false;
		cout << "Enter the value for e: ";
		cin >> e;
		
		if (e <= 0)
		{
			errorOccurred = true;
			cout << "e needs to be a positive integer" << endl;
		}
	}
	while (errorOccurred);

	do
	{
		errorOccurred = false;
		cout << "Enter the value for d: ";
		cin >> d;
		
		if (d <= 0)
		{
			errorOccurred = true;
			cout << "d needs to be a positive integer" << endl;
		}
	}
	while (errorOccurred);

	int N = p * q;
	int phi = (p - 1) * (q - 1);

	do
	{
		errorOccurred = false;
		if (((e * d) % phi) != 1)
		{
			errorOccurred = true;
			cout << "d must be the multiplicative inverse of e" << endl;
			cout << "e*d mod phi = " << ((e * d) % phi) << endl;
			cout << "Enter d again: ";
			cin >> d;
		}

	} while (errorOccurred);

	cout << "Do you want to encrypt(E) or decrypt(D)? ";
	cin >> inputResponse;

	cout << "Enter the input filename: ";
	cin >> inputFileName;

	if (inputResponse == 'E')
	{
		// open the file
		ifstream ins(inputFileName);

		ofstream outs("results.txt");

		// Check the file could be opened
		if (!ins) {
			cerr << "Could not open the file" << endl;
			return 0;
		}

		// Get each character
		char ch;
		int m;
		int c;
		while (ins.get(ch)) {
			m = static_cast<int>(ch);
			c = m;
			int mBase = m;

			// Compute c = m^e Mod N
			for (int i = 1; i <= e - 1; i++)
				c = (mBase * c) % N;

			outs << c << " ";
		}

		// close the file
		ins.close();

		// close the file
		outs.close();

	}

	else if (inputResponse == 'D')
	{
		// Open file of numbers
		ifstream ins;
		ins.open(inputFileName);

		ofstream outs("results.txt");

		// Check the file could be opened
		if (!ins) {
			cerr << "Could not open the file" << endl;
			return 0;
		}

		int num;
		char m;
		int c;
		while (ins >> num) {
			c = num;
			int cBase = c;

			// Compute m = c^d Mod N
			for (int i = 1; i <= d - 1; i++)
				c = (cBase * c) % N;

			m = static_cast<char>(c);
			outs << m;
		}

		// close the file
		ins.close();

		// close the file
		outs.close();
	}

	cout << endl;
	system("Pause");
	return 0;
}
