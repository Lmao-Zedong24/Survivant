#include "SurvivantCore/Utility/FileSystem.h"
#include "SurvivantCore/Utility/LeanWindows.h"

#include <direct.h>
#include <filesystem>

namespace SvCore::Utility
{
    std::string GetApplicationDirectory()
    {
        static std::string applicationPath(MAX_PATH, '\0');
        static bool        wasLoaded = false;

        if (wasLoaded)
            return applicationPath;

        const DWORD pathLength = GetModuleFileNameA(nullptr, applicationPath.data(), MAX_PATH);
        const auto  tmp        = std::filesystem::canonical(pathLength > 0 ? applicationPath : "./").remove_filename();

        applicationPath = tmp.string();
        applicationPath.shrink_to_fit();
        wasLoaded = true;

        return applicationPath;
    }

    std::string GetWorkingDirectory()
    {
        auto tmp = std::filesystem::current_path().string();

        if (!tmp.ends_with(std::filesystem::path::preferred_separator))
            tmp += std::filesystem::path::preferred_separator;

        return tmp;
    }

    bool SetWorkingDirectory(const std::string& p_directory)
    {
        return _chdir(p_directory.c_str()) == 0;
    }
}
