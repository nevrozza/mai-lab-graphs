#ifndef GRAPHS_CLI_H
#define GRAPHS_CLI_H

#include "../solve/solve.h"

typedef enum {
    INPUT_OK,
    INPUT_RESET,
    INPUT_QUIT,
    INPUT_ERROR
} InputStatus;

InputStatus readLine(char *buf, int maxLen);

InputStatus readInt(int *val);

InputStatus readMatrixRow(int rowId, int count, int graph[MAX_VERTICES][MAX_VERTICES]);

#endif //GRAPHS_CLI_H
