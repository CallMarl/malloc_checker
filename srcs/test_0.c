
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "test.h"

int     test_0(void)
{
    void        *data = malloc(0);
    int         res = 0;

    if (data == NULL) {
        return 0;
    }
#ifdef CHECK_ALIGN
    if ((uintptr_t)data % 16 != 0) {
        dprintf(STDERR_FILENO, "malloc(0) returned a non aligned boundary");
        res =  -1;
    }
#endif
    free(data);
    return res;
}