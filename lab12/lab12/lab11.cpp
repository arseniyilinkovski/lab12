#include <iostream>
#include <string>
using namespace std;
#define endl "\n"


void task1();
void task2();
void dop_2();
void dop_1();
void dop_3();
int create_mask(int len_of_num);


int main()
{
	setlocale(LC_CTYPE, "Russian");
	dop_3();
	dop_2();
	dop_1();
	task2();
	task1();
    return 0;
}

void task1() {
	
	char tmp[33];
	int A, maskA = 0;
	cout << "Первое число А = "; cin >> A;
	_itoa_s(A, tmp, 2);
	cout << "A = " << tmp << endl;
	int len = strlen(tmp);
	maskA = create_mask(len);
	_itoa_s(A | maskA, tmp, 2);
	cout << "Новый A = " << tmp << endl;
}

int create_mask(int len_of_num) {
	int maskA = 0;
	for (int i = 1; i < len_of_num; i += 2) {
		maskA += pow(2, i);
	}
	return maskA;
}

void task2() {
	char tmp[33];
	int A, B, maskA = 0, maskB = 0, n = 0, m = 0, mask;
	cout << "Введите число А: "; cin >> A;
	_itoa_s(A, tmp, 2);
	cout << "A = " << tmp << endl;
	cout << "Введите число B: "; cin >> B;
	_itoa_s(B, tmp, 2);
	cout << "B = " << tmp << endl;

	cout << "Введите n: "; cin >> n;
	cout << "Введите m: "; cin >> m;

	maskA = ((1 << 3) - 1) << (n - 1);
	maskB = ~((1 << 3) - 1) << (m - 1);
	mask = (1 << m) - 1;
	_itoa_s((((B >> (m) << (n)) | ((A & maskA) >> (n - 1)))<<m) | (B & mask), tmp, 2);
	cout << "Результат: " << tmp << "\n";
}



void dop_1() { //var3
	int A, maska, h; 
	char tmp[33];
	printf("Введите число А=");
	cin >> A;
	_itoa_s(A, tmp, 2);
	cout << "A в двоичной системе =" << tmp << endl;
	maska = 16382, h = 8192;
	while (A < h)
	{
		maska = maska >> 1;
		h = h / 2;
	}
	maska = maska >> 1, maska = maska << 1;
	_itoa_s((A & (~maska)) | ((~(A & maska)) & maska), tmp, 2);
	cout << "Изменённое A:" << tmp << endl;
}


void dop_2() { //var 3
	int A = 0, B = 0, n = 0, q = 0, p = 0, m = 0, maska = 0, maskb = 0;
	char tmp[33];
	printf("Введите число А=");
	cin >> A;
	_itoa_s(A, tmp, 2);
	cout << "A в двоичной системе =" << tmp << endl;
	printf("Введите число В=");
	cin >> B;
	_itoa_s(A, tmp, 2);
	cout << "A в двоичной системе =" << tmp << endl;
	printf("Сколько битов взять из А?\n");
	cin >> n;
	printf("C какой позиции в А начинать брать биты?\n");   //биты отсчитываются справа налево
	cin >> p;
	printf("Сколько битов заменить в В?\n");
	cin >> m;
	printf("C какой позиции в В начинать вставлять биты?\n");
	cin >> q;
	maska = ((1 << n) - 1) << (p - 1);
	maskb = ~(((1 << m) - 1) << (q - 1));
	_itoa_s((A & (~maska)) | ((~(A & maska)) & maska), tmp, 2);
	_itoa_s((B & maskb) | (((~(A & maska) & maska) >> (p - 1)) << (q - 1)), tmp, 2);   //сдвиги для регулирования 
	cout << "Изменённое А=" << tmp << endl;
	cout << "Изменённое В=" << tmp << endl;
}

void dop_3() {// var 7
	int A = 0, B = 0, n = 0, q = 0, p = 0, m = 0, maska = 0, maskb = 0;
	char tmp[33];
	printf("Введите число А=");
	cin >> A;
	printf("Введите число В=");
	cin >> B;
	_itoa_s(A, tmp, 2);
	cout << "A в двоичной системе =" << tmp << endl;
	_itoa_s(B, tmp, 2);
	cout << "B в двоичной системе =" << tmp << endl;
	maska = ((1 << 4) - 1) << 5;
	_itoa_s((B << 4) | ((A & maska) >> 5), tmp, 2);
	cout << "Изменённое В=" << tmp << endl;
}

