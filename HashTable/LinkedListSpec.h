#pragma once
//this code is specialized version of LinkedList for Pair<int> type
#include <iostream>
#include <string>
#include <math.h>
#include "LinkedList.h"
#include "Pair.h"
using namespace std;

template <> class List_Node < Pair < int > >
{
	//template <> friend class List_Node < Pair < int > >;
public: 
	Pair<int> data;
	List_Node* next;
	List_Node* previous;

	List_Node(Pair<int>* data)
	{
		this->data = *data;
		this->next = NULL;
		this->previous = NULL;
	}

	Pair<int> GetData()
	{
		return data;
	}

	string ToString()
	{
		string outcome = "";

		if (this == nullptr)
			return "\nPrintData: There isn't any given data.\n\n"; //return "";
		else
			outcome = this->data.key + "->" + to_string(this->data.value) + " ";

		return outcome;
	}
};

template <> class Linked_List < Pair < int > >
{
public:
	List_Node < Pair < int > >* head;
	List_Node < Pair < int > >* tail;
	unsigned int size;

	Linked_List()
	{
		this->head = NULL;
		this->tail = NULL;
		size = 0;
	}

	//desctrutor deletes the list from the tail
	~Linked_List()
	{
		while (size) RemoveFromTail();
		delete head;
		delete tail;
	}


	//add node to the end of the list
	void addToTail(Pair<int>* data)
	{
		List_Node<Pair<int>>* node = new List_Node<Pair<int>>(data);

		if (size == 0)
		{
			this->head = node;
			this->tail = node;
		}
		else
		{
			tail->next = node;
			node->previous = tail;
			this->tail = node;
		}
		size++;
	}
	//add node to the begining of the list
	void addToHead(Pair<int>* data)
	{
		List_Node<Pair<int>>* node = new List_Node<Pair<int>>(data);

		if (size == 0)
		{
			this->head = node;
			this->tail = node;
		}
		else
		{
			head->previous = node;
			node->next = head;
			this->head = node;
		}
		size++;
	}
	//remove node from the begining of the list
	void RemoveFromHead()
	{
		if (size == 0)
		{
			cout << "\nThe list is empty.\n\n";
		}
		//else if (size == 1)
		//{
		//	delete head;

		//	size--;
		//}
		else
		{
			List_Node<Pair<int>>* temp;

			if (size == 1)
				head = tail = nullptr;
			else
			{
				temp = head->next;
				//temp->previous = NULL;
				//head->next = NULL;
				delete head;
				head = temp;
			}

			size--;
		}
	}

	//remove node from the end of the list
	void RemoveFromTail()
	{

		if (size == 0)
		{
			cout << "\nThe list is empty.\n\n";
		}
		else
		{
			List_Node<Pair<int>>* temp;


				
				temp = tail->previous;
				
				delete tail;
				tail = temp;
				//tail->next = NULL;



			size--;

			if (size == 0)
				head = nullptr;

		}
	}

	bool isEmpty() { return !size; }

	//returns the position of data with the same key or -1 if not found
	int Search(string key)
	{
		List_Node<Pair<int>>* temp = head;

		for (int i = 0; i < size; i++)
		{
			if (key.compare(temp->data.key) == 0) //if (temp->data == data) 
				return i;
			temp = temp->next;
		}

		return -1;
	}

	void OverwriteValue(int iterator, int value)
	{
		(head + iterator)->data.value = value;
	}

	string ToString()
	{
		string outcome = "";
		List_Node<Pair<int>>* temp = head;

		while (temp)
		{
			outcome = outcome + temp->ToString() + " ";
			temp = temp->next;
		}
		
		return outcome;
	}
};