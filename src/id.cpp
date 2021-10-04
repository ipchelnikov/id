#include <mutex>
#include <stdexcept>
#include <string>
#include <unordered_map>

#include "id.h"

const std::unordered_map<char, size_t> id::letter_ind = std::invoke(
    []() -> const std::unordered_map<char, size_t>
    {
        std::unordered_map<char, size_t> r;
        for (size_t i = 0; i < sizeof(LETTERS); ++i)
        {
            r[LETTERS[i]] = i;
        }
        return r;
    });

id::id(std::string s) : _val{std::move(s)}
{
    const auto s_size = _val.size() + 1;

    // Input size validation
    if (s_size < GROUP_SIZE ||
        s_size > GROUP_SIZE * MAX_GROUPS ||
        s_size % GROUP_SIZE)
    {
        throw std::invalid_argument(SIZE_ISSUE);
    }

    for (size_t i = 0; i < (s_size + 1) / GROUP_SIZE; ++i)
    {
        const auto pos = i * GROUP_SIZE;

        // Check delimiter format
        if (pos && _val[pos - 1] != DELIMITER)
        {
            throw std::invalid_argument(FORMAT_ISSUE);
        }

        // Check letter
        if (letter_ind.find(_val[pos]) == letter_ind.end())
        {
            throw std::out_of_range(LETTER_OUT_OF_RANGE);
        }

        // Check number
        if (const auto n = _val[pos + 1];
            n < MIN_NUMBER || n > MAX_NUMBER)
        {
            throw std::out_of_range(NUMBER_OUT_OF_RANGE);
        }
    }
}

id& id::operator=(const std::string &s)
{
    const id tmp{s};

    std::unique_lock<std::mutex> lk(_m);

    _val = tmp._val;

    return *this;
}

std::string id::get_next()
{
    std::unique_lock<std::mutex> lk(_m);

    ++*this;

    return _val;
}

id& id::operator++()
{
    const auto groups{(_val.size() + 1) / GROUP_SIZE};

    for (auto group{groups}; group > 0; --group)
    {
        // Increment the number
        const auto pos = (group - 1) * GROUP_SIZE;
        if (_val[pos + 1] < MAX_NUMBER)
        {
            ++_val[pos + 1];
            return *this;
        }
        _val[pos + 1] = MIN_NUMBER;

        // Increment the letter
        if (const auto ind = letter_ind.at(_val[pos]);
            ind < sizeof(LETTERS) - 2)
        {
            _val[pos] = LETTERS[ind + 1];
            return *this;
        }
        _val[pos] = LETTERS[0];
    }

    // If there is enough capacity add new group
    if (groups < MAX_GROUPS)
    {
        _val += ID_SEPARATED;
    }
    // Otherwise overflow to the initial value
    else
    {
        _val = ID_INITIAL;
    }

    return *this;
}
