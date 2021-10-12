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
    static constexpr char size_issue[] = "Size issue";
    static constexpr char format_issue[] = "Format issue";
    static constexpr char letter_out_of_range[] = "Letter is out of the range";
    static constexpr char number_out_of_range[] = "Number is out of the range";

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
    explicit id(std::string s);

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
    static constexpr char id_initial[] = "A1";
    static constexpr char id_separated[] = "-A1";

    static constexpr char min_number{'1'};
    static constexpr char max_number{'9'};
    static constexpr char delimiter{'-'};

    static constexpr size_t max_groups{10};
    static constexpr size_t group_size{3};

    // Allowed letters
    // ReSharper disable once StringLiteralTypo
    static constexpr char letters[] = "ABCEHIKLNOPRSTUWXYZ";

    // Letter indexes
    static const std::unordered_map<char, size_t> letter_ind;


    // Internal interface

    /**
     * @brief increments the id value
     */
    id& operator++();


    std::string val_ = id_initial;

    std::mutex m_;

};
