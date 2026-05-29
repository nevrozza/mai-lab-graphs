#include <stdio.h>

#include "solve/solve.h"

int main(void) {
    const int numVertices = 5;

    int graph[MAX_VERTICES][MAX_VERTICES] = {
        {0, 10, 3, 0, 0},
        {0, 0, 1, 2, 0},
        {0, 4, 0, 8, 2},
        {0, 0, 0, 0, 7},
        {0, 0, 0, 9, 0}
    };

    const int startVertex = 0;

    printf("Матрица смежности (%d вершин):\n", numVertices);
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            printf("%4d", graph[i][j]);
        }
        printf("\n");
    }

    deikstra(graph, numVertices, startVertex);

    return 0;
}
