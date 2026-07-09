/*
 * Copyright (C) 2026  Ortega Froysa, Nicolás <nicolas@ortegas.org>
 * Author: Ortega Froysa, Nicolás <nicolas@ortegas.org>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <cmath>

template <typename T>
class Vec {
public:
	T x, y;

	Vec() : x(0), y(0) {}
	Vec(T x, T y) : x(x), y(y) {}

	inline void set(T x, T y) {
		this->x = x;
		this->y = y;
	}

	inline T length() const {
		return std::sqrt(static_cast<double>(x * x + y * y));
	}

	inline Vec<T> normalized() const {
		const T len = length();

		if (len == 0)
			return Vec<T>(0, 0);

		return Vec<T>(x / len, y / len);
	}

	inline Vec<T>& operator+=(const Vec<T> &other) {
		this->x += other.x;
		this->y += other.y;
		return *this;
	}
	inline Vec<T>& operator*=(const T scalar) {
		this->x *= scalar;
		this->y *= scalar;
		return *this;
	}

	inline Vec<T> operator+(const Vec<T> &other) const {
		return Vec<T>(this->x + other.x, this->y + other.y);
	}
	inline Vec<T> operator+(const T scalar) const {
		return Vec<T>(this->x + scalar, this->y + scalar);
	}

	inline Vec<T>& operator-=(const Vec<T> &other) {
		this->x -= other.x;
		this->y -= other.y;
		return *this;
	}
	inline Vec<T>& operator-=(const T scalar) {
		this->x -= scalar;
		this->y -= scalar;
		return *this;
	}

	inline Vec<T> operator-(const Vec<T> &other) const {
		return Vec<T>(this->x - other.x, this->y - other.y);
	}
	inline Vec<T> operator-(const T scalar) const {
		return Vec<T>(this->x - scalar, this->y - scalar);
	}

	inline Vec<T> operator*(const T scalar) const {
		return Vec<T>(this->x * scalar, this->y * scalar);
	}
	inline Vec<T> operator/(const T scalar) const {
		return Vec<T>(this->x / scalar, this->y / scalar);
	}
};
