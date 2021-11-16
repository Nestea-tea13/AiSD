#include <iostream>
#include <fstream>
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
    const int un = 27;
    char A[un] = {}, B[un] = {}, C[un] = {}, D[un] = {}, E[un] = {};
    int bA[un] = { 0 }, bB[un] = { 0 }, bC[un] = { 0 },  // Инициализация массивов битов
        bD[un] = { 0 }, bE[un] = { 0 };

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

    //Преобразование массивов в массивы битов
    for (int i = 0; A[i]; ++i) bA[A[i] - 'a'] = 1;
    for (int i = 0; B[i]; ++i) bB[B[i] - 'a'] = 1;
    for (int i = 0; C[i]; ++i) bC[C[i] - 'a'] = 1;
    for (int i = 0; D[i]; ++i) bD[D[i] - 'a'] = 1;

    const long Repeat = 1000000; // для измерения времени
    clock_t t1 = clock();
    for (long cnt = 0; cnt < Repeat; ++cnt) { //Контрольный цикл
        for (int i = 0; i < un; ++i) {
            bE[i] = (bA[i] | bB[i] | bC[i]) & ~bD[i];
        }
    }
    clock_t t2 = clock();

    //Обратное преобразование результата в массив символов
    int nE = 0;
    for (int i = 0, k = 0; i < un; ++i)
        if (bE[i] == 1) {
            nE++;
            E[k++] = i + 'a';
        }

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
