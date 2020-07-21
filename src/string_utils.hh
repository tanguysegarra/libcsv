#pragma once

#include <string>

namespace str
{
    std::string ltrim(const std::string& s);
    std::string rtrim(const std::string& s);
    std::string trim(const std::string& s);
    std::string format_csv(std::string& s);
}

#include "string_utils.hxx"
