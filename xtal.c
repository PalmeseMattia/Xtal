#include "xtal.h"

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

void run_tests()
{
	for (int i = 0; i < reg.test_count; i++)
		(*(reg.tests + i))();
}


