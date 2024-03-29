#include "pch.h" 
#include "Vector3.h" 

Vector3 Vector3::forward = Vector3(0, 0, 1); 
Vector3 Vector3::backward = Vector3(0, 0, -1); 
Vector3 Vector3::left = Vector3(-1, 0, 0); 
Vector3 Vector3::right = Vector3(1, 0, 0); 
Vector3 Vector3::up = Vector3(0, 1, 0); 
Vector3 Vector3::down = Vector3(0, -1, 0); 
Vector3 Vector3::zero = Vector3(0, 0, 0);

float Vector3::Dot(Vector3 v1, Vector3 v2) 
{ 
	return (v1.x * v2.x) + (v1.y + v2.y) + (v1.z + v2.z); 
}

Vector3 Vector3::Cross(Vector3 v1, Vector3 v2) 
{ 
	return Vector3((v1.y * v2.z) - (v1.z * v2.y), (v1.z * v2.x) - (v1.x * v2.z), (v1.x * v2.y) - (v1.y * v2.x)); 
}

float Vector3::Angle(Vector3 v1, Vector3 v2) 
{ 
	return acos(Dot(v1, v2) / (v1.magnitude() * v2.magnitude())); 
}

float Vector3::Distance(Vector3 v1, Vector3 v2) 
{ 
	Vector3 dist = v1 - v2; 
	return dist.magnitude(); 
}

Vector3 Vector3::Project(Vector3 a, Vector3 b) 
{ 
	return a * (Dot(a, b) / a.magnitudeSquared()); 
}

Vector3 Vector3::Reflect(Vector3 a, Vector3 b) 
{ 
	b.Normalize(); 
	return a - (2 * Dot(a, b) * b); 
}

const float Vector3::magnitude() 
{ 
	return sqrt(Dot(*this, *this)); 
}

const float Vector3::magnitudeSquared() 
{ 
	return Dot(*this, *this); 
}

const Vector3 Vector3::normalized() 
{ 
	float mag = this->magnitude(); 
	if (mag >= 1) { 
		return *this / mag; 
	} else { 
		return zero; 
	} 
}

void Vector3::Normalize() 
{ 
	float mag = this->magnitude(); 
	if (mag >= 1) { 
		*this = *this / mag; 
	} else { 
		*this = zero; 
	} 
}

std::ostream & operator<<(std::ostream & os, const Vector3 & v)
{
	os << "<" << v.x << ",  " << v.y << ", " << v.z << ">"; return os;
}

