#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

string getDataBits(string binNumber) { //Return the data bits from a bin number in string form
	string dataBits = "";
	int length = binNumber.length();
	int binCount = 3;
	int stringPosition = 0;
	while (binCount <= length) {
		stringPosition = length - binCount;
		dataBits.insert(0, 1, binNumber.at(stringPosition));
		binCount++;
		if ((binCount & (binCount - 1)) == 0) { //If the bit number is a multiple of 2 skip it
			binCount++;
		}
	}
	return dataBits;
}
string getCheckBits(string binNumber) { //Return the check bits from a bin number in string form
	string checkBits = "";
	int length = binNumber.length();
	int powerOfTwo = 1;
	int stringPosition = 0;
	while (powerOfTwo < length) { //Get the bit at the next power of 2
		stringPosition = length - powerOfTwo;
		checkBits.insert(0, 1, binNumber.at(stringPosition));
		powerOfTwo *= 2;
	}
	return checkBits;
}
string getCalculatedCheckBits(string binNumber) { //Calculate the check bits based on the data bits
	string calcCheckBits = "";
	int length = binNumber.length();
	int powerOfTwo = 1;
	int parity = 0;
	int binCount = 1;
	int stringPosition = 0;

	while (powerOfTwo <= length) {
		parity = 0; //Set parity to 0
		binCount = powerOfTwo; // Move to start at the next power of 2
		while (binCount <= length) {

			for (int i = 0; i < powerOfTwo && binCount <= length; i++) {
				while ((binCount & (binCount - 1)) == 0) { //Skip if power of 2
					binCount++;
					i++;
					if (binCount > length) {
						break;
					}
				}
				stringPosition = length - binCount;
				if (binNumber.at(stringPosition) == '1') {
					parity++;
				}
				binCount++;
			}
			binCount += powerOfTwo; //Move to the next position in bin number
		}
		if (parity % 2 == 0) {
			calcCheckBits.insert(0, "0");
		}
		else {
			calcCheckBits.insert(0, "1");
		}
		powerOfTwo *= 2; // Increase to the next power of two
	}

	return calcCheckBits;
}
	//Correct the binary number based on the check bits and calculated check bits
string getCorrectedBinNumber(string binNumber, string checkBits, string calcedCheckBits) {
	int wrongBit = 0;
	string wrongBitBin = "";
	string correctedBinNumber;
	if (checkBits == calcedCheckBits) {
		correctedBinNumber = "OK";
	}
	else {
			//Find the parity of the calculated check bits and check bits
		for (int i = 0; i < checkBits.length(); i++) {
			if (checkBits.at(i) == calcedCheckBits.at(i)) {
				wrongBitBin.append("0");
			}
			else {
				wrongBitBin.append("1");
			}
		}
		int j = 0;
			//Calculate the parity in decimal
		for (int i = wrongBitBin.length() - 1; i >= 0; i--) {
			if (wrongBitBin.at(i) == '1') {
				wrongBit += pow(2, j);
			}
			j++;
		}
		wrongBit = binNumber.length() - wrongBit; //Flip to count from front
		if (binNumber.at(wrongBit) == '1') { //Insert the right bit			
			correctedBinNumber = binNumber.insert(wrongBit, "0");
		}
		else {
			correctedBinNumber = binNumber.insert(wrongBit, "1");
		}
		correctedBinNumber = binNumber.erase(wrongBit+1,1);//Delete the bad bit
	}

	return correctedBinNumber;
}
int main() {
	string fileName;
	cout << "Please enter the name of an input file: " << endl;
	cin >> fileName; 
	ifstream inFile("inputFile.txt");  // Open the file containing data.

	string binNumber, dataBits, checkBits, calcedCheckBits;
	inFile >> binNumber; //Seed read
	while (binNumber != "quit") {
		cout << binNumber << " ";
		dataBits = getDataBits(binNumber);
		checkBits = getCheckBits(binNumber);
		calcedCheckBits = getCalculatedCheckBits(binNumber);
		cout << dataBits << " ";
		cout << checkBits << " ";
		cout << calcedCheckBits << " ";
		cout << getCorrectedBinNumber(binNumber, checkBits, calcedCheckBits) << endl;
		inFile >> binNumber; // Read the next number
	}
	return 0;
}