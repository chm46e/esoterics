#pragma once

#include <cstdint>
#include <memory>
#include <array>

namespace esoterics::brainfuck {

typedef int16_t CellPos;
typedef uint8_t Cell;

// bounded, to allow overwrap
#define MAXCELLS 30000

/* Program memory allocator and manager
 * 8-bit cell-based (position is 16bit)
 */
class Memory {
public:
	Memory() = default;
	~Memory() = default;

	[[nodiscard]] CellPos verify_pos(CellPos position) const;
	[[nodiscard]] Cell at(CellPos position) const;
	Cell operator[](CellPos position) const;

	template <typename T>
	T next(CellPos current) const;
	template <typename T>
	T previous(CellPos current) const;

	/* TODO: operator functions: = -- ++
	 * requires last_accessed_pos (could be unsafe implementation)
	 */
	void set(CellPos position, Cell value);
	void increment(CellPos position);
	void decrement(CellPos position);

	[[maybe_unused]]
	std::shared_ptr<std::array<Cell, MAXCELLS>> get_raw_memory();
	[[maybe_unused]]
	Cell *get_raw_ptr(CellPos position);

private:
	std::array<Cell, MAXCELLS> memory = {0};
};

}