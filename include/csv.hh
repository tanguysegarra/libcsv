#ifndef CSV_HH
#define CSV_HH

#include <algorithm>
#include <exception>
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

/*
 *  STRING UTILITARIES
 */

using table_t = std::vector<std::pair<std::string, std::vector<std::string>>>;

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

/*
 *  CUSTOM EXCEPTION CLASS (FOR FUN)
 */

class InvalidArgumentException : public std::exception
{
public:
    InvalidArgumentException(const std::string& msg)
    {
        msg_ = msg;
        std::cerr << msg << "\n";
    }

    virtual const char* what() const noexcept
    {
        return msg_.c_str();
    }

private:
    std::string msg_;
};

/*
 *  CSV MODULE SOURCE CODE
 */

namespace csv
{

    /*
     *  CSV READER DEFINITION
     */

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
            rows_.push_back({str::format_csv(col), std::vector<std::string>{}});

        // Get all the values
        while (std::getline(ifs, line))
        {
            std::stringstream ss(line);
            int colIndex = 0;
            std::string val;
            while (getline(ss, val, ','))
            {
                rows_[colIndex].second.push_back(str::format_csv(val));
                colIndex++;
            }
        }

        ifs.close();
    }

    table_t Reader::get_rows() const
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

    /*
     *  CSV WRITER DEFINITION
     */

    class Writer
    {
    public:
        Writer(const std::string& filename);
        Writer(const std::string& filename, const std::string& delimiter);
        void set_rows(table_t& rows);
        void write_rows() const;

    private:
        std::vector<std::pair<std::string, std::vector<std::string>>> rows_;
        std::string filename_;
        std::string delimiter_;
    };

    Writer::Writer(const std::string& filename)
        : filename_(filename),
          delimiter_(",")
    {}

    Writer::Writer(const std::string& filename, const std::string& delimiter)
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
            ofs << rows_.at(i).first;
            if(i != rows_.size() - 1)
                ofs << ",";
        }
        ofs << "\n";

        for (size_t i = 0; i < rows_.at(0).second.size(); i++)
        {
            for (size_t j = 0; j < rows_.size(); j++)
            {
                ofs << rows_.at(j).second.at(i);
                if (j != rows_.size() - 1)
                    ofs << ",";
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

#endif /* !CSV_HH */
