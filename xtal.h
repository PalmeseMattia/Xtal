#ifndef XTAL_H
# define XTAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void (*testcase)();
typedef struct test_register
{
	int		test_count;
	int		register_size;
	testcase	*tests;
} t_testregister;

void register_test(testcase test);
void run_tests();

#define TEST(name) \
    void name(); \
    __attribute__((constructor)) void register_##name() { register_test(name); } \
    void name()

#define ASSERT_EQUAL_INT(expected, actual) \
	if (expected != actual) { \
		fprintf(stderr, "Assertion failed: expected %d, got %d\n", expected, actual); \
		exit(EXIT_FAILURE); \
	} else { \
		printf("Test Passed \u2713\n"); \
	}

#define ASSERT_EQUAL_STR(expected, actual) \
	for (int i = 0; *(actual + i) ;i++) { \
		if (*(expected + i) != *(actual + i)) { \
			fprintf(stderr, "Assertion failed: Strings differ at index %d.\nExpected \"%s\", got \"%s\"\n", i, expected, actual); \
			exit(EXIT_FAILURE); \
		} \
	} \
	printf("Test Passed \u2713\n"); \

#define ASSERT_TRUE(condition) \
	if (!condition) { \
		fprintf(stderr, "Assertion failed: Condition is false\n"); \
		exit(EXIT_FAILURE); \
	} else { \
		printf("Test Passed \u2713\n"); \
	}

#endif
