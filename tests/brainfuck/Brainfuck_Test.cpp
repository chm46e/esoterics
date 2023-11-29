#include <gtest/gtest.h>
#include <memory>
#include "Translator.h"
#include "File.h"

namespace esoterics {
namespace brainfuck {

class TranslatorTest : public ::testing::Test {
protected:
    TranslatorTest() = default;
};


TEST_F(TranslatorTest, TranslatesValidBrainfuckCodeFromFile) {
    std::vector<int> output = {3, 3, 3, 3, 3, 3, 3, 3, 7, 1, 3, 3, 3, 3, 3, 3, 3, 3, 2, 4, 8, 1, 3, 3, 3, 3, 3, 3, 3, 3, 5, 1, 3, 3, 3, 3, 3, 3, 3, 3, 7, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 4, 8, 1, 3, 3, 3, 3, 3, 5, 3, 3, 3, 3, 3, 3, 3, 5, 5, 3, 3, 3, 5, 1, 3, 3, 3, 3, 3, 3, 3, 3, 7, 1, 3, 3, 3, 3, 3, 2, 4, 8, 1, 3, 3, 3, 3, 5, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 5, 1, 1, 5, 3, 3, 3, 5, 4, 4, 4, 4, 4, 4, 5, 4, 4, 4, 4, 4, 4, 4, 4, 5, 1, 1, 3, 5};
    std::vector<Command> expected;
    for (int i : output)
        expected.push_back(static_cast<Command>(i));
    std::shared_ptr<File> file = std::make_shared<File>("./tests/brainfuck/samples/helloworld.bf");
    std::shared_ptr<TranslationUnit> unit = std::make_shared<TranslationUnit>(file);
    Translator translator(unit);

    translator.translate();
    EXPECT_EQ(translator.get_executable(), expected);
}

}
}