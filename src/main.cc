//#include "csv.hh"
#include "reader.hh"
#include "writer.hh"

int main(void)
{
    /* TESTING READER CLASS */ 
    auto r = csv::Reader("tests/test.csv", ';');
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

    for (auto& val : r["NAME"])
        std::cout << val << ", ";

    std::cout << "\n";

    /* TESTING WRITER CLASS */ 

    auto data = r.get_rows();

    auto w = csv::Writer("output.csv", ';');
    w.set_rows(data);
    w.write_rows();

    return 0;
}
