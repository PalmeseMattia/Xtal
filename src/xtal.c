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
