
#include "Poly.h"


/*
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------

Constructors  and Destructor 
(1)
Constructors:
Takes in no parameters and creates a polynomial object of length zero and
	array of size zero. No coefficient is set.

(2)
Destructor:
Goes through the whole array and sets the coefficient to zero to make sure
	that no information is leaked. The deletes the array pointer revealing
	and memory taken. Sets the variable to NULL to confirm that no value 
	can retrieved

(3)
Constructors:
Takes in two parameter, one the coefficient and other is the index of where
	coefficient will be stored. The index represents the power of the 
	coefficient. 

The first check is to see if the index value is valid
The second check is to see if the coefficient is zero. If it is zero then
	no array is built. Therefore, no array can be printed incorrectly, since
	leading coefficient is not printed.

	If the coefficient is not zero then it creates the array of size
	power + 1 to allow for index 0 to be used.
	The array is filled with zero throughout to allow the random memory to
	be cleaned out
(4)
Constructors:
Create an array of size 1, and store the value passed in at index 0

(5)
Constructors:
Deep copy constructors.
Creates a new array of the same size of the array length passed in as 
	parameter. Each value is read as a primitive and copied into the new 
	array.

//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
*/
//(1)
Poly::Poly()
{
	length =0;
	coeffPtr = new int[0];
}
//(2)
Poly::~Poly()
{
	for (int i = 0; i < length; i++)
	{
		coeffPtr[i] = 0;
	}
	delete[] coeffPtr;
	coeffPtr = NULL;
}
//(3)
Poly::Poly(int Coeff, int Power)
{
	
	if (Power >= 0)
	{/*
		if (Coeff == 0)
		{
			coeffPtr = new int[0];
			length = 0;
		}*/
		//else
		//{
			length = Power + 1;
			coeffPtr = new int[length];
			for (int i = 0; i < length; i++)
			{
				coeffPtr[i] = 0;
			}
			coeffPtr[length - 1] = Coeff;

		//}
	}
	else
	{
		cout << "Cant have negative Poly power" << endl;
	}
}
//(4)
Poly::Poly(int Coeff)
{
	length = 1;
	coeffPtr = new int[length];
	coeffPtr[length - 1] = Coeff;
}

Poly::Poly(const Poly &copy)
{
	length = copy.getLength();
	coeffPtr = new int[length];
	for (int i = 0; i < copy.getLength(); i++)
	{
		this->coeffPtr[i] = copy.coeffPtr[i];
	}
}

/*
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------

Assignment operator overload.
Similar to a deep copy.
Checks if the value passed is not the same as the left hand side
delete the original array by making each value of the array 0 first then
deleting the array itself.
Setting the new size of the array. 
Creating the array with new size
Then copying over each of the value as primitive to deep copy the polynomial
Returning the polynomial.

//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
*/
Poly& Poly::operator=(const Poly &rhs)
{
	if (*this != rhs)
	{
		for (int i = 0; i < length; i++)
		{
			coeffPtr[i] = 0;
		}
		delete[] this->coeffPtr;
		length = rhs.getLength();
		coeffPtr = new int[length];
		for (int i = 0; i < rhs.length; i++)
		{
			this->coeffPtr[i] = rhs.coeffPtr[i];
		}
	}
	return *this;
}
/*
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------

Multiplication operator overload 
The algorithm for this method is inspired from the algorithm of the 
	multiplication
	The size of the new array is created from the sum of the two arrays.
	Goes through two for loops (one inside the other) to imitate the effect
	of the Foil method

//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
*/
Poly Poly::operator*(const Poly & val) const
{
	Poly temp(0, val.getLength() + length);

	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < val.getLength(); j++)
		{
			int product = getCoeff(i)*val.getCoeff(j);
			temp.setCoeff(temp.getCoeff(i + j) + product, i + j);
		}
	}
	return temp;

}
/*
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------

Addition operator Overload
Subtraction operator Overload
-Derived  from the plus/minus equals operator 

//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
*/
Poly Poly::operator+(const Poly & val) const
{
	Poly temp = *this;
	temp += val;
	return temp;
}
Poly Poly::operator-(const Poly & val) const
{
	Poly temp = *this;
	temp -= val;
	return temp;
}
/*
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------

Addition operator Overload
Subtraction operator Overload

int bigger keeps track of the bigger array size
int smaller keeps track of the smaller array size
boolean isOrginialBig is variable to keep track of if the left hand side is
	bigger than right hand side

	The first if-else statement organize and sets bigger, smaller, and 
	isOrginalBig. 
	The new array is made with the biggest possible size
	Then sum of the two primitive is stored into the new array
	If the Left hand side array is bigger than it will copy whats left of 
	that array and put it into the array.
	If other wise, then it will copy the rest of the other array.
	Then array pointers are managed and deleted accordingly

	Also manage if the summation results in the leading figure to be 
	equal zero, then the size of the array is changed.


//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
*/

Poly& Poly::operator+=(const Poly &val)
{
	//add the val to this. This is the one that changes. So this array= val+this
	int bigger;
	int smaller;
	bool isOrginalBig;
	if (val.getLength() > length)
	{
		bigger = val.getLength();
		smaller = length;
		isOrginalBig = false;
	}
	else
	{
		smaller = val.getLength();
		bigger = length;
		isOrginalBig = true;
	}

	int *pArray = new int[bigger];
	for (int i = 0; i < smaller; i++)
	{
		pArray[i] = val.coeffPtr[i] + coeffPtr[i];
		//add both of the coeeficent to the array as one.
		//subtract the length of bigger one and then start the array to fillout the rest of it
	}
	//add rest of the array into the new array
	if (isOrginalBig)
	{
		for (int i = smaller; i < bigger; i++)
		{
			pArray[i] = coeffPtr[i];
		}
	}
	else
	{
		for (int i = smaller; i < bigger; i++)
		{
			pArray[i] = val.coeffPtr[i];
		}
	}
	int *temp =this->coeffPtr;
	coeffPtr = pArray;
	delete[] temp;
	length = bigger;
	return *this;
	// the bigger one adds the new array
}
Poly& Poly::operator-=(const Poly &rhs)
{
	int bigger;
	int smaller;
	bool isOrginalBig;
	if (rhs.getLength() > length)
	{
		bigger = rhs.getLength();
		smaller = length;
		isOrginalBig = false;
	}
	else
	{
		smaller = rhs.getLength();
		bigger = length;
		isOrginalBig = true;
	}

	int *pArray = new int[bigger];



	for (int i = 0; i < smaller; i++)
	{
		pArray[i] = coeffPtr[i] - rhs.coeffPtr[i];
		//add both of the coefficient to the array as one.
		//subtract the length of bigger one and then start the array to fill out the rest of it
		//
	}
	//add rest of the array into the new array
	if (isOrginalBig)
	{
		for (int i = smaller; i < bigger; i++)
		{
			pArray[i] = coeffPtr[i];
		}
	}
	else
	{
		for (int i = smaller; i < bigger; i++)
		{
			pArray[i] = -rhs.coeffPtr[i];
		}
	}
	int nLength = bigger - 1;
	bool IsSmaller = false;
	while (pArray[nLength] == 0)
	{
		nLength--;
		IsSmaller = true;
	}
	if (IsSmaller)
	{
		int *temp = coeffPtr;
		delete[] temp;
		length = nLength + 1;
		coeffPtr = new int[length];
		for (int i = 0; i < length; i++)
		{
			coeffPtr[i] = pArray[i];
			pArray[i] = 0;
		}
		delete[] pArray;
		return *this;
	}
	int *temp = coeffPtr;
	coeffPtr = pArray;
	length = bigger;
	delete[] temp;
	return *this;
}

//Assignment of *= overload is derived from * overload 
Poly& Poly::operator*=(const Poly &val)
{
	Poly temp = *this;
	temp = temp *val;
	*this = temp;
	return *this;
}

/*
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
Has a index integer j which increments through the array of both the this 
	and the right hand side array.
	If the array is the same length then none of the inner if-else statements
	get executed except when the arrays have reached the end. 
	The inner statements execute if one array is bigger but has zeros as 
	there leading terms.

//--------------------------------------------------------------------------
//--------------------------------------------------------------------------

*/

bool Poly::operator==(const Poly &val) const
{
	int j = 0;

	while (coeffPtr[j] == val.coeffPtr[j])
	{
		if (j == length-1 && val.getLength()-1 == j)
		{
			return true;
		}
		if (j == length-1)
		{
			while (val.coeffPtr[j] == 0&&j< val.getLength())//the other is all zero
			{
				if (val.getLength()-1 == j)
				{
					return true;
				}
				j++;
			}
			
		}
		else if (j == val.getLength()-1)
		{
			while (coeffPtr[j]==0&&length > j)
			{
				if (length -1 == j)
				{
					return true;
				}
				j++;
			}
		}
		j++;
	}
	return false;

}
//Negation of the == operator
bool Poly::operator!=(const Poly&val) const
{
	return !(*this == val);
}

/*
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
Sets the coefficient by taking the index where the coefficient should be 
placed.
If the coefficient is zero then the array does not set to that power.

If the Power Index is bigger than the array currently available then a new 
array is built and the data is deep copied and old adult is deleted.

//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
*/

void Poly::setCoeff(const int coeff, const int powerIndex)
{//take the power if bigger make a new array
	//if power index is same as length -1; then resize the array
	//apply same logic over the constructors
	if (powerIndex == length - 1&&coeff == 0)
	{
		int*temp = new int[powerIndex - 1];
		coeffPtr[powerIndex] = 0;
		for (int i = 0; i < powerIndex; i++)
		{
			temp[i] = coeffPtr[i];
			coeffPtr[i] = 0;
		}
		int *delPtr = coeffPtr;
		coeffPtr = temp;
		delete[] delPtr;
	}
	if (powerIndex > length)
	{
		int *temp = new int[powerIndex+1];
		for (int i = 0; i <= powerIndex; i++)
		{
			temp[i] = 0;
		}
		for (int i = 0; i < length; i++)
		{
			temp[i] = coeffPtr[i];
			coeffPtr[i] = 0;
		}
		int *delPtr = coeffPtr;
		coeffPtr = temp;
		length = powerIndex + 1;
		coeffPtr[powerIndex] = coeff;
		delete[] delPtr;
	}
	else if(powerIndex< 0)
	{
		cerr << "Can not set coeff in this index";
		return;

	}
	else
	{
		coeffPtr[powerIndex] = coeff;
	}
}

/*
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
Checks if the index is inbound with the array
return the coefficient from the indicated array
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
*/

int Poly::getCoeff(const int index) const
{
	//check if index array in bound 
	if (index < length && index >= 0) 
	{
		return coeffPtr[index];
	}
	else
	{
		return -1;
	}
}

/*
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
Not really used, but allows us to access the pointer array from the driver 
file for testing
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
*/

int* Poly::getcoeffPtr() const
{
	return coeffPtr;
}

/*
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
returns the length of the array
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
*/
int Poly::getLength() const
{
	return length;
}

/*
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
Output operator overload. 
Runs through the array backwards till it get to zero
Checks if the value is not zero
If coefficient is zero, then that index is skipped
otherwise checks if the number is positive or negative and prints to the 
console accordingly 
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
*/

ostream& operator<<(ostream &out, const Poly &val)
{
	for (int i = val.getLength() - 1; i >= 0; i--)
	{
		if (val.coeffPtr[i] != 0)
		{
			if (i == 0)
			{
				if (val.coeffPtr[i] >= 0) {
					out << " +" << val.coeffPtr[i];
				}
				else
				{
					out << " " << val.coeffPtr[i];
				}
			}
			else if (i == 1)
			{
				if (val.coeffPtr[i] >= 0) {
					out << " +" << val.coeffPtr[i] << "x";
				}
				else
				{
					out << " " << val.coeffPtr[i] << "x";
				}
			}
			else 
			{
				if (val.coeffPtr[i] >= 0) {
					out << " +" << val.coeffPtr[i] << "x^" << i;
				}
				else
				{
					out << " " << val.coeffPtr[i] << "x^" << i;
				}
			}
		}
	}
	return out;
	//return out << "Hours: " << time.hours << " Minutes: " << time.minutes << " Seconds: " << time.seconds;
}

/*
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
Input stream operator overload
The user has to enter two integers at time. First is coefficient and 
the next is the index (power) of the coefficient

It call the setCoefficient()  method to place it in the correct place
it checks if the power and coefficient are not -1; which is the stopping 
point

Runs in a loop to keep taking inputs from the user. So it can be a lot
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
*/
istream& operator>>(std::istream &in, Poly &val)
{
	int coeffs, power;
	in >> coeffs >> power;
	while (coeffs != -1 && power != -1)
	{
		val.setCoeff(coeffs, power);
		in >> coeffs >> power;
	}
	return in;
}