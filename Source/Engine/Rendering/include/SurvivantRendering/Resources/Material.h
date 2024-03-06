#pragma once
#include "SurvivantRendering/RHI/IShader.h"

#include <SurvivantCore/Resources/IResource.h>

#include <any>

namespace SvRendering::Resources
{
    class Material final : public SvCore::Resources::IResource
    {
    public:
        struct Property
        {
            Enums::EShaderDataType m_type;
            std::any               m_value;
        };

        /**
         * \brief Creates a default material
         */
        Material() = default;

        /**
         * \brief Creates a material with the given shader
         * \param p_shader The material's shader
         */
        explicit Material(const std::shared_ptr<RHI::IShader>& p_shader);

        /**
         * \brief Creates a copy of the given material
         * \param p_other The material to copy
         */
        Material(const Material& p_other) = default;

        /**
         * \brief Creates a move copy of the given material
         * \param p_other The material to move
         */
        Material(Material&& p_other) noexcept = default;

        /**
         * \brief Destroys the material
         */
        ~Material() override = default;

        /**
         * \brief Assigns a copy of the given material to this one
         * \param p_other The material to copy
         * \return A reference to the modified material
         */
        Material& operator=(const Material& p_other) = default;

        /**
         * \brief Moves the given material into this one
         * \param p_other The material to move
         * \return A reference to the modified material
         */
        Material& operator=(Material&& p_other) noexcept = default;

        /**
         * \brief Loads the material from the given file
         * \param p_fileName The path of the material to load
         * \return True if the material was successfully loaded. False otherwise.
         */
        bool Load(const std::string& p_fileName) override;

        bool Init() override
        {
            return true;
        }

        /**
         * \brief Gets the material's shader
         * \return A reference to the material's shader
         */
        RHI::IShader& GetShader() const;

        /**
         * \brief Sets the material's shader to the given value
         * \param p_shader The material's new shader's resource reference
         */
        void SetShader(const std::shared_ptr<RHI::IShader>& p_shader);

        /**
         * \brief Gets read-only access to the property with the given name
         * \param p_name The target property's name
         * \return The found property
         */
        const Property& GetProperty(const std::string& p_name) const;

        /**
         * \brief Gets read & write access to the property with the given name
         * \param p_name The target property's name
         * \return The found property
         */
        Property& GetProperty(const std::string& p_name);

        /**
         * \brief Gets read-only access to the material's properties
         * \return The material's properties
         */
        const std::unordered_map<std::string, Property>& GetProperties() const;

        /**
         * \brief Gets read & write access to the material's properties
         * \return The material's properties
         */
        std::unordered_map<std::string, Property>& GetProperties();

        /**
         * \brief Gets read-only access to the property with the given name
         * \param p_name The target property's name
         * \return The found property
         */
        template <typename T>
        const T& GetProperty(const std::string& p_name) const;

        /**
         * \brief Gets read & write access to the property with the given name
         * \param p_name The target property's name
         * \return The found property
         */
        template <typename T>
        T& GetProperty(const std::string& p_name);

        /**
         * \brief Binds the material to the current context
         */
        void Bind() const;

    private:
        static constexpr const char* ENGINE_UNIFORM_PREFIX = "sv_";

        std::shared_ptr<RHI::IShader>             m_shader;
        std::unordered_map<std::string, Property> m_properties;

        /**
         * \brief Gets the default value for the given data type
         * \param p_dataType The values data type
         * \return The data type's default value
         */
        static std::any GetDefaultValue(Enums::EShaderDataType p_dataType);

        /**
         * \brief Binds the given property to the material's shader
         * \param p_name The target property's name
         * \param p_property The target property
         */
        void BindProperty(const std::string& p_name, const Property& p_property) const;
    };

    template <typename T>
    const T& Material::GetProperty(const std::string& p_name) const
    {
        return std::any_cast<const T&>(GetProperty(p_name).m_value);
    }

    template <typename T>
    T& Material::GetProperty(const std::string& p_name)
    {
        return std::any_cast<T&>(GetProperty(p_name).m_value);
    }
}
