#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>  
#include <math.h>   

int N;

void prntBin(int* num)
{
	for (int i = N - 1; i >= 0; i--)
		printf("%d", num[i]);
	printf("\n");
}

void invers(int **bin)
{
	for (int i = 0; i < N; i++)
		(*bin)[i] = abs((*bin)[i] - 1);
	int temp;
	int e = 1;
	for (int i = 0; i < N; i++)
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
		invers(&a);
	return a;
}

int binToDec(int* num)
{
	int sign = 1;
	if (num[N - 1] == 1)
	{
		sign = -1;
		invers(&num);
	}
	int d = 0;
	for (int i = 0; i < N; i++)
		d += pow(2, i)*num[i];
	d *= sign;
	return d;
}

int* binSum(int*a, int*b)
{
	int e = 0;
	int *c;
	c = (int*)malloc(N * sizeof(int));
	for (int i = 0; i < N; i++)
	{
		c[i] = (a[i] ^ b[i]) ^ e;
		e = (a[i] && b[i]) || (a[i] && e) || (b[i] && e);
	}
	return c;
}

void shift(int** bin)
{
	for (int i = N - 2; i > 0; i--)
		(*bin)[i] = (*bin)[i - 1];

	(*bin)[0] = 0;
}

void backShift(int** bin)
{
	for (int i = 0; i < N-1; i++)
		(*bin)[i] = (*bin)[i + 1];
}



int difference(int *a, int *b)
{
	int an = 0, bn = 0;
	int ac = 1, bc = 1;
	for (int i = N - 1; i >= 0; i--)
	{
		if (a[i] == 0 && ac)
			an++;
		else
			ac = 0;

		if (b[i] == 0 && bc)
			bn++;
		else
			bc = 0;
	}

	return bn - an;
}

int* binPosDivision(int **a, int *b)
{	
	int k = difference((*a), b);

	for (int i = 0; i < k; i++)
		shift(&b);
	
	int *mb = (int*)malloc(N * sizeof(int));

	for (int i = 0; i < N; i++)
		mb[i] = b[i];

	invers(&mb);

	int *ans = (int*)malloc(N * sizeof(int));

	for (int i = 0; i < N; i++)
		ans[i] = 0;

	(*a) = binSum((*a), mb);
	ans[0] = abs((*a)[N - 1] - 1);

	for (int i = 0; i < k; i++)
	{
		shift(&(*a));

		if ((*a)[N - 1] == 1)
			(*a) = binSum((*a), b);
		else
			(*a) = binSum((*a), mb);

		shift(&ans);
		ans[0] = abs((*a)[N -1] - 1);
	}


	if ((*a)[N - 1] == 1)
		(*a) = binSum((*a), b);

	for(int i=0; i<k;i++)
		backShift(&(*a));

	return ans;
}

int binMultiplication(int *a, int *b)
{
	int *ans = (int*)malloc(N * sizeof(int));
	int *A = (int*)malloc(N * sizeof(int));
	int *B = (int*)malloc(N * sizeof(int));
	int min = 0;

	for (int i = 0; i < N; i++)
	{
		A[i] = a[i];
		B[i] = b[i];
		ans[i] = 0;
	}

	min = B[N - 1] ^ A[N - 1];

	if (B[N - 1] == 1)
		invers(&B);
	if (A[N - 1] == 1)
		invers(&A);

	for (int i = 0; i < N; i++)
	{
		if (B[i] == 1)
			ans = binSum(ans, A);
		shift(&A);
	}
	if (min)
		invers(&ans);
	free(A);
	free(B);
	return ans;
}

int isZero(int *a)
{
	for (int i = 0; i < N; i++)
		if (a[i] != 0)
			return 0;
	return 1;
}

int* binDivision(int **a, int *b)
{
	int c = (*a)[N - 1] * 2 + b[N - 1];

	int *A = (int*)malloc(N * sizeof(int));
	int *B = (int*)malloc(N * sizeof(int));
	int *e = (int*)malloc(N * sizeof(int));

	if ((*a)[N - 1] == 1)
		invers(&(*a));
	if (b[N - 1] == 1)
		invers(&b);

	for (int i = 0; i < N; i++)
	{
		A[i] = (*a)[i];
		B[i] = b[i];
		e[i] = 0;
	}
	e[0] = 1;

	int d = binPosDivision(&(*a), b);

	if (c > 1 && isZero(*(a)) == 0)
	{
		d = binSum(d, e);
		invers(&A);
		(*a) = binSum(binMultiplication(B, d), A);
	}

	if (c > 0 && c < 3)
	{
		invers(&d);
	}

	return d;
}

int main(void)
{
	int x, y;

	printf("Bit count:");
	scanf("%d", &N);

	printf("First integer number:");
	scanf("%d", &x);
	
	printf("Second integer number:");
	scanf("%d", &y);

	if (x > pow(2, N - 1) - 1 || y > pow(2, N - 1) - 1 || x < -pow(2, N - 1) || y < -pow(2, N - 1))
	{
		printf("ERROR! OVERFLOW!\n");
		return 1;
	}

	if (x*10 <= y)
	{
		printf("ERROR! LOSS OF SIGNIFICANCE!\n");
		return 1;
	}

	int *a = (int*)malloc(N * sizeof(int));
	a = decToBin(x);

	int *b = (int*)malloc(N * sizeof(int));
	b = decToBin(y);

	if (isZero(b))
	{
		printf("ERROR! ZERO DIVISION!\n");
		return 1;
	}

	int *A = (int*)malloc(N * sizeof(int));
	for (int i = 0; i < N; i++)
		A[i] = a[i];

	int *B = (int*)malloc(N * sizeof(int));
	for (int i = 0; i < N; i++)
		B[i] = b[i];

	int *c = (int*)malloc(N * sizeof(int));
	c = binDivision(&a, b);

	if ((A[N-1]^B[N-1]!=c[N-1])||(a[N-1]==1))
	{
		printf("ERROR! OVERFLOW!\n");
		return 1;
	}

	printf("First integer binary number:");
	prntBin(A);

	printf("Second integer binary number:");
	prntBin(B);

	printf("Binary division:");
	prntBin(c);
	printf("Decimal division: %d\n", binToDec(c));

	printf("Binary rest:");
	prntBin(a);
	printf("Decimal rest: %d\n", binToDec(a));
}