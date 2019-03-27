#include <stdio.h>
#include <iostream>
#include <string>
#include <ctype.h>
#include <algorithm>

using namespace std;

void error() {
	// Raises an error
	cerr << "error" << endl;
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
int calc(const string& s, int len, int i, bool& error, bool minus = false);

int toi(const string& s, int len, int i, bool& error) {
	// Converts string to integer

	if (len == i) {
		error = true;
		return 0;
	} else {

		try {
			return stoi(s.substr(i, len - i));
		} catch (const std::invalid_argument&) {
			error = true;
			return 0;
		}

	}
}

int mul_div(const string& s, int len, int i, bool& error) {
	// Looks for multiplication and division operators

	int start = i;

	while ((i < len) & (s[i] != '*') & (s[i] != '/')) {
		i++;
	}

	if (i != len) {
		if (s[i] == '*') {
			return calc(s, i, start, error) * calc(s, len, i + 1, error);
		} else {
			if (calc(s, len, i + 1, error) == 0) {
				error = true;
				return 0;
			} else {
				return calc(s, i, start, error) / calc(s, len, i + 1, error);
			}
		}
	} else {
		return toi(s, len, start, error);
	}
}

int add_sub(const string& s, int len, int i, bool& error, bool minus = false) {
	// Looks for addition and subtraction operators

	int start = i;

	while ((i < len) & (s[i] != '+') & ((s[i] != '-') || !(is_minus(s, i)))) {
		i++;
	}

	if (i != len) {
		// Here it determines sign and if it's minus it inverts signs for the part of the statement

		if (s[i] == '+') {
			if (minus) {
				return calc(s, i, start, error) - calc(s, len, i + 1, error);
			} else {
				return calc(s, i, start, error) + calc(s, len, i + 1, error);
			}
		} else {
			if (minus) {
				return calc(s, i, start, error) + calc(s, len, i + 1, error);
			} else {
				return calc(s, i, start, error)
						- calc(s, len, i + 1, error, true);
			}
		}

	} else {
		return mul_div(s, len, start, error);
	}

}

int calc(const string& s, int len, int i, bool& error, bool minus) {
	// Calls add_sub

	return add_sub(s, len, i, error, minus);
}

int main(int argc, char** argv) {
	bool error_flag = false;

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
	for (int i = 0; i < str.length(); i++) {

		if (str[i] != ' ') {
			str[count++] = str[i];
		}
	}
	str.erase(count, str.length() - count);

	// Call the calculator
	int answer = calc(str, str.length(), 0, error_flag);

	if (!error_flag) {
		cout << answer << endl;
	} else {
		error();
		return 1;
	}
	return 0;
}
