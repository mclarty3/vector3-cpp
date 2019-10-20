// main.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "pch.h"
#include "Vector3.h"
#include "Charge.h"
#include <iostream>

int main()
{
	Charge testMono = Charge::Monopole(Vector3(0, 0, 0), -10);
	Vector3 testPoint = Vector3(1, 0, 0);
	std::cout << testMono.getFieldAtPoint(testPoint) << std::endl;
}

