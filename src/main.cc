#include "reader.hh"

int main(void)
{
    auto r = csv::Reader("src/test.csv");
    r.display();

    return 0;
}
