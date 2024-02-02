#pragma once
#include "SurvivantCore/Resources/IResource.h"

#include <Matrix.h>
#include <Vector.h>

#include <string>
#include <unordered_map>

namespace SvRendering::Resources
{
    class Shader final : public SvCore::Resources::IResource
    {
    public:
        Shader() = default;

        /**
         * \brief Creates a shader with the given source
         * \param p_source The shader's source
         */
        explicit Shader(std::string p_source);

        /**
         * \brief Copies the given shader
         * \param p_other The shader to copy
         */
        Shader(const Shader& p_other);

        /**
         * \brief Moves the given shader
         * \param p_other The shader to move
         */
        Shader(Shader&& p_other) noexcept;

        /**
         * \brief Destroys the shader and frees its resources
         */
        ~Shader() override;

        /**
         * \brief Assigns a copy of the given shader to the current one
         * \param p_other The shader to copy
         * \return A reference to the updated shader
         */
        Shader& operator=(const Shader& p_other);

        /**
         * \brief Moves the given shader into the current one
         * \param p_other The shader to move
         * \return A reference to the modified shader
         */
        Shader& operator=(Shader&& p_other) noexcept;

        /**
         * \brief Loads the shader from the file at the given path
         * \param p_path The loaded shader's path
         * \return True on success. False otherwise
         */
        bool Load(const std::string& p_path) override;

        /**
         * \brief Initializes the shader
         * \return True on success. False otherwise
         */
        bool Init() override;

        /**
         * \brief Uses the shader program.
         */
        void Use() const;

        /**
         * \brief Unbinds the current shader
         */
        static void Unbind();

        /**
         * \brief Sets the value of the int uniform with the given name
         * \param p_name The name of the uniform
         * \param p_value The value of the uniform
         */
        void SetUniformInt(const std::string& p_name, int p_value);

        /**
         * \brief Sets the value of the float uniform with the given name
         * \param p_name The name of the uniform
         * \param p_value The value of the uniform
         */
        void SetUniformFloat(const std::string& p_name, float p_value);

        /**
         * \brief Sets the value of the Vector2 uniform with the given name
         * \param p_name The name of the uniform
         * \param p_value The value of the uniform
         */
        void SetUniformVec2(const std::string& p_name, const LibMath::Vector2& p_value);

        /**
         * \brief Sets the value of the Vector3 uniform with the given name
         * \param p_name The name of the uniform
         * \param p_value The value of the uniform
         */
        void SetUniformVec3(const std::string& p_name, const LibMath::Vector3& p_value);

        /**
         * \brief Sets the value of the Vector4 uniform with the given name
         * \param p_name The name of the uniform
         * \param p_value The value of the uniform
         */
        void SetUniformVec4(const std::string& p_name, const LibMath::Vector4& p_value);

        /**
         * \brief Sets the value of the Matrix4 uniform with the given name
         * \param p_name The name of the uniform
         * \param p_value The value of the uniform
         */
        void SetUniformMat4(const std::string& p_name, const LibMath::Matrix4& p_value);

        /**
         * \brief Gets the value of the int uniform with the given name
         * \param p_name The name of the uniform
         * \return The value of the uniform
         */
        int GetUniformInt(const std::string& p_name);

        /**
         * \brief Gets the value of the float uniform with the given name
         * \param p_name The name of the uniform
         * \return The value of the uniform
         */
        float GetUniformFloat(const std::string& p_name);

        /**
         * \brief Gets the value of the Vector2 uniform with the given name
         * \param p_name The name of the uniform
         * \return The value of the uniform
         */
        LibMath::Vector2 GetUniformVec2(const std::string& p_name);

        /**
         * \brief Gets the value of the Vector3 uniform with the given name
         * \param p_name The name of the uniform
         * \return The value of the uniform
         */
        LibMath::Vector3 GetUniformVec3(const std::string& p_name);

        /**
         * \brief Gets the value of the Vector4 uniform with the given name
         * \param p_name The name of the uniform
         * \return The value of the uniform
         */
        LibMath::Vector4 GetUniformVec4(const std::string& p_name);

        /**
         * \brief Gets the value of the Matrix4 uniform with the given name
         * \param p_name The name of the uniform
         * \return The value of the uniform
         */
        LibMath::Matrix4 GetUniformMat4(const std::string& p_name);

    private:
        std::unordered_map<std::string, int> m_uniformLocationsCache;
        std::string                          m_source;
        uint32_t                             m_program = 0;

        static constexpr int INFO_LOG_SIZE = 512;

        /**
         * \brief Converts a shader type enum value to its corresponding token string
         * \param p_shaderType The target shader type
         * \return The token string corresponding to the given shader type
         */
        static std::string GetTokenFromType(uint32_t p_shaderType);

        /**
         * \brief Converts a shader type token string to its corresponding enum value
         * \param p_shaderType The target shader type
         * \return The type enum value corresponding to the given shader type token
         */
        static uint32_t GetTypeFromToken(const std::string& p_shaderType);

        /**
         * \brief Compiles the given shader source
         * \param p_shaderType The type of shader to compile
         * \param p_source The source of the shader to compile
         * \return The compiled shader's handle
         */
        static uint32_t CompileSource(uint32_t p_shaderType, const std::string& p_source);

        /**
         * \brief Parses the shader's source and create the appropriate shader types
         * \return True if at least one type of shader was extracted. False otherwise
         */
        bool ParseSource();

        /**
         * \brief Links the shader program.\n
         * \return True if the shader is linked successfully. False otherwise
         */
        bool Link() const;

        /**
         * \brief Gets the location of a given uniform variable
         * in the current shader program
         * \param p_uniformName The searched uniform variable's name
         * \return The location of the searched uniform variable
         */
        int GetUniformLocation(const std::string& p_uniformName);

        /**
         * \brief Resets the shader program and the uniform locations cache
         */
        void Reset();
    };
}
