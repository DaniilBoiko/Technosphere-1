#include <stdio.h>
#include <iostream>
#include <string>
#include "numbers.dat"

using namespace std;

bool is_prime(int number) {
	if (number == 1) {
		return false;
	}

	for (int i = 2; i*i <= number; i++) {
		if (number % i == 0) {
			return false;
		}
	}

	return true;

}

int find_prime_count(int start, int end) {
	int result = 0;
	int is_parsing = false;

	if (end <= start) {
		return 0;
	}

	for (int i = 0; i < Size; i++) {
		if (is_parsing) {
			result += is_prime(Data[i]);

			if (Data[i] > end) {
				return -1;
			}

			if ((Data[i] == end)&(Data[i+1] != end)) {
				return result;
			}
		} else {
			if (Data[i] == start) {
				is_parsing = true;
				result += is_prime(Data[i]);
			}

			if (Data[i] > start) {
				return -1;
			}
		}
	}
}

int main(int argc, char* argv[]) {
	// Check for a wrong input
	if (((argc-1) % 2 != 0)|(argc-1 == 0)) {
		return -1;
	}

	// Iterate through pairs of values
	for (int i = 0; i < (argc-1)/2; ++i) {
		int n_of_primes = find_prime_count(std::atoi(argv[2*i+1]),std::atoi(argv[2*i+2]));

		if (n_of_primes == -1){
			return -1;
		}
		else {
			cout << n_of_primes << endl;
		}
	}

	return 0;
}
