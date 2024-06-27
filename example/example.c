#include "../xtal.h"

TEST(test_one) {
	ASSERT_EQUAL_STR("bello", "bello");
}

TEST(test_two) {
	ASSERT_EQUAL_INT(10, 15);
}

TEST(test_three) {
	int *p = NULL;
	*p = 42;
	ASSERT_EQUAL_INT(42, *p);
}

int main() {
	run_tests();
	return 0;
}
