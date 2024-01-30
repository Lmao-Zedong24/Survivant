#pragma once

#include <string>
#include <vector>

namespace SvCore::Utility
{
    /**
     * \brief Formats a string using the printf syntax
     * \tparam Args The arguments to insert into the format string
     * \param p_format The format string (follows printf syntax)
     * \param p_args The arguments to insert into the format string
     * \return The formatted string
     */
    template <class... Args>
    std::string FormatString(const std::string& p_format, Args&&... p_args);

    /**
     * \brief Splits the given string using the given delimiter
     * \param p_str The string to split
     * \param p_delimiter The delimiter to use to split the string
     * \param p_includeEmpty Whether empty substrings should be included in the result
     * \return A vector containing the sub-strings
     */
    std::vector<std::string> SplitString(const std::string& p_str, const char* p_delimiter, bool p_includeEmpty);

    /**
     * \brief Trims the beginning of the given string using the given compare func
     * \param p_str The string to trim
     * \param p_compareFunc The function used to check if a character should be trimmed
     */
    template <class CompareFunc>
    void TrimStringStart(std::string& p_str, CompareFunc p_compareFunc = &isspace);

    /**
     * \brief Trims the end of the given string using the given compare func
     * \param p_str The string to trim
     * \param p_compareFunc The function used to check if a character should be trimmed
     */
    template <class CompareFunc>
    void TrimStringEnd(std::string& p_str, CompareFunc p_compareFunc = &isspace);

    /**
     * \brief Trims the given string using the given compare func
     * \param p_str The string to trim
     * \param p_compareFunc The function used to check if a character should be trimmed
     */
    template <class CompareFunc>
    void TrimString(std::string& p_str, CompareFunc p_compareFunc = &isspace);
}

#include "SurvivantCore/Utility/Utility.inl"
