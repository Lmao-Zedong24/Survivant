#pragma once
#include "SurvivantRendering/Enums/EShaderDataType.h"
#include "SurvivantRendering/Enums/EShaderType.h"

#include <SurvivantCore/Resources/IResource.h>

#include <Matrix.h>
#include <Vector.h>

#include <string>
#include <unordered_map>

namespace SvRendering::RHI
{
    class ITexture;

    class IShader : public SvCore::Resources::IResource
    {
    public:
        struct UniformInfo
        {
            Enums::EShaderDataType m_type;
            int                    m_location;
        };

        /**
         * \brief Creates a copy of the given shader
         * \param p_other The shader to copy
         */
        IShader(const IShader& p_other) = default;

        /**
         * \brief Creates a move copy of the given shader
         * \param p_other The shader to move
         */
        IShader(IShader&& p_other) noexcept = default;

        /**
         * \brief Destroys the shader
         */
        ~IShader() override = default;

        /**
         * \brief Assigns a copy of the given shader to this one
         * \param p_other The shader to copy
         * \return A reference to the modified shader
         */
        IShader& operator=(const IShader& p_other) = default;

        /**
         * \brief Moves the given shader into this one
         * \param p_other The shader to move
         * \return A reference to the modified shader
         */
        IShader& operator=(IShader&& p_other) noexcept = default;

        /**
         * \brief Binds the shader to the context.
         */
        virtual void Bind() = 0;

        /**
         * \brief Unbinds the currently bound shader
         */
        virtual void Unbind() = 0;

        /**
         * \brief Get information about the uniform with the given name
         * \param p_name The searched uniform's name
         * \return Information about the searched uniform
         */
        virtual const UniformInfo& GetUniformInfo(const std::string& p_name) = 0;

        /**
         * \brief Sets the value of the int uniform with the given name
         * \param p_name The name of the uniform
         * \param p_value The value of the uniform
         */
        virtual void SetUniformInt(const std::string& p_name, int p_value) = 0;

        /**
         * \brief Sets the value of the unsigned int uniform with the given name
         * \param p_name The name of the uniform
         * \param p_value The value of the uniform
         */
        virtual void SetUniformUInt(const std::string& p_name, uint32_t p_value) = 0;

        /**
         * \brief Sets the value of the float uniform with the given name
         * \param p_name The name of the uniform
         * \param p_value The value of the uniform
         */
        virtual void SetUniformFloat(const std::string& p_name, float p_value) = 0;

        /**
         * \brief Sets the value of the Vector2 uniform with the given name
         * \param p_name The name of the uniform
         * \param p_value The value of the uniform
         */
        virtual void SetUniformVec2(const std::string& p_name, const LibMath::Vector2& p_value) = 0;

        /**
         * \brief Sets the value of the Vector3 uniform with the given name
         * \param p_name The name of the uniform
         * \param p_value The value of the uniform
         */
        virtual void SetUniformVec3(const std::string& p_name, const LibMath::Vector3& p_value) = 0;

        /**
         * \brief Sets the value of the Vector4 uniform with the given name
         * \param p_name The name of the uniform
         * \param p_value The value of the uniform
         */
        virtual void SetUniformVec4(const std::string& p_name, const LibMath::Vector4& p_value) = 0;

        /**
         * \brief Sets the value of the Matrix3 uniform with the given name
         * \param p_name The name of the uniform
         * \param p_value The value of the uniform
         */
        virtual void SetUniformMat3(const std::string& p_name, const LibMath::Matrix3& p_value) = 0;

        /**
         * \brief Sets the value of the Matrix4 uniform with the given name
         * \param p_name The name of the uniform
         * \param p_value The value of the uniform
         */
        virtual void SetUniformMat4(const std::string& p_name, const LibMath::Matrix4& p_value) = 0;

        /**
         * \brief Sets the value of the Texture uniform with the given name
         * \param p_name The name of the uniform
         * \param p_value The value of the uniform
         */
        virtual void SetUniformTexture(const std::string& p_name, ITexture* p_value) = 0;

        /**
         * \brief Gets the value of the int uniform with the given name
         * \param p_name The name of the uniform
         * \return The value of the uniform
         */
        virtual int GetUniformInt(const std::string& p_name) = 0;

        /**
         * \brief Gets the value of the float uniform with the given name
         * \param p_name The name of the uniform
         * \return The value of the uniform
         */
        virtual float GetUniformFloat(const std::string& p_name) = 0;

        /**
         * \brief Gets the value of the Vector2 uniform with the given name
         * \param p_name The name of the uniform
         * \return The value of the uniform
         */
        virtual LibMath::Vector2 GetUniformVec2(const std::string& p_name) = 0;

        /**
         * \brief Gets the value of the Vector3 uniform with the given name
         * \param p_name The name of the uniform
         * \return The value of the uniform
         */
        virtual LibMath::Vector3 GetUniformVec3(const std::string& p_name) = 0;

        /**
         * \brief Gets the value of the Vector4 uniform with the given name
         * \param p_name The name of the uniform
         * \return The value of the uniform
         */
        virtual LibMath::Vector4 GetUniformVec4(const std::string& p_name) = 0;

        /**
         * \brief Gets the value of the Matrix3 uniform with the given name
         * \param p_name The name of the uniform
         * \return The value of the uniform
         */
        virtual LibMath::Matrix3 GetUniformMat3(const std::string& p_name) = 0;

        /**
         * \brief Gets the value of the Matrix4 uniform with the given name
         * \param p_name The name of the uniform
         * \return The value of the uniform
         */
        virtual LibMath::Matrix4 GetUniformMat4(const std::string& p_name) = 0;

        /**
         * \brief Gets the shader's uniforms
         * \return The shader's uniforms
         */
        const std::unordered_map<std::string, UniformInfo>& GetUniforms() const;

        /**
         * \brief Creates a shader for the current rendering API
         * \return The created shader
         */
        static std::shared_ptr<IShader> Create();

        /**
         * \brief Converts a shader type token string to its corresponding enum value
         * \param p_shaderType The target shader type
         * \return The type enum value corresponding to the given shader type token
         */
        static Enums::EShaderType GetTypeFromToken(std::string p_shaderType);

        /**
         * \brief Converts a shader type enum value to its corresponding token string
         * \param p_shaderType The target shader type
         * \return The token string corresponding to the given shader type
         */
        static std::string GetTokenFromType(Enums::EShaderType p_shaderType);

    protected:
        std::unordered_map<std::string, UniformInfo> m_uniforms;

        /**
         * \brief Creates a default shader
         */
        IShader() = default;
    };
}
