#include <iostream>
#include <fstream>
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
    char A[un] = {}, B[un] = {}, C[un] = {},
        D[un] = {}, E[un] = {}, F[un] = {};
    int nE = 0;

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

    cout << "E = A | B | C \\ D" << endl << endl;
    cout << "Set A: ";
    for (int i = 0; A[i]; ++i) cout << A[i] << " ";
    cout << endl << "Set B: ";
    for (int i = 0; B[i]; ++i) cout << B[i] << " ";
    cout << endl << "Set C: ";
    for (int i = 0; C[i]; ++i) cout << C[i] << " ";
    cout << endl << "Set D: ";
    for (int i = 0; D[i]; ++i) cout << D[i] << " ";
    cout << endl << endl;

    const long Repeat = 1000000; // для измерения времени
    clock_t t1 = clock();
    for (long cnt = 0; cnt < Repeat; ++cnt) { //Контрольный цикл
        nE = 0;
        //Запись всех элементов из A в F (F = A)
        for (int i = 0; A[i]; ++i) F[i] = A[i];

        //Сравнение эл-в из B с элементами F, если текущего эл-та нет в F (F = F | (B \ F))
        for (int i = 0; B[i]; ++i) {
            int key = 0; //0 - если эл-та нет в F, 1 - если уже есть
            int j;
            for (j = 0; F[j] && key == 0; ++j) {
                if (B[i] == F[j]) {
                    key = 1;
                }
            }
            if (key == 0) {
                F[j] = B[i];
            }
        }

        //Сравнение эл-в из C с элементами F, если текущего эл-та нет в F (F = F | (C \ F))
        for (int i = 0; C[i]; ++i) {
            int key = 0; //0 - если эл-та нет в F, 1 - если уже есть
            int j;
            for (j = 0; F[j] && key == 0; ++j) {
                if (C[i] == F[j]) {
                    key = 1;
                }
            }
            if (key == 0) {
                F[j] = C[i];
            }
        }

        //Сравниваем F с D: если элемента из F нет в D, то записываем в результат (E = F \ D)
        for (int i = 0; F[i]; ++i) {
            int key = 0; //0 - если эл-та нет в D, 1 - если есть
            for (int j = 0; D[j] && key == 0; ++j) {
                if (F[i] == D[j]) {
                    key = 1;
                }
            }
            if (key == 0) {
                E[nE++] = F[i];
            }
        }
    }
    clock_t t2 = clock();

    //Вывод результата
    if (nE > 0) {
        cout << "Result set: ";
        for (int i = 0; E[i]; ++i) cout << E[i] << " ";
        cout << "\nt1 = " << t1 << "\nt2 = " << t2 << endl;
        //cout << "t = " << (t2 - t1) << "/" << Repeat;
        cout << "\nTime = " << (t2 - t1) << " / " << Repeat << " = " << (float)(t2 - t1) / CLOCKS_PER_SEC;
    }
    else cout << "Result set is empty!" << endl;
    return 0;
}