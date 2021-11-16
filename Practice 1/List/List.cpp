#include <iostream>
#include <fstream>
#include <set>
#include <stdlib.h>
#include <time.h>

struct Set {
    char el; Set* next;
    Set(char e, Set* n) : el(e), next(n) {};
    ~Set() { delete next; }
};

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
    char A[un] = {}, B[un] = {},
        C[un] = {}, D[un] = {};

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

    //Преобразование массивов в списки
    Set* LA = nullptr;
    Set* LB = nullptr;
    Set* LC = nullptr;
    Set* LD = nullptr;
    Set* LE = nullptr;
    Set* LF = nullptr;

    //Инициализация списков
    for (int i = 0; A[i]; ++i) LA = new Set(A[i], LA);
    for (int i = 0; B[i]; ++i) LB = new Set(B[i], LB);
    for (int i = 0; C[i]; ++i) LC = new Set(C[i], LC);
    for (int i = 0; D[i]; ++i) LD = new Set(D[i], LD);

    cout << "E = A | B | C \\ D" << endl << endl;
    cout << "Set A: ";
    for (Set* p = LA; p; p = p->next) cout << p->el << " ";
    cout << endl;
    cout << "Set B: ";
    for (Set* p = LB; p; p = p->next) cout << p->el << " ";
    cout << endl;
    cout << "Set C: ";
    for (Set* p = LC; p; p = p->next) cout << p->el << " ";
    cout << endl;
    cout << "Set D: ";
    for (Set* p = LD; p; p = p->next) cout << p->el << " ";
    cout << endl << endl;

    const long Repeat = 1000000; // для измерения времени
    clock_t t1 = clock();
    for (long cnt = 0; cnt < Repeat; ++cnt) { //Контрольный цикл
        delete LF;
        delete LE;
        LF = nullptr;
        LE = nullptr;
        //Запись всех элементов из A в F (F = A)
        for (int i = 0; A[i]; ++i) LF = new Set(A[i], LF);

        //Сравнение эл-в из B с элементами F, если текущего эл-та нет в F (F = F | (B \ F))
        for (Set* p = LB; p; p = p->next) {
            int key = 0; //0 - если эл-та нет в F, 1 - если уже есть
            for (Set* q = LF; q && key == 0; q = q->next) {
                if (p->el == q->el) {
                    key = 1;
                }
            }
            if (key == 0) {
                LF = new Set(p->el, LF);
            }
        }

        //Сравнение эл-в из C с элементами F, если текущего эл-та нет в F (F = F | (C \ F))
        for (Set* p = LC; p; p = p->next) {
            int key = 0; //0 - если эл-та нет в F, 1 - если уже есть
            for (Set* q = LF; q && key == 0; q = q->next) {
                if (p->el == q->el) {
                    key = 1;
                }
            }
            if (key == 0) {
                LF = new Set(p->el, LF);
            }
        }

        //Сравниваем F с D: если элемента из F нет в D, то записываем в результат (E = F \ D)
        for (Set* p = LF; p; p = p->next) {
            int key = 0; //0 - если эл-та нет в D, 1 - если есть
            for (Set* q = LD; q && key == 0; q = q->next) {
                if (p->el == q->el) {
                    key = 1;
                }
            }
            if (key == 0) {
                LE = new Set(p->el, LE);
            }
        }
    }
    clock_t t2 = clock();

    //Вывод результата
    if (LE) {
        cout << "Result set: ";
        for (Set* p = LE; p; p = p->next) cout << p->el << " ";
        cout << endl << "t1 = " << t1 << endl << "t2 = " << t2 << endl;
        cout << "\nTime = " << (t2 - t1) << " / " << Repeat << " = " << (float)(t2 - t1) / CLOCKS_PER_SEC;
    }
    else cout << "Result set is empty!" << endl;

    //Очищение памяти
    delete LA;
    delete LB;
    delete LC;
    delete LD;
    delete LE;
    delete LF;
    return 0;
}