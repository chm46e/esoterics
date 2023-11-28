#include "Memory.h"

#include <memory>
#include <array>

namespace esoterics::brainfuck {

/* Constrain position argument to memory space
 * int, as it's required to wrap around both ways
 */
CellPos Memory::verify_pos(CellPos position) const {
	if (position >= 0) {
		while (position >= MAXCELLS)
			position -= MAXCELLS;
	} else {
		while (position < 0)
			position += MAXCELLS;
	}
	return position;
}

Cell Memory::at(CellPos position) const {
	return memory.at(verify_pos(position));
}

Cell Memory::operator[](CellPos position) const {
	return memory.at(position);
}

void Memory::set(CellPos position, Cell value) {
	memory.at(verify_pos(position)) = value;
}

void Memory::increment(CellPos position) {
	memory.at(verify_pos(position))++;
}

void Memory::decrement(CellPos position) {
	memory.at(verify_pos(position))--;
}

std::shared_ptr<std::array<Cell, MAXCELLS>> Memory::get_raw_memory() {
	return std::make_shared<std::array<Cell, MAXCELLS>>(memory);
}

Cell *Memory::get_raw_ptr(CellPos position) {
	return &memory.at(verify_pos(position));
}

template <typename T>
T Memory::previous(CellPos current) const {
	return previous<CellPos>(current);
}
template <>
CellPos Memory::previous<CellPos>(CellPos current) const {
	return verify_pos(current - 1);
}
template <>
Cell Memory::previous<Cell>(CellPos current) const {
	return at(current - 1);
}

template<typename T>
T Memory::next(CellPos current) const {
	return next<CellPos>(current);
}
template <>
CellPos Memory::next<CellPos>(CellPos current) const {
	return verify_pos(current + 1);
}
template <>
Cell Memory::next<Cell>(CellPos current) const {
	return at(current + 1);
}
}