#ifndef XTAL_H
# define XTAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

# define BUFFER_SIZE 10
# define TEST(name) \
    void name(); \
    __attribute__((constructor)) void register_##name() { register_test(name); } \
    void name()

typedef void (*testcase)();
void register_test(testcase test);
void run_tests();

/*
 * ASSERTIONS
 */
# define ASSERT_EQUAL_INT(expected, actual) \
	if (expected != actual) { \
		fprintf(stderr, "Assertion failed: expected %d, got %d\n", expected, actual); \
		exit(EXIT_FAILURE); \
	}

# define ASSERT_EQUAL_STR(expected, actual) \
	for (int i = 0; expected[i] ;i++) { \
		if (expected[i] != actual[i] || !actual[i]) { \
			fprintf(stderr, "Assertion failed: Strings differ at index %d.\nExpected \"%s\", got \"%s\"\n", i, expected, actual); \
			exit(EXIT_FAILURE); \
		} \
	} \

# define ASSERT_TRUE(condition) \
	if (!condition) { \
		fprintf(stderr, "Assertion failed: Condition is false\n"); \
		exit(EXIT_FAILURE); \
	}

/*
 * PRINT UTILITIES 
 */
# define GREEN "\x1B[32m"
# define RED "\x1B[31m"
# define NRM "\x1B[0m"
# define CHECK "\u2713"
# define CROSS "\u2715"
# define PRINT_PASSED printf("%sTest passed %s%s\n\n", GREEN, CHECK, NRM)
# define PRINT_FAILED_SIG printf("%sTest failed with signal %d and status %d %s%s\n\n", RED, WTERMSIG(status), WEXITSTATUS(status), CROSS, NRM)
# define PRINT_SEG_FAULT printf("%sTest failed due to segmentation fault %s%s\n\n", RED, CROSS, NRM)
# define PRINT_FAILED printf("%sTest failed with status %d %s%s\n\n", RED, WEXITSTATUS(status), CROSS, NRM)

#endif
