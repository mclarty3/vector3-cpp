// main.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "pch.h"
#include "Vector3.h"
#include <iostream>

int main()
{
	Vector3 v = Vector3(1, 1, 1);
	std::cout << v.normalized() << std::endl;

}

