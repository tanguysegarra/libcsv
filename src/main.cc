#include "reader.hh"

int main(void)
{
    auto r = csv::Reader("src/test.csv");
    auto colnames = r.get_column_names();
    for (size_t i = 0; i < colnames.size(); i++)
    {
        std::cout << colnames[i];
        if (i != colnames.size() - 1)
            std::cout << " | ";
    }
    std::cout << "\n";

    for (auto& colname : colnames)
    {
        std::cout << colname << ": ";
        for (auto& val : r[colname])
            std::cout << val << ", ";
        std::cout << "\n";
    }

    return 0;
}
