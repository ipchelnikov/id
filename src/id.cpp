#include <iostream>
#include <mutex>
#include <stdexcept>
#include <string>

#include "id.h"

// Constant initialization
const std::string id::padding {"Z9-Z9-Z9-Z9-Z9-Z9-Z9-Z9-Z9-Z9"};
const std::string id::letters {"ABCEHIKLNOPRSTUWXYZ"};

const char* id::SIZE_ISSUE {"Size issue"};
const char* id::PADDING_FORMAT_ISSUE {"Padding format issue"};
const char* id::LETTER_OUT_OF_RANGE {"Letter is out of the range"}; 
const char* id::NUMBER_OUT_OF_RANGE {"Number is out of the range"};


id::id(const std::string &s)
{
    const auto s_size = s.size();

    // Input size validation
    if (s_size < 2 || s_size > 29 || (s_size + 1) % 3)
    {
        throw std::invalid_argument(SIZE_ISSUE);
    }

    // Init group
    _g = ((s_size + 1) / 3) - 1;

    if (_g > 0 && s.compare(0, 3 * (_g), padding, 0, 3 * (_g)) != 0)
    {
        throw std::invalid_argument(PADDING_FORMAT_ISSUE);
    }

    auto pos = _g * 3;

    // Init letter
    _l = letters.find(s[pos]);

    if (_l == letters.npos)
    {
        throw std::invalid_argument(LETTER_OUT_OF_RANGE);
    }

    // Init number
    _n = s[pos + 1];

    if (_n < '1' || _n > '9')
    {
        throw std::invalid_argument(NUMBER_OUT_OF_RANGE);
    }
}

id& id::operator=(const std::string &s)
{
    id tmp{s};

    std::unique_lock<std::mutex> lk(_m);

    _g = tmp._g;
    _l = tmp._l;
    _n = tmp._n;

    return *this;
}

std::string id::get_incremented()
{
    std::unique_lock<std::mutex> lk(_m);
    return (++*this).get();
}

id &id::operator++()
{
    if (_n < '9')
    {
        ++_n;
        return *this;
    }
    _n = '1';

    if (_l < letters.size() - 1)
    {
        ++_l;
        return *this;
    }
    _l = 0;

    // As not mentioned in the task,
    // let us assume the following is the desired behaviour for overflow
    _g = _g < 9 ? _g + 1 : 0;

    return *this;
}

// Replaced with a better version
// std::string get()
// {
//     return padding.substr(0, _g*3)+letters[_l]+_n;
// }
std::string id::get()
{
    auto res = padding.substr(0, _g * 3 + 2);

    res[_g * 3] = letters[_l];
    res[_g * 3 + 1] = _n;

    return res;
}

int main()
{
    id test_id {"Z9-Z9"};

    std::cout << test_id.get_incremented() << std::endl;

    return 0;
}
