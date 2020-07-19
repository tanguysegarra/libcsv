#include <fstream>
#include <sstream>

#include "invalid-argument-exception.hh"

namespace csv
{
    Reader::Reader(const std::string& filename)
        : filename_(filename),
          delimiter_(",")
    {
        read_rows();
    }

    Reader::Reader(const std::string& filename, const std::string& delimiter)
        : filename_(filename),
          delimiter_(delimiter)
    {
        read_rows();
    }

    void Reader::read_rows()
    {
        std::ifstream ifs(filename_);
        if (!ifs.is_open())
            throw InvalidArgumentException("Could not load file: " + filename_);

        std::string col;
        std::string line;
        std::getline(ifs, line);
        std::stringstream ss(line);

        // Get columns names from the first line
        while (std::getline(ss, col, ','))
            rows_.push_back({col, std::vector<std::string>{}});

        // Get all the values
        while (std::getline(ifs, line))
        {
            std::stringstream ss(line);
            int colIndex = 0;
            std::string val;
            while (getline(ss, val, ','))
            {
                rows_.at(colIndex).second.push_back(val);
                colIndex++;
            }
        }

        ifs.close();
    }


    std::vector<std::pair<std::string, std::vector<std::string>>> Reader::rows()
    {
        return rows_;
    }

    void Reader::display()
    {
        for (size_t i = 0; i < rows_.size(); i++)
        {
            std::cout << rows_.at(i).first;
            if (i != rows_.size() - 1)
                std::cout << ",";
        }
        std::cout << "\n";

        for (size_t i = 0; i < rows_.at(0).second.size(); i++)
        {
            for (size_t j = 0; j < rows_.size(); j++)
            {
                std::cout << rows_.at(j).second.at(i);
                if (j != rows_.size() - 1)
                    std::cout << ",";
            }
            std::cout << "\n";
        }
    }
}
