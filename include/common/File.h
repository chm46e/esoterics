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
    explicit File(std::string &&new_contents);
	~File() = default;

    // do not allow File object memory duplication
    File(const File &other) = delete;
    File &operator=(const File &other) = delete;

	[[nodiscard]]
    const char *name() const;
    [[maybe_unused]] [[nodiscard]]
    Status get_status() const;

    [[maybe_unused]] [[nodiscard]]
    const std::string &get_contents() const;

private:
	template <typename T>
	T read_contents();

	const char *filename;
	Status status_code = Status::Ok;
	std::string contents;
};

class TranslationUnit {
public:
    TranslationUnit() = default;
    template <typename ...Args>
    explicit TranslationUnit(Args... args);
    explicit TranslationUnit(std::shared_ptr<File> file);
    ~TranslationUnit() = default;

    template <typename ...Args>
    void add(Args... filelist);

    [[nodiscard]]
    const std::vector<std::shared_ptr<File>>& get() const;

    std::shared_ptr<File> operator[](std::size_t idx);
    std::shared_ptr<File> at(std::size_t idx);

private:
    std::vector<std::shared_ptr<File>> files;
};

}