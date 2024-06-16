#include "../xtal.h"

TEST(test_one) {
	ASSERT_EQUAL_STR("bello", "bello");
}

TEST(test_two) {
	ASSERT_EQUAL_INT(10, 10);
}

TEST(test_three) {
	ASSERT_TRUE(10 > 3);
}

//FAIL TEST
TEST(test_four) {
	ASSERT_EQUAL_STR("ciao", "cix");
}

int main() {
	run_tests();
	return 0;
}
