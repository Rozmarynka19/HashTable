#include <iostream>
#include <cstring>
#include <time.h>
#include "DynamicArraySpec.h"
#include "DynamicArray.h"
#include "LinkedList.h"
#include "LinkedListSpec.h"
#include "Pair.h"
using namespace std;
//returns string with 6 characters
string static GetRandomKey()
{
	string outcome = "";
	for (int i = 0; i < 6; i++)
		outcome = outcome + string(1,(char)(rand() % 26 + 97));
	return outcome;
}

int main()
{
	Dynamic_Array<Linked_List<Pair<int>>>* HashTable = new Dynamic_Array<Linked_List<Pair<int>>>();
	const int MAX_INDEX = 6;
	srand(time(NULL));
	cout.precision(numeric_limits<double>::max_digits10);

	for (int i = 1; i <= MAX_INDEX; i++)
	{
		const int N = pow(10, i);

		clock_t start = clock();
		for (int n = 0; n < N; n++)
			HashTable->Put(GetRandomKey(), n);
		clock_t stop = clock();

		double result = (stop - start) / (double)CLOCKS_PER_SEC;
		cout << HashTable->ToString(10) << endl;
		cout << "Adding time: " << result << endl;
		cout << "----------------------------------------------------------------------------------------------------------------" << endl;
		
		//===============================================================================================
		const int M = pow(10, 4);
		int hits = 0;
		start = clock();
		for (int m = 0; m < M; m++)
		{
			Pair<int>* pair = HashTable->GetPair(GetRandomKey());
			if (pair) hits++;
		}
		stop = clock();

		result = (stop - start) / (double)CLOCKS_PER_SEC;
		cout << "Searching time: " << result << endl;
		cout << "Hits: " << hits << endl;
		cout << "----------------------------------------------------------------------------------------------------------------" << endl;

		//===============================================================================================
		cout<<HashTable->GetStats()<<endl;
		//===============================================================================================
		cout << "===============================================================================================================\n";
		delete HashTable;
		HashTable = new Dynamic_Array<Linked_List<Pair<int>>>();
		getchar();
	}
	//HashTable->Put(GetRandomKey(), 1);
	//HashTable->Put(GetRandomKey(), 2);
	//HashTable->Put(GetRandomKey(), 3);
	//HashTable->Put(GetRandomKey(), 4);
	//HashTable->Put(GetRandomKey(), 5);
	//HashTable->Put(GetRandomKey(), 6);
	//HashTable->Put(GetRandomKey(), 7);
	//HashTable->Put(GetRandomKey(), 8);
	//HashTable->Put(GetRandomKey(), 534);
	//HashTable->Put("qwertu", 5);
	//cout << HashTable->ToString(HashTable->GetMaxSize());/*
	//if (HashTable->SearchAndDelete("xydfsz")) cout << "Failed" << endl;
	//if (HashTable->SearchAndDelete("abceef")) cout << "Failed" << endl;
	//if (HashTable->SearchAndDelete("qwertu")) cout << "Failed" << endl;*/
	//Pair<int>* pair = HashTable->GetPair("qwertu");
	//if(pair)
	//cout << pair->ToString();
	//cout << GetRandomKey() << endl;
	//cout << HashTable->ToString(HashTable->GetMaxSize());
	//cout << HashTable->GetStats() << endl;
	delete HashTable;
}