#include <gtest/gtest.h>
#include <string>

#include "File.h"
#include "Error.h"

namespace esoterics {

class FileTest : public ::testing::Test {
protected:
    FileTest() = default;
};

TEST_F(FileTest, ReadsFileCorrectly) {
    File file("./tests/brainfuck/samples/helloworld.bf");
    std::string expected = "++++++++[>++++++++<-]>++++++++.>++++++++[>++++++++++++<-]>+++++.+++++++..+++.>++++++++[>+++++<-]>++++.------------.<<<<+++++++++++++++.>>.+++.------.--------.>>+.";
    EXPECT_EQ(file.get_status(), Status::Ok);
    EXPECT_EQ(file.get_contents(), expected);
}

TEST_F(FileTest, ReturnsErrorForNonExistingFiles) {
    File file("./a_non_existing_file.bf");
    std::string expected;

    EXPECT_EQ(file.get_status(), Status::Err);
    EXPECT_EQ(file.get_contents(), expected);
}

}