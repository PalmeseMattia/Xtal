#include <stdio.h>
#include <stdlib.h>

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

typedef void	(*testcase)();
typedef struct test_register
{
	int		test_count;
	int		register_size;
	testcase	*tests;
} t_testregister;

static t_testregister reg = {.test_count = 0, .register_size = 0, .tests = NULL};

void register_test(testcase test)
{
	if (reg.tests == NULL)
		reg.tests = malloc(sizeof(testcase) * 10);
	else if (reg.test_count >= reg.register_size) {
		realloc(reg.tests, reg.register_size += 10);
	}
	*(reg.tests + reg.test_count++) = test;
}

#define TEST(name) \
	void name(); \
    	__attribute__((constructor)) void register_##name() { register_test(name); } \
    	void name()


void run_tests()
{
	for (int i = 0; i < reg.test_count; i++)
		(*(reg.tests + i))();
}

TEST(str_test_esempio) {
	ASSERT_EQUAL_STR("ciao", "ciao");
}

TEST(num_test_esempio) {
	ASSERT_EQUAL_INT(10, 20);
}

int main()
{
	run_tests();
	return (0);
}

