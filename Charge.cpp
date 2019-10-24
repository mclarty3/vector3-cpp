#include "pch.h" 
#include "Charge.h"
#include <iostream>

#define PI 3.14159265358979

void Charge::Print()
{
	std::cout << chargeString << " at " << position << " with charge " << charge;
	if (radius > 0) {
		std::cout << " and radius " << radius << std::endl;
	}
	else {
		std::cout << std::endl;
	}
}

Charge::Charge(Vector3 pos, float q, float r, std::function<Vector3(Vector3 testPoint)> eFieldFunc,
               std::function<float(Vector3)> potentialFunc, std::string nameOfCharge)
{
	position = pos;
	charge = q;
	radius = r;
	GetEFieldAtPoint = eFieldFunc;
	GetPotentialAtPoint = potentialFunc;
	chargeString = nameOfCharge;
}

Charge Charge::Monopole(Vector3 pos, float q)
{
	std::function<Vector3(Vector3)> eFieldFunc = [pos, q](Vector3 testPoint) 
	{ 
		Vector3 dist = testPoint - pos;
		if (dist.magnitude() == 0) {
			return Vector3::infinity;
		}
		float forceMagnitude = (k * q) / dist.magnitudeSquared();
		return forceMagnitude * dist.normalized();
	};

	std::function<float(Vector3)> potentFunc = [pos, q](Vector3 testPoint)
	{
		Vector3 dist = testPoint - pos;
		return (k * q) / dist.magnitude();
	};
	return Charge(pos, q, 0, eFieldFunc, potentFunc, "Monopole");
}


Charge Charge::Dipole(Vector3 negativeChargePos, Vector3 positiveChargePos, float q)
{
	float q2 = -q;

	Vector3 dist = positiveChargePos - negativeChargePos;
	Vector3 midpoint = Vector3::Midpoint(positiveChargePos, negativeChargePos);
	Vector3 dipoleMoment = dist * q;
	std::function<Vector3(Vector3)> eFieldFunc = [midpoint, dipoleMoment](Vector3 testPoint)
	{
		Vector3 distToMidpoint = testPoint - midpoint;
		if (distToMidpoint.magnitude() == 0) {
			return Vector3::infinity;
		}
		Vector3 distUnitVect = distToMidpoint.normalized();
		
		return k * (3 * Vector3::Dot(distUnitVect, dipoleMoment) * distUnitVect - dipoleMoment) / 
			   pow(distToMidpoint.magnitude(), 3);
	};
	
	std::function<float(Vector3)> potentialFunc = [midpoint, dipoleMoment](Vector3 testPoint)
	{
		Vector3 distToMidpoint = testPoint - midpoint;
		if (distToMidpoint.magnitude() == 0) {
			return INFINITY;
		}
		return Vector3::Dot(dipoleMoment, distToMidpoint.normalized()) * k / distToMidpoint.magnitudeSquared();
	};
	return Charge(midpoint, q, 0, eFieldFunc, potentialFunc, "Dipole");
}

Charge Charge::Dipole(Vector3 midpointPos, Vector3 dipoleMoment)
{
	std::function<Vector3(Vector3)> eFieldFunc = [midpointPos, dipoleMoment](Vector3 testPoint)
	{
		Vector3 distToMidpoint = testPoint - midpointPos;
		if (distToMidpoint.magnitude() == 0) {
			return Vector3::infinity;
		}
		Vector3 distUnitVect = distToMidpoint.normalized();

		return k * (3 * Vector3::Dot(distUnitVect, dipoleMoment) * distUnitVect - dipoleMoment) /
			pow(distToMidpoint.magnitude(), 3);
	};
	std::function<float(Vector3)> potentialFunc = [midpointPos, dipoleMoment](Vector3 testPoint)
	{
		Vector3 distToMidpoint = testPoint - midpointPos;
		if (distToMidpoint.magnitude() == 0) {
			return INFINITY;
		}
		return Vector3::Dot(dipoleMoment, distToMidpoint.normalized()) * k / distToMidpoint.magnitudeSquared();
	};
	return Charge(midpointPos, 0, 0, eFieldFunc, potentialFunc, "Dipole"); // This shouldn't have 0 charge
}


/* I'm gonna hold off on these for this commit, I really want to figure out a general way to
   calculate electric fields for these shapes in 3D regardless of orientation. Maybe I'll need
   calculus, who knows!

Charge Charge::Line(float q, Vector3 midpointPos, Vector3 velocity, float length)
{
	return Charge();
}

Charge Charge::Line(Vector3 midpointPos, Vector3 velocity, float chargeDensisty, float length)
{
	return Charge();
}

Charge Charge::InfiniteLine(Vector3 pos, Vector3 velocity, float chargeDensity)
{
	return Charge();
}

Charge Charge::Loop(Vector3 centerPos, Vector3 radius, float chargeDensity)
{
	return Charge();
}

Charge Charge::Loop(float charge, Vector3 centerPos, Vector3 radius)
{
	//std::function<Vector3(Vector3 testPoint)> eFieldFunc = []
	return Charge();
}

Charge Charge::Disk(Vector3 centerPos, Vector3 radius, float chargeDensity)
{
	return Charge();
}

Charge Charge::Disk(float charge, Vector3 centerPos, Vector3 radius)
{
	return Charge();
}
*/

Charge Charge::HollowSphere(float charge, Vector3 centerPos, float radius)
{
	std::function<Vector3(Vector3)> eFieldFunc = [centerPos, radius, charge](Vector3 testPoint)
	{
		if ((testPoint - centerPos).magnitude() < radius) {
			return Vector3::zero;
		}
		Vector3 dist = testPoint - centerPos;
		return ((k * charge) / dist.magnitudeSquared()) * dist.normalized();
	};
	std::function<float(Vector3)> potentFunc = [centerPos, radius, charge](Vector3 testPoint)
	{
		if ((testPoint - centerPos).magnitude() < radius) {
			testPoint.Clamp(radius); // Sets the magnitude of the test point to the radius of the sphere
		}
		Vector3 dist = testPoint - centerPos;
		return ((k * charge) / dist.magnitude());
	};
	return Charge(centerPos, charge, radius, eFieldFunc, potentFunc, "Hollow sphere");
}

Charge Charge::HollowSphere(Vector3 centerPos, float radius, float chargeDensity)
{
	float charge = chargeDensity * ((4 / 3) * PI * pow(radius, 3));
	return Charge::HollowSphere(charge, centerPos, radius);
}

Charge Charge::SolidSphere(float charge, Vector3 centerPos, float radius)
{
	float chargeDensity = charge / ((4 / 3) * PI * pow(radius, 3));
	return Charge::SolidSphere(centerPos, radius, chargeDensity);
}

Charge Charge::SolidSphere(Vector3 centerPos, float radius, float chargeDensity)
{
	float charge = 0;
	std::function<Vector3(Vector3)> eFieldFunc = [centerPos, radius, chargeDensity, &charge](Vector3 testPoint)
	{
		Vector3 dist = testPoint - centerPos;
		Vector3 force;
		if (dist.magnitude() == 0) {
			force = Vector3::infinity;
		}
		else if (dist.magnitude() < radius) // Inside sphere
		{
			force = ((chargeDensity * radius) / (3 * epsilonNaught)) * dist.normalized();
		}
		else {
			charge = chargeDensity * ((4 / 3) * PI * pow(radius, 3));
			force = ((((k * charge) / dist.magnitudeSquared())) * radius) * dist.normalized();
		}
		return force;
	};
	std::function<float(Vector3)> potentFunc = [centerPos, radius, chargeDensity, charge](Vector3 testPoint)
	{
		Vector3 dist = testPoint - centerPos;
		float potential;
		if (dist.magnitude() < radius) { // Inside sphere
			potential = ((k * charge) / (2 * radius)) * (3 - (dist.magnitudeSquared() / pow(radius, 2)));
		}
		else { // Outside sphere
			potential = (k * charge) / dist.magnitude();
		}
		return potential;
	};
	return Charge(centerPos, charge, radius, eFieldFunc, potentFunc, "Solid sphere");
}
