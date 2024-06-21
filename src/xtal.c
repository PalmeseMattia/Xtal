#include "xtal.h"

static int	test_count = 0;
static int	register_size = 0;
static testcase	*tests = NULL;

void register_test(testcase test)
{
	if (test_count >= (register_size - 1)) {
		tests = realloc(tests, sizeof(testcase) * (register_size += BUFFER_SIZE));
	}
	*(tests + test_count) = test;
	test_count++;
}

void run_tests()
{
	int	pid;
	int	status;

	for (int i = 0; i < test_count; i++) {
		if ((pid = fork()) < 0) {
			perror("Fork failed");
			exit(1);
		}
		if (pid == 0) {
			(*(tests + i))();
			exit(0);
		}
		else {
			printf("Running test %d\n", i + 1);
			waitpid(pid, &status, 0);
			if (WIFSIGNALED(status)) {
				if (WTERMSIG(status) == SIGSEGV)
					PRINT_SEG_FAULT;
				else
					PRINT_FAILED_SIG;
			}
			else if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
				PRINT_PASSED;
			else
				PRINT_FAILED;
		}
	}
	free(tests);
	tests = NULL;
}
