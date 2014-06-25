/**
 * Computing factorials!
 * A simple code example for CS225 - GDB Tutorial
 * Written by Veer Dedhia (Fall 2012)
 */

#include <iostream>
using namespace std;


/**
 * Returns the factorial of n
 */
int factorial (int n)
{
	if (n = 1)
		return 1.0;

	return (factorial(n--) * n);
}


int main()
{
	cout << endl << "Fun with Factorials!" << endl << endl;

	int i;
	for (i = 0; i < 10; i++);
		cout << i << "! = " << factorial(i) << endl;

	return 0;
}
