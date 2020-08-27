// BinDiv.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>

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

void leftShift(int** bin)
{
	for (int i = N - 2; i > 0; i--)
		(*bin)[i] = (*bin)[i - 1];

	(*bin)[0] = 0;
}

int* binDivision(int*a, int*b)
{
	int *ans = (int*)malloc(N * sizeof(int));
	for (int i = 0; i < N; i++)
		ans[i] = 0;
	
}

void rightShift(int** bin)
{
	for (int i = 0; i < N - 1; i++)
		(*bin)[i] = (*bin)[i + 1];
}



int main()
{
    std::cout << "Hello World!\n"; 
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
