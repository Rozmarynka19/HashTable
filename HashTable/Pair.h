#pragma once
#include <cstring>
#include <iostream>
#include <cstring>
using namespace std;

template <class T>
class Pair {
public:
	string key;
	T value;

	Pair() { key = ""; value = 0; }
	Pair(string k, T v)
	{
		key = k;
		value = v;
	}
	string ToString()
	{
		string outcome = "\n"+key+"->"+to_string(value)+"\n";
		return outcome;
	}
};