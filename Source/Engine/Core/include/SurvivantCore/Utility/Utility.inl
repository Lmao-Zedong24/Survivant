#pragma once

#include "SurvivantCore/Utility/Utility.h"

#include <algorithm>
#include <stdexcept>

namespace SvCore::Utility
{
    template <typename... Args>
    std::string FormatString(const std::string& p_format, Args&&... p_args)
    {
        // If no template parameters are passed
        // return the format string as is to avoid unnecessary allocation
        if constexpr (sizeof...(Args) == 0)
        {
            return p_format;
        }
        else
        {
            // get the formatted text's size
            const int bufferSize = std::snprintf(nullptr, 0, p_format.c_str(), std::forward<Args>(p_args)...) + 1;

            if (bufferSize <= 0)
                throw std::runtime_error("Unable to format string.");

            // Create a buffer of the computed size
            std::string message;
            message.resize(bufferSize, 0);

            // Write the formatted string in the buffer
            message.resize(std::snprintf(message.data(), bufferSize, p_format.c_str(), std::forward<Args>(p_args)...));

            return message;
        }
    }

    template <class CompareFunc>
    void TrimStringStart(std::string& p_str, CompareFunc p_compareFunc)
    {
        p_str.erase(p_str.begin(), std::ranges::find_if_not(p_str, p_compareFunc));
    }

    template <class CompareFunc>
    void TrimStringEnd(std::string& p_str, CompareFunc p_compareFunc)
    {
        p_str.erase(std::find_if_not(p_str.rbegin(), p_str.rend(), p_compareFunc).base(), p_str.end());
    }

    template <class CompareFunc>
    void TrimString(std::string& p_str, CompareFunc p_compareFunc)
    {
        TrimStringEnd(p_str, p_compareFunc);
        TrimStringStart(p_str, p_compareFunc);
    }
}
