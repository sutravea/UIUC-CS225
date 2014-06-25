/**
 * GDB Tutorial Example 2
 *
 * Author: Eunsoo Roh
 * CS 225 Fall 2012
 * Copyright (C) 2012 University of Illinois
 */

#include <iostream>
#include <string>

using namespace std;

/**
 * main entry point of the program.
 * \param argc # of arguments
 * \param argv array of argument strings
 */
int main(int argc, char *argv[])
{
	/**
	 * The goal is to find the last argument that partially matches
	 * our query string.
	 */

	if(argc < 2)
	{
		// we need at least one input
		cout << "USAGE: example2 input1 [input2 [..]]" << endl;
		return 1;
	}

	// The query string to find
	string query("cs225");
	string match;

	// check all arguments
	for(int i = 0; i <= argc; ++i)
	{
		// does the argument match our query?
		if(query.find(argv[i]) != string::npos)
		{
			// convert C-string argument to C++ string
			string match = argv[i];
		}
	}

	// did we found the match?
	if(!match.empty())
	{
		// absolutely!
		cout << "Match found: " << match << endl;
	}
	else
	{
		// not found
		cout << "Match was not found." << endl;
	}

	return 0;
}
