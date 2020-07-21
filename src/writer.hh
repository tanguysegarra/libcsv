#pragma once

#include <string>
#include <utility>
#include <vector>

using table_t = std::vector<std::pair<std::string, std::vector<std::string>>>;

namespace csv
{
    class Writer
    {
    public:
        Writer(const std::string& filename);
        Writer(const std::string& filename, const char& delimiter);
        void set_rows(table_t& rows);
        void write_rows() const;

    private:
        table_t rows_;
        const std::string filename_;
        const char delimiter_;
    };
}

#include "writer.hxx"
