---
marp: true
paginate: false
backgroundImage: linear-gradient(135deg, white, white 50%, lightblue)
style: 'section{padding-left: 110px}'
---
<!-- 
This presentation is written in markdown, and should be formatted using marp
-->

# Unit Testing with GTEST

![width:400px](Ocient_logo_1333x304.png)

---
<!-- These settings take effect for the remainder of the slides -->
<!-- header: '![](Ocient_symbol_75x75.png)' -->
<!-- paginate: true -->
---

# Why tests?

- Allow rapid evolution of software
  - Bug fixes
  - Optimizations
  - New function

- Confidently make changes without knowing all the code
  - Not break existing behavior

---

# <!-- fit --> Run manually or through Continuous Integration (CI)

- ```make test``` in your container
- can run individual unit tests
- CI runs on Gitlab for every pull request
- A larger set of tests run nightly
  [https://gitlab.com/ocient/xgsrc/pipelines](https://gitlab.com/ocient/xgsrc/pipelines)

---

# Small Tests not Large Tests

- Large Tests
  - A.K.A. sytem/intgegration/end-to-end tests
  - Hard to localize errors
  - Run slowly
  - Resources not available before every Pull Request
- Small Tests
  - A.K.A unit tests
  - Test module / class / function in isolation
  - Run quickly
  - Run whole suite before Pull Request

---

# Google Test

- Framework for writing unit tests
- Allows you to declare expected results

```c++
TEST(MyTestcase, test_add) {
    int a=1;
    int b=2;
    EXPECT_EQ(a+b, 3);
}

TEST(MyTestcase, test_sub) {
    int a=1;
    int b=2;
    EXPECT_EQ(a-b, -1);
}
```

[https://github.com/Xeograph/xgsrc/blob/db/libxg/src/data/test/test_hashing.cpp](https://github.com/Xeograph/xgsrc/blob/db/libxg/src/data/test/test_hashing.cpp)

--- 

Google Test
- Runtime output

```plain
[==========] Running 2 tests from 1 test case.
[----------] Global test environment set-up.
[----------] 2 tests from MyTestcase
[ RUN      ] MyTestcase.test_add
[       OK ] MyTestcase.test_add (1 ms)
[ RUN      ] MyTestcase.test_sub
[       OK ] My Testcase.test_sub (1 ms)
[----------] 2 tests from MyTestcase (2 ms total)
[----------] Global test environment tear-down
[==========] 2 tests from 1 test case ran. (2 ms total)
[  PASSED  ] 2 tests.
```

---

# Expecting results

- EXPECT_TRUE(condition)
- EXPECT_FALSE(condition)
- EXPECT_EQ(a, b)
- EXPECT_NE(a, b)
- EXPECT_LE/LT/GT/GE(a, b)

- EXPECT_STREQ/STRNE(a, b)
- EXPECT_STRCASEEQ/STRCASENE(a, b)

- EXPECT_DOUBLE_EQ(a, b)

---

# Failure Diagnostics
```plain
[==========] Running 2 tests from 1 test case.
[----------] Global test environment set-up.
[----------] 2 tests from MyTestcase
[ RUN      ] MyTestcase.test_add
Mytest.cpp:44: Failure
      Expected: a+b
      Which is: 3
To be equal to: 5
      Which is: 5
[  FAILED  ] MyTestcase.test_add (1 ms)
[ RUN      ] MyTestcase.test_sub
[       OK ] My Testcase.test_sub (1 ms)
[----------] 2 tests from MyTestcase (2 ms total)
[----------] Global test environment tear-down
[==========] 2 tests from 1 test case ran. (2 ms total)
[  PASSED  ] 1 tests.
[  FAILED  ] 1 test, listed below:
[  FAILED  ] MyTestcase.test_add
 1 FAILED TEST
```

---

# Writing Good Testcases
- Prefer EXPECT_EQ(a, b) to EXPECT_TRUE(a == b)
  - In an error case displays more useful information

- You can output additional information using <<

```c++
TEST(MyTestcase, test_add) {
    for (i=0; i<100; i++) {
        EXPECT_TRUE(myFunc()) << "loop iteration " << I;
    }
}
```

---


# Asserting results – stops testcase if fails
- ASSERT_TRUE(condition)
- ASSERT_FALSE(condition)
- ASSERT_EQ(a, b)
- ASSERT_NE(a, b)
- ASSERT_LE/LT/GT/GE(a, b)
- ASSERT_STREQ/STRNE(a, b)
- ASSERT_STRCASEEQ/STRCASENE(a, b)
- ASSERT_DOUBLE_EQ(a, b)

---

# ASSERT vs EXPECT

```c++
TEST(MyTestcase, test_first) {

    Thing *thing = allocate_a_thing();

    ASSERT_NE(thing, nullptr);

    EXPECT_EQ(thing->magic, 0xDEADBEEF);

}
```

---

# Test Fixtures – setup and teardown

```c++
class MyTestcase : public ::testing::Test{
    MyTestcase() : data(new int[100]) {}
    ~MyTestcase() { delete[] data; }
}
TEST_F(MyTestcase, test_first) {
    EXPECT_EQ(data[0], 0);
}
TEST_F(MyTestcase, test_second) {
    EXPECT_EQ(data[1], 0);
}
```

---

# Test Program parameters
test_program --help
test Selection:

  ```--gtest_list_tests```
  List the names of all tests instead of running them. The name of  TEST(Foo, Bar) is "Foo.Bar".

  ```--gtest_filter=POSTIVE_PATTERNS[-NEGATIVE_PATTERNS]```
  Run only the tests whose name matches one of the positive patterns but none of the negative patterns. '?' matches any single character; '*’            matches any substring; ':' separates two patterns.

  ```--gtest_also_run_disabled_tests```
  Run all disabled tests too.

```test_program --gtest_filter=MyTestcase.*```

---

# GTEST at Ocient

- Any file named “test*.cpp” in the src directory of a library will be built and included in the test program
- Each library (e.g. libxgnvme) builds a program called libxgnvme_test which includes all the test files in that library
- You can also build individual test files
```make test_foo```

---

# GTEST at Ocient	

Occasionally we add special methods to classes to enable testing

Normally name these very explicitly:

    ```__test__do_something_clever();```

Don’t ever do things like:
 ```#define private public```

(I’ve seen that done……………)

---

# Google Mocks (GMOCK)

Framework for mocking classes and methods

```c++
class MyClass : MyBase Class {
public:
    MOCK_METHOD2(generate, double(double, double));
}
```

```c++
EXPECT_CALL(thing, generate(DoubleEq(0.0), DoubleEq(1.0))
    .Times(Exactly(1))
    .WillOnce(Return(0.25));
```

---

# Google Mocks

Much more complicated that GTEST

Much more powerful…we don’t use them a lot (maybe we should.)