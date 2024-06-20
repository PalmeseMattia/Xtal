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
void assert_equal_int(int expected, int actual);
void assert_equal_str(char *expected, char *actual);
void assert_true(int condition);

#endif
