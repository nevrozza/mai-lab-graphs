#include "solve.h"

#include <stdbool.h>
#include <stdint.h>

#include "../utils/utils.h"


// Непосещённая вершина с минимальным расстоянием
static int findMinDistance(const int dist[], const bool visited[], const int numVertices) {
    int min = INT32_MAX;
    int minIndex = -1;

    for (int v = 0; v < numVertices; v++) {
        if (!visited[v] && dist[v] <= min) {
            min = dist[v];
            minIndex = v;
        }
    }
    return minIndex;
}

void deikstra(int graph[MAX_VERTICES][MAX_VERTICES], const int numVertices, const int startVertex) {
    int dist[MAX_VERTICES];
    bool visited[MAX_VERTICES];
    int parents[MAX_VERTICES];

    for (int i = 0; i < numVertices; i++) {
        dist[i] = INT32_MAX;
        visited[i] = false;
        parents[i] = -1;
    }

    dist[startVertex] = 0;

    for (int count = 0; count < numVertices - 1; count++) {
        const int minDistanceVertex = findMinDistance(dist, visited, numVertices);

        if (minDistanceVertex == -1 || dist[minDistanceVertex] == INT32_MAX) {
            break;
        }

        visited[minDistanceVertex] = true;

        for (int v = 0; v < numVertices; v++) {
            if (!visited[v] && graph[minDistanceVertex][v] > 0 && dist[minDistanceVertex] != INT32_MAX
                && dist[minDistanceVertex] + graph[minDistanceVertex][v] < dist[v]) {
                dist[v] = dist[minDistanceVertex] + graph[minDistanceVertex][v];
                parents[v] = minDistanceVertex;
            }
        }
    }

    printResults(dist, parents, numVertices, startVertex);
}
