# LibCSV++

## What is it?

A very basic C++ library for CSV parsing.

What is CSV ?

According to [Wikipedia](https://en.wikipedia.org/wiki/Comma-separated_values),
a comma-separated values (CSV) file is a delimited text file that uses a comma
to separate values. Each line of the file is a data record. Each record
consists of one or more fields, separated by commas. The use of the comma as a
field separator is the source of the name for this file format. A CSV file
typically stores tabular data (numbers and text) in plain text, in which case
each line will have the same number of fields.

## How to use it

Simply include the header located in include/csv.hh in your project.

## API

For convenience, our data object will be stored as the following:

`using table_t = std::vector<std::pair<std::string, std::vector<std::string>>>;`

### Reader

**Two constructors**
* `Reader(const std::string& filename)`
* `Reader(const std::string& filename, const std::string& delimiter)`

**Methods**
* `table_t get_rows() const`
* `std::vector<std::string> operator[](const std::string& id) const`
* `std::vector<std::string> get_column_names() const`

**Use example**
```c++
auto r = csv::Reader("tests/test.csv");
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
```

### csv::Writer

**Two constructors**
* `Writer(const std::string& filename)`
* `Writer(const std::string& filename, const std::string& delimiter)`

**Methods**
* `void set_rows(table_t& rows)`
* `void write_rows() const`

**Use example**
```c++
auto r = csv::Reader("tests/test.csv", ';');
auto data = r.get_rows();
auto w = csv::Writer("tests/output.csv", ';');
w.set_rows(data);
w.write_rows();
```

### Author

* [Tanguy Segarra](https://github.com/tanguysegarra/) - *Initial work*

### TODO

* add tests
* add a script that builds the big include file from the src/ folder
