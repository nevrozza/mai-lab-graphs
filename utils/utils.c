#include "utils.h"

#include <stdint.h>
#include <stdio.h>

static void printPathHelper(int parents[], const int j) {
    if (parents[j] == -1) {
        return;
    }
    printPathHelper(parents, parents[j]);
    printf(" -> %d", j);
}

void printResults(int dist[], int parents[], const int numVertices, const int startVertex) {
    printf("\nКратчайшие пути от вершины %d:\n", startVertex);
    printf("Куда | Расстояние | Маршрут\n");
    for (int i = 0; i < numVertices; i++) {
        if (dist[i] == INT32_MAX) {
            printf("%4d | %10s | %s\n", i, "Нет пути", "-");
        } else {
            printf("%4d | %10d | %d", i, dist[i], startVertex);
            printPathHelper(parents, i);
            printf("\n");
        }
    }
}
