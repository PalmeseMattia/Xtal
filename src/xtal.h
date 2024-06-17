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
void assert_equal_int(int expected, int actual);
void assert_equal_str(char *expected, char *actual);
void assert_true(int condition);

#define TEST(name) \
    void name(); \
    __attribute__((constructor)) void register_##name() { register_test(name); } \
    void name()


#endif
