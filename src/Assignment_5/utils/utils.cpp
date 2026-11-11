#include "utils.h"
#include <iomanip>
#include <sstream>
std::vector<std::string> splitLine(const std::string& line)
{
    std::vector<std::string> fields;
    std::string field;
    std::stringstream ss(line);
    while (std::getline(ss, field, '|')) {
        fields.push_back(field);
    }
    return fields;
}

std::string getTodayDateString()
{
    std::time_t t = std::time(nullptr);
    std::tm timeInfo;
#if defined(_MSC_VER)
    localtime_s(&timeInfo, &t);
#else
    localtime_r(&t, &timeInfo);
#endif
    std::stringstream ss;
    ss << std::put_time(&timeInfo, "%Y-%m-%d");
    return ss.str();
}