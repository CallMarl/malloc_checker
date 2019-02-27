
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "test.h"

int     test_12(void)
{
	void		*data[MAX_ALLOC];
	size_t		i;

	for (i = 1; i < MAX_ALLOC; i += INCR) {
		data[i] = malloc(i);
		memset(data[i], 'a', i);
	}

	for (i = 1; i < MAX_ALLOC; i += INCR) {
		data[i] = realloc(data[i], i * 2);

		#ifdef CHECK_ALIGN
			if ((uintptr_t)data[i] % 16 != 0) {
				dprintf(STDERR_FILENO, "malloc(%zu) returned a non aligned boundary", i);
				return -1;
			}
		#endif
		char cmp[i];

		memset(cmp, 'a', i);
		if (memcmp(cmp, data[i], i) != 0) {
			dprintf(STDERR_FILENO, "Segment %zu is corrupted ( %d )", i, __LINE__);
			return -1;
		}
	}

	for (i = 1; i < MAX_ALLOC; i += INCR) {
		char cmp[i];

		memset(cmp, 'a', i);
		if (memcmp(cmp, data[i], i) != 0) {
			dprintf(STDERR_FILENO, "Segment %zu is corrupted ( %d )", i, __LINE__);
			return -1;
		}
	}
	return 0;
}
