#include <mutex>
#include <stdexcept>
#include <string>
#include <unordered_map>

#include "id.h"

const std::unordered_map<char, size_t> id::letter_ind = 
    []() -> const std::unordered_map<char, size_t>
    {
        std::unordered_map<char, size_t> r;
        for (size_t i = 0; i < sizeof(letters); ++i)
        {
            r[letters[i]] = i;
        }
        return r;
    } ();

id::id(std::string s) : val_{std::move(s)}
{
    const auto s_size = val_.size() + 1;

    // Input size validation
    if (s_size < group_size ||
        s_size > group_size * max_groups ||
        s_size % group_size)
    {
        throw std::invalid_argument(size_issue);
    }

    for (size_t i = 0; i < (s_size + 1) / group_size; ++i)
    {
        const auto pos = i * group_size;

        // Check delimiter format
        if (pos && val_[pos - 1] != delimiter)
        {
            throw std::invalid_argument(format_issue);
        }

        // Check letter
        if (letter_ind.find(val_[pos]) == letter_ind.end())
        {
            throw std::out_of_range(letter_out_of_range);
        }

        // Check number
        if (const auto n = val_[pos + 1];
            n < min_number || n > max_number)
        {
            throw std::out_of_range(number_out_of_range);
        }
    }
}

id& id::operator=(const std::string &s)
{
    const id tmp{s};

    std::unique_lock<std::mutex> lk(m_);

    val_ = tmp.val_;

    return *this;
}

std::string id::get_next()
{
    std::unique_lock<std::mutex> lk(m_);

    ++*this;

    return val_;
}

id& id::operator++()
{
    const auto groups{(val_.size() + 1) / group_size};

    for (auto group{groups}; group > 0; --group)
    {
        // Increment the number
        const auto pos = (group - 1) * group_size;
        if (val_[pos + 1] < max_number)
        {
            ++val_[pos + 1];
            return *this;
        }
        val_[pos + 1] = min_number;

        // Increment the letter
        if (const auto ind = letter_ind.at(val_[pos]);
            ind < sizeof(letters) - 2)
        {
            val_[pos] = letters[ind + 1];
            return *this;
        }
        val_[pos] = letters[0];
    }

    // If there is enough capacity add new group
    if (groups < max_groups)
    {
        val_ += id_separated;
    }
    // Otherwise overflow to the initial value
    else
    {
        val_ = id_initial;
    }

    return *this;
}
