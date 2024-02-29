#pragma once
#include "Vertex.h"

template<typename T, int rows, int cols>
struct Matrix {
	T data[rows * cols]{ 0 };
	T& operator()(const int& i, const int& j) {
		return data[i * cols + j];
	};
	T operator()(const int& i, const int& j) const {
		return data[i * cols + j];
	};
	/*std::istream& operator>>(std::istream& in, std::initializer_list<T> dataList) {
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < cols; j++) {
				data[i * cols + j];
			}
		}
		return in;
	};*/
	static Matrix<T, rows, rows> Identity() {
		Matrix<T, rows, rows> mat;
		for (int i = 0; i < rows; i++) {
			mat(i, i) = 1;
		}
		return mat;
	}
};

template<typename T, int rows, int cols>
std::ostream& operator<<(std::ostream& out, Matrix<T, rows, cols>& mat) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			out << mat(i, j) << ' ';
		}
		out << '\n';
	}
	out << std::endl;
	return out;
};

template<typename T, int r1, int c1, int c2>
Matrix<T, r1, c2> operator*(const Matrix<T, r1, c1>& mat1, const Matrix<T, c1, c2>& mat2) {
	Matrix<T, r1, c2> res;
	for (int i = 0; i < r1; i++) {
		for (int j = 0; j < c1; j++) {
			for (int k = 0; k < c1; k++) {
				res(i, j) += mat1(i, k) * mat2(k, j);
			}
		}
	}
	return res;
}

template<typename T, int rows, int n>
Vertex<T, n> operator*(const Matrix<T, rows, n>& mat, const Vertex<T, n>& vtx) {
	Vertex<T, n> vTmp;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < n; j++) {
			vTmp[i] += mat(i, j) * vtx[j];
		}
	}
	return vTmp;
}

template<typename T, int r1, int c1, int r2, int c2>
void ToMatrix3f(Matrix<T, r1, c1>& res, const Matrix<T, r2, c2>& mat) {
	for (int i = 0; i < r1; i++) {
		for (int j = 0; j < c1; j++) {
			res(i, j) = mat(i, j);
		}
	}
}

using Matrix4f = Matrix<float, 4, 4>;
using Matrix3f = Matrix<float, 3, 3>;