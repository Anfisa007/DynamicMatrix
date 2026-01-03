#include "interface.h"

int** allocateMatrix(int n, int m) {
    int **a = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
        a[i] = (int *)malloc(m * sizeof(int));
    return a;
}

void freeMatrix(int **a, int n) {
    for (int i = 0; i < n; i++)
        free(a[i]);
    free(a);
}

void inputManual(int **a, int n, int m) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            printf("a[%d][%d] = ", i, j);
            scanf("%d", &a[i][j]);
        }
}

void inputStatic(int **a, int *n, int *m) {
    *n = 3; *m = 3;
    int temp[3][3] = {
        {1, -2, 3},
        {4, 5, -6},
        {-7, 8, 9}
    };
    for (int i = 0; i < *n; i++)
        for (int j = 0; j < *m; j++)
            a[i][j] = temp[i][j];
}

void inputFromFile(int **a, int *n, int *m) {
    FILE *f = fopen("data.txt", "r");
    fscanf(f, "%d%d", n, m);
    for (int i = 0; i < *n; i++)
        for (int j = 0; j < *m; j++)
            fscanf(f, "%d", &a[i][j]);
    fclose(f);
}

void inputRandom(int **a, int n, int m) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            a[i][j] = rand() % 21 - 10;
}

void printMatrix(int **a, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            printf("%5d", a[i][j]);
        printf("\n");
    }
}

void printMatrixToFile(int **a, int n, int m, FILE *f) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            fprintf(f, "%5d", a[i][j]);
        fprintf(f, "\n");
    }
}

void taskA(int **a, int n, int m) {
    for (int i = 0; i < n; i++) {
        int min = a[i][0];
        for (int j = 1; j < m; j++)
            if (a[i][j] < min) min = a[i][j];
        for (int j = 0; j < m; j++)
            a[i][j] += min;
    }
}

void taskB(int **a, int n, int m) {
    int k = 0;
    for (int i = 0; i < n && i < m; i++)
        if (a[i][i] > 0) k++;

    for (int i = 0; i < n; i++)
        a[i][m - 1 - i] *= k;
}

void taskC(int **a, int n, int m) {
    int *sum = (int *)malloc(m * sizeof(int));
    for (int j = 0; j < m; j++) {
        sum[j] = 0;
        for (int i = 0; i < n; i++)
            if (a[i][j] > 0) sum[j] += a[i][j];
    }

    for (int i = 0; i < m - 1; i++)
        for (int j = i + 1; j < m; j++)
            if (sum[i] < sum[j]) {
                int t = sum[i];
                sum[i] = sum[j];
                sum[j] = t;
            }

    printf("Отсортированные суммы столбцов:\n");
    for (int i = 0; i < m; i++)
        printf("%d ", sum[i]);
    printf("\n");

    free(sum);
}

void taskD(int **a, int n, int m) {
    if (n < 2 || m < 2) return;

    for (int i = 0; i < n - 2; i++)
        for (int j = i + 1; j < n - 1; j++)
            if (a[i + 1][i] < a[j + 1][j]) {
                int t = a[i + 1][i];
                a[i + 1][i] = a[j + 1][j];
                a[j + 1][j] = t;
            }
}

void startProgram() {
    int choiceTask, choiceInput;
    int n = 3, m = 3;
    srand(time(NULL));

    do {
        printf("\nЗадача №25\nЧигарева Анфиса Ильинична, ИТПИ-2515\n");
        printf("Выберите задание:\n");
        printf("1 - a\n2 - б\n3 - в\n4 - г\nEsc - выход\n");

        choiceTask = getchar();
        if (choiceTask == 27) break;
        getchar();

        printf("Выберите ввод данных:\n");
        printf("1 - в программе\n2 - с экрана\n3 - из файла\n4 - случайные\n");
        scanf("%d", &choiceInput);

        int **a = allocateMatrix(10, 10);if (choiceInput == 1) inputStatic(a, &n, &m);
        if (choiceInput == 2) {
            printf("Введите n, m: ");
            scanf("%d%d", &n, &m);
            inputManual(a, n, m);
        }
        if (choiceInput == 3) inputFromFile(a, &n, &m);
        if (choiceInput == 4) {
            printf("Введите n, m: ");
            scanf("%d%d", &n, &m);
            inputRandom(a, n, m);
        }

        FILE *f = fopen("dataout.txt", "w");

        printf("\nИсходная матрица:\n");
        printMatrix(a, n, m);
        fprintf(f, "Исходная матрица:\n");
        printMatrixToFile(a, n, m, f);

        if (choiceTask == '1') taskA(a, n, m);
        if (choiceTask == '2') taskB(a, n, m);
        if (choiceTask == '3') taskC(a, n, m);
        if (choiceTask == '4') taskD(a, n, m);

        printf("\nРезультат:\n");
        printMatrix(a, n, m);
        fprintf(f, "\nРезультат:\n");
        printMatrixToFile(a, n, m, f);

        fclose(f);
        freeMatrix(a, 10);

        printf("\nНажмите Enter для продолжения...");
        getchar(); getchar();

    } while (1);
}
