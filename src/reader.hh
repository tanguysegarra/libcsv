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
        std::vector<std::pair<std::string, std::vector<std::string>>> rows();
        void display();

    private:
        void read_rows();
        std::vector<std::pair<std::string, std::vector<std::string>>> rows_;
        std::string filename_;
        std::string delimiter_;
    };
}

#include "reader.hxx"
