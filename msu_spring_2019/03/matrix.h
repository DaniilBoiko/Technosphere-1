#include <stdio.h>
#include <iostream>

using namespace std;

class Matrix {
	size_t columns;
	size_t rows;
	int **content;

public:
	Matrix(size_t _rows, size_t _columns) :
			columns(_columns), rows(_rows), content(new int*[rows]) {
		for (int i = 0; i < rows; ++i) {
			content[i] = new int[columns];
		}
	}

	Matrix(const Matrix &other) :
			columns(other.columns), rows(other.rows), content(new int*[rows]) {
		for (int i = 0; i < rows; ++i) {
			content[i] = new int[columns];
		}
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < columns; ++j) {
				content[i][j] = other.content[i][j];
			}
		}
	}

	size_t getRows() const {
		return rows;
	}

	size_t getColumns() const {
		return columns;
	}

	class Row {
	public:
		int *content;
		size_t columns;

		Row(int *row, const int c) :
				content(row), columns(c) {
		}

		const int& operator [](size_t i) const {
			if (i >= columns) {
				throw std::out_of_range("");
			} else {
				return content[i];
			}
		}

		int& operator [](size_t i) {
			if (i >= columns) {
				throw std::out_of_range("");
			} else {
				return content[i];
			}
		}

	};

	const Row operator [](const size_t i) const {
		if (i >= rows) {
			throw std::out_of_range("");
		} else {
			Row row(content[i], columns);
			return row;
		}
	}

	Row operator [](const size_t i) {
		if (i >= rows) {
			throw std::out_of_range("");
		} else {
			Row row(content[i], columns);
			return row;
		}
	}

	// Равенство
	bool operator==(const Matrix& other) const {
		if (this == &other)
			return true;

		if (rows != other.rows ||  columns != other.columns) {
			return false;
		}

		for (size_t i = 0; i < rows; ++i) {
			for (size_t j = 0; j < columns; ++j) {
				if (content[i][j] != other.content[i][j]) {
					return false;
				}
			}
		}
		return true;
	}

	// Неравенство
	bool operator!=(const Matrix& other) const {
		return !(*this == other);
	}

	// Произведение
	Matrix& operator*=(int c) {
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < columns; ++j) {
				content[i][j] *= c;
			}
		}

		return *this;
	}

	~Matrix() {
		for (int i = 0; i < rows; ++i) {
			delete[] content[i];
		}
		delete[] content;
	}

};
