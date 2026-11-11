#pragma once
#include <fstream>
#include <string>
#include <vector>

std::vector<std::string> splitLine(const std::string& line);

std::string getTodayDateString();

template <typename T, typename ParseFunc>
bool loadData(const std::string& filename, std::vector<T>& collection, ParseFunc parseFunc)
{
    std::ifstream file(filename);

    if (!file.is_open()) {
        return false;
    }
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty())
            continue;

        std::vector<std::string> fields = splitLine(line);

        if (auto item = parseFunc(fields)) {
            collection.push_back(*item);
        }
    }
    return true;
}

template <typename T, typename ToCsvFunc>
bool saveData(const std::string& filename, const std::vector<T>& collection, ToCsvFunc toCsvFunc)
{
    std::ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    for (const auto& item : collection) {
        file << toCsvFunc(item) << "\n";
    }

    return true;
}