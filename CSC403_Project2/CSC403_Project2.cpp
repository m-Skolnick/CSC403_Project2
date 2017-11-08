#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;



string getDataBits(string binNumber) {

	string dataBits = "";
	int length = binNumber.length();
	int binCount = 3;
	int stringPosition = 0;
	

	while (binCount <= length) {		
		stringPosition = length - binCount;
		dataBits.insert(0, 1, binNumber.at(stringPosition));
		binCount++;
		if ((binCount & (binCount-1))==0) {
			binCount++;
		}
	}

	return dataBits;
}
string getCheckBits(string binNumber) {

	string checkBits = "";
	int length = binNumber.length();
	int powerOfTwo = 1;
	int stringPosition = 0;

	while (powerOfTwo < length) {
		stringPosition = length - powerOfTwo;
		checkBits.insert(0, 1, binNumber.at(stringPosition));
		powerOfTwo *= 2;
	}

	return checkBits;
}
string getCalculatedCheckBits(string binNumber) {

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
string getCorrectedDataBits(string dataBits, string checkBits, string calcedCheckBits) {
	int wrongBit = 0;
	string wrongBitBin= "";
	string correctedDataBits;
	if (checkBits == calcedCheckBits) {
		correctedDataBits = "OK";
	}
	else {
		
		for (int i = 0; i < checkBits.length(); i++) {
			if (checkBits.at(i) == calcedCheckBits.at(i)) {
				wrongBitBin.append("0");
			}
			else {
				wrongBitBin.append("1");
			}
		}
		int j = 0;
		for (int i = wrongBitBin.length()-1; i >0; i--) {
			if (wrongBitBin.at(i) == '1') {
				wrongBit += pow(2, j);
			}
			j++;
		}
		wrongBit = dataBits.length() - wrongBit; //Flip to count from front
		if (dataBits.at(wrongBit) == '1') { //Insert the right bit			
			correctedDataBits = dataBits.insert(wrongBit,"0");
		}
		else {
			correctedDataBits = dataBits.insert(wrongBit, "1");
		}
		correctedDataBits = dataBits.erase(wrongBit+1);//Delete the bad bit
		//correctedDataBits = calcedCheckBits.replace(wrongBit, "1");

	}

	return correctedDataBits;
}

int main() {

	string fileName;
	cout << "Please enter the name of an input file: " << endl;
	//cin >> fileName; **********************MAKE SURE TO ENABLE THIS **********
	ifstream inFile("inputFile.txt");  // Open the file containing data.

	string binNumber,dataBits,checkBits,calcedCheckBits;
	inFile >> binNumber; //Seed read
	while (binNumber != "quit") {		
		cout << binNumber << " ";
		dataBits = getDataBits(binNumber);
		checkBits = getCheckBits(binNumber);
		calcedCheckBits = getCalculatedCheckBits(binNumber);
		cout << dataBits << " ";
		cout << checkBits << " ";
		cout << calcedCheckBits << " ";
		cout << getCorrectedDataBits(dataBits, checkBits, calcedCheckBits) << endl;
		inFile >> binNumber; // Read the next number

	}
	return 0;
}