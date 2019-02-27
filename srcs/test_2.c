
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

#include "test.h"

int		test_2(void)
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
		memset(data[i], 'a', i);
	}

	for (size_t i = 1; i < MAX_ALLOC; i += INCR) {
		char	cmp[i];
		char	zzzz[i+1];

		memset(cmp, 'a', i);
		if (memcmp(cmp, data[i], i) != 0) {
			memcpy(zzzz, data[i], i);
			zzzz[i] = 0;
			dprintf(STDERR_FILENO, "Segment %zu is corrupted ( '%s' )", i, zzzz);
			return -1;
		}
		free(data[i]);
	}
	return 0;
}
