#pragma once

#include <vector>
#include <cstdint>
#include <sstream>
#include <array>

#include "File.h"

namespace esoterics::brainfuck {

enum class Command {
    UNKNOWN,
    MOVE_PTR_RIGHT,
    MOVE_PTR_LEFT,
    INC_CELL,
    DEC_CELL,
    STDOUT_CELL,
    STDIO_CELL,
    WHILE_START,
    WHILE_END
};

/* Translator should work only on the given brainfuck code buffer.
 * It shouldn't manage runtime (ex: memory logic)
 * Input: files' contents
 * Output: vector of command types
 */
class Translator {
public:
	explicit Translator(std::shared_ptr<TranslationUnit> unit);
    Translator() = default;
	~Translator();

	int translate();

    [[maybe_unused]] [[nodiscard]]
    const std::shared_ptr<TranslationUnit> &get_unit() const;
    [[maybe_unused]]
    void set_unit(std::shared_ptr<TranslationUnit> new_unit);

    [[maybe_unused]] [[nodiscard]]
    int get_err_code() const;
    [[maybe_unused]] [[nodiscard]]
    std::string get_err_msg() const;

	[[nodiscard]]
    const std::vector<Command> &get_executable() const;

    [[maybe_unused]] [[nodiscard]]
    const std::vector<size_t> &get_l_bracket_history() const;
    [[maybe_unused]]
    void set_l_bracket_history(std::vector<size_t>&& l_history);

    [[maybe_unused]] [[nodiscard]]
    const std::vector<size_t> &get_r_bracket_history() const;
    [[maybe_unused]]
    void set_r_bracket_history(std::vector<size_t>&& r_history);

private:
	[[nodiscard]]
    Command DecipherChar(char c) const;

	std::vector<Command> executable;

    std::shared_ptr<TranslationUnit> unit;

	std::vector<size_t> L_bracket_history = {0};
	std::vector<size_t> R_bracket_history = {0};

	int status_code = 0;
	std::string status_message;
};

}