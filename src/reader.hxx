#include <algorithm>
#include <fstream>
#include <sstream>

#include "invalid-argument-exception.hh"
#include "string_utils.hh"

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
            rows_.push_back({format_csv(col), std::vector<std::string>{}});

        // Get all the values
        while (std::getline(ifs, line))
        {
            std::stringstream ss(line);
            int colIndex = 0;
            std::string val;
            while (getline(ss, val, ','))
            {
                rows_[colIndex].second.push_back(format_csv(val));
                colIndex++;
            }
        }

        ifs.close();
    }

    std::vector<std::pair<std::string, std::vector<std::string>>> Reader::get_rows() const
    {
        return rows_;
    }

    std::vector<std::string> Reader::get_column_names() const
    {
        auto colnames = std::vector<std::string>{};
        for (size_t i = 0; i < rows_.size(); i++)
            colnames.push_back(rows_[i].first);

        return colnames;
    }

    size_t Reader::find_column_id(const std::string& id) const
    {
        for (size_t i = 0; i < rows_.size(); i++)
            if (rows_[i].first == id)
                return i;

        throw InvalidArgumentException("Could not find column: " + id);
    }

    std::vector<std::string> Reader::operator[](const std::string& id) const
    {
        auto index = find_column_id(id);
        return rows_[index].second;
    }
}
