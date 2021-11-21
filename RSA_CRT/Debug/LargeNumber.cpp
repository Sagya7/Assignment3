#include <stdio.h>
#include <iostream>
using namespace std;

bool IsNegative = false;

//defining a double linked list node.
typedef struct node
{
	int data;
	node* next;
	node* prev;
	node(int);
};


// To initialize the structure with a single digit 
node::node(int val) 
{ 
    data = val; 
    next  = NULL;
	prev = NULL;
}

//adding nodes to the end of the list
void insertatrear(int data,node* db)
{
	node* temp = new node(0);
	while (db->next != NULL)
	{
		db = db->next;
	}
	temp->data = data;
	temp->prev = db;
	db->next = temp;
}

//adding nodes to the start of the list
void insertatfront(int data, node* db)
{
	node* temp = new node(0);
	while (db->prev != NULL)
	{
		db = db->prev;
	}
	temp->data = data;
	temp->next = db;
	db->prev = temp;
}

//adding nodes in the front of the list
void insertatfrontwithhead(int data, node* additive, node* head)
{
	node* temp = new node(0);
	while (additive->prev != head)
	{
		additive = additive->prev;
	}
	temp->data = data;
	head->next = temp;
	temp->prev = head;
	temp->next = additive;
	additive->prev = temp;
	temp->next = additive;
	additive->prev = temp;
}

//delete nodes to the end of the list
void deleteatrear(node* db)
{
	while (db->next != NULL)
	{
		db = db->next;
	}
	db->prev->next = NULL;
	db->prev = NULL;
}

//Multiplication
node* mul(string firstnumber, string secondnumber,node* result)
{
	bool firstdigitmul = true;
	int specialnum = 0;
	int multiplication = 1;
	int num;
	bool replacelastdigit = true;

	int mul,sum;
	int carry;
	int shift = 0;
	bool onetimeshift = false;
	int lengthofseconddata = 2;
	bool addnode = false;

	node* first = new node(int(firstnumber[firstnumber.length() - 1]) - 48);
	node* second = new node(int(secondnumber[secondnumber.length() - 1]) - 48);

	for (int i = firstnumber.length() - 2; i >= 0; i--)
	{
		insertatfront(int(firstnumber[i]) - 48, first);
	}

	for (int i = secondnumber.length() - 2; i >= 0; i--)
	{
		insertatfront(int(secondnumber[i]) - 48, second);
	}

	while (second->prev != NULL)
	{
		carry = 0;
		int currentnodepos = shift + 1;
		while (first->prev != NULL)
		{
			for (int i = 0; i < shift; i++)
			{
				if (onetimeshift == true)
				{
					result = result->prev;
				}
			}
			onetimeshift = false;
			multiplication = (second->data * first->data) + carry;
			mul = (multiplication % 10);
			carry = multiplication / 10;
			if (result->prev == NULL && result->next == NULL && replacelastdigit)
			{
				result->data = mul;
				replacelastdigit = false;
			}
			else if (firstdigitmul)
			{
				insertatfront(mul,result);
			}
			first = first->prev;
			if (result->prev == NULL && first->prev != NULL && !firstdigitmul)
			{
				carry = carry + (result->data + mul) / 10;
				sum = (result->data + mul) % 10;
				result->data = sum;
				addnode = true;
			}
			if (result->prev != NULL && !firstdigitmul)
			{
				carry = carry + (result->data + mul) / 10;
				sum = (result->data + mul) % 10;
				result->data = sum;
				result = result->prev;
			}
			if (result->prev == NULL && first->prev == NULL && !firstdigitmul && !addnode)
			{
				carry = carry + (result->data + mul) / 10;
				sum = (result->data + mul) % 10;
				result->data = sum;
				if (carry != 0)
				{
					insertatfront(carry, result);
				}
			}
			if (first->prev == NULL && !firstdigitmul && addnode)
			{
				insertatfront(mul, result);
				if (carry != 0)
				{
					insertatfront(carry, result);
				}
			}
			if (first->prev == NULL && carry != 0 && firstdigitmul)
			{
				insertatfront(carry, result);
			}
		}
		second = second->prev;
		firstdigitmul = false;
		onetimeshift = true;
		while (result->prev != NULL)
		{
			result = result->prev;
		}
		shift = shift + 1;
		while (result->next != NULL)
		{
			cout << result->data;
			result = result->next;
		}
		cout << result->data << endl;

		while (first->next != NULL)
		{
			first = first->next;
		}
	}
	return result;
}

int main()
{
	node* head = new node(0);
	node* result = new node(0);

	string firstnumber = "099900011";
	string secondnumber = "098131";

	mul(firstnumber, secondnumber, result);

	while (result->prev != NULL)
	{
		result = result->prev;
	}

	while (result != NULL)
	{

		printf("%d",result->data);

		result = result->next;
	}

	cin.get();

	return 0;

}

