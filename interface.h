#ifndef INTERFACE_H
#define INTERFACE_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void startProgram();

//Работа с памятью
int** allocateMatrix(int n, int m);
void freeMatrix(int **a, int n);

//Ввод
void inputManual(int **a, int n, int m);
void inputFromFile(int **a, int *n, int *m);
void inputRandom(int **a, int n, int m);
void inputStatic(int **a, int *n, int *m);

//Вывод
void printMatrix(int **a, int n, int m);
void printMatrixToFile(int **a, int n, int m, FILE *f);

//Задания
void taskA(int **a, int n, int m);
void taskB(int **a, int n, int m);
void taskC(int **a, int n, int m);
void taskD(int **a, int n, int m);

#endif
