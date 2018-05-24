#include <gtest/gtest.h>

#include <ExampleClass.h>

TEST(TestExClass, TestRetOne) {
    EXPECT_EQ(ExampleClass::returnOne(), 1);
}
