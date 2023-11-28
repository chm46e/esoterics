#pragma once

#include <string>
#include <sstream>
#include <memory>
#include <vector>

#include "Error.h"

namespace esoterics {

class File {
public:
	explicit File(const char *filename);
	~File() = default;

	[[nodiscard]]
    const char *name() const;
    [[maybe_unused]] [[nodiscard]]
    Status get_status() const;

    [[maybe_unused]] [[nodiscard]]
    const std::shared_ptr<std::string>& get_contents() const;

private:
	template <typename T>
	T read_contents();

	const char *filename;
	Status status_code = Status::Ok;
	std::shared_ptr<std::string> contents;
};

class TranslationUnit {
public:
    TranslationUnit() = default;
    template <typename ...Args>
    explicit TranslationUnit(Args... args);
    ~TranslationUnit() = default;

    template <typename ...Args>
    void add(Args... filelist);

    [[nodiscard]]
    const std::vector<File>& get() const;

    File &operator[](std::size_t idx);
    File &at(std::size_t idx);

private:
    std::vector<File> files;
};

}