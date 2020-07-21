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
        Writer(const std::string& filename, const std::string& delimiter);
        void set_rows(table_t& rows);
        void write_rows() const;

    private:
        table_t rows_;
        std::string filename_;
        std::string delimiter_;
    };
}

#include "writer.hxx"
