

//Madison Sawvel -- I wasn't sure how specific it needs to be

//This file is where you tell the computer exactly what you want to do. 
//You call the methods from the header file on data you declare in main.
//This program takes in two fractions from the user that they would like to add together. 
//But in order to do that, the fractions have to be simplified. 

#include <iostream>
#include <string>
#include <cstdlib>
#include "Arithmetic.h"
#include <list> 

using namespace std;

int main(int argc, char** argv) { //The main asks the reader for numbers. They are made into fractions and the two fractions are sent to addFraction to be added together
	cout << "Please enter the first numerator: ";
	string n1;
	getline(cin, n1); 
	cout << "Please enter the first denominator: ";
	string d1;
	getline(cin, d1); 
	cout << "Please enter the second numerator: ";
	string n2;
	getline(cin, n2); 
	cout << "Please enter the second denominator: ";
	string d2;
	getline(cin, d2); 

	cout << n1 << "/" << d1 << " + " << n2 << "/" << d2 << addFraction(n1, d1, n2, d2);

	return 0;

}
string sum(string n1, string n2) { //This method breaks down the string of numbers and adds each one together at a time. If a number is larger than 9, a carry is used. returns the sum
	remleadingzeroes(n1); 
	remleadingzeroes(n2);
	while (n1.length() < n2.length()) 
		n1 = "0" + n1;
	while (n2.length() < n1.length()) 
		n2 = "0" + n2;
	n1 = "0" + n1;
	n2 = "0" + n2;
	string ans = "";
	int carry = 0;
	for (int i = n1.length() - 1; i >= 0; i--) { 
		int num = (n1[i] - '0') + (n2[i] - '0') + carry; 
		carry = num / 10; 
		char dig = (num % 10) + '0'; 
		ans = dig + ans;
	}
	remleadingzeroes(ans);
	return ans;
}
void remleadingzeroes(string& n) { //this removes all zeroes in front of the string
	while (n.length() > 1 && n[0] == '0') {
		n = n.substr(1); 
	}
}
string subtract(string n1, string n2) {// this method also breaks down the string of numbers but it subtracts each number. returns the difference
	remleadingzeroes(n1); 
	remleadingzeroes(n2);
	while (n2.length() < n1.length()) { 
		n2 = '0' + n2;
	}
	for (int i = 0; i < (int)n2.length(); i++) { 
		n2[i] = '9' - n2[i] + '0';
	}
	string diff = sum("1", sum(n1, n2));
	diff = diff.substr(1);
	remleadingzeroes(diff);
	return diff;
}
string times(string n1, string n2) { //this method multiplies each number in the string and returns its product
	remleadingzeroes(n1);
	remleadingzeroes(n2);
	string rsum = "0";
	for (int i = 0; i < n1.length(); i++)
		for (int j = 0; j < n2.length(); j++) {
			string prod = to_string((n1[i] - '0') * (n2[j] - '0'));
			for (int k = 0; k < n1.length() - i - 1 + n2.length() - j - 1; k++)
				prod += "0";
			rsum = sum(rsum, prod);
		}
	return rsum;
}

string divide(string dividend, string divisor, string& remainder) { //Divide is called to find the quotient/gcf of the numerator and denominator
	remleadingzeroes(dividend); 
	remleadingzeroes(divisor);
	string quotient = "0"; 
	string newdiv = "0"; 
	list<string> stringList; 
	stringList.push_front(divisor); 
	newdiv = divisor; 
	while (compare(dividend, newdiv) == 1 || compare(dividend, newdiv) == 0) {
		newdiv = times("2", newdiv); 
		stringList.push_back(newdiv); 
	}
	stringList.pop_back(); 
	newdiv = stringList.back();
	remainder = dividend; 
	while (!stringList.empty()) { 
		if (compare(newdiv, remainder) == 1) { 
			quotient = times("2", quotient); 
			stringList.pop_back(); 
		}
		else {
			remainder = subtract(remainder, newdiv);
			quotient = sum("1", times("2", quotient)); 
			stringList.pop_back(); 
		}
		if (!stringList.empty()) { 
			newdiv = stringList.back(); 
		}
	}
	return quotient;
}

int compare(string a, string b) {// compare checks the size of strings as well as the size of numbers. returns greater than, less than, or equal 
	remleadingzeroes(a); 
	remleadingzeroes(b);

	if (a.length() > b.length()) { 
		return 1;
	}
	else if (a.length() < b.length()) { 
		return -1;
	}
	for (int i = 0; i < a.length(); i++) { 
		if ((a[i] - '0') < (b[i] - '0')) { 
			return -1;
		}
		else if ((a[i] - '0') > (b[i] - '0')) { 
			return 1;
		}
	}
	return 0; 
}
string GCF(string a, string b) { //Called to simplify the final fraction
	remleadingzeroes(a); 
	remleadingzeroes(b);
	string numerator = a; 
	string denominator = b; 
	string remainder = "0"; 
	string gcf = "0"; 
	while (denominator != "0") { 
		if (compare(numerator,denominator) == -1) { 
			remainder = numerator; 
			numerator = denominator; 
			denominator = remainder; 
		}
		gcf = divide(numerator, denominator, remainder); 
		numerator = denominator; 
		denominator = remainder; 
	}
	a = divide(a, numerator, remainder);
	b = divide(b, numerator, remainder); 
	return (a + "/" + b); 
}

string addFraction(string a, string b, string c, string d) {//method determines unsimplified numerator and denominator and requests to find the gcf to add the fractions together. returns the answer to reader
	remleadingzeroes(a); 
	remleadingzeroes(b);
	remleadingzeroes(c);
	remleadingzeroes(d);
	string num = sum(times(a, d), (times(b, c)));
	string den = times(b, d); 
	string frac = GCF(num, den); 
	return (" = " + frac); 
}
