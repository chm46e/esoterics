#include "Brainfuck.h"

#include <iostream>

#include "File.h"

namespace esoterics::brainfuck {

BrainfuckRuntime::BrainfuckRuntime(const char *filename)
: filename(filename) {
    File file{filename};
    std::shared_ptr<TranslationUnit> unit = std::make_shared<TranslationUnit>(file);
    translator = std::make_shared<Translator>(unit);
    translator->translate();

    commands = {
            &BrainfuckRuntime::UNKNOWN,
            &BrainfuckRuntime::MOVE_PTR_RIGHT,
            &BrainfuckRuntime::MOVE_PTR_LEFT,
            &BrainfuckRuntime::INC_CELL,
            &BrainfuckRuntime::DEC_CELL,
            &BrainfuckRuntime::STDOUT_CELL,
            &BrainfuckRuntime::STDIO_CELL,
            &BrainfuckRuntime::WHILE_START,
            &BrainfuckRuntime::WHILE_END
    };
}

bool BrainfuckRuntime::run() {
    for (insptr = 0; insptr < translator->get_executable().size(); insptr++) {
        Command cmd = translator->get_executable().at(insptr);
        (this->*commands[static_cast<int>(cmd)])();
    }
    return true;
}

void BrainfuckRuntime::UNKNOWN() {
    // ignore for now
}
void BrainfuckRuntime::MOVE_PTR_RIGHT() {
    memptr++;
}
void BrainfuckRuntime::MOVE_PTR_LEFT() {
    memptr--;
}
void BrainfuckRuntime::INC_CELL() {
    memory.set(memptr, memory[memptr] + 1);
}
void BrainfuckRuntime::DEC_CELL() {
    memory.set(memptr, memory[memptr] - 1);
}
void BrainfuckRuntime::STDOUT_CELL() {
    // TODO: could? result in weird behaviour when (uchar) value > char max.
    char c = (char)memory[memptr];
    std::cout << c;
}
void BrainfuckRuntime::STDIO_CELL() {
    char c;
    std::cin >> c;
    memory.set(memptr, (int)c);
}
void BrainfuckRuntime::WHILE_START() {
    if (memory[memptr] == 0) {
        int i = 0;
        for (; i < translator->get_l_bracket_history().size() && translator->get_l_bracket_history()[i] != insptr; i++) {}
        if (i == translator->get_l_bracket_history().size())
            std::cout << "err. correct lbracket[ not found?\n";

        insptr = translator->get_r_bracket_history().at(i);
    }
}
void BrainfuckRuntime::WHILE_END() {
    if (memory[memptr] != 0) {
        int i = 0;
        for (; i < translator->get_r_bracket_history().size() && translator->get_r_bracket_history()[i] != insptr; i++) {}
        if (i == translator->get_r_bracket_history().size())
            std::cout << "err. correct rbracket] not found?\n";

        insptr = translator->get_l_bracket_history().at(i);
    }
}

}