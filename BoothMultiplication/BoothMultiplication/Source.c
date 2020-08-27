#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>  
#include <math.h>

int N;

void invers(int** bin, int len)
{
	for (int i = 0; i < len; i++)
		(*bin)[i] = abs((*bin)[i] - 1);
	int temp;
	int e = 1;
	for (int i = 0; i < len; i++)
	{
		temp = (*bin)[i];
		(*bin)[i] = (*bin)[i] ^ e;
		e = temp && e;
	}
}

int* decToBin(int num)
{
	int *a;
	int inv;
	a = (int*)malloc(N * sizeof(int));
	if (num < 0)
		inv = 1;
	else
		inv = 0;
	num = abs(num);
	for (int i = 0; i < N; i++)
	{
		a[i] = num % 2;
		num /= 2;
	}
	if (inv == 1)
		invers(&a, N);
	return a;
}

void prntBinary(int* num, int len)
{
	for (int i = len - 1; i >= 0; i--)
		printf("%d", num[i]);
	printf("\n");
}

int binToDec(int* num)
{
	int sign = 1;
	if (num[2 * N - 1] == 1)
	{
		sign = -1;
		invers(&num, 2 * N);
	}
	int d = 0;
	for (int i = 0; i < 2 * N - 1; i++)
	{
		d += pow(2, i)*num[i];
	}
	d *= sign;
	return d;
}

int* binSum(int*a, int*b, int len)
{
	int e = 0;
	int *c = (int*)malloc(len * sizeof(int));
	for (int i = 0; i < len; i++)
	{
		c[i] = (a[i] ^ b[i]) ^ e;
		e = (a[i] && b[i]) || (a[i] && e) || (b[i] && e);
	}
	return c;
}

void shift(int** bin, int len)
{
	for (int i = 0; i < len - 1; i++)
		(*bin)[i] = (*bin)[i + 1];
	(*bin)[len - 1] = (*bin)[len - 2];
}

int* binMultiplication(int*a, int*b)
{
	int *A = (int*)malloc((2 * N + 1) * sizeof(int));
	int *S = (int*)malloc((2 * N + 1) * sizeof(int));
	int *P = (int*)malloc((2 * N + 1) * sizeof(int));

	int *a1 = (int*)malloc(N * sizeof(int));
	for (int i = 0; i < N; i++)
		a1[i] = a[i];
	invers(&a1, N);

	for (int i = 0; i < 2 * N + 1; i++)
	{
		if (i < N)
		{
			A[2 * N - i] = a[N - 1 - i];
			P[1 + i] = b[i];
			S[2 * N - i] = a1[N - 1 - i];
		}
		else
		{
			A[2 * N - i] = 0;
			P[1 + i] = 0;
			S[2 * N - i] = 0;
		}
	}

	free(a1);

	P[0] = 0;

	for (int i = 0; i < N; i++)
	{
		if (P[0] != P[1])
		{
			if (P[1] == 1)
				P = binSum(P, S, 2 * N + 1);
				
			else
				P = binSum(P, A, 2 * N + 1);
		}
		shift(&P, 2 * N + 1);
	}

	int *p = (int*)malloc((2 * N) * sizeof(int));
	for (int i = 0; i <= 2 * N; i++)
		p[2 * N - i] = P[2 * N + 1 - i];
	free(P);
	return p;
}

int main()
{
	int x, y, res;

	do
	{
		printf("Bit count:");
		res = scanf("%d", &N);
		while (getchar() != '\n');
		if (res != 1)
			printf("ERROR! INVALID INPUT!\n");
	} while (res != 1);

	do
	{
		printf("First integer number:");
		res = scanf("%d", &x);
		while (getchar() != '\n');
		if (res != 1)
			printf("ERROR! INVALID INPUT!\n");
	} while (res != 1);

	do
	{
		printf("Second integer number:");
		res = scanf("%d", &y);
		while (getchar() != '\n');
		if (res != 1)
			printf("ERROR! INVALID INPUT!\n");
	} while (res != 1);

	if (x > pow(2, N - 1) - 1 || y > pow(2, N - 1) - 1 || x < -pow(2, N - 1) || y < -pow(2, N - 1))
	{
		printf("ERROR! OVERFLOW!\n");
		return 1;
	}

	int *a = (int*)malloc(N * sizeof(int));
	a = decToBin(x);

	int *b = (int*)malloc(N * sizeof(int));
	b = decToBin(y);

	int *c;
	c = (int*)malloc(N * sizeof(int));
	c = binMultiplication(a, b);

	if ((a[N - 1] ^ b[N - 1]) != c[N - 1])
	{
		printf("ERROR! OVERFLOW!\n");
		return 1;
	}

	printf("First integer binary number:");
	prntBinary(a, N);

	printf("Second integer binary number:");
	prntBinary(b, N);

	printf("Binary multiplication:");
	prntBinary(c, 2 * N);
	printf("Decimal multiplication: %d", binToDec(c));
}