#include "Translator.h"

#include <vector>
#include <sstream>

#include "File.h"

namespace esoterics::brainfuck {

Translator::Translator(std::shared_ptr<TranslationUnit> unit)
: unit(unit) {
}

Translator::~Translator() {
}

Command Translator::DecipherChar(char c) const {
	switch (c) {
	case '>':
		return Command::MOVE_PTR_RIGHT;
	case '<':
		return Command::MOVE_PTR_LEFT;
	case '+':
		return Command::INC_CELL;
	case '-':
		return Command::DEC_CELL;
	case '.':
		return Command::STDOUT_CELL;
	case ',':
		return Command::STDIO_CELL;
	case '[':
		return Command::WHILE_START;
	case ']':
		return Command::WHILE_END;
	default:
		return Command::UNKNOWN;
	}
}

// TODO: add support for files' contents size > 1
int Translator::translate() {
	char c;
	for (int i = 0; i < unit->at(0)->get_contents().size(); i++) {
        c = unit->at(0)->get_contents().at(i);
		if (c == '[')
			L_bracket_history.push_back(i);
		else if (c == ']')
			R_bracket_history.push_back(i);

		executable.push_back(DecipherChar(c));
	}

	if (L_bracket_history.size() != R_bracket_history.size()) {
		status_code = -1;
		status_message = "lbracket & rbracket mismatch\n";
	}

	return status_code;
}

[[maybe_unused]] int Translator::get_err_code() const {
	return status_code;
}

[[maybe_unused]] std::string Translator::get_err_msg() const {
	return status_message;
}

const std::vector<Command> &Translator::get_executable() const {
	return executable;
}

[[maybe_unused]]
const std::vector<size_t>& Translator::get_l_bracket_history() const {
    return L_bracket_history;
}

[[maybe_unused]]
const std::vector<size_t>& Translator::get_r_bracket_history() const {
    return R_bracket_history;
}

[[maybe_unused]]
void Translator::set_r_bracket_history(std::vector<size_t>&& r_history) {
    R_bracket_history = std::move(r_history);
}

[[maybe_unused]]
void Translator::set_l_bracket_history(std::vector<size_t>&& l_history) {
    L_bracket_history = std::move(l_history);
}

[[maybe_unused]]
const std::shared_ptr<TranslationUnit>& Translator::get_unit() const {
    return unit;
}

[[maybe_unused]]
void Translator::set_unit(std::shared_ptr<TranslationUnit> new_unit) {
    unit = std::move(new_unit);
}

}