#pragma once
#include "SurvivantRendering/RHI/IShader.h"

namespace SvRendering::RHI
{
    class OpenGLShader final : public IShader
    {
    public:
        /**
         * \brief Creates a default shader
         */
        OpenGLShader() = default;

        /**
         * \brief Creates a copy of the given shader
         * \param p_other The shader to copy
         */
        OpenGLShader(const OpenGLShader& p_other);

        /**
         * \brief Creates a move copy of the given shader
         * \param p_other The shader to move
         */
        OpenGLShader(OpenGLShader&& p_other) noexcept;

        /**
         * \brief Destroys the given shader
         */
        ~OpenGLShader() override;

        /**
         * \brief Assigns a copy of the given shader to this one
         * \param p_other The shader to copy
         * \return A reference to the modified shader
         */
        OpenGLShader& operator=(const OpenGLShader& p_other);

        /**
         * \brief Moves the given shader into this one
         * \param p_other The shader to move
         * \return A reference to the modified shader
         */
        OpenGLShader& operator=(OpenGLShader&& p_other) noexcept;

        /**
         * \brief Loads the source code of a shader from a given file
         * \param p_path The path of the source file to load
         * \return True if the shader was successfully loaded. False otherwise.
         */
        bool Load(const std::string& p_path) override;

        /**
         * \brief Initializes the shader
         * \return True on success. False otherwise
         */
        bool Init() override;

        /**
         * \brief Binds the shader to the context
         */
        void Bind() override;

        /**
         * \brief Unbinds the currently bound shader
         */
        void Unbind() override;

        /**
         * \brief Get information about the uniform with the given name
         * \param p_name The searched uniform's name
         * \return Information about the searched uniform
         */
        const UniformInfo& GetUniformInfo(const std::string& p_name) override;

        /**
         * \brief Sets the value of the int uniform with the given name
         * \param p_name The name of the uniform
         * \param p_value The value of the uniform
         */
        void SetUniformInt(const std::string& p_name, int p_value) override;

        /**
         * \brief Sets the value of the unsigned int uniform with the given name
         * \param p_name The name of the uniform
         * \param p_value The value of the uniform
         */
        void SetUniformUInt(const std::string& p_name, uint32_t p_value) override;

        /**
         * \brief Sets the value of the float uniform with the given name
         * \param p_name The name of the uniform
         * \param value The value of the uniform
         */
        void SetUniformFloat(const std::string& p_name, float value) override;

        /**
         * \brief Sets the value of the Vector2 uniform with the given name
         * \param p_name The name of the uniform
         * \param p_value The value of the uniform
         */
        void SetUniformVec2(const std::string& p_name, const LibMath::Vector2& p_value) override;

        /**
         * \brief Sets the value of the Vector3 uniform with the given name
         * \param p_name The name of the uniform
         * \param p_value The value of the uniform
         */
        void SetUniformVec3(const std::string& p_name, const LibMath::Vector3& p_value) override;

        /**
         * \brief Sets the value of the Vector4 uniform with the given name
         * \param p_name The name of the uniform
         * \param p_value The value of the uniform
         */
        void SetUniformVec4(const std::string& p_name, const LibMath::Vector4& p_value) override;

        /**
         * \brief Sets the value of the Matrix3 uniform with the given name
         * \param p_name The name of the uniform
         * \param p_value The value of the uniform
         */
        void SetUniformMat3(const std::string& p_name, const LibMath::Matrix3& p_value) override;

        /**
         * \brief Sets the value of the Matrix4 uniform with the given name
         * \param p_name The name of the uniform
         * \param p_value The value of the uniform
         */
        void SetUniformMat4(const std::string& p_name, const LibMath::Matrix4& p_value) override;

        /**
         * \brief Sets the value of the Texture uniform with the given name
         * \param p_name The name of the uniform
         * \param p_value The value of the uniform
         */
        void SetUniformTexture(const std::string& p_name, ITexture* p_value) override;

        /**
         * \brief Gets the value of the int uniform with the given name
         * \param p_name The name of the uniform
         * \return The value of the uniform
         */
        int GetUniformInt(const std::string& p_name) override;

        /**
         * \brief Gets the value of the float uniform with the given name
         * \param p_name The name of the uniform
         * \return The value of the uniform
         */
        float GetUniformFloat(const std::string& p_name) override;

        /**
         * \brief Gets the value of the Vector2 uniform with the given name
         * \param p_name The name of the uniform
         * \return The value of the uniform
         */
        LibMath::Vector2 GetUniformVec2(const std::string& p_name) override;

        /**
         * \brief Gets the value of the Vector3 uniform with the given name
         * \param p_name The name of the uniform
         * \return The value of the uniform
         */
        LibMath::Vector3 GetUniformVec3(const std::string& p_name) override;

        /**
         * \brief Gets the value of the Vector4 uniform with the given name
         * \param p_name The name of the uniform
         * \return The value of the uniform
         */
        LibMath::Vector4 GetUniformVec4(const std::string& p_name) override;

        /**
         * \brief Gets the value of the Matrix3 uniform with the given name
         * \param p_name The name of the uniform
         * \return The value of the uniform
         */
        LibMath::Matrix3 GetUniformMat3(const std::string& p_name) override;

        /**
         * \brief Gets the value of the Matrix4 uniform with the given name
         * \param p_name The name of the uniform
         * \return The value of the uniform
         */
        LibMath::Matrix4 GetUniformMat4(const std::string& p_name) override;

    private:
        std::string m_source;
        uint32_t    m_program = 0;

        static constexpr int INFO_LOG_SIZE = 512;

        /**
         * \brief Compiles the given shader source
         * \param p_shaderType The type of shader to compile
         * \param p_source The source of the shader to compile
         * \return The compiled shader's handle
         */
        static uint32_t CompileSource(Enums::EShaderType p_shaderType, std::string& p_source);

        /**
         * \brief Processes includes for the given shader source
         * \param p_source The shader source for which includes should be processed
         * \return True on success. False otherwise
         */
        static bool ProcessIncludes(std::string& p_source);

        /**
         * \brief
         * \param p_source The shader source to process
         * \return The created shader id
         */
        static uint32_t ProcessSource(std::string& p_source);

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
         * \brief Caches the shader's uniforms
         */
        void CacheUniforms();

        /**
         * \brief Resets the shader program and the uniform locations cache
         */
        void Reset();
    };
}
