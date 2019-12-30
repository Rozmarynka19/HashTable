#pragma once
#include <iostream>
#include <string>
#include <cmath>
using namespace std;

template <class T>
class Dynamic_Array
{
	T* array;
	int maxSize;

	const int AUGMENTATION_FACTOR = 2;

public:
	int currentSize;
	Dynamic_Array()
	{
		currentSize = 0;
		maxSize = 1;
		array = new T[1];
	}

	~Dynamic_Array()
	{
		currentSize = maxSize = 0;
		delete[] array;
		//array = 0;
	}

	void addElement(T data)
	{
		if (currentSize < maxSize)
		{
			array[currentSize] = data;
			currentSize++;
		}
		else
		{
			maxSize *= AUGMENTATION_FACTOR;

			T* extendedArray = new T[maxSize];

			for (int i = 0; i < currentSize; i++)
				extendedArray[i] = array[i];

			extendedArray[currentSize] = data;

			currentSize++;

			delete[] array;
			array = extendedArray;
		}
	}

	//returns true if the replacement completed or false if failed
	bool replaceData(int index, T data)
	{
		if (index >= 0 && index < currentSize)
		{
			array[index] = data;
			return true;
		}
		else
		{
			cout << "Replacement failed - index out of range" << endl;;
			return false;
		}

	}

	T getData(int index)
	{
		if (index >= 0 && index < currentSize)
		{
			return array[index];
		}
		else
		{
			cout << "Retrieving failed - index out of range" << endl;;
			return NULL;
		}
	}

	//full version
	string toString()
	{
		string outcome = "";

		outcome = "Number of array's elements: " + to_string(currentSize) + "\n";
		for (int i = 0; i < currentSize; i++)
		{
			outcome = outcome + to_string(array[i]) + " ";
		}

		outcome += "\n\n";

		return outcome;
	}

	//short version
	string toString(int numberOfElements)
	{
		string outcome = "";

		outcome = "Number of array's elements: " + to_string(currentSize) + "\n";
		for (int i = 0; i < numberOfElements; i++)
		{
			outcome = outcome + to_string(array[i]) + " ";
		}

		outcome += "\n\n";

		return outcome;
	}

	//char's version
	string toString(int numberOfElements, string(*elementToString)(T))
	{
		string outcome = "";

		outcome = "Number of array's elements: " + to_string(currentSize) + "\n";
		for (int i = 0; i < numberOfElements; i++)
		{
			outcome = outcome + elementToString(array[i]) + " ";
		}

		outcome += "\n\n";

		return outcome;
	}

};


