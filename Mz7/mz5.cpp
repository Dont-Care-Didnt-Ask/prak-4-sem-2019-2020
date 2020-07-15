#include <iostream>
#include <string>
#include <sstream>
#include <boost/date_time.hpp>

/*
 * You are given a set of dates, like
 * "2009/05/05 2010/05/05 2010/04/05".
 * Compute the sum of differences (by absolute value)
 * between consecutive dates.
 * In the example –  1 year + 1 month = 395 days.
*/

using namespace boost::gregorian;

int main()
{
    std::string str;
    int sum = 0;
    int y, m, d;
    char sym;
    std::cin >> str;
    std::stringstream(str) >> y >> sym >> m >> sym >> d;

    date prev(y, m, d);

    while (std::cin >> str) {
        std::stringstream(str) >> y >> sym >> m >> sym >> d;
        date cur(y, m, d);
        sum += abs((cur - prev).days());
        prev = cur;
    }
    std::cout << sum << std::endl;
}