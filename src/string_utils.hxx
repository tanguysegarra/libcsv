#include <algorithm>
#include <regex>
#include <string>
#include <vector>

namespace str
{
    std::string ltrim(const std::string& s)
    {
        return std::regex_replace(s, std::regex("^\\s+"), std::string(""));
    }

    std::string rtrim(const std::string& s)
    {
        return std::regex_replace(s, std::regex("\\s+$"), std::string(""));
    }

    std::string trim(const std::string& s)
    {
        return ltrim(rtrim(s));
    }

    std::string format_csv(std::string& s)
    {
        s = trim(s);
        std::replace(s.begin(), s.end(), ' ', '_');
        return s;
    }
}
