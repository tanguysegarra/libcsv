#include <fstream>
#include <sstream>

#include "invalid-argument-exception.hh"

namespace csv
{
    Writer::Writer(const std::string& filename)
        : filename_(filename),
          delimiter_(',')
    {}

    Writer::Writer(const std::string& filename, const char& delimiter)
        : filename_(filename),
          delimiter_(delimiter)
    {}

    void Writer::write_rows() const
    {
        std::ofstream ofs(filename_);
        if (!ofs.is_open())
            throw InvalidArgumentException("Could not open file: " + filename_);

        for (size_t i = 0; i < rows_.size(); i++)
        {
            ofs << rows_[i].first;
            if(i != rows_.size() - 1)
                ofs << delimiter_;
        }
        ofs << "\n";

        for (size_t i = 0; i < rows_[0].second.size(); i++)
        {
            for (size_t j = 0; j < rows_.size(); j++)
            {
                ofs << rows_[j].second[i];
                if (j != rows_.size() - 1)
                    ofs << delimiter_;
            }
            ofs << "\n";
        }

        ofs.close();
    }

    void Writer::set_rows(table_t& rows)
    {
        rows_ = rows;
    }
}
