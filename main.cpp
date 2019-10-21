// main.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "pch.h"
#include "Vector3.h"
#include "Charge.h"
#include <iostream>

const int MAX_CHARGES = 10;

void addCharge(Charge, Charge[], int&);
Vector3 calculateTotalEField(Charge[], int, Vector3);
float calculateTotalPotential(Charge[], int, Vector3);

int main()
{
	// An example of what a system electric field calculator could look like!
	// Gonna finish up the other charge distributions next 

	Charge system[MAX_CHARGES];
	int numCharges = 0;

	std::string input, chargeOrDensity;
	float pos_x, pos_y, pos_z, charge, chargeDensity, radius;
	while (true) {
		std::cout << "Type 'exit' to stop adding charges." << std::endl;
		std::cout << "Would you like to add a 1) Point charge, 2) Hollow sphere, or 3) Solid sphere?: ";
		std::cin >> input;
		if (input == "1" || input == "2" || input == "3") {
			std::cout << "Please enter the x, y, and z positions of the charge, separated by a space: ";
			std::cin >> pos_x >> pos_y >> pos_z;
			if (input == "2" || input == "3") {
				std::cout << "What is the sphere's radius?: ";
				std::cin >> radius;
				while (true) {
					std::cout << "Would you like to input 1) the sphere's total charge, or 2) the charge density?: ";
					std::cin >> chargeOrDensity;
					if (chargeOrDensity == "1") {
						std::cout << "Please enter the sphere's total charge: ";
						std::cin >> charge;
					}
					else if (chargeOrDensity == "2") {
						std::cout << "Please enter the sphere's charge density: ";
						std::cin >> chargeDensity;
					}
					else {
						std::cout << "Please enter a valid input." << std::endl;
						continue;
					}
				}
				if (input == "2") {
					if (chargeOrDensity == "1") {
						addCharge(Charge::HollowSphere(charge, Vector3(pos_x, pos_y, pos_z), radius), system, numCharges);
					}
					else {
						addCharge(Charge::HollowSphere(Vector3(pos_x, pos_y, pos_z), radius, chargeDensity), system, numCharges);
					}
				}
				else {
					if (chargeOrDensity == "1") {
						addCharge(Charge::SolidSphere(charge, Vector3(pos_x, pos_y, pos_z), radius), system, numCharges);
					}
					else {
						addCharge(Charge::SolidSphere(Vector3(pos_x, pos_y, pos_z), radius, chargeDensity), system, numCharges);
					}
				}
			}
			else {
				std::cout << "What is the monopole's charge?: ";
				std::cin >> charge;
				addCharge(Charge::Monopole(Vector3(pos_x, pos_y, pos_z), charge), system, numCharges);
			}
		} 
		else if (input == "quit") {
			break;
		}
		else {
			std::cout << "Please enter a valid input." << std::endl;
			continue;
		}
	}
	while (true) {
		std::cout << "Would you like to find 1) the electric field or 2) the potential?: ";
		std::cin >> input;
		if (input == "1" || input == "2") {
			std::cout << "Please enter the x, y, and z coordinates of your test point, separated by spaces: ";
			std::cin >> pos_x >> pos_y >> pos_z;
			Vector3 pos = Vector3(pos_x, pos_y, pos_x);
			if (input == "1") {
				std::cout << "The electric field at " << pos << " is " << calculateTotalEField(system, numCharges, pos) << std::endl;
			}
			else {
				std::cout << "The potential at " << pos << " is " << calculateTotalPotential(system, numCharges, pos) << std::endl;
			}
		}
		else {
			std::cout << "Please enter a valid input." << std::endl;
			continue;
		}
	}
}

void addCharge(Charge charge, Charge chargeSystem[], int& sizeOfSystem)
{
	if (sizeOfSystem < MAX_CHARGES) {
		chargeSystem[sizeOfSystem] = charge;
		sizeOfSystem++;
	}
	else {
		std::cout << "System is full!" << std::endl;
	}
}

Vector3 calculateTotalEField(Charge chargeSystem[], int size, Vector3 testPoint)
{
	Vector3 totalForce = Vector3();
	for (int i = 0; i < size; i++) {
		totalForce = totalForce + chargeSystem[i].getEFieldAtPoint(testPoint);
	}
	return totalForce;
}

float calculateTotalPotential(Charge chargeSystem[], int size, Vector3 testPoint)
{
	float totalPotential = 0;
	for (int i = 0; i < size; i++) {
		totalPotential += chargeSystem[i].getPotentialAtPoint(testPoint);
	}
	return totalPotential;
}
