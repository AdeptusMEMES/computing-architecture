// RealMultiplication.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

typedef union
{
	float number;
	struct
	{
		unsigned int mantissa :23;
		unsigned int exponent : 8;
		unsigned int sign : 1;
	} parts;
}number;

bool revers = false, znak1 = false, znak2 = false, sign_revers = false, result_znak;
string copy_a, copy_b, copy_c, copy_d, reg_a, reg_b, reg_c, reg_d, result, resilt_exp;
int counter, new_porydok;

void push(int a, string& b, int code)
{
	b = "";
	while (a > 0)
	{
		b = (char)(a % 2 + '0') + b;
		a /= 2;
	}
	if (code == 1)
		while (b.size() != 8)
			b = '0' + b;
	if (code == 2)
		while (b.size() != 23)
			b = '0' + b;
}

int get_porydok(string reg_a, string reg_b)
{
	int ram = 0;
	reg_a = '0' + reg_a;
	reg_b = '0' + reg_b;

	string result;
	for (int i = reg_a.size() - 1; i > -1; i--)
	{
		int k = (reg_a[i] - '0') + (reg_b[i] - '0') + ram;
		ram = k / 2;
		k %= 2;
		result = (char)(k + '0') + result;
	}
	result = (char)(ram + '0') + result;
	if (result[0] == '1') to_additional(result);
	int res = stoi(result, nullptr, 2);
	return res;
}

void prepare(float &a)
{
	to_additional(reg_c);
}

void to_additional(string a)
{
	for (int i = 0; i < a.size(); i++)
		a[i] = (char)((a[i] - '0') % 2) + '0';
	int j = a.size() - 1;
	a[j]++;
	while (a[j] == '2')
	{
		a[j--] -= 2;
		a[j]++;
	}
}

void sub(string a, string b)
{
	for (int j = 0; j < a.size() - b.size(); j++)
		b += '0';

	while (result.size() != a.size())
		result = '0' + result;
	int ram = 0;
	for (int i = result.size() - 1; i > -1; i--)
	{
		int k = (result[i] - '0') - (a[i] - '0') + ram;
		ram = k / 2;
		k %= 2;
		result[i] = (char)(k + '0');
	}
	if (ram == 1)
		result = '1' + result;
}

void division(number a, number b)
{
	new_porydok = get_porydok(reg_a, reg_b);
	reg_b = '1' + reg_b;
	reg_d = '1' + reg_d;
	sub(reg_b, reg_d);

	if (result.size() > 47)
		new_porydok++;
	result.erase(0, 1);
	while (result.size() > 23)
		result.erase(result.size() - 1, 1);
	new_porydok += 127;
	if (new_porydok < 0)
	{
		cout << "ERROR! UNDERFLOW";
		exit(0);
	}
}

int main()
{
    cout << "Hello World!\n"; 
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
