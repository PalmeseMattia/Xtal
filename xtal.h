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
    __attribute__((constructor)) void register_##name() { register_test(#name, name); } \
    void name()

/*
 * PRINT UTILITIES 
 */
# define GREEN "\x1B[32m"
# define RED "\x1B[31m"
# define YELLOW "\x1B[033m"
# define BLUE "\e[0;94m"
# define RESET "\x1B[0m"
# define CHECK "\u2713"
# define CROSS "\u2715"
# define PRINT_PASSED printf("%sTest passed %s%s\n\n", GREEN, CHECK, RESET)
# define PRINT_FAILED_SIG printf("%sTest failed with signal %d and status %d %s%s\n\n", RED, WTERMSIG(status), WEXITSTATUS(status), CROSS, RESET)
# define PRINT_SEG_FAULT printf("%sTest failed due to segmentation fault %s%s\n\n", RED, CROSS, RESET)
# define PRINT_FAILED printf("%sTest failed with status %d %s%s\n\n", RED, WEXITSTATUS(status), CROSS, RESET)
# define PRINT_LINE printf("__________________________\n");


typedef void (*testcase)();

typedef struct {
    const char *name;
    testcase function;
} test_t;

static int test_count = 0;
static int register_size = 0;
static int test_passed = 0;
static int test_failed = 0;
static test_t *tests = NULL;

void register_test(const char *name, testcase function)
{
    if (test_count >= (register_size - 1)) {
        tests = (test_t *)realloc(tests, sizeof(test_t) * (register_size += BUFFER_SIZE));
    }
    tests[test_count].name = name;
    tests[test_count].function = function;
    test_count++;
}

void run_tests()
{
    int pid;
    int status;

    for (int i = 0; i < test_count; i++) {
        if ((pid = fork()) < 0) {
            perror("Fork failed");
            exit(1);
        }
        if (pid == 0) {
            tests[i].function();
            exit(0);
        }
        else {
			printf(BLUE "=== TEST %d: %s ===%s\n" , i + 1, tests[i].name, RESET);
            waitpid(pid, &status, 0);
            if (WIFSIGNALED(status)) {
                if (WTERMSIG(status) == SIGSEGV)
                    PRINT_SEG_FAULT;
                else
                    PRINT_FAILED_SIG;
				test_failed++;
            }
            else if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
                PRINT_PASSED;
				test_passed++;
			}
            else {
                PRINT_FAILED;
				test_failed++;
			}
        }
    }
	printf("\n=== Test Summary ===\n");
	printf(GREEN "Passed: %d\n" RESET, test_passed);
	printf(RED "Failed: %d\n" RESET, test_failed);
    free(tests);
    tests = NULL;
}

/*
 * ASSERTIONS
 */
# define ASSERT_EQUAL_INT(expected, actual) \
    if (expected != actual) { \
        fprintf(stderr, "Assertion failed: expected %d, got %d\n", expected, actual); \
        exit(EXIT_FAILURE); \
    }

# define ASSERT_EQUAL_STR(expected, actual) \
    for (int i = 0; expected[i]; i++) { \
        if (expected[i] != actual[i] || !actual[i]) { \
            fprintf(stderr, "Assertion failed: Strings differ at index %d.\nExpected \"%s\", got \"%s\"\n", i, expected, actual); \
            exit(EXIT_FAILURE); \
        } \
    }

# define ASSERT_TRUE(condition) \
    if (!condition) { \
        fprintf(stderr, "Assertion failed: Condition is false\n"); \
        exit(EXIT_FAILURE); \
    }

# define ASSERT_FALSE(condition) \
    if (condition) { \
        fprintf(stderr, "Assertion failed: Condition is true\n"); \
        exit(EXIT_FAILURE); \
    }

# define ASSERT_NOT_NULL(stuff) \
    if (stuff == NULL) { \
        fprintf(stderr, "Assertion failed: Memory points to null\n"); \
        exit(EXIT_FAILURE); \
    }

# define ASSERT_NULL(stuff) \
    if (stuff != NULL) { \
        fprintf(stderr, "Assertion failed: Memory do not points to null\n"); \
        exit(EXIT_FAILURE); \
    }

#endif
