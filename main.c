
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include "test.h"

typedef int (*c_test)(void);

#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))

void	start_test(int *pid, int *error_stream, c_test test)
{
	int		piped[2];

	pipe(piped);
	*pid = fork();
	if (*pid == 0)
	{
		// Child
		close(piped[0]);
		dup2(piped[1], STDERR_FILENO);
		exit(test());
	}
	else
	{
		// Parent
		*error_stream = piped[0];
		close(piped[1]);
	}
}

void	wait_test(size_t test_number, int *pid, int *error_stream)
{
	int		status;
	char	buff[500];

	waitpid(*pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		printf("\033[031m [SIGNALED]\033[0m Test %zu received signal %s\n", test_number, strsignal(WTERMSIG(status)));
	}
	else
	{
		if (WEXITSTATUS(status) != 0)
		{
			buff[read(*error_stream, buff, 499)] = 0;
			printf("\033[031m [FAILURE]\033[0m Test %zu ended with an error ( stderr -> '%s' )\n", test_number, buff);
		}
		else
		{
			printf("\033[032m [OK]\033[0m Test %zu seems passed\n", test_number);
		}
	}
	close(*error_stream);
	*error_stream = -1;
}

int		main(int argc, char **argv)
{
	c_test			tests[] = {
		test_0, test_1, test_2, test_3, test_4, test_5, test_6, test_7, test_8, test_9, test_10, test_11, test_12
	};
	const size_t	tests_nb = ARRAY_SIZE(tests);
	pid_t			pids[tests_nb];
	pid_t			error_streams[tests_nb];

	if (argc > 1) {
		for (int i = 1; i < argc; i++) {
			size_t index = atoi(argv[i]);

			printf("once index %zu\n", index);
			if (index < ARRAY_SIZE(tests)) {
				start_test(&pids[index], &error_streams[index], tests[index]);
			}
		}

		for (int i = 1; i < argc; i++) {
			size_t index = atoi(argv[i]);

			if (index < ARRAY_SIZE(tests)) {
				wait_test(index, &pids[index], &error_streams[index]);
			}
		}
	}
	else {
		for (size_t i = 0; i < tests_nb; i++) {
			start_test(&pids[i], &error_streams[i], tests[i]);
		}

		for (size_t i = 0; i < tests_nb; i++) {
			wait_test(i, &pids[i], &error_streams[i]);
		}
	}
	return EXIT_SUCCESS;
}
