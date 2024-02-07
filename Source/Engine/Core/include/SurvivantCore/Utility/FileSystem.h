#pragma once
#include <string>

namespace SvCore::Utility
{
    /**
     * \brief Gets the calling application's directory
     * \return The calling application's directory
     */
    std::string GetApplicationDirectory();

    /**
     * \brief Gets the current working directory
     * \return The current working directory
     */
    std::string GetWorkingDirectory();

    /**
     * \brief Sets the application's working directory
     * \param p_directory The new working directory
     * \return True on success. False otherwise
     */
    bool SetWorkingDirectory(const std::string& p_directory);
}
