#include "File.h"

#include <fstream>
#include <memory>

#include "Error.h"

namespace esoterics {

const char* File::name() const {
    return filename;
}

[[maybe_unused]]
Status File::get_status() const {
    return status_code;
}

[[maybe_unused]]
const std::string& File::get_contents() const {
    return contents;
}

template<typename T>
T File::read_contents() {
    return read_contents<Status>();
}

template<>
Status File::read_contents<Status>() {
    std::fstream file;
    std::stringstream internals;
    file.open(filename, std::ios::in);

    if (!file.is_open()) {
        status_code = Status::Err;
        return status_code;
    }

    internals << file.rdbuf();
    // copy internals, keep the std::string
    contents = internals.str();
    file.close();
    return status_code;
}

template<>
const std::string &File::read_contents<const std::string &>() {
    std::fstream file;
    std::stringstream internals;
    file.open(filename, std::ios::in);

    if (!file.is_open()) {
        status_code = Status::Err;
        return nullptr;
    }

    internals << file.rdbuf();
    // copy internals, keep the std::string
    contents = internals.str();
    file.close();
    return contents;
}

File::File(const char* filename)
        :filename(filename) {
    status_code = read_contents<Status>();
}

File::File(std::string&& new_contents)
: contents(std::move(new_contents)), filename(nullptr) {
    status_code = Status::Ok;
}

template<typename... Args>
TranslationUnit::TranslationUnit(Args... args) {
    add(args...);
}

template<typename... Args>
void TranslationUnit::add(Args... filelist) {
    (files.push_back(filelist), ...);
}

const std::vector<std::shared_ptr<File>>& TranslationUnit::get() const {
    return files;
}

std::shared_ptr<File> TranslationUnit::operator[](std::size_t idx) {
    return files[idx];
}

std::shared_ptr<File> TranslationUnit::at(std::size_t idx) {
    if (idx >= files.size())
        throw std::out_of_range("Index out of range");
    return files[idx];
}

TranslationUnit::TranslationUnit(std::shared_ptr<File> file) {
    files.push_back(file);
}

}