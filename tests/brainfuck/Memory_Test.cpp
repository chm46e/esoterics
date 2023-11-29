#include <gtest/gtest.h>
#include "Memory.h"

namespace esoterics::brainfuck {

class MemoryTest : public ::testing::Test {
protected:
    Memory memory;

    MemoryTest() = default;
};

TEST_F(MemoryTest, ReturnsNormalVerifyPosCorrectly) {
    EXPECT_EQ(memory.verify_pos(25), 25);
}
TEST_F(MemoryTest, ReturnsNegativeVerifyPosCorrectly) {
    EXPECT_EQ(memory.verify_pos(-130), MAXCELLS - 130);
}
TEST_F(MemoryTest, ReturnsPosOverflowVerifyPosCorrectly) {
    EXPECT_EQ(memory.verify_pos(52000), 52000 - MAXCELLS);
}
TEST_F(MemoryTest, ReturnsNegOverflowVerifyPosCorrectly) {
    EXPECT_EQ(memory.verify_pos(-62000), MAXCELLS - 2000);
}

TEST_F(MemoryTest, MemoryModificationWorks) {
    memory.set(250, 10);
    EXPECT_EQ(memory.at(250), 10);
}

}