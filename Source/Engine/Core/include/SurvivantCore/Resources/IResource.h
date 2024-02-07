#pragma once

#include <string>

namespace SvCore::Resources
{
    class IResource
    {
    public:
        /**
         * \brief Destroys the resource
         */
        virtual ~IResource() = default;

        /**
         * \brief Loads the resource from the given file
         * \param p_fileName The resource file's path
         * \return True if the resource was successfully loaded. False otherwise.
         */
        virtual bool Load(const std::string& p_fileName) = 0;

        /**
         * \brief Initializes the resource
         * \return True on success. False otherwise.
         */
        virtual bool Init() = 0;
    };
}
