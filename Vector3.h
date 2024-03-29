#pragma once 

#include <math.h> 
#include <iostream> 

class Vector3 {
private:


public:
	static Vector3 forward; 
	static Vector3 backward; 
	static Vector3 left; 
	static Vector3 right; 
	static Vector3 up; 
	static Vector3 down; 
	static Vector3 zero;

	static float Dot(Vector3 v1, Vector3 v2); 
	static Vector3 Cross(Vector3 v1, Vector3 v2); 
	static float Angle(Vector3 v1, Vector3 v2); 
	static float Distance(Vector3 v1, Vector3 v2); 
	static Vector3 Project(Vector3 v1, Vector3 v2); 
	static Vector3 Reflect(Vector3 v1, Vector3 v2);

	Vector3 operator*(const float n) { return Vector3(n * x, n * y, n * z); } 
	friend Vector3 operator*(const float &n, const Vector3 &vect) { return n * vect; } 
	Vector3 operator/(const float n) { return Vector3(x / n, y / n, z / n); } 
	Vector3 operator+(const Vector3 other) { return Vector3(x + other.x, y + other.y, z + other.z); } 
	Vector3 operator-(const Vector3 other) { return Vector3(x - other.x, y - other.y, z - other.z); } 
	void operator=(const Vector3 v2) { x = v2.x; y = v2.y; z = v2.z; } 
	bool operator==(const Vector3 other) { return (x == other.x) && (y == other.y) && (z == other.z); } 
	bool operator!=(const Vector3 other) { return !(*this == other); } 
	friend std::ostream& operator<<(std::ostream& os, const Vector3 &v);

	float x; 
	float y; 
	float z;

	Vector3(float x_value, float y_value, float z_value) { x = x_value; y = y_value; z = z_value; }

	const float magnitude(); 
	const float magnitudeSquared(); 
	const Vector3 normalized(); 
	void Normalize();
};