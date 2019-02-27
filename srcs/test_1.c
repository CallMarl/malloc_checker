
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "test.h"

int		test_1(void)
{
	for (size_t i = 1; i < MAX_ALLOC; i += INCR) {
		void	*data = malloc(i);

#ifdef CHECK_ALIGN
		if ((uintptr_t)data % 16 != 0) {
			dprintf(STDERR_FILENO, "malloc(%zu) returned a non aligned boundary", i);
			return -1;
		}
#endif
		memset(data, 'a', i);
		free(data);
	}
	return 0;
}
