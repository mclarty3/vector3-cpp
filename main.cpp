// main.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "pch.h"
#include "Vector3.h"
#include "Charge.h"
#include "ChargeSystem.h"
#include <iostream>
#include <Windows.h>

const int MAX_CHARGES = 10;

enum CHARGE_TYPE
{
	MONOPOLE,
	DIPOLE,
	LINE,
	LOOP,
	DISK,
	HOLLOW_SPHERE,
	SOLID_SPHERE
};

void ClearScreen();

void ShowMainMenu(ChargeSystem sys);
void DisplaySystemView(ChargeSystem sys);
void AddChargeFromInput(ChargeSystem &sys);
Charge GetChargeFromInput(CHARGE_TYPE type);
void RemoveChargeFromInput(ChargeSystem &sys);
bool DisplayExitConfirmationMenu();

int main()
{
	// An example of what a system electric field calculator could look like!
	// Gonna finish up the other charge distributions next 

	ChargeSystem system = ChargeSystem(MAX_CHARGES);

	ShowMainMenu(system);
	
	/*while (true) {
		std::cout << "Type 'exit' to stop adding charges." << std::endl;
		std::cout << "Would you like to add 1) Point charge, 2) Dipole, 3) Hollow sphere, or 4) Solid sphere?: ";
		std::cin >> input;
		if (input == "1") {
			selectedDistribution = MONOPOLE;
		}
		else if (input == "2") {
			selectedDistribution = DIPOLE;
		}
		else if (input == "3") {
			selectedDistribution = HOLLOW_SPHERE;
		}
		else if (input == "4") {
			selectedDistribution = SOLID_SPHERE;
		}
		else if (input == "exit") {
			break;
		}
		else {
			std::cout << "Please enter a valid input." << std::endl;
			continue;
		}
		system.AddCharge(GetChargeFromInput(selectedDistribution));
	}
	while (true) {
		std::cout << "Would you like to find 1) the electric field or 2) the potential?: ";
		std::cin >> input;
		if (input == "1" || input == "2") {
			std::cout << "Please enter the x, y, and z coordinates of your test point, separated by spaces: ";
			std::cin >> pos_x >> pos_y >> pos_z;
			Vector3 pos = Vector3(pos_x, pos_y, pos_z);
			if (input == "1") {
				std::cout << "The electric field at " << pos << " is " << system.GetTotalElectricField(pos) << std::endl;
			}
			else {
				std::cout << "The potential at " << pos << " is " << system.GetTotalPotential(pos) << std::endl;
			}
		}
		else {
			std::cout << "Please enter a valid input." << std::endl;
			continue;
		}
	}*/
}

void ShowMainMenu(ChargeSystem sys)
{
	std::string input;
	while (true) {
		std::cout <<
			"Electrostatics simulator\n" <<
			"Please select an option:\n" <<
			"1) View system\n" <<
			"2) Add charges to system\n" <<
			"3) Remove charges from system\n" <<
			"4) Exit simulation\n";
		std::cin >> input;
		if (input == "1") {
			ClearScreen();
			DisplaySystemView(sys);
			ClearScreen();
		}
		else if (input == "2") {
			ClearScreen();
			AddChargeFromInput(sys);
			ClearScreen();
		}
		else if (input == "3") {
			ClearScreen();
			RemoveChargeFromInput(sys);
			ClearScreen();
		}
		else if (input == "4") {
			ClearScreen();
			if (DisplayExitConfirmationMenu()) {
				break;
			}
			else {
				continue;
				ClearScreen();
			}
		}
		else {
			ClearScreen();
		}
	} 
}

// Takes user input and calls GetChargeFromInput to add a charge to the ChargeSystem
void AddChargeFromInput(ChargeSystem &sys)
{
	std::string input;
	CHARGE_TYPE selectedDistribution;
	bool validInput = true;
	do {
		std::cout << sys.GetNumCharges() << " / " << sys.GetMaxCharges() << " charges" << std::endl;
		std::cout << "Type 'exit' to return to previous menu." << std::endl;
		std::cout << "Would you like to add 1) Point charge, 2) Dipole, 3) Hollow sphere, or 4) Solid sphere?: ";
		std::cin >> input;
		if (input == "1") {
			selectedDistribution = MONOPOLE;
		}
		else if (input == "2") {
			selectedDistribution = DIPOLE;
		}
		else if (input == "3") {
			selectedDistribution = HOLLOW_SPHERE;
		}
		else if (input == "4") {
			selectedDistribution = SOLID_SPHERE;
		}
		else if (input == "exit") {
			return;
		}
		else {
			std::cout << "Please enter a valid input." << std::endl;
			validInput = false;
		}
	} while (!validInput);
	sys.AddCharge(GetChargeFromInput(selectedDistribution));
}

// Takes user input dependent on charge type argument passed, and returns the appropriate charge
Charge GetChargeFromInput(CHARGE_TYPE type)
{
	float x_pos, y_pos, z_pos, charge, radius;
	Vector3 charge1Pos, charge2Pos;
	int chargeOrChargeDensity;
	switch (type)
	{
		case MONOPOLE:
			std::cout << "Please enter the x, y, and z positions of the charge, separated by spaces: ";
			std::cin >> x_pos >> y_pos >> z_pos;
			std::cout << "What is the monopole's charge?: ";
			std::cin >> charge;
			return Charge::Monopole(Vector3(x_pos, y_pos, z_pos), charge);
			break;
		case DIPOLE:
			std::cout << "Please enter the x, y, z positions of the negative charge, separated by spaces: ";
			std::cin >> x_pos >> y_pos >> z_pos;
			charge1Pos = Vector3(x_pos, y_pos, z_pos);
			std::cout << "Please enter the x, y, z positions of the positive charge, separated by spaces: ";
			std::cin >> x_pos >> y_pos >> z_pos;
			charge2Pos = Vector3(x_pos, y_pos, z_pos);
			std::cout << "What is the magnitude of charge (+q)?: ";
			std::cin >> charge;
			return Charge::Dipole(charge1Pos, charge2Pos, charge);
			break;
		/*case LINE:
			break;
		case LOOP:
			break;
		case DISK:
			break;*/
		case HOLLOW_SPHERE:
			std::cout << "Please enter the x, y, z positions of the center of the sphere: ";
			std::cin >> x_pos >> y_pos >> z_pos;
			std::cout << "What is the radius of the sphere?: ";
			std::cin >> radius;
			std::cout << "Would you like to enter 1) the charge or 2) the charge density?: ";
			std::cin >> chargeOrChargeDensity;
			if (chargeOrChargeDensity == 1) {
				std::cout << "Please enter the total charge of the sphere: ";
				std::cin >> charge;
				return Charge::HollowSphere(charge, Vector3(x_pos, y_pos, z_pos), radius);
			}
			else {
				std::cout << "Please enter the surface charge density of the sphere: ";
				std::cin >> charge;
				return Charge::HollowSphere(Vector3(x_pos, y_pos, z_pos), radius, charge);
			}
			break;
		case SOLID_SPHERE:
			std::cout << "Please enter the x, y, z positions of the center of the sphere: ";
			std::cin >> x_pos >> y_pos >> z_pos;
			std::cout << "What is the radius of the sphere?: ";
			std::cin >> radius;
			std::cout << "Would you like to enter 1) the charge or 2) the charge density?: ";
			std::cin >> chargeOrChargeDensity;
			if (chargeOrChargeDensity == 1) {
				std::cout << "Please enter the total charge of the sphere: ";
				std::cin >> charge;
				return Charge::SolidSphere(charge, Vector3(x_pos, y_pos, z_pos), radius);
			}
			else {
				std::cout << "Please enter the volume charge density of the sphere: ";
				std::cin >> charge;
				return Charge::SolidSphere(Vector3(x_pos, y_pos, z_pos), radius, charge);
			}
			break;
	}
	return Charge(); // This should never get returned 
}

// Displays the current charges in the system and allows the user to calculate electric field or potential
void DisplaySystemView(ChargeSystem sys)
{
	std::string input;
	int x_pos, y_pos, z_pos;
	bool repeat;

		std::cout << sys.GetNumCharges() << " / " << sys.GetMaxCharges() << " charges in the system" << std::endl;
		sys.PrintCharges();

	do {
		repeat = true;
		std::cout << "Would you like to calculate\n" <<
			"1) the electric field\n" <<
			"2) the potential\n" <<
			"3) the potential difference\n" <<
			"Type -1 to exit\n";
		std::cin >> input;
		if (input == "1") {
			std::cout << "Please input the x, y, z positions of the test point, separated by spaces: ";
			std::cin >> x_pos >> y_pos >> z_pos;
			std::cout << sys.GetTotalElectricField(Vector3(x_pos, y_pos, z_pos)) << " Newtons/Coulomb" << std::endl;
		}
		else if (input == "2") {
			std::cout << "Please input the x, y, z positions of the test point, separated by spaces: ";
			std::cin >> x_pos >> y_pos >> z_pos;
			std::cout << sys.GetTotalPotential(Vector3(x_pos, y_pos, z_pos)) << " Volts" << std::endl;
		} 
		else if (input == "3") {
			std::cout << "Please input the x, y, z positions of the first point, separated by spaces: ";
			std::cin >> x_pos >> y_pos >> z_pos;
			Vector3 pos1 = Vector3(x_pos, y_pos, z_pos);
			std::cout << "Please input the x, y, z positions of the second point, separated by spaces: ";
			std::cin >> x_pos >> y_pos >> z_pos;
			Vector3 pos2 = Vector3(x_pos, y_pos, z_pos);
			float diff = sys.GetTotalPotential(pos2) - sys.GetTotalPotential(pos1);
			std::cout << "The potential difference is " << diff << " Volts" << std::endl;
		}
		else if (input == "-1") {
			break;
		}
		else {
			ClearScreen();
			continue;
		}
		std::cout << "Would you like to perform another calculation? [y/n]: ";
		std::cin >> input;
		if (input != "y" && input != "Y") {
			ClearScreen();
			repeat = false;
		}
		std::cout << std::endl;
	} while (repeat);
}

// Takes user input and removes the requested charge from the system
void RemoveChargeFromInput(ChargeSystem &sys) 
{
	int numToRemove;
	for (int i = 0; i < sys.GetNumCharges(); i++) {
		std::cout << i + 1 << ") ";
		sys.GetCharge(i).Print();
	}
	std::cout << "Please enter the number of the charge you'd like to remove (-1 to exit): ";
	std::cin >> numToRemove;
	if (numToRemove == -1)
	{
		return;
	}
	sys.RemoveCharge(numToRemove - 1); // This function handles out of range calls, so no need to check
	std::cout << "Charge successfully removed!" << std::endl;
	system("pause");
}

// Confirms the user wants to quit before exiting the program
bool DisplayExitConfirmationMenu()
{
	std::string input;
	while (true) {
		std::cout << "Are you sure you want to exit? [y/n]: ";
		std::cin >> input;
		if (input == "y" || input == "Y") {
			return true;
		} 
		else if (input == "n" || input == "N") {
			return false;
		}
		else {
			continue;
		}
	}
}

// I'm sorry, I know this isn't very platform-friendly
void ClearScreen()
{
	system("cls");
}