#pragma once
#include "Resources.h"

template <typename T, int n>
struct Vertex {
	T data[n]{ 0 };
	T& operator[](const int& idx) {
		return data[idx];
	};
	T operator[](const int& idx) const {
		return data[idx];
	};
	T norm() {
		return std::sqrt(*this * *this);
	};
	Vertex<T, n> normalize() {
		return *this / norm();
	}
};

template <typename T, int n>
Vertex<T, n> operator+(const Vertex<T, n>& v1, const Vertex<T, n>& v2) {
	Vertex<T, n> vTmp = v1;
	for (int i = 0; i < n; i++) {
		vTmp[i] += v2[i];
	}
	return vTmp;
};

template <typename T, int n>
Vertex<T, n> operator+=(const Vertex<T, n>& v1, const Vertex<T, n>& v2) {
	Vertex<T, n> vTmp = v1;
	for (int i = 0; i < n; i++) {
		vTmp[i] += v2[i];
	}
	return vTmp;
};

template <typename T, int n>
Vertex<T, n> operator-(const Vertex<T, n>& v1, const Vertex<T, n>& v2) {
	Vertex<T, n> vTmp = v1;
	for (int i = 0; i < n; i++) {
		vTmp[i] -= v2[i];
	}
	return vTmp;
}

template <typename T, int n>
Vertex<T, n> operator-=(const Vertex<T, n>& v1, const Vertex<T, n>& v2) {
	Vertex<T, n> vTmp = v1;
	for (int i = 0; i < n; i++) {
		vTmp[i] -= v2[i];
	}
	return vTmp;
}

template <typename T, int n>
Vertex<T, n> operator-(const T& value, const Vertex<T, n>& v) {
	Vertex<T, n> vTmp = v;
	for (int i = 0; i < n; i++) {
		vTmp[i] = value - v[i];
	}
	return vTmp;
}

template <typename T, int n>
Vertex<T, n> operator*(const Vertex<T, n>& v1, const float& w) {
	Vertex<T, n> vTmp = v1;
	for (int i = 0; i < n; i++) {
		vTmp[i] *= w;
	}
	return vTmp;
}

template <typename T, int n>
Vertex<T, n> operator/(const Vertex<T, n>& v1, const float& w) {
	Vertex<T, n> vTmp = v1;
	for (int i = 0; i < n; i++) {
		vTmp[i] /= w;
	}
	return vTmp;
}

template <typename T, int n>
Vertex<T, n> operator/=(const Vertex<T, n>& v1, const float& w) {
	Vertex<T, n> vTmp = v1;
	for (int i = 0; i < n; i++) {
		vTmp[i] /= w;
	}
	return vTmp;
}

template<typename T, int n>
std::ostream& operator<<(std::ostream& out, Vertex<T, n>& v) {
	for (int i = 0; i < n; i++) {
		out << v[i];
		if (i != n - 1) {
			out << ',';
		}
	}
	out << std::endl;
	return out;
};

template <typename T, int n>
float vDot(const Vertex<T, n>& v1, const Vertex<T, n>& v2) {
	float value = 0;
	for (int i = 0; i < n; i++) {
		value += v1[i] * v2[i];
	}
	return value;
}

template <typename T, int n>
Vertex<T, n> lerp(const Vertex<T, n>& v1, const Vertex<T, n>& v2, float weight) {
	return (1.0f - weight) * v1 + weight * v2;
}

template <typename T, int n1, int n2>
Vertex<T, n1> squeeze(const Vertex<T, n2>& v) {
	Vertex<T, n1> res;
	for (size_t i = 0; i < n1; i++) {
		res[i] = v[i];
	}
	return res;
}

template<>
struct Vertex<float, 2> {
	float x = 0.0f, y = 0.0f;
	float& operator[](const int& idx) {
		return idx == 0 ? x : y;
	};
	float operator[](const int& idx) const {
		return idx == 0 ? x : y;
	};
};

template<>
struct Vertex<float, 4> {
	float x = 0.0f, y = 0.0f, z = 0.0f, w = 0.0f;
	float& operator[](const int& idx) {
		return idx == 0 ? x : (idx == 1 ? y : (idx == 2 ? z : w));
	};
	float operator[](const int& idx) const {
		return idx == 0 ? x : (idx == 1 ? y : (idx == 2 ? z : w));
	};
};

template<>
struct Vertex<float, 3> {
	float x = 0.0f, y = 0.0f, z = 0.0f;
	float& operator[](const int& idx) {
		return idx == 0 ? x : (idx == 1 ? y : z);
	};
	float operator[](const int& idx) const {
		return idx == 0 ? x : (idx == 1 ? y : z);
	};
	float norm() {
		return std::sqrt(vDot(*this, *this));
	};
	Vertex<float, 3> normalize() {
		return *this / norm();
	};
	static Vertex<float, 3> cross(const Vertex<float, 3>& v1, const Vertex<float, 3>& v2) {
		return Vertex<float, 3>{v1.y* v2.z - v2.y * v1.z, -(v1.x * v2.z - v2.x * v1.z), v1.x* v2.y - v2.x * v1.y};
	};
	Vertex<float, 4> homogeneous() {
		return Vertex<float, 4>{x, y, z, 1.0f};
	};
};

using Vertex2f = Vertex<float, 2>;
using Vertex3f = Vertex<float, 3>;
using Vertex4f = Vertex<float, 4>;