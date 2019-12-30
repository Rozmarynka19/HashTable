#pragma once
#include <iostream>
#include <string>
#include <math.h>
using namespace std;


template <class T>
class List_Node
{
public:
	template <class T> friend class Linked_List;
	//template <class T> friend void PrintData(List_Node<T>* node);

	T data;
	List_Node* next;
	List_Node* previous;

	//public:
	List_Node(T data)
	{
		this->data = data;
		this->next = NULL;
		this->previous = NULL;
	}

	T PrintData()
	{
		return data;
	}

	string ToString()//string ToString(List_Node<T>* node)
	{
		string outcome = "";

		if (this == nullptr)
			return "";//return "\nPrintData: There isn't any given data.\n\n";
		else
			outcome = to_string(this->data) + " ";

		//outcome = outcome + " ";

		return outcome;
	}
};



template <class T>
class Linked_List
{
public:
	List_Node<T>* head;
	List_Node<T>* tail;
	unsigned int size;

	//public:
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
	void addToTail(T data)
	{
		List_Node<T>* node = new List_Node<T>(data);

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
	void addToHead(T data)
	{
		List_Node<T>* node = new List_Node<T>(data);

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
			List_Node<T>* temp;

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
			List_Node<T>* temp;

			if (size == 1)
				head = tail = nullptr;
			else
			{
				temp = tail->previous;
				delete tail;
				tail = temp;
				//tail->next = NULL;
			}


			size--;

		}
	}

	string GetDataOfElement(int iterator)
	{

		if (iterator<0 || iterator>size - 1)
			cout << "\nWrong iterator - out of range.";
		else if (iterator == size - 1) return tail->ToString();//return ToString(tail);//cout << tail->data << endl;
		else if (iterator == 0) return head->ToString();//return ToString(head);//cout << head->data << endl;
		else
		{
			List_Node<T>* temp = head;

			for (int i = 0; i < iterator; i++)
			{
				temp = temp->next;
			}

			return temp->ToString();
			//cout <<  << endl;
		}

	}
	//is searching wheter the node with given data exists (given data as a 'pattern')
	List_Node<T>* SearchByTheData(T data, int (*compare)(T Data1, T Data2))
	{
		List_Node<T>* temp = head;

		for (int i = 0; i < size; i++)
		{
			if (compare(temp->data, data) == 0) //if (temp->data == data) 
				return temp;
			temp = temp->next;
		}

		return NULL;
	}
	//returns 0 if the node has been removed, 1 if sth went wrong
	bool SearchAndDestoryNode(T data, int (*compare)(T Data1, T Data2))
	{
		List_Node<T>* temp = SearchByTheData(data, compare);

		if (size == 0)
		{
			cout << "The list is empty.\n\n";
			return 1;
		}
		else if (temp == nullptr)
		{
			//cout << "SearchAndDestoryNode: There isn't any given data.\n\n";
			return 1;
		}
		else if (temp == this->head)
		{
			/*temp->next->previous = NULL;
			this->head = temp->next;
			delete temp;
			size--;*/
			RemoveFromHead();
			//delete temp;

			return 0;
		}
		else if (temp == this->tail)
		{
			/*temp->previous->next = NULL;
			this->tail = temp->previous;
			delete temp;
			size--;*/
			RemoveFromTail();
			//delete temp;

			return 0;
		}
		else
		{
			temp->previous->next = temp->next;
			temp->next->previous = temp->previous;
			delete temp;
			size--;

			return 0;
		}

	}

	void ReplaceData(int iterator, T data)
	{
		if (iterator<0 || iterator>size - 1)
			cout << "\nWrong iterator - out of range.\n\n";
		else if (iterator == size - 1) tail->data = data;
		else if (iterator == 0) head->data = data;
		else
		{
			List_Node<T>* temp = head;

			for (int i = 0; i < iterator; i++)
			{
				temp = temp->next;
			}

			temp->data = data;
		}

	}

	void AddInOrder(T data, int (*compare)(T Data1, T Data2))
	{
		//cout << size << endl;
		if (size == 0)
		{
			//delete node; 
			this->addToTail(data);
		}
		else
		{
			List_Node<T>* node = new List_Node<T>(data);
			List_Node<T>* current = head;

			while (current != NULL)
			{
				if (compare(data, current->data) < 0)
				{
					if (current->previous != NULL)
					{
						current->previous->next = node;
						node->previous = current->previous;

						node->next = current;
						current->previous = node;

						size++;

						current = NULL;
					}
					else
					{
						addToHead(data);
						delete node;

						current = NULL;
					}
				}
				else
				{
					current = current->next;

					if (current == NULL)
					{
						delete node;

						addToTail(data);
					}
				}

			}
		}


	}

	string ToString()
	{
		string outcome = "";
		List_Node<T>* temp = head;


		outcome = "\nlist size: " + to_string(size) + "\n";
		while (temp)
		{
			outcome = outcome + to_string(temp->data) + " ";
			temp = temp->next;
		}
		outcome = outcome + "\n\n";
		return outcome;
	}

	string ToString(string(*el_to_str)(T))
	{
		string outcome = "";
		List_Node<T>* temp = head;


		outcome = "\nlist size: " + to_string(size) + "\n";
		while (temp)
		{
			//outcome = outcome + to_string(temp->data) + " ";
			outcome = outcome + el_to_str(temp->data) + " ";
			temp = temp->next;
		}
		outcome = outcome + "\n\n";
		return outcome;
	}

	string ToString(int number_of_elements)
	{
		string outcome = "";
		List_Node<T>* temp = head;

		outcome = "list size: " + to_string(size) + "\n";
		for (int i = 0; (i < size) && (i < number_of_elements) && (temp != nullptr); i++)
		{

			outcome = outcome + to_string(temp->data) + " ";
			temp = temp->next;
		}
		outcome = outcome + "\n\n";
		return outcome;
	}

};


//template <class T>
//void PrintData(List_Node<T>* node)
//{
//	if (node == nullptr)
//		cout << "PrintData: There isn't any given data.\n\n";
//	else
//		cout << node->data << endl;
//}

template<class T>
int Compare(T Data1, T Data2)
{
	if (Data1 < Data2) return -1;
	else if (Data1 == Data2) return 0;
	else return 1;
}

string char_to_str(char c)
{
	return string(1, c);
}
