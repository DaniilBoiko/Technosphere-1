#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <thread>
#include <vector>

using namespace std;

const size_t buff_size = 1024 * 512;

void merge_files(const string &in1, const string &in2, const string &out) {
	ifstream inf_1(in1, std::ios::binary);
	ifstream inf_2(in2, std::ios::binary);

	ofstream output(out, std::ios::binary);
	uint64_t buffer1;
	uint64_t buffer2;

	while (inf_1.read(reinterpret_cast<char*>(&buffer1), sizeof(buffer1))
			&& inf_2.read(reinterpret_cast<char*>(&buffer2), sizeof(buffer2))) {
		if (buffer1 > buffer2) {
			unsigned char value[sizeof(buffer1)];
			std::memcpy(value, &buffer1, sizeof(buffer1));

			output.write(reinterpret_cast<char*>(&value), sizeof(uint64_t));

		} else {
			unsigned char value[sizeof(buffer2)];
			std::memcpy(value, &buffer2, sizeof(buffer2));

			output.write(reinterpret_cast<char*>(&value), sizeof(uint64_t));

		}
	}

	unsigned char buffer[sizeof(uint64_t)];

	while (inf_1.read((char*) &buffer, sizeof(buffer))) {
		output.write((char*) &buffer, sizeof(uint64_t));
	}
	while (inf_2.read((char*) &buffer, sizeof(buffer2))) {
		output.write((char*) &buffer, sizeof(uint64_t));
	}

	remove(in1.c_str());
	remove(in2.c_str());

}

void merge(const string &in, const vector<uint64_t> &out_new) {
	string out = in + ".cache";
	string out_temp = in + "tmp.cache";

	ifstream input_f(out, std::ios::binary);
	ofstream output_cache(out_temp, std::ios::binary);

	size_t vector_size = out_new.size();
	size_t current_pos = 0;

	uint64_t buffer;

	while (input_f.read(reinterpret_cast<char*>(&buffer), sizeof(buffer))) {
		for (int i = current_pos; i < vector_size; i++) {
			if (buffer < out_new[i]) {
				output_cache.write(reinterpret_cast<char*>(&buffer),
						sizeof(uint64_t));
				current_pos = i;
				break;
			} else {
				unsigned char value[sizeof(out_new[i])];
				std::memcpy(value, &out_new[i], sizeof(out_new[i]));

				output_cache.write(reinterpret_cast<char*>(&value),
						sizeof(uint64_t));
			}
		}
	}

	for (int i = current_pos; i < vector_size; i++) {
		unsigned char value[sizeof(out_new[i])];
		std::memcpy(value, &out_new[i], sizeof(out_new[i]));
		output_cache.write(reinterpret_cast<char*>(&value), sizeof(uint64_t));
	}

	remove(out.c_str());
	rename(out_temp.c_str(), out.c_str());

}

void sort_file(const string &in) {
	ifstream input_f(in, std::ios::binary);

	vector<uint64_t> buffer(buff_size);
	size_t current_pos = 0;

	uint64_t number;

	while (input_f.read(reinterpret_cast<char*>(&number), sizeof(number))) {
		if (current_pos >= buff_size) {
			sort(buffer.begin(), buffer.end());
			merge(in, buffer);
			current_pos = 0;
		} else {
			buffer[current_pos] = number;
			current_pos += 1;
		}

	}

}

int main() {
	const string file = "/Users/daniilboiko/n.numbers";

	ifstream input_f(file, std::ios::binary);
	ofstream output1(file + "1", std::ios::binary);
	ofstream output2(file + "2", std::ios::binary);

	bool flag = true;
	uint64_t number;

	if (!input_f or !output1 or !output2) {
		return -1;
	}

	while (input_f.read(reinterpret_cast<char*>(&number), sizeof(number))) {
		if (flag) {
			output1.write(reinterpret_cast<char*>(&number), sizeof(number));
			flag = false;
		} else {
			output2.write(reinterpret_cast<char*>(&number), sizeof(number));
			flag = true;

		}
		cout << number << endl;
	}

	thread sort_1(sort_file, file + "1");
	thread sort_2(sort_file, file + "2");

	sort_1.join();
	sort_2.join();

	merge_files(file + "1.cache", file + "2.cache", file);

	return 0;
}
