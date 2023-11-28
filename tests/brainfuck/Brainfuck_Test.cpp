#include <gtest/gtest.h>
#include "Brainfuck.h"

namespace brainfuck {
namespace interpreter {

class BrainfuckInterpreterTest : public ::testing::Test {
protected:
    BrainfuckInterpreter interpreter;
    BrainfuckInterpreterTest() : interpreter("./test.bf") {}
    // void SetUp() override...
    // void TearDown() override...
};

}
}