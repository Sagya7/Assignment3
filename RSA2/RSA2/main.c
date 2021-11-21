#include <stdio.h>
#include <stdint.h>
#include<math.h>
#include <time.h>

uint64_t modcal(uint64_t n, uint64_t base) {
	return (n - (n / base)*base);
}

//modulo inverse extended Euclid Algorithm
uint64_t modInverse(uint64_t a, uint64_t m)
{
	uint64_t m0 = m;
	int64_t y = 0, x = 1;
	uint64_t q, t;
	if (m == 1) {
		return 0;
	}
	while (a > 1) {
		q = a / m;
		t = m;
		m = modcal(a, m);
		a = t;
		t = y;
		y = x - q * y;
		x = t;
	}
	// If x is negative make it positive
	if (x < 0)
		x += m0;
	return x;
}

uint64_t Exp(uint64_t a, uint64_t b, uint64_t n) {
	uint64_t x = 1, y;
	a = modcal(a, n);
	y = a;
	while (b > 0) {
		if (modcal(b, 2) == 1)
			x = modcal((x*y), n);
		y = modcal((y*y), n);
		b = b >> 1;
	}
	return (modcal(x, n));
}

// Returns gcd of a and b
uint64_t  gcd(uint64_t  a, uint64_t  h)
{
	uint64_t  temp;
	while (1)
	{
		temp = modcal(a, h);
		if (temp == 0)
			return h;
		a = h;
		h = temp;
	}
}

// Encryption c = (msg ^ e) % n
uint64_t encrypt(uint64_t msg, uint64_t  e, uint64_t n) {
	uint64_t c;
	c = Exp(msg, e, n);
	return c;
}

void decryptusingCRT(uint64_t c, uint64_t d, uint64_t n, uint64_t p, uint64_t q)
{
	clock_t start_t, end_t, total_t1, total_t2;
	uint64_t m;
	uint64_t vp, vq, xp, xq, dp1, dq1, vpq;//,cp1,cq1,cn1;

	dp1 = modcal(d, p - 1);
	dq1 = modcal(d, q - 1);
	xp = q*modInverse(q, p);
	xq = p*modInverse(p, q);

	start_t = clock();
	vp = Exp(c, dp1, p);
	vq = Exp(c, dq1, q);
	vpq = vp*xp + vq*xq;
	m = vpq - ((vpq / n)*n);
	end_t = clock();
	total_t1 = (double)(end_t - start_t);

	printf("Decrypted message is %llu\n", m);
	printf("Time taken for decryption is %lf\n", total_t1);

}

void decrypt(uint64_t c, uint64_t d, uint64_t n)
{
	clock_t start_t, end_t, total_t1;
	uint64_t m;

	start_t = clock();
	m = Exp(c, d, n);
	end_t = clock();
	total_t1 = (double)(end_t - start_t);

	printf("Decrypted message is %llu\n", m);
	printf("Time taken for decryption is %lf\n\n", total_t1);
}

int main()
{
	int    check, mode;
	uint64_t p = 48907;
	uint64_t q = 43237;
	uint64_t d_int, d, c, m;
	uint64_t msg = 0;
	uint64_t n = p*q;
	uint64_t e = 1;
	uint64_t phi = (p - 1)*(q - 1);
	printf("n = %llu \np = %llu \nq = %llu \npi(n) = %llu\n", n, p, q, phi);

	e = 65537;// Usual e 

	d = modInverse(e, phi);

	printf("\nPublic Key = %llu \nPrivate Key = %llu \n", e, d);
	//Key check for confirming they are modulo inverses
	check = modcal(d*e, phi);
	if (check != 1) {
		printf("Error: Inverse e*d modphi is not equal to 1 !\n");
		return 0;
	}
	printf("\nEnter the Number to be encrypted: Positive number < %llu\n ", n);
	scanf_s("%llu", &msg);
	if (msg >= n) {
		printf("Error: Please enter lesser number than %d", n);
		return 0;
	}
	printf("Number Entered is = %llu \n", msg);
	c = encrypt(msg, e, n);

	//Decryption

	decrypt(c, d, n);

	//CRT
	decryptusingCRT(c, d, n, p, q);

	getch();
	return 0;
}