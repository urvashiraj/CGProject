#ifndef __MATH_UTILS_H__
#define __MATH_UTILS_H__

/*

	Copyright 2014 Etay Meiri

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <math.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>

#define ToRadian(x) (double)(((x) * M_PI / 180.0f))
#define ToDegree(x) (double)(((x) * 180.0f / M_PI))

struct Color {
	double r;
	double g;
	double b;

	Color() {}

	Color(double _r, double _g, double _b) {
		r = _r;
		g = _g;
		b = _b;
	}

	Color(double v) {
		r = g = b = v;
	}

  Color operator+(const Color &c) {
    return Color(r+c.r,g+c.g,b+c.b);
  }

  Color operator-(const Color &c) {
    return Color(r-c.r,g-c.g,b-c.b);
  }

  Color operator*(double f){
    return Color(f*r,f*g,f*b);
  }

	Color& operator+=(const Color& c) {
		r += c.r;
		g += c.g;
		b += c.b;

		return *this;
	}

	Color& operator-=(const Color& c) {
		r -= c.r;
		g -= c.g;
		b -= c.b;

		return *this;
	}

	Color& operator*=(double f) {
		r *= f;
		g *= f;
		b *= f;

		return *this;
	}

  Color operator*(const Color &c) const {
    return Color(r*c.r,g*c.g,b*c.b);
  }

	operator const double*() const {
		return &(r);
	}

};


struct Vector3f {
	double x;
	double y;
	double z;

	Vector3f() {
	}

	Vector3f(double _x, double _y, double _z) {
		x = _x;
		y = _y;
		z = _z;
	}

	Vector3f(double f) {
		x = y = z = f;
	}

  Vector3f operator+(const Vector3f& r) {
    return Vector3f(x+r.x,y+r.y,z+r.z);
  }

  Vector3f operator-(const Vector3f& r) {
    return Vector3f(x-r.x,y-r.y,z-r.z);
  }

  Vector3f operator*(double f) const {
    return Vector3f(f*x,f*y,f*z);
  }

	Vector3f& operator+=(const Vector3f& r) {
		x += r.x;
		y += r.y;
		z += r.z;

		return *this;
	}

	Vector3f& operator-=(const Vector3f& r) {
		x -= r.x;
		y -= r.y;
		z -= r.z;

		return *this;
	}

	Vector3f& operator*=(double f) {
		x *= f;
		y *= f;
		z *= f;

		return *this;
	}

	operator const double*() const {
		return &(x);
	}

  double Dot(const Vector3f& v) const {
    return x*v.x + y*v.y + z*v.z;
  }

	Vector3f Cross(const Vector3f& v) const {
		const double _x = y * v.z - z * v.y;
		const double _y = z * v.x - x * v.z;
		const double _z = x * v.y - y * v.x;

		return Vector3f(_x, _y, _z);
	}

	Vector3f & Normalize() {
		const double Length = sqrtf(x * x + y * y + z * z);

		x /= Length;
		y /= Length;
		z /= Length;

		return *this;
	}

	double dist(const Vector3f& other){
		double diffX = x - other.x;
		double diffY = y - other.y;
		double diffZ = z - other.z;
		double Length = sqrtf(diffX * diffX + diffY * diffY + diffZ * diffZ);
		return Length;	
	}

	double length() const{
		double Length = sqrtf(x * x + y * y + z * z);
		return Length;	
	}

	void Print() const {
		printf("(%.02f, %.02f, %.02f)", x, y, z);
	}
};

#endif /* __MATH_UTILS_H__ */
