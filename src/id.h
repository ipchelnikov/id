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

    // Exceptions
    static constexpr char SIZE_ISSUE[] = "Size issue";
    static constexpr char FORMAT_ISSUE[] = "Format issue";
    static constexpr char LETTER_OUT_OF_RANGE[] = "Letter is out of the range";
    static constexpr char NUMBER_OUT_OF_RANGE[] = "Number is out of the range";

    // Disabled constructors
    id(const id&) = delete;
    id(id&&) = delete;
    id& operator=(const id&) = delete;
    id& operator=(id&&) = delete;

    // Public interface

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
    std::string get_next();

private:

    // Helper constants
    static constexpr char ID_INITIAL[] = "A1";
    static constexpr char ID_SEPARATED[] = "-A1";

    static constexpr char MIN_NUMBER{'1'};
    static constexpr char MAX_NUMBER{'9'};
    static constexpr char DELIMITER{'-'};

    static constexpr size_t MAX_GROUPS{10};
    static constexpr size_t GROUP_SIZE{3};

    // Allowed letters
    static constexpr char LETTERS[] = "ABCEHIKLNOPRSTUWXYZ";

    // Letter indexes
    static const std::unordered_map<char, size_t> letter_ind;


    // Internal interface

    /**
     * @brief increments the id value
     */
    id& operator++();

    /**
     * @brief Gets the value in string format
     * @return Formatted string
     */
    std::string get();

    std::string _val = ID_INITIAL;

    std::mutex _m;

};
