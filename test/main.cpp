#include <gtest/gtest.h>

#include <VM.h>

TEST(TestExClass, TestRetOne) {
    char dummy_bytecodes[] = {0x00};
    EXPECT_EQ(VM(dummy_bytecodes).run(), 0);
}
