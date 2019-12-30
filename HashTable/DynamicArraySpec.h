#pragma once
//this code is specialized version of DynamicArray for Linked_List<Pair<int>> type
#include <iostream>
#include <cstring>
#include "LinkedListSpec.h"
#include "DynamicArray.h"
#include "LinkedList.h"
#include "Pair.h"
#include <cmath>
using namespace std;

template <> class Dynamic_Array< Linked_List< Pair < int > > >
{
	Linked_List<Pair<int>>** array;
	int maxSize;

	//extends array and recalcuates HashCodes
	void Rehash() {
		int prevMaxSize = maxSize;
		maxSize *= AUGMENTATION_FACTOR;

		Linked_List<Pair<int>>** extendedArray = new Linked_List<Pair<int>> * [maxSize];

		for (int i = 0; i < maxSize; i++)
			extendedArray[i] = new Linked_List<Pair<int>>();

		for (int i = 0; i < prevMaxSize; i++)
		{
			if (!array[i]->isEmpty())
			{
				List_Node<Pair<int>>* tmp = array[i]->head;
				while (tmp)
				{
					int newHash = GetHash(tmp->data.key);
					extendedArray[newHash]->addToTail(&(tmp->data));
					tmp = tmp->next;
				}
			}
		}

		for (int i = 0; i < prevMaxSize; i++)
			delete array[i];
		delete[] array;
		array = extendedArray;
	}
	//returns HashCode based on the given key
	int GetHash(string key)
	{
		unsigned long sum = 0;
		for (int i = 0; i < key.length(); i++)
			sum = sum + key[i] * pow(31, key.length() - (i + 1));
		return sum % maxSize;
	}

public:
	int currentSize;
	const float MAX_FULFILLMENT = 0.75;
	const int AUGMENTATION_FACTOR = 2;
	Dynamic_Array()
	{
		currentSize = 0;
		maxSize = 10;
		array = new Linked_List<Pair<int>> * [maxSize];
		for (int i = 0; i < maxSize; i++)
			array[i] = new Linked_List<Pair<int>>();
	}

	~Dynamic_Array()
	{
		for (int i = 0; i < maxSize; i++)
			delete array[i];
		delete[] array;
		currentSize = maxSize = 0;
		//array = 0;
	}
	int GetMaxSize() { return maxSize; }
	//inserts new Pair into table
	void Put(string key, int value)
	{
		if (((float)(currentSize + 1) / (float)maxSize) > MAX_FULFILLMENT)
			Rehash();

		Pair<int> * newPair = new Pair<int>(key, value);
		int Hash = GetHash(key);

		if (array[Hash]->isEmpty())
		{
			array[Hash]->addToTail(newPair);
			currentSize++;
		}
		else
		{
			long searchResult = array[Hash]->Search(newPair->key);
			if (searchResult != -1)
				array[Hash]->OverwriteValue(searchResult, newPair->value);
			else
			{
				array[Hash]->addToTail(newPair);
				currentSize++;
			}
		}
		delete newPair;
	}
	//returns 0 if succeed 1 if failed
	bool SearchAndDelete(string key)
	{
		int Hash = GetHash(key);
		List_Node<Pair<int>>* temp = array[Hash]->head;
		if (array[Hash]->isEmpty()) return 1;

		int searchResult = array[Hash]->Search(key);
		if (searchResult == -1) return -1;
		temp = temp + searchResult;

		if (temp == array[Hash]->head)
		{
			array[Hash]->RemoveFromHead();
			currentSize--;
			return 0;
		}
		if (temp == array[Hash]->tail)
		{
			array[Hash]->RemoveFromTail();
			currentSize--;
			return 0;
		}

		temp->previous->next = temp->next;
		temp->next->previous = temp->previous;
		delete temp;
		array[Hash]->size--;
		currentSize--;
		return 0;
	}

	//returns pointer at found Pair with given key or NULL if failed
	Pair<int>* GetPair(string key)
	{
		int Hash = GetHash(key);
		List_Node<Pair<int>>* temp = array[Hash]->head;
		int searchResult = array[Hash]->Search(key);
		if (searchResult != -1) return &((temp + searchResult)->data);
		return NULL;
	}
	//returns statistics about lists (MaxListSize, MinListSize, AvrgListSize, how many lists aren't empty)
	string GetStats()
	{
		string outcome = "Stats:\n";
		int MinListSize = 100000, MaxListSize = 0, NoEmptyLists = 0;
		for (int i = 0; i < maxSize; i++)
		{
			if (array[i]->size != 0) 
			{
				NoEmptyLists++;
				if (array[i]->size < MinListSize) MinListSize = array[i]->size;
				if (array[i]->size > MaxListSize) MaxListSize = array[i]->size;
			}
			
		}
		outcome = outcome + "MinListSize: " + to_string(MinListSize)+"\n";
		outcome = outcome + "MaxListSize: " + to_string(MaxListSize)+"\n";
		outcome = outcome + "NoEmptyLists: " + to_string(NoEmptyLists)+"\n";
		outcome = outcome + "ListAvrgSize: " + to_string((double)currentSize/(double)NoEmptyLists)+"\n";
		return outcome;
	}
	//returns formated first numberOfElements lists
	string ToString(int numberOfElements)
	{
		string outcome = "Current size: " + to_string(currentSize) + "\nMax size: " + to_string(maxSize) + "\nTable:\n{";
		for (int i = 0; i < numberOfElements; i++)
		{
			if (!array[i]->isEmpty())
				outcome = outcome + "\n\t" + to_string(i) + ": " + array[i]->ToString();
		}
		outcome = outcome + "\n}\n";
		return outcome;
	}
};

string elementToString(char c)
{
	return string(1, c);
}