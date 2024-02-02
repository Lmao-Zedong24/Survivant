#include "SurvivantCore/Utility/Utility.h"

#include <sstream>

namespace SvCore::Utility
{
    std::vector<std::string> SplitString(const std::string& p_str, const char* p_delimiter, const bool p_includeEmpty)
    {
        std::vector<std::string> result{};

        if (p_str.empty())
        {
            if (p_includeEmpty)
                result.push_back(p_str);

            return result;
        }

        size_t start = 0;
        size_t end   = p_str.find(p_delimiter, start);

        while (start < p_str.size())
        {
            std::string token = p_str.substr(start, end - start);

            if (p_includeEmpty || !token.empty())
                result.push_back(std::move(token));

            if (end == std::string::npos)
                break;

            start = end + strlen(p_delimiter);
            end   = p_str.find(p_delimiter, start);
        }

        return result;
    }

    void ToUpperInPlace(std::string& p_str)
    {
        std::ranges::transform(p_str, p_str.begin(), [](const char p_c)
        {
            return static_cast<char>(std::toupper(p_c));
        });
    }

    void ToLowerInPlace(std::string& p_str)
    {
        std::ranges::transform(p_str, p_str.begin(), [](const char p_c)
        {
            return static_cast<char>(std::tolower(p_c));
        });
    }

    std::string ToUpper(std::string p_str)
    {
        ToUpperInPlace(p_str);
        return p_str;
    }

    std::string ToLower(std::string p_str)
    {
        ToLowerInPlace(p_str);
        return p_str;
    }
}
