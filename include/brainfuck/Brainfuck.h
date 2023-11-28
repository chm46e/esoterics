#pragma once

#include <sstream>
#include <iostream>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "File.h"
#include "Memory.h"
#include "Translator.h"

namespace esoterics::brainfuck {

class BrainfuckRuntime {
public:
    explicit BrainfuckRuntime(const char *filename);
    ~BrainfuckRuntime() = default;

    bool run();

private:
    void UNKNOWN();
    void MOVE_PTR_RIGHT();
    void MOVE_PTR_LEFT();
    void INC_CELL();
    void DEC_CELL();
    void STDOUT_CELL();
    void STDIO_CELL();
    void WHILE_START();
    void WHILE_END();

    const char *filename;

    CellPos memptr = 0;
    size_t insptr = 0;

    std::shared_ptr<Translator> translator;

    class Memory memory;
	typedef void (BrainfuckRuntime::*BrainfuckCommand)();
	std::array<BrainfuckCommand, 9> commands;
};

}