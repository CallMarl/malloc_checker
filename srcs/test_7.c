
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "test.h"

int     test_7(void)
{
	void		*data[MAX_ALLOC];

	for (size_t i = 1; i < MAX_ALLOC; i += INCR) {
		data[i] = realloc(NULL, i);
		memset(data[i], 'a', i);

#ifdef CHECK_ALIGN
		if ((uintptr_t)data[i] % 16 != 0) {
			dprintf(STDERR_FILENO, "malloc(%zu) returned a non aligned boundary\n", i);
			return -1;
		}
#endif
	}

	for (size_t i = 1; i < MAX_ALLOC; i += INCR) {
		char cmp[i];

		memset(cmp, 'a', i);
		if (memcmp(cmp, data[i], i) != 0) {
			dprintf(STDERR_FILENO, "Segment %zu is corrupted ( %d )\n", i, __LINE__);
			return -1;
		}
	}

	for (size_t i = 1; i < MAX_ALLOC; i += INCR) {
		char cmp[i];

		memset(cmp, 'a', i);
		if (memcmp(cmp, data[i], i) != 0) {
			dprintf(STDERR_FILENO, "Segment %zu is corrupted ( %d )", i, __LINE__);
			return -1;
		}

		free(data[i]);
	}
	return 0;
}