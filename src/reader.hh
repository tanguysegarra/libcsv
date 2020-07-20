#pragma once

#include <string>
#include <utility>
#include <vector>

namespace csv
{
    class Reader
    {
    public:
        Reader(const std::string& filename);
        Reader(const std::string& filename, const std::string& delimiter);
        std::vector<std::pair<std::string, std::vector<std::string>>> get_rows() const;
        std::vector<std::string> operator[](const std::string& id) const;
        std::vector<std::string> get_column_names() const;

    private:
        void read_rows();
        size_t find_column_id(const std::string& id) const;
        std::vector<std::pair<std::string, std::vector<std::string>>> rows_;
        std::string filename_;
        std::string delimiter_;
    };
}

#include "reader.hxx"
