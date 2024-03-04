#include "SurvivantRendering/Resources/Shader.h"

#include <sstream>

#include <glad/gl.h>

#include <SurvivantCore/Debug/Assertion.h>
#include <SurvivantCore/Debug/Logger.h>
#include <SurvivantCore/Utility/Utility.h>

using namespace SvCore::Utility;

namespace SvRendering::Resources
{
    Shader::Shader(std::string p_source)
        : m_source(std::move(p_source))
    {
        ASSERT(ParseSource(), "Unable to initialize shader - Couldn't parse source");
    }

    Shader::Shader(const Shader& p_other)
        : m_source(p_other.m_source)
    {
        if (p_other.m_program != 0)
        ASSERT(ParseSource());
    }

    Shader::Shader(Shader&& p_other) noexcept
        : m_source(std::move(p_other.m_source)), m_program(p_other.m_program)
    {
        p_other.m_program = 0;
    }

    Shader::~Shader()
    {
        glDeleteProgram(m_program);
    }

    Shader& Shader::operator=(const Shader& p_other)
    {
        if (&p_other == this)
            return *this;

        m_source = p_other.m_source;

        if (p_other.m_program != 0)
        ASSERT(ParseSource());

        return *this;
    }

    Shader& Shader::operator=(Shader&& p_other) noexcept
    {
        if (&p_other == this)
            return *this;

        m_source  = p_other.m_source;
        m_program = p_other.m_program;

        p_other.m_program = 0;

        return *this;
    }

    bool Shader::Load(const std::string& p_path)
    {
        Reset();
        m_source.clear();

        if (!CHECK(!p_path.empty(), "Unable to load the shader - empty path"))
            return false;

        std::ifstream fileStream(p_path, std::ios::binary | std::ios::ate);

        if (!CHECK(fileStream.is_open(), "Failed to load the shader - Couldn't open file at path \"%s\"", p_path.c_str()))
            return false;

        const std::ios::pos_type fileLength = fileStream.tellg();
        fileStream.seekg(0, std::ios::beg);

        m_source.resize(fileLength);
        fileStream.read(m_source.data(), fileLength);

        return true;
    }

    bool Shader::Init()
    {
        return ParseSource();
    }

    void Shader::Use() const
    {
        glUseProgram(m_program);
    }

    void Shader::Unbind()
    {
        glUseProgram(0);
    }

    void Shader::SetUniformInt(const std::string& p_name, const int p_value)
    {
        glUniform1i(GetUniformLocation(p_name), p_value);
    }

    void Shader::SetUniformFloat(const std::string& p_name, const float p_value)
    {
        glUniform1f(GetUniformLocation(p_name), p_value);
    }

    void Shader::SetUniformVec2(const std::string& p_name, const LibMath::Vector2& p_value)
    {
        glUniform2fv(GetUniformLocation(p_name), 1, p_value.getArray());
    }

    void Shader::SetUniformVec3(const std::string& p_name, const LibMath::Vector3& p_value)
    {
        glUniform3fv(GetUniformLocation(p_name), 1, p_value.getArray());
    }

    void Shader::SetUniformVec4(const std::string& p_name, const LibMath::Vector4& p_value)
    {
        glUniform4fv(GetUniformLocation(p_name), 1, p_value.getArray());
    }

    void Shader::SetUniformMat4(const std::string& p_name, const LibMath::Matrix4& p_value)
    {
        glUniformMatrix4fv(GetUniformLocation(p_name), 1, GL_TRUE, p_value.getArray());
    }

    int Shader::GetUniformInt(const std::string& p_name)
    {
        int value;
        glGetUniformiv(m_program, GetUniformLocation(p_name), &value);
        return value;
    }

    float Shader::GetUniformFloat(const std::string& p_name)
    {
        float value;
        glGetUniformfv(m_program, GetUniformLocation(p_name), &value);
        return value;
    }

    LibMath::Vector2 Shader::GetUniformVec2(const std::string& p_name)
    {
        GLfloat values[16];
        glGetUniformfv(m_program, GetUniformLocation(p_name), values);
        return reinterpret_cast<LibMath::Vector2&>(values);
    }

    LibMath::Vector3 Shader::GetUniformVec3(const std::string& p_name)
    {
        GLfloat values[16];
        glGetUniformfv(m_program, GetUniformLocation(p_name), values);
        return reinterpret_cast<LibMath::Vector3&>(values);
    }

    LibMath::Vector4 Shader::GetUniformVec4(const std::string& p_name)
    {
        GLfloat values[16];
        glGetUniformfv(m_program, GetUniformLocation(p_name), values);
        return reinterpret_cast<LibMath::Vector4&>(values);
    }

    LibMath::Matrix4 Shader::GetUniformMat4(const std::string& p_name)
    {
        GLfloat values[16];
        glGetUniformfv(m_program, GetUniformLocation(p_name), values);
        return reinterpret_cast<LibMath::Matrix4&>(values);
    }

    std::string Shader::GetTokenFromType(const uint32_t p_shaderType)
    {
        switch (p_shaderType)
        {
        case GL_VERTEX_SHADER:
            return "vertex";
        case GL_FRAGMENT_SHADER:
            return "fragment";
        case GL_GEOMETRY_SHADER:
            return "geometry";
        case GL_TESS_EVALUATION_SHADER:
            return "tess_evaluation";
        case GL_TESS_CONTROL_SHADER:
            return "tess_control";
        case GL_COMPUTE_SHADER:
            return "compute";
        default:
            return {};
        }
    }

    uint32_t Shader::GetTypeFromToken(std::string p_shaderType)
    {
        ToLowerInPlace(p_shaderType);

        if (p_shaderType == "vertex" || p_shaderType == "vert")
            return GL_VERTEX_SHADER;

        if (p_shaderType == "fragment" || p_shaderType == "frag")
            return GL_FRAGMENT_SHADER;

        if (p_shaderType == "geometry" || p_shaderType == "geo")
            return GL_GEOMETRY_SHADER;

        if (p_shaderType == "tesselation_evaluation" || p_shaderType == "tess_evaluation"
            || p_shaderType == "tesselation_eval" || p_shaderType == "tess_eval")
            return GL_TESS_EVALUATION_SHADER;

        if (p_shaderType == "tesselation_control" || p_shaderType == "tess_control"
            || p_shaderType == "tesselation_ctrl" || p_shaderType == "tess_ctrl")
            return GL_TESS_CONTROL_SHADER;

        if (p_shaderType == "compute" || p_shaderType == "com")
            return GL_COMPUTE_SHADER;

        return GL_INVALID_VALUE;
    }

    std::string Shader::GetShaderLog(const uint32_t p_shaderId)
    {
        GLint infoLogLength = 0;
        glGetShaderiv(p_shaderId, GL_INFO_LOG_LENGTH, &infoLogLength);

        std::string infoLog(infoLogLength, '\0');
        glGetShaderInfoLog(p_shaderId, infoLogLength, &infoLogLength, infoLog.data());

        return infoLog;
    }

    std::string Shader::GetProgramLog(const uint32_t p_shaderProgram)
    {
        GLint infoLogLength = 0;
        glGetProgramiv(p_shaderProgram, GL_INFO_LOG_LENGTH, &infoLogLength);

        std::string infoLog(infoLogLength, '\0');
        glGetProgramInfoLog(p_shaderProgram, infoLogLength, &infoLogLength, infoLog.data());

        return infoLog;
    }

    bool Shader::ParseSource()
    {
        Reset();

        if (m_source.empty())
            return false;

        m_program = glCreateProgram();

        std::vector<std::string> sources = SplitString(m_source, "#shader ", true);

        std::vector<GLuint> shaderIds;
        shaderIds.reserve(sources.size());

        for (std::string& source : sources)
        {
            if (source.empty())
                continue;

            std::istringstream iStrStream(source);
            std::string        token;

            iStrStream >> token;

            const GLuint shaderType = GetTypeFromToken(token);

            if (shaderType != GL_INVALID_VALUE)
            {
                std::string firstLine;
                std::getline(iStrStream, firstLine);
                source.erase(0, token.size() + firstLine.size());

                if (!ProcessIncludes(source))
                    continue;

                if (const GLuint shaderId = CompileSource(shaderType, source))
                {
                    shaderIds.emplace_back(shaderId);
                    glAttachShader(m_program, shaderId);
                }
            }
        }

        const bool isSuccess = Link();

        for (const GLuint shaderId : shaderIds)
            glDeleteShader(shaderId);

        return isSuccess;
    }

    bool Shader::ProcessIncludes(std::string& p_source)
    {
        if (p_source.empty())
            return true;

        std::string        line;
        std::istringstream sourceStream(p_source);
        ptrdiff_t          offset = 0;

        while (std::getline(sourceStream, line))
        {
            if (!line.starts_with("#include "))
                continue;

            const size_t lineSize = line.size();
            const size_t curPos   = !sourceStream.eof() ? static_cast<size_t>(sourceStream.tellg()) - 1 : p_source.size();
            const size_t startPos = curPos - lineSize;

            line.erase(0, 9); // Remove the #include
            const auto trimCallback = [](const char c)
            {
                return std::isspace(c) || c == '"' || c == '<' || c == '>';
            };

            TrimString(line, trimCallback);

            if (!CHECK(!line.empty(), "Empty shader include path", line.c_str()))
                return false;

            std::ifstream sourceFile(line, std::ios::binary | std::ios::ate);

            if (!CHECK(sourceFile.is_open(), "Invalid shader include path: \"%s\"", line.c_str()))
                return false;

            const std::ifstream::pos_type length = sourceFile.tellg();
            sourceFile.seekg(0, std::ios::beg);

            std::string includedShader(length, 0);
            sourceFile.read(includedShader.data(), length);
            sourceFile.close();

            if (!ProcessIncludes(includedShader))
                return false;

            p_source.replace(startPos + offset, lineSize, includedShader);
            offset += static_cast<ptrdiff_t>(includedShader.size()) - lineSize;
        }

        return true;
    }

    GLuint Shader::CompileSource(const GLenum p_shaderType, const std::string& p_source)
    {
        const GLuint shaderId     = glCreateShader(p_shaderType);
        const char*  shaderSource = p_source.c_str();
        const auto   sourceSize   = static_cast<GLint>(p_source.size());

        glShaderSource(shaderId, 1, &shaderSource, &sourceSize);
        glCompileShader(shaderId);

        int success;
        glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);

        if (!success)
        {
            SV_LOG_ERROR("ERROR::SHADER::%s::COMPILATION_FAILED\n%s", ToUpper(GetTokenFromType(p_shaderType)).c_str(),
                GetShaderLog(shaderId).c_str());

            glDeleteShader(shaderId);
            return 0;
        }

        return shaderId;
    }

    bool Shader::Link() const
    {
        if (m_program == 0)
            return false;

        int success;
        glLinkProgram(m_program);
        glGetProgramiv(m_program, GL_LINK_STATUS, &success);

        if (!success)
        {
            SV_LOG_ERROR("ERROR::SHADER::PROGRAM::LINKING_FAILED\n%s", GetProgramLog(m_program).c_str());
            return false;
        }

        glValidateProgram(m_program);
        glGetProgramiv(m_program, GL_VALIDATE_STATUS, &success);

        if (!success)
        {
            SV_LOG_ERROR("ERROR::SHADER::PROGRAM::VALIDATION_FAILED\n%s", GetProgramLog(m_program).c_str());
            return false;
        }

        return true;
    }

    GLint Shader::GetUniformLocation(const std::string& p_uniformName)
    {
        const auto& it = m_uniformLocationsCache.find(p_uniformName);

        if (it != m_uniformLocationsCache.end())
            return it->second;

        return m_uniformLocationsCache[p_uniformName] = glGetUniformLocation(m_program, p_uniformName.c_str());
    }

    void Shader::Reset()
    {
        glDeleteProgram(m_program);
        m_program = 0;

        m_uniformLocationsCache.clear();
    }
}
