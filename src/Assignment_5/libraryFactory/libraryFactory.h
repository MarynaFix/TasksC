#pragma once
#include "library\library.h"
#include <optional>
#include <string>

class LibraryFactory {
public:
    static std::optional<Library> createLibrary(const std::string& directoryPath);
};