#include "cli.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


InputStatus readLine(char *buf, int maxLen) {
    if (fgets(buf, maxLen, stdin) == NULL) { // for startup.
        return INPUT_ERROR;
    }
    buf[strcspn(buf, "\r\n")] = '\0';
    if (strcmp(buf, "reset") == 0) {
        return INPUT_RESET;
    }
    if (strcmp(buf, "quit") == 0 || strcmp(buf, "exit") == 0) {
        return INPUT_QUIT;
    }
    return INPUT_OK;
}

InputStatus readInt(int *val) {
    char buf[128];
    const InputStatus status = readLine(buf, sizeof(buf));
    if (status != INPUT_OK) {
        return status;
    }
    char *endptr;
    const long lval = strtol(buf, &endptr, 10);
    if (endptr == buf || *endptr != '\0') {
        return INPUT_ERROR;
    }
    *val = (int) lval;
    return INPUT_OK;
}

InputStatus readMatrixRow(int rowId, int count, int graph[MAX_VERTICES][MAX_VERTICES]) {
    char buf[1024];
    printf("Строка %d (введите %d nums через пробел): ", rowId, count);

    const InputStatus status = readLine(buf, sizeof(buf));
    if (status != INPUT_OK) {
        return status;
    }

    const char *token = strtok(buf, " \t");
    for (int i = 0; i < count; i++) {
        if (token == NULL) {
            return INPUT_ERROR;
        }
        char *endptr;
        const long val = strtol(token, &endptr, 10);
        if (endptr == token) {
            return INPUT_ERROR;
        }
        graph[rowId][i] = (int) val;
        token = strtok(NULL, " \t");
    }
    return INPUT_OK;
}
