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
	for (int i = 0; i < test_count; i++)
		(*(tests + i))();
	free(tests);
	tests = NULL;
}

void assert_equal_int(int expected, int actual)
{
	if (expected != actual) {
		fprintf(stderr, "Assertion failed: expected %d, got %d\n", expected, actual); \
		exit(EXIT_FAILURE); \
	} else {
		printf("Test Passed \u2713\n");
	}
}

void assert_equal_str(char *expected, char *actual)
{
	for (int i = 0; *(expected + i) ;i++) {
		if (*(expected + i) != *(actual + i) || !(actual + i)) {
			fprintf(stderr, "Assertion failed: Strings differ at index %d.\nExpected \"%s\", got \"%s\"\n", i, expected, actual);
			exit(EXIT_FAILURE);
		}
	}
	printf("Test Passed \u2713\n");
}

void assert_true(int condition)
{
	if (!condition) {
		fprintf(stderr, "Assertion failed: Condition is false\n");
		exit(EXIT_FAILURE);
	} else {
		printf("Test Passed \u2713\n");
	}
}
