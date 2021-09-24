// id.h
#pragma once

#include <string>
#include <mutex>

/**
 * @brief The class provides id ("identifier") interface implementation,
 * according to the following rules:
 * 
 * Identifier is a literal string, split into groups.
 * 
 * Each of the groups consist of two symbols, alphabetical and number. e.g. "A1"
 * 
 * Id must have from 1 to 10 groups, separated by '-'
 *  
 * Allowed letters are - A B C E H I K L N O P R S T U W X Y Z
 * Allowed numbers are - 1...9
 * 
 */
class id final
{
public:

    // Public constant declarations
    static const char* SIZE_ISSUE;
    static const char* PADDING_FORMAT_ISSUE;
    static const char* LETTER_OUT_OF_RANGE; 
    static const char* NUMBER_OUT_OF_RANGE;

    // The constactors could be implemented,
    // but it was not a part of the task.
    // So, they are disabled for now.
    id(const id&) = delete;
    id(id&&) = delete;
    id& operator=(const id&) = delete;
    id& operator=(id&&) = delete;
    
    id() = default;
    ~id() = default;

    /**
     * @brief Creates an id instance from the argument string
     * @param s formatted string
     * @throw std::invalid_argument in case of issues with the string format
     */
    id(const std::string &s);

    /**
     * @brief Sets id to the value in the argument string
     * @param s formatted string
     * @throw std::invalid_argument in case of issues with the string format
     * 
     * @return reference to the id instance
     */
    id& operator=(const std::string& s);

    /**
     * @brief Increments id and returns the new value in formatted string
     * @return formatted string
     */
    std::string get_incremented();

private:

    static const std::string padding;
    static const std::string letters;

    /**
     * @brief increments the id
     */
    id& operator++();

    /**
     * @brief Gets the value in string format
     * @return Formatted string
     */
    std::string get();

    int _g{0};    // group
    int _l{0};    // letter
    char _n{'1'}; // number

    std::mutex _m;

};
