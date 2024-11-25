#include <iostream>
#include <stdio.h>
#include <conio.h> 
#include <cmath>

using namespace std;

void p1();
void p21();
void p22();
void p3();
void p41();
void p42();

void dop1();
void dop2();
void dop3();

void main()
{
	setlocale(LC_CTYPE, "RU");
	
	int x;
	
	cout << "1 - Найти сумму 4 чисел\n2 - Найти сумму квадратов 4 чисел\n3 - Найти произведение 4 чисел " << endl;
	cin >> x;

	float a, sum = 0; 
	int i;
	const int size = 4;

	switch (x)
	{
		case 1:
		{
			for (i = 0; i < size; i++)
			{
				cout << "Введите a" << i << endl;
				cin >> a;
				sum = sum + a;
			}
		} break;
		case 2:
		{
			for (i = 0; i < size; i++)
			{
				cout << "Введите a" << i << endl;
				cin >> a;
				sum = sum + a * a;
			}
		} break;
		case 3:
		{
			sum = 1;
			for (i = 0; i < size; i++)
			{
				cout << "Введите a" << i << endl;
				cin >> a;
				sum = sum * a;
			}
		} break;
		default: cout << "Неверный ввод" << endl; break;
	}
	cout << "Ответ: " << sum << endl;

//	p1();
//	p21();
//	p22();
//	p3();
//	p41();
//	p42();

//	dop1();
//	dop2();
	dop3();
}

void p1()
{
	int n, pr = 1;

	cout << "Введите число для нахождения факториала: ";
	cin >> n;

	for (int i = 1; i <= n; i++)
	{
		pr = pr * i;
	}
	cout << "Ответ: " << pr << endl;
}

void p21()
{
	cout << "Найти среднее арифметическое некоторого количества чисел, введенных с клавиатуры" << endl;

	char ch;
	float sv, x, sum = 0;
	float count = 0;
	do
	{
		printf("Enter x:");
		scanf_s("%f", &x);
		sum += x;
		count++;
		sv = sum / count;
		printf("sv=%1.3f\n", sv);
		printf("if continue input 'y' else 'n' ");
		ch = _getch();
	} while (ch != 'n');
}

void p22()
{
	cout << "Найти сумму(n ^ log(n)) / (log(n) ^ n), где n принимает значения от 2 до 9 включительно" << endl;

	float sum = 0, a, t, p;
	for (int n = 2; n < 10; n++)
	{
		t = pow(n, log((float)n));
		p = pow(log((float)n), n);
		a = t / p;
		sum += a;
	}
	printf("S=%f\n", sum);
}

void p3()
{
	cout << "Найти минимальное значение из 5 чисел, введенных с клавиатуры и вывести ее номер в массиве" << endl;

	int count = 5, n = 1;
	float b, m = 9999;
	for (int i = 0; i < count; i++)
	{
		cout << "Введите b" << i << endl;
		cin >> b;
		if (b < m)
		{
			m = b;
			n = i;
		}
	}
	cout << "m = " << m << endl;
	cout << "n = " << n << endl;
}

void p41()
{
	float f, g, summ = 0;
	float a[4];
	for (int i = 0; i < 4; i++)
	{
		cout << "Введите a" << i << endl;
		cin >> a[i];
	}
	for (float k = 6; k < 7; k = k + 0.2)
	{
		f = k;
		for (int i = 0; i < 4; i++)
		{
			summ = summ + a[i] / (i + 1);
			g = f / summ;
		}
	}
	cout << "Сумма: " << g << endl;
}

void p42()
{
	float y[5], q = 1, max;
	for (int i = 0; i < 5; i++)
	{
		cout << "Введите y" << i << endl;
		cin >> y[i];
	}
	max = y[0];
	for (int i = 1; i < 5; i++)
	{
		if (y[i] > max)
		{
			max = y[i];
		}
	}
	for (int i = 1; i < 5; i++)
	{
		q = q * (y[i] + 2 * max);
	}
	cout << "Произвдение: " << q;
}

void dop1()
{
	cout << "В последовательности из n целых чисел найти и вывести значение суммы четных элементов." << endl;

	int a[100], n, summ = 0;
	cout << "Сколько чисел хотите ввести? ";
	cin >> n;

	for (int x = 0; x < n; x++)
	{
		cout << "Введите " << x << " число ";
		cin >> a[x];
	}

	for (int x = 0; x < n; x++)
	{
		if (a[x] % 2 == 0)
		{
			summ = summ + a[x];
		}
	}
	
	cout << "Сумма: " << summ << endl;
}

void dop2()
{
	cout << "В последовательности из n целых чисел найти и вывести порядковый номер последнего отрицательного элемента." << endl;
	
	int a[100], n, k = 0, l = 0;
	cout << "Сколько чисел хотите ввести? ";
	cin >> n;

	for (int x = 0; x < n; x++)
	{
		cout << "Введите " << x << " число ";
		cin >> a[x];
	}

	for (int x = 0; x < n; x++)
	{
		if (a[x] < 0)
		{
			k = a[x];
			l = x;
		}
	}

	cout << "Последний отрицательный член: " << k << "\tего номер: " << l << endl;
}

void dop3()
{
	cout << "В последовательности найти число чередований знака" << endl;
	
	int a[100], n, k = 0;
	cout << "Сколько чисел хотите ввести? ";
	cin >> n;

	for (int x = 0; x < n; x++)
	{
		cout << "Введите " << x << " число ";
		cin >> a[x];
	}

	for (int x = 0; x < n - 1 ;x++)
	{
		if ((a[x] < 0 && a[x + 1] >= 0) || (a[x] >= 0 && a[x + 1] < 0))
		{
			k++;
		}
	}

	cout << "Число чередований знака: " << k << endl;
}