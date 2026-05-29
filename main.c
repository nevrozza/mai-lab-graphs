#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "cli/cli.h"
#include "solve/solve.h"

int main(void) {
    char buf[256];
    int graph[MAX_VERTICES][MAX_VERTICES];
    int numVertices = 0;

    printf("reset – быстрый перезапуск; quit – выход\n");

    while (true) {
        printf("Выберите способ задания графа (матрица смежности):\n");
        printf("1. Вручную\n");
        printf("2. Заготовленный граф (5 вершин)\n");
        printf("> ");

        InputStatus status = readLine(buf, sizeof(buf));
        if (status == INPUT_RESET) {
            continue;
        }
        if (status == INPUT_QUIT) {
            break;
        }

        int choice = 0;
        if (strcmp(buf, "1") == 0) choice = 1;
        else if (strcmp(buf, "2") == 0) choice = 2;
        else {
            printf("Введите 1 или 2.\n");
            continue;
        }

        if (choice == 1) {
            int count = 0;
            while (1) {
                printf("Введите размер сетки (от 1 до %d): ", MAX_VERTICES);
                const InputStatus s = readInt(&count);
                if (s == INPUT_RESET || s == INPUT_QUIT) {
                    status = s;
                    break;
                }
                if (s == INPUT_OK && count > 0 && count <= MAX_VERTICES) {
                    break;
                }
            }

            if (status == INPUT_RESET) {
                continue;
            }
            if (status == INPUT_QUIT) {
                break;
            }

            numVertices = count;
            printf("Введите строки матрицы построчно через пробел\n");

            for (int i = 0; i < count; i++) {
                while (true) {
                    const InputStatus s = readMatrixRow(i, count, graph);
                    if (s == INPUT_RESET || s == INPUT_QUIT) {
                        status = s;
                        break;
                    }
                    if (s == INPUT_OK) {
                        break;
                    }
                }
                if (status == INPUT_RESET || status == INPUT_QUIT) break;
            }

            if (status == INPUT_RESET) {
                continue;
            }
            if (status == INPUT_QUIT) {
                break;
            }
        } else {
            numVertices = 5;
            int preset[MAX_VERTICES][MAX_VERTICES] = {
                {0, 10, 3, 0, 0},
                {0, 0, 1, 2, 0},
                {0, 4, 0, 8, 2},
                {0, 0, 0, 0, 7},
                {0, 0, 0, 9, 0}
            };
            for (int i = 0; i < numVertices; i++) {
                for (int j = 0; j < numVertices; j++) {
                    graph[i][j] = preset[i][j];
                }
            }
        }
        printf("Итоговая матрица:\n");
        for (int i = 0; i < numVertices; i++) {
            for (int j = 0; j < numVertices; j++) {
                printf("%4d", graph[i][j]);
            }
            printf("\n");
        }

        int startVertex;
        printf("\nВведите число от 0 до %d; reset для выхода", numVertices - 1);
        while (true) {
            printf("\n> ");
            const InputStatus s = readInt(&startVertex);
            if (s == INPUT_RESET || s == INPUT_QUIT) {
                status = s;
                break;
            }
            if (s == INPUT_OK && startVertex >= 0 && startVertex < numVertices) {
                deikstra(graph, numVertices, startVertex);
                continue;
            }
            printf("Значение должно быть в диапазоне [0..%d]", numVertices - 1);
        }

        if (status == INPUT_RESET) {
            continue;
        }
        if (status == INPUT_QUIT) {
            break;
        }
    }

    printf("Пока-пока!\n");

    return 0;
}
