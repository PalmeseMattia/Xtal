#include "../src/xtal.h"

TEST(test_one) {
	assert_equal_str("bello", "bello");
}

TEST(test_two) {
	assert_equal_int(10, 10);
}

TEST(test_three) {
	assert_true(10 > 3);
}

//THIS TEST WILL FAIL
TEST(test_four) {
	assert_equal_str("Hello", "Hell");
}

int main() {
	run_tests();
	return 0;
}
