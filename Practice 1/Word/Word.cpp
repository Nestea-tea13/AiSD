#include <iostream>
#include <fstream>
#include <ctime>
#include <stdlib.h>
#include <time.h>

char getRandomSymbol()
{
	char symb;
	int min = 97, max = 122;
	symb = min + (rand() % (max - min) + 1);
	return symb;
}

using namespace std;
int main()
{
	srand(time(0));
	const int un = 27; //Мощность универсума
	char A[un] = {}, B[un] = {}, C[un] = {}, D[un] = {}, E[un] = {};
	long wA = 0, wB = 0, wC = 0, wD = 0, wE; //Выделение памяти для машинных слов

	//Генерация массивов символов
	int flag = 0;
	int nrand = rand() % (un - 1);
	for (int i = 0; i < nrand; ++i) {
		char a = getRandomSymbol();
		for (int j = 0; flag == 0 && j <= i; ++j)
			if (A[j] == a) flag = 1;
		if (flag == 0) A[i] = a;
	}


	flag = 0;
	nrand = rand() % (un - 1);
	for (int i = 0; i < nrand; ++i) {
		char a = getRandomSymbol();
		for (int j = 0; flag == 0 && j <= i; ++j)
			if (B[j] == a) flag = 1;
		if (flag == 0) B[i] = a;
	}

	flag = 0;
	nrand = rand() % (un - 1);
	for (int i = 0; i < nrand; ++i) {
		char a = getRandomSymbol();
		for (int j = 0; flag == 0 && j <= i; ++j)
			if (C[j] == a) flag = 1;
		if (flag == 0) C[i] = a;
	}

	flag = 0;
	nrand = rand() % (un - 1);
	for (int i = 0; i < nrand; ++i) {
		char a = getRandomSymbol();
		for (int j = 0; flag == 0 && j <= i; ++j)
			if (D[j] == a) flag = 1;
		if (flag == 0) D[i] = a;
	}

	cout << "E = A | B | C \\ D" << endl;
	cout << endl << "Set A: ";
	for (int i = 0; A[i]; ++i) cout << A[i] << " ";
	cout << endl << "Set B: ";
	for (int i = 0; B[i]; ++i) cout << B[i] << " ";
	cout << endl << "Set C: ";
	for (int i = 0; C[i]; ++i) cout << C[i] << " ";
	cout << endl << "Set D: ";
	for (int i = 0; D[i]; ++i) cout << D[i] << " ";
	cout << endl << endl;

	//Преобразование строк символов в машинные слова
	for (int i = 0; A[i]; ++i) wA |= (1L << (A[i] - 'a')); //Здесь – сдвиг 1 на номер бита
	for (int i = 0; B[i]; ++i) wB |= (1L << (B[i] - 'a'));
	for (int i = 0; C[i]; ++i) wC |= (1L << (C[i] - 'a'));
	for (int i = 0; D[i]; ++i) wD |= (1L << (D[i] - 'a'));

	const long Repeat = 1000000; // для измерения времени
	clock_t t1 = clock();
	for (long cnt = 0; cnt < Repeat; ++cnt) { //Контрольный цикл
		wE = (wA | wB | wC) & ~wD;
	}
	clock_t t2 = clock();

	//Преобразование машинного слова в строку символов
	int nE = 0;
	for (int i = 0; i < un; ++i)
		if (wE & (1L << i)) E[nE++] = char(i + 'a');
	E[nE] = '\0'; //26 в универсуме тогда?

	//Вывод результата
	if (nE > 0) {
		cout << "Result set: ";
		for (int i = 0; E[i]; ++i) cout << E[i] << " ";
		cout << endl << "t1 = " << t1 << endl << "t2 = " << t2 << endl;
		//cout << "t = " << (t2 - t1) << "/" << Repeat;
		cout << "\nTime = " << (t2 - t1) << " / " << Repeat << " = " << (float)(t2 - t1) / CLOCKS_PER_SEC;
	}
	else cout << "Result set is empty!" << endl;
	return 0;
}