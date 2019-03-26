#include <stdio.h>
#include <iostream>
#include <string>
#include <ctype.h>
#include <algorithm>

using namespace std;

void error() {
	// Raises an error

	cerr << "error" << endl;
	exit(1);
}

double is_minus(const string& s, int i) {
	// Checks for the unary minus

	if (i == 0) {
		return 0;
	} else {
		if (isdigit(s[i - 1])) {
			return 1;
		} else {
			return 0;
		}
	}
}


// Declaration of the 'calc' function
int calc(const string& s, int len, int i, bool minus = false);

int toi(const string& s, int len, int i) {
	// Converts string to integer

	if (len == i) {
		error();
	} else {

		try {
			return stoi(s.substr(i, len - i));
		} catch (const std::invalid_argument&) {
			error();
		}

	}
}

int mul_div(const string& s, int len, int i) {
	// Looks for multiplication and division operators

	int start = i;

	while ((i < len) & (s[i] != '*') & (s[i] != '/')) {
		i++;
	}

	if (i != len) {
		if (s[i] == '*') {
			return calc(s, i, start) * calc(s, len, i + 1);
		} else {
			if (calc(s, len, i + 1) == 0) {
				error();
			} else {
				return calc(s, i, start) / calc(s, len, i + 1);
			}
		}
	} else {
		return toi(s, len, start);
	}
}

int add_sub(const string& s, int len, int i, bool minus = false) {
	// Looks for addition and subtraction operators

	int start = i;

	while ((i < len) & (s[i] != '+') & ((s[i] != '-') || !(is_minus(s, i)))) {
		i++;
	}

	if (i != len) {
		// Here it determines sign and if it's minus it inverts signs for the part of the statement

		if (s[i] == '+') {
			if (minus) {
				return calc(s, i, start) - calc(s, len, i + 1);
			} else {
				return calc(s, i, start) + calc(s, len, i + 1);
			}
		} else {
			if (minus) {
				return calc(s, i, start) + calc(s, len, i + 1);
			} else {
				return calc(s, i, start) - calc(s, len, i + 1, true);
			}
		}

	} else {
		return mul_div(s, len, start);
	}

}

int calc(const string& s, int len, int i, bool minus) {
	// Calls add_sub

	return add_sub(s, len, i, minus);
}

int main(int argc, char** argv) {

	// Check args
	if (argc > 2) {
		error();
		return 1;
	}
	if (argc == 1) {
		error();
		return 1;
	}

	// Get an argument
	string str = argv[1];

	// Remove spaces
	int count = 0;
	for (int i = 0; str[i]; i++) {

		if (str[i] != ' ') {
			str[count++] = str[i];
		}
	}
	str[count] = '\0';

	// Call the calculator
	cout << calc(str, str.length(), 0) << endl;

	return 0;
}
