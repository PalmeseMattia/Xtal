#include "xtal.h"

static t_testregister reg = {.test_count = 0, .register_size = 0, .tests = NULL};

void register_test(testcase test)
{
	if (reg.test_count >= (reg.register_size - 1)) {
		reg.tests = realloc(reg.tests, sizeof(testcase) * (reg.register_size += 10));
	}
	*(reg.tests + reg.test_count) = test;
	reg.test_count++;
}

void run_tests()
{
	for (int i = 0; i < reg.test_count; i++)
		(*(reg.tests + i))();
	free(reg.tests);
	reg.tests = NULL;
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
