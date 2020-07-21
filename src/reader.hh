#pragma once

#include <string>
#include <utility>
#include <vector>

using table_t = std::vector<std::pair<std::string, std::vector<std::string>>>;

namespace csv
{
    class Reader
    {
    public:
        Reader(const std::string& filename);
        Reader(const std::string& filename, const std::string& delimiter);
        table_t get_rows() const;
        std::vector<std::string> operator[](const std::string& id) const;
        std::vector<std::string> get_column_names() const;

    private:
        void read_rows();
        size_t find_column_id(const std::string& id) const;
        table_t rows_;
        std::string filename_;
        std::string delimiter_;
    };
}

#include "reader.hxx"
