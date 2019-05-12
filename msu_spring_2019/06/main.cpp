#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <thread>
#include <vector>

const size_t size_of_buffer = 20;

void merge(std::ifstream &in1, std::ifstream &in2, std::ofstream &out) {
	uint64_t in1_n;
	uint64_t in2_n;

	in1.read((char*) (&in1_n), sizeof(uint64_t));
	in2.read((char*) (&in2_n), sizeof(uint64_t));

	while (!in1.eof() && !in2.eof()) {
		if (in1_n > in2_n) {
			out.write((char*) (&in2_n), sizeof(uint64_t));
			in2.read((char*) (&in2_n), sizeof(uint64_t));
		} else {
			out.write((char*) (&in1_n), sizeof(uint64_t));
			in1.read((char*) (&in1_n), sizeof(uint64_t));

		}
	}

	while (!in1.eof()) {
		out.write((char*) (&in1_n), sizeof(uint64_t));
		in1.read((char*) (&in1_n), sizeof(uint64_t));
	}

	while (!in2.eof()) {
		out.write((char*) (&in2_n), sizeof(uint64_t));
		in2.read((char*) (&in2_n), sizeof(uint64_t));
	}
}

void sort(const std::string& in_filename, size_t start, size_t end,
		const std::string& filename) {
	std::ifstream in(in_filename, std::ios::binary);

	std::ofstream create(filename + "1", std::ios::binary);
	std::ofstream create_cache(filename + "11", std::fstream::binary);
	create.close();
	create_cache.close();

	std::fstream out(filename + "1",
			std::fstream::in | std::fstream::out | std::fstream::binary);
	std::fstream out_cache(filename + "11",
			std::fstream::in | std::fstream::out | std::fstream::binary);

	in.seekg(start);

	std::vector<uint64_t> buffer(size_of_buffer);
	bool flag = false;

	for (size_t i = start; i < end; i += size_of_buffer * sizeof(uint64_t)) {
		size_t how_many;

		if ((i + size_of_buffer * sizeof(uint64_t)) > end) {
			how_many = end - i;
		} else {
			how_many = size_of_buffer * sizeof(uint64_t);
		}

		in.read(reinterpret_cast<char*>(&buffer[0]), how_many);

		std::sort(buffer.begin(), buffer.end());


		if (!flag) {
			out_cache.seekp(0);
			out_cache.write((char*) &buffer[0], how_many);
			flag = true;

		}

		else {

			size_t current = 0;
			uint64_t number_cache;
			out.seekp(0);
			out_cache.seekg(0);

			size_t out_pos = 0;

			for (size_t j = 0; j < i-start; j += sizeof(uint64_t)) {

				out_cache.read((char *) &number_cache, sizeof(uint64_t));

				if (current != (how_many / sizeof(uint64_t)) - 1) {
					for (size_t k = current; k < (how_many / sizeof(uint64_t));
							k++) {

						if (buffer[k] > number_cache) {
							out.write((char*) (&number_cache),
									sizeof(uint64_t));

							current = k;
							break;
						} else {
							out.write((char*) (&buffer[k]), sizeof(uint64_t));

							current = k;

						}
					}
					if (current == (how_many / sizeof(uint64_t)) - 1) {
						out.write((char*) (&number_cache), sizeof(uint64_t));

					}
				} else {
					out.write((char*) (&number_cache), sizeof(uint64_t));

				}

			}

			out_cache.seekp(0);
			out.seekg(0);

			for (size_t j = 1; j < i - start + how_many; j += sizeof(uint64_t)) {
				uint64_t copy_buffer;
				out.read((char *) (&copy_buffer), sizeof(uint64_t));
				out_cache.write((char *) (&copy_buffer), sizeof(uint64_t));
			}
		}

	}
	std::remove((filename + "11").c_str());
}

int main() {
	std::ifstream in("numbers.bin", std::ios::binary | std::ios::ate);
	std::ofstream fout("numbers_sorted.bin", std::ios::binary);

	if (!in) {
		std::cerr << "Can't open";
		return -1;
	}

	if (in.is_open()) {
		size_t size = in.tellg();

		size_t middle = sizeof(uint64_t) * ((size / sizeof(uint64_t)) / 2);

		std::string inp = "numbers.bin";
		std::string out1 = "numbers1.bin";
		std::string out2 = "numbers2.bin";

		std::thread sort1(sort, std::cref(inp), 0, middle, std::cref(out1));
		std::thread sort2(sort, std::cref(inp), middle, size, std::cref(out2));

		sort1.join();
		sort2.join();

		std::ifstream in1("numbers1.bin1", std::ios::binary);
		std::ifstream in2("numbers2.bin1", std::ios::binary);

		merge(in1, in2, fout);
	}

	return 0;

}
