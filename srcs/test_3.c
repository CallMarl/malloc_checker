
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "test.h"

int		test_3(void)
{
	void		*data[MAX_ALLOC];

	for (size_t i = 1; i < MAX_ALLOC; i += INCR) {
		data[i] = malloc(i);

#ifdef CHECK_ALIGN
		if ((uintptr_t)data[i] % 16 != 0) {
			dprintf(STDERR_FILENO, "malloc(%zu) returned a non aligned boundary", i);
			return -1;
		}
#endif
	}

	for (size_t i = 1; i < MAX_ALLOC; i += INCR) {
		memset(data[i], 'a', i);
		free(data[i]);
	}
	return 0;
}
