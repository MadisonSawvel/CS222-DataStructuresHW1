

//Madison Sawvel

//Header file saves the methods which will be used and allows us to call on them later in
//the .cpp file.

#include <iostream>
#include <string>
#include <cstdlib>
#ifndef _ARITHMETIC_
#define _ARITHMETIC_

using namespace std;

int main(int argc, char** argv);
string sum(string n1, string n2);
void remleadingzeroes(string& n);
string subtract(string n1, string n2);
string times(string n1, string n2);
string divide(string dividend, string divisor, string& remainder);
int compare(string a, string b);
string GCF(string a, string b);
string addFraction(string a, string b, string c, string d);
#endif

