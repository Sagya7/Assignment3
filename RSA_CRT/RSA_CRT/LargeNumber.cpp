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


void print(node* result)
{
	while (result->prev != NULL)
	{
		result = result->prev;
	}

	while (result != NULL)
	{

		printf("%d", result->data);

		result = result->next;
	}
}

int countthenumberofnodes(node* input)
{
	int NumberOfNodes = 1;
	while (input->prev != NULL)
	{
		input = input->prev;
	}

	while (input->next != NULL)
	{
		input = input->next;
		NumberOfNodes++;
	}
	return NumberOfNodes;
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

void deleteatfront(node* db)
{
	while (db->prev != NULL)
	{
		db = db->prev;
	}
	db->next->prev = NULL;
	db->next = NULL;
}

void addsinglezeroatfront(node* db)
{
	while (db->prev != NULL)
	{
		db = db->prev;
	}
	while (db->data == 0 && db->next != NULL)
	{
		db = db->next;
		deleteatfront(db);
	}
	insertatfront(0, db);
}

int numberofnodeswithoutfrontzeroes(node* input)
{
	int nodes;

	nodes = countthenumberofnodes(input);

	while (input->prev != NULL)
	{
		input = input->prev;
	}
	while (input->data == 0 && input->next != NULL)
	{
		nodes--;
		input = input->next;
	}

	return nodes;
}

int compare(node* first, node* second)
{
	int firstnumbernodes, secondnumbernodes;

	firstnumbernodes = countthenumberofnodes(first);

	while (first->prev != NULL)
	{
		first = first->prev;
	}
	while (first->data == 0 && first->next != NULL)
	{
		firstnumbernodes--;
		first = first->next;
	}

	secondnumbernodes = countthenumberofnodes(second);

	while (second->prev != NULL)
	{
		second = second->prev;
	}
	while (second->data == 0 && second->next != NULL)
	{
		secondnumbernodes--;
		second = second->next;
	}

	if (firstnumbernodes > secondnumbernodes)
	{
		return 1;
	}
	else if (secondnumbernodes > firstnumbernodes)
	{
		return 2;
	}
	else
	{
		while (first != NULL)
		{
			if (first->data > second->data)
			{
				return 1;
			}
			else if (first->data < second->data)
			{
				return 2;
			}
			first = first->next;
			second = second->next;
		}
		return 0;
	}
}

node* makesmallernumber(node* first, int digitsindividend)
{
	int i = 1;
	node* smaller = new node(first->data);
	first = first->next;
	while(i < digitsindividend && first!= NULL)
	{
		insertatrear(first->data, smaller);
		first = first->next;
		i++;
	}
	return smaller;
}

node* addition(node* first, node* second)
{
	bool firstdigit = true;;
	int carry = 0;
	int addition = 0;
	int seconddata = 0;

	node* Add = new node(0);

	while (first->next != NULL)
	{
		first = first->next;
	}
	while (second->next != NULL)
	{
		second = second->next;
	}
	while (first != NULL)
	{
		addition = 0;
		if (second != NULL)
		{
			seconddata = second->data;
		}
		else
		{
			seconddata = 0;
		}
		if (firstdigit)
		{
			addition = (first->data + seconddata) % 10;
			carry = (first->data + seconddata) / 10;
			Add->data = addition;
		}
		if (!firstdigit)
		{
			addition = (first->data + seconddata) + carry;
			carry = addition / 10;
			addition = addition % 10;
			insertatfront(addition, Add);
		}
		if (first->prev == NULL && carry != 0)
		{
			insertatfront(carry, Add);
		}
		if (second != NULL)
		{
			second = second->prev;
		}
		first = first->prev;
		firstdigit = false;
	}
	while (Add->prev != NULL)
	{
		Add = Add->prev;
	}
	if (Add->data != 0)
	{
		insertatfront(0, Add);
	}
	return Add;
}

node* subtract(node* first, node* second)
{
	bool firstdigit = true;;
	int borrow = 0;
	int previousborrow = 0;
	int seconddata = 0;

	node* subtracted = new node(0);

	while (first->next != NULL)
	{
		first = first->next;
	}
	while (second->next != NULL)
	{
		second = second->next;
	}
	while (first != NULL)
	{
		borrow = 0;
		if (second != NULL)
		{
			seconddata = second->data;
		}
		else
		{
			seconddata = 0;
		}
		if (first->data < (seconddata + previousborrow))
		{
			borrow = 1;
		}
		if (firstdigit)
		{
			subtracted->data = ((borrow * 10) + first->data) - seconddata;
		}
		if (first != NULL && !firstdigit)
		{
			insertatfront((((borrow * 10) + first->data) - seconddata - previousborrow), subtracted);
		}
		if (second != NULL)
		{
			second = second->prev;
		}
		first = first->prev;
		//if (first == NULL && borrow == 1)
		//{
		//	printf("\nFirst number is smaller than second\n");
		//	IsNegative = true;
		//}
		firstdigit = false;
		previousborrow = borrow;
	}
	while (subtracted->prev != NULL)
	{
		subtracted = subtracted->prev;
	}
	while (subtracted->data == 0 && subtracted->next != NULL)
	{
		subtracted = subtracted->next;
		deleteatfront(subtracted);
	}
	insertatfront(0, subtracted);
	return subtracted;
}

node* mul(node* first, node* second)
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

	node* result = new node(0);

	//addsinglezeroatfront(first);
	//addsinglezeroatfront(second);

	while (first->next != NULL)
	{
		first = first->next;
	}
	while (second->next != NULL)
	{
		second = second->next;
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
			if (result->prev == NULL && first->prev != NULL && !firstdigitmul && addnode)
			{
				carry = carry + (result->data + mul) / 10;
				sum = (result->data + mul) % 10;
				result->data = sum;
				insertatfront(sum, result);
				result = result->prev;
			}
			if (result->prev == NULL && first->prev != NULL && !firstdigitmul && !addnode)
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
		addnode = false;
		shift = shift + 1;
		while (result->next != NULL)
		{
			result = result->next;
		}
		while (first->next != NULL)
		{
			first = first->next;
		}
	}
	insertatfront(0, result);
	return result;
}

node* division(node* first, node* second)
{
	node* divisor = new node(0);
	//node* mult = new node(0);
	node* sub = new node(0);
	int digitsindividend;
	int isbig;
	digitsindividend = countthenumberofnodes(second);

	bool firsttime = true;

	node* one = new node(1);
	insertatfront(0, one);

	node* constantone = new node(1);
	insertatfront(0, constantone);

	node* constantzero = new node(0);

	node* mult = new node(1);

	while (first->prev != NULL)
	{
		first = first->prev;
	}
	while (second->prev != NULL)
	{
		second = second->prev;
	}
	
	while (first != NULL)
	{

		node* pseudofirst = makesmallernumber(first, digitsindividend);
		int i = 1;
		while (i < digitsindividend && first != NULL && firsttime)
		{
			first = first->next;
			i++;
		}

		int nodeswithoutzeroes = numberofnodeswithoutfrontzeroes(sub);

		int j = 0;
		while (sub->next != NULL)
		{
			sub = sub->next;
		}
		while (sub != NULL && !firsttime && j < nodeswithoutzeroes)
		{
			insertatfront(sub->data, pseudofirst);
			sub = sub->prev;
			j++;
		}

		firsttime = false;
		int isbigger = compare(pseudofirst, second);
		if (isbigger == 2 && first != NULL)
		{
			first = first->next;
      		insertatrear(0, divisor);
			if (first != NULL)
			{
				insertatrear(first->data, pseudofirst);
			}
		}
		while (true)
		{
			if (compare(second, one) == 1 || compare(second, one) == 0)
			{
				mult = mul(second, one);
			}
			else
			{
				mult = mul(one, second);
			}
			sub = subtract(pseudofirst,mult);
			isbig = compare(sub,second);
			if (isbig == 2 && first != NULL)
			{
				while (one->next != NULL)
				{
					one = one->next;
				}
				insertatrear(one->data, divisor);
				while (sub->next != NULL)
				{
					sub = sub->next;
				}
				break;
			}
			if (isbig == 2 && first == NULL)
			{
				break;
			}
			else if (isbig == 0)
			{
				one = addition(one, constantone);
				while (sub->prev != NULL)
				{
					sub = sub->prev;
				}
				while (sub->next != NULL)
				{
					sub->data = 0;
					sub = sub->next;
				}
				sub->data = 0;
				while (one->next != NULL)
				{
					one = one->next;
				}
				insertatrear(one->data, divisor);
				break;
			}
			one = addition(one, constantone);
			continue;
		}
		if (first != NULL)
		{
			first = first->next;
		}
		while (one->next != NULL)
		{
			one = one->next;
			one->data = 0;
		}
		one->data = 1;
		digitsindividend = 1;//only one node should be added after each division

	}
	return divisor;
}

node* modulo(node* first, node* second)
{
	node* divisor = new node(0);
	//node* mult = new node(0);
	node* sub = new node(0);
	int digitsindividend;
	int isbig;
	digitsindividend = countthenumberofnodes(second);

	bool firsttime = true;

	node* one = new node(1);
	insertatfront(0, one);

	node* constantone = new node(1);
	insertatfront(0, constantone);

	node* constantzero = new node(0);

	node* mult = new node(1);

	while (first->prev != NULL)
	{
		first = first->prev;
	}
	while (second->prev != NULL)
	{
		second = second->prev;
	}

	while (first != NULL)
	{

		node* pseudofirst = makesmallernumber(first, digitsindividend);
		int i = 1;
		while (i < digitsindividend && first != NULL && firsttime)
		{
			first = first->next;
			i++;
		}

		int nodeswithoutzeroes = numberofnodeswithoutfrontzeroes(sub);

		int j = 0;
		while (sub->next != NULL)
		{
			sub = sub->next;
		}
		while (sub != NULL && !firsttime && j < nodeswithoutzeroes)
		{
			insertatfront(sub->data, pseudofirst);
			sub = sub->prev;
			j++;
		}

		firsttime = false;
		int isbigger = compare(pseudofirst, second);
		if (isbigger == 2 && first != NULL)
		{
			first = first->next;
			insertatrear(0, divisor);
			if (first == NULL)
			{
				return pseudofirst;
			}
			if (first != NULL)
			{
				insertatrear(first->data, pseudofirst);
			}
		}
		while (true)
		{
			if (compare(second, one) == 1 || compare(second, one) == 0)
			{
				mult = mul(second, one);
			}
			else
			{
				mult = mul(one, second);
			}

			sub = subtract(pseudofirst, mult);
			isbig = compare(sub, second);
			if (isbig == 2 && first != NULL)
			{
				while (one->next != NULL)
				{
					one = one->next;
				}
				insertatrear(one->data, divisor);
				while (sub->next != NULL)
				{
					sub = sub->next;
				}
				break;
			}
			if (isbig == 2 && first == NULL)
			{
				break;
			}
			else if (isbig == 0)
			{
				one = addition(one, constantone);
				while (sub->prev != NULL)
				{
					sub = sub->prev;
				}
				while (sub->next != NULL)
				{
					sub->data = 0;
					sub = sub->next;
				}
				sub->data = 0;
				insertatrear(one->data, divisor);
				break;
			}
			one = addition(one, constantone);
			continue;
		}
		if (first != NULL)
		{
			first = first->next;
		}
		while (one->prev != NULL)
		{
			one = one->prev;
		}
		while (one->next != NULL)
		{
			one = one->next;
			one->data = 0;
		}
		one->data = 1;
		digitsindividend = 1;//only one node should be added after each division

	}
	return sub;
}

node* gcd(node* first, node* second)
{
	node* constantzero = new node(0);
	node* constanttwo = new node(2);
	insertatfront(0, constanttwo);
	node* constantone = new node(1);
	insertatfront(0, constantone);
	//node* realfirst = first;
	//node* realsecond = second;
	int whichoneisbig;
	whichoneisbig = compare(first, second);
	if (whichoneisbig == 2)
	{
		printf("In GCD divisor is bigger than Dividend please change!");
	}
	else if (whichoneisbig == 0)
	{
		return first;
	}
	while (true)
	{
		node* quetient = division(first, second);
		node* modulus = modulo(first, second);
		int x = compare(modulus, constantzero);
		//int y = compare(modulus, constantone);
		if (x == 0)
		{
			while (second->prev != NULL)
			{
				second = second->prev;
			}
			while (second->data == 0)
			{
				second = second->next;
				deleteatfront(second);
			}
			insertatfront(0, second);
			return second;
		}
		first = second;
		second = modulus;
	}
}

//extended euclidian algorithm.
node* findinverese(node* modn, node* inversetobefound)
{
	node* constantzero = new node(0);
	node* constanttwo = new node(2);
	insertatfront(0, constanttwo);
	node* constantone = new node(1);
	insertatfront(0, constantone);

	bool resultisnegativeB2 = false;

	bool resultisnegativePrevB2 = false;

	bool resultisnegativePrevA2 = false;

	node* A2 = new node(0);
	insertatfront(0, A2);
	node* A3 = modn;

	node* B2 = new node(1);
	insertatfront(0, B2);
	node* B3 = inversetobefound;

	node* Q = new node(1);
	insertatfront(0,Q);

	int compareB3 = compare(B3, constantone);
	while (compareB3 != 0)
	{
		node* previousB2 = B2;
		node* previousB3 = B3;

		node* x = new node(1);

		addsinglezeroatfront(A3);
		addsinglezeroatfront(B3);
		Q = division(A3, B3);
		B3 = modulo(A3, B3);
		while (Q->prev != NULL)
		{
			Q = Q->prev;
		}
		while (Q->data == 0 && Q->next != NULL)
		{
			Q = Q->next;
			deleteatfront(Q);
		}
		insertatfront(0, Q);
		while (B2->prev != NULL)
		{
			B2 = B2->prev;
		}
		while (B2->data == 0 && B2->next != NULL)
		{
			B2 = B2->next;
			deleteatfront(B2);
		}
		insertatfront(0, B2);
		addsinglezeroatfront(B2);
		if (compare(Q, B2) == 1 || compare(Q, B2) == 0)
		{
			x = mul(Q, B2);
		}
		else if (compare(Q, B2) == 2)
		{
			x = mul(B2, Q);
		}


		if (compare(A2, x) == 0 || compare(A2, x) == 1)
		{
			if ((resultisnegativePrevA2 == false && resultisnegativePrevB2 == false))
			{
				B2 = subtract(A2, x);
				resultisnegativeB2 = false;
			}
			else if((resultisnegativePrevA2 == false && resultisnegativePrevB2 == true))
			{
				B2 = addition(A2, x);
				resultisnegativeB2 = false;
			}
			else if ((resultisnegativePrevA2 == true && resultisnegativePrevB2 == false))
			{
				B2 = addition(A2, x);
				resultisnegativeB2 = true;
			}
			else if ((resultisnegativePrevA2 == true && resultisnegativePrevB2 == true))
			{
				B2 = subtract(A2, x);
				resultisnegativeB2 = true;
			}
		}
		else
		{
			if ((resultisnegativePrevA2 == false && resultisnegativePrevB2 == false))
			{
				B2 = subtract(x, A2);
				resultisnegativeB2 = true;

			}
			else if ((resultisnegativePrevA2 == false && resultisnegativePrevB2 == true))
			{
				B2 = addition(x, A2);
				resultisnegativeB2 = false;
			}
			else if ((resultisnegativePrevA2 == true && resultisnegativePrevB2 == false))
			{
				B2 = addition(x, A2);
				resultisnegativeB2 = true;
			}
			else if ((resultisnegativePrevA2 == true && resultisnegativePrevB2 == true))
			{
				B2 = subtract(x, A2);
				resultisnegativeB2 = false;
			}
		}

		A2 = previousB2;
		A3 = previousB3;

		resultisnegativePrevA2 = resultisnegativePrevB2;
		resultisnegativePrevB2 = resultisnegativeB2;
		compareB3 = compare(B3, constantone);
	}

	if (resultisnegativeB2 == true)
	{
		if (compare(B2, modn) == 2)
		{
			B2 = subtract(modn, B2);
		}
		else if (compare(B2, modn) == 1)
		{
			node* div = division(B2, modn);
			while (compare(div, constantzero) == 0)
			{
				B2 = subtract(B2, modn);
				div = subtract(div, constantzero);
			}
			if (compare(B2, constantzero) != 0)
			{
				B2 = subtract(B2, modn);
			}
		}
	}
	return B2;
}

node* moduloinverse(node* modn, node* inversetobefound)
{
	node* constantzero = new node(0);
	node* constanttwo = new node(2);
	insertatfront(0, constanttwo);
	node* constantone = new node(1);
	insertatfront(0, constantone);
	node* inverse = new node(0);
	node* ngcd = gcd(modn,inversetobefound);
	int inverseexists = compare(ngcd, constantone);
	if (inverseexists == 0)
	{
		inverse = findinverese(modn,inversetobefound);
	}
	return inverse;
}

int main()
{
	node* head = new node(0);
	node* result = new node(0);
	node* constantzero = new node(0);
	node* constanttwo = new node(2);
	insertatfront(0, constanttwo);

	//string firstnumber ="03492127768456780987654321234567890987653234567890987653";
	//string secondnumber = "099345";

	//node* first = new node(int(firstnumber[firstnumber.length() - 1]) - 48);
	//node* second = new node(int(secondnumber[secondnumber.length() - 1]) - 48);

	//for (int i = firstnumber.length() - 2; i >= 0; i--)
	//{
	//	insertatfront(int(firstnumber[i]) - 48, first);
	//}

	//for (int i = secondnumber.length() - 2; i >= 0; i--)
	//{
	//	insertatfront(int(secondnumber[i]) - 48, second);
	//}


	//node* Multiplicationresult = mul(first, second);
	//print(Multiplicationresult);

	//std::cout << endl;

	////first argument should be bigger than second
	//node* subtractresult = subtract(first, second);
	//print(subtractresult);

	//std::cout << endl;

	////first argument should be bigger than second
	//node* Additionresult = addition(first, second);
	//print(Additionresult);

	//std::cout << endl;

	////first argument should be bigger than second
	//node* divisionresult = division(first, second);
	//print(divisionresult);

	//std::cout << endl;

	//RSA Algorithm.......

	string primenumber1 = "04259458051";
	string primenumber2 = "03832510679";

	node* first = new node(int(primenumber1[primenumber1.length() - 1]) - 48);
	node* second = new node(int(primenumber2[primenumber2.length() - 1]) - 48);

	for (int i = primenumber1.length() - 2; i >= 0; i--)
	{
		insertatfront(int(primenumber1[i]) - 48, first);
	}

	for (int i = primenumber2.length() - 2; i >= 0; i--)
	{
		insertatfront(int(primenumber2[i]) - 48, second);
	}


	node* Multiplicationresult = gcd(first, second);
	print(Multiplicationresult);

	cout << endl;

	node* constantone = new node(1);
	node* firstminusone = subtract(first, constantone);
	print(firstminusone);

	cout << endl;

	node* secondminusone = subtract(second, constantone);
	print(secondminusone);

	cout << endl;

	node* phiofn = mul(firstminusone, secondminusone);
	print(phiofn);

	//choose any e which is relatively prime to phi of n
	string ee = "065537";

	node* e = new node(int(ee[ee.length() - 1]) - 48);

	for (int i = ee.length() - 2; i >= 0; i--)
	{
		insertatfront(int(ee[i]) - 48, e);
	}
	cout << endl;

	//finding d which is inverese of e in mod phiofn
	node* d = moduloinverse(phiofn,e);
	print(d);

	string dd = "016324418459118057900";
	node* d = new node(int(dd[dd.length() - 1]) - 48);

	for (int i = dd.length() - 2; i >= 0; i--)
	{
		insertatfront(int(dd[i]) - 48, d);
	}

	//node* d = constantone;
	//insertatfront(0, d);

	//verify the d
	//node* gcdd = new node(1);
	//while (true)
	//{
	//	node* x = mul(e,d);
	//	if (compare(x, phiofn) == 2)
	//	{
	//		d = addition(d, constantone);
	//		continue;
	//	}
	//	//printf("\n");
	//	//print(d);
	//	node* gcdd = modulo(x,phiofn);
	//	//printf(" ");
	//	//print(gcdd);
	//	int comp = compare(gcdd, constantone);
	//	if (comp == 0)
	//	{
	//		printf("\nd is inverse of e");
	//		print(d);
	//		break;
	//	}
	//	d = addition(d, constantone);
	//}

	printf("\nEnter the message to Encrypt\n");
	char message[100];






	//while (true)
	//{
	//	int k;
	//	printf("\nEnter a k greater than 1 to choose an e which is relatively prime to phi of n\n");
	//	scanf_s("%d", &k);
	//	node* e = new node(1);
	//	insertatfront(0, e);
	//	e = mul(e, constanttwo);
	//	k = k - 1;
	//	while (k > 0)
	//	{
	//		e = mul(e, constanttwo);
	//		k = k - 1;
	//	}
	//	e = addition(e, constantone);
	//	cout << endl;
	//	//chcek whether number is prime
	//	bool isprime = true;
	//	node* checkprime = new node(2);
	//	insertatfront(0, checkprime);
	//	node* halfofprime = new node(1);
	//	insertatfront(0, halfofprime);
	//	int comparison = 1;
	//	int halfcomparison = 2;
	//	halfofprime = division(e, constanttwo);
	//	halfcomparison = compare(checkprime, halfofprime);
	//	while (halfcomparison != 0)
	//	{
	//		node* comparemodulo = modulo(e, checkprime);
	//		int comparison = compare(comparemodulo, constantzero);
	//		if (comparison == 0)
	//		{
	//			isprime = false;
	//			break;
	//		}
	//		checkprime = addition(checkprime, constantone);
	//		halfcomparison = compare(checkprime, halfofprime);
	//	}
	//	if (isprime == true)
	//	{
	//		cout << endl;
	//		printf("choosen e is prime number so relatively prime to phi of n\n");
	//		print(e);
	//		break;
	//	}
	//}

	int wait;
	scanf_s("%d", &wait); 
	std::cin.get();

	return 0;

}

