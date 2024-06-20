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

# define GREEN "\x1B[32m"
# define RED "\x1B[31m"
# define NRM "\x1B[0m"
# define CHECK "\u2713"
# define CROSS "\u2715"
# define TEST_PASSED GREEN "Test passed " CHECK NRM
# define SEG_FAULT RED "Test failed due to segmentation fault " CROSS NRM

typedef void (*testcase)();

void register_test(testcase test);
void run_tests();
void assert_equal_int(int expected, int actual);
void assert_equal_str(char *expected, char *actual);
void assert_true(int condition);

#endif
