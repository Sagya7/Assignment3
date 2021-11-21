#include <stdio.h>



int gcd(int a, int b)
{
	// Everything divides 0
	if (a == 0)
		return b;
	if (b == 0)
		return a;

	// base case
	if (a == b)
		return a;

	// a is greater
	if (a > b)
		return gcd(a - b, b);
	return gcd(a, b - a);
}

int TotalNumberOfRelativePrimes(int PrimeNumberMultiple)
{
	int TotalNumberOfRelativePrimes = 0;
	for (int i = 1; i < PrimeNumberMultiple; i++)
	{
		if (gcd(i, PrimeNumberMultiple) == 1)
		{
			TotalNumberOfRelativePrimes++;
		}
	}
	return TotalNumberOfRelativePrimes;
}

int PickOneRelativePrimeNumber(int TotalRelativelyPrimeNumbers)
{
	int TotalNumberOfDevisors,GCD;
	//int e;
	//int* ptr = (int*)malloc(TotalRelativelyPrimeNumbers * sizeof(int));
	//int k = 0;
	for (int i = 2; i < TotalRelativelyPrimeNumbers; i++)
	{
		GCD = gcd(i, TotalRelativelyPrimeNumbers);
		if (GCD == 1)
		{
			return i;
			//ptr[k] = i;
			//k++;
		}
	}
	
	//if (k > 0)
	//{
	//	int RandomNumberOfNodes = rand() % k;
	//	e = ptr[RandomNumberOfNodes];
	//	return e;
	//}
	return 0;
}


int FindingInverse(int e, int TotalRelativelyPrimeNumbers)
{
	int d;
	for (int i = 2; i < TotalRelativelyPrimeNumbers; i++)
	{
		if ((e*i) % TotalRelativelyPrimeNumbers == 1)
		{
			return i;
		}
	}
	return 0;
}

int RSAEncryption(int m, int e, int N)
{
	unsigned long long int cipher = 1;
	for (int i = 0; i < e; i++)
	{
		cipher = cipher * m;
	}
	cipher = cipher % N;
	return cipher;
}

int RSADecryption(long long c, int d, int N)
{
	unsigned long long int m = 1;
	for (int i = 0; i < d; i++)
	{
		m = m * c;
	}
	m = m % N;
	return m;
}

//int main()
//{
//	int PrimeNumberFactor1, PrimeNumberFactor2;
//	printf("Enter first prime number factor\n");
//	scanf_s("%d", &PrimeNumberFactor1);
//
//	printf("Enter Second prime number factor\n");
//	scanf_s("%d", &PrimeNumberFactor2);
//
//	int PrimeNumberMultiple;
//	PrimeNumberMultiple = PrimeNumberFactor1 * PrimeNumberFactor2;
//
//	int TotalRelativelyPrimeNumbers;
//	TotalRelativelyPrimeNumbers = TotalNumberOfRelativePrimes(PrimeNumberMultiple);
//
//	int e;
//	e = PickOneRelativePrimeNumber(TotalRelativelyPrimeNumbers);
//
//	if (e == 0)
//	{
//		printf("e can't be calculated! \n No Number is relatively prime to pi(N)");
//		return 0;
//	}
//
//	int d = FindingInverse(e, TotalRelativelyPrimeNumbers);
//	if (d == 0)
//	{
//		printf("Inverse for e doesn't exist.");
//		return 0;
//	}
//
//	printf("Public Keys are N = %d and e = %d\n", PrimeNumberMultiple, e);
//	printf("Total number of Relatively prime numbers %d\n", TotalRelativelyPrimeNumbers);
//	printf("Private Keys are p = %d,q = %d,d = %d\n", PrimeNumberFactor1, PrimeNumberFactor2, d);
//
//	int message;
//	printf("Enter number to Encrypt\n");
//	scanf_s("%d", &message);
//
//	int cipher = RSAEncryption(message, e, PrimeNumberMultiple);
//	printf("Encrypted Mesage is %d \n", cipher);
//
//	int DecyptedMessage = RSADecryption(cipher, d, PrimeNumberMultiple);
//	printf("Decrypted Mesage is %d \n", DecyptedMessage);
//
//	//for (int i = 0; i < 30; i++)
//	//{
//	//	int message = i;
//
//	//	int cipher = RSAEncryption(message, e, PrimeNumberMultiple);
//	//	printf("Encrypted Mesage is %d \n", cipher);
//
//	//	int DecyptedMessage = RSADecryption(cipher, d, PrimeNumberMultiple);
//	//	printf("Decrypted Mesage is %d \n", DecyptedMessage);
//
//	//	printf("----------------------------------------------\n\n");
//
//	//}
//
//	getch();
//
//	return 0;
//
//
//}