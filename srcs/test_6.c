
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "test.h"

int		test_6(void)
{
	void		*data[MAX_ALLOC];

	for (size_t len = 0; len < MAX_ALLOC; len += INCR)
	{
		char cmp[len];

		memset(cmp, 'a', len);

		for (size_t i = 1; i < MAX_ALLOC; i += INCR) {
			data[i] = malloc(len);
			memset(data[i], 'a', len);

#ifdef CHECK_ALIGN
			if ((uintptr_t)data[i] % 16 != 0) {
				dprintf(STDERR_FILENO, "malloc(%zu) returned a non aligned boundary", i);
				return -1;
			}
#endif
		}

		for (size_t i = 1; i < MAX_ALLOC; i += INCR) {
			if (memcmp(cmp, data[i], len) != 0)
			{
				dprintf(STDERR_FILENO, "Segment %zu is corrupted ( %d )", i, __LINE__);
				return -1;
			}
		}

		for (size_t i = 1; i < MAX_ALLOC; i += INCR) {
			if (memcmp(cmp, data[i], len) != 0)
			{
				dprintf(STDERR_FILENO, "Segment %zu is corrupted ( %d )", i, __LINE__);
				return -1;
			}
			free(data[i]);
		}
	}
	return 0;
}
