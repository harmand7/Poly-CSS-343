#include "stdafx.h"
#pragma once

#include <iostream>
#include <array>
using namespace std;


//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
//Harman Dhunna
//CSS 343
//Assignmen1
//
//This is the header file for the class polynomials.
//There are two friend functions that allow inputs and outputs.
//There are four constructors and one destructor.
//Assignment operator is overload
//Multiplication, Addition, subtraction operators are overload... as well as
//	the boolean equality operators.
//Required was the setCoeff() function
//Required was the getCoeff() function
//Provided is getLength() method that keeps track of how
//	big the array is.
//The private member variable: pointer to an array = coeffptr,
//	keeps track of the size of the array =length


class Poly
{

	friend ostream& operator<<(std::ostream &out, const Poly &val);
	friend istream& operator>>(std::istream &in, Poly &val);

public:
	Poly();
	~Poly();
	Poly(int, int);
	Poly(int);

	Poly(const Poly &copy);

	Poly& operator=(const Poly &);

	Poly operator*(const Poly &val) const;
	Poly operator+(const Poly &val) const;
	Poly operator-(const Poly &val) const;

	Poly& operator+=(const Poly &val);
	Poly& operator-=(const Poly &val);
	Poly& operator*=(const Poly &val);

	bool operator==(const Poly &val) const;
	bool operator!=(const Poly &val) const;

	void setCoeff(const int coeff, const int powerIndex);
	int getCoeff(const int index) const;
	int* getcoeffPtr()const;
	int getLength() const;


private:
	int *coeffPtr;
	int length;
};

