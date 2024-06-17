mi# Xtal

A single file C unit test tool (a lot of words...).
Create your own library or just compile your test file with xtal.c.
I know, unity is quite good, but with xtal you don't need to explicitly run every test.
Take a look at the examples.

### Syntax:
```c
#include "xtal.h"

TEST(test_name) {
    //Your code
    assert_somethinh(args...);
}

int main() {
    run_tests();
}
```

### Basic Usage:
![Alt text](resources/result.png)

### Make a library
![Alt text](resources/lib.png)
