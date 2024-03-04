#include "SurvivantRendering/RHI/OpenGL/OpenGLShader.h"

#include "SurvivantRendering/RHI/ITexture.h"

#include <SurvivantCore/Debug/Assertion.h>
#include <SurvivantCore/Debug/Logger.h>
#include <SurvivantCore/Utility/utility.h>

#include <sstream>

#include <glad/gl.h>

using namespace SvCore::Resources;
using namespace SvCore::Utility;
using namespace SvRendering::Enums;

namespace SvRendering::RHI
{
    GLenum ToGLEnum(const EShaderType p_shaderType)
    {
        switch (p_shaderType)
        {
        case EShaderType::VERTEX:
            return GL_VERTEX_SHADER;
        case EShaderType::FRAGMENT:
            return GL_FRAGMENT_SHADER;
        case EShaderType::GEOMETRY:
            return GL_GEOMETRY_SHADER;
        case EShaderType::TESSELATION_EVALUATION:
            return GL_TESS_EVALUATION_SHADER;
        case EShaderType::TESSELATION_CONTROL:
            return GL_TESS_CONTROL_SHADER;
        case EShaderType::COMPUTE:
            return GL_COMPUTE_SHADER;
        case EShaderType::UNKNOWN:
        default:
            return GL_INVALID_ENUM;
        }
    }

    EShaderDataType GetDataType(GLenum DataType)
    {
        switch (DataType)
        {
        case GL_BOOL:
            return EShaderDataType::BOOL;
        case GL_INT:
            return EShaderDataType::INT;
        case GL_UNSIGNED_INT:
            return EShaderDataType::UNSIGNED_INT;
        case GL_FLOAT:
            return EShaderDataType::FLOAT;
        case GL_FLOAT_VEC2:
            return EShaderDataType::VEC2;
        case GL_FLOAT_VEC3:
            return EShaderDataType::VEC3;
        case GL_FLOAT_VEC4:
            return EShaderDataType::VEC4;
        case GL_FLOAT_MAT3:
            return EShaderDataType::MAT3;
        case GL_FLOAT_MAT4:
            return EShaderDataType::MAT4;
        case GL_SAMPLER_2D:
            return EShaderDataType::TEXTURE;
        default:
            ASSERT(false, "Unsupported shader data type");
            return EShaderDataType::UNKNOWN;
        }
    }

    OpenGLShader::OpenGLShader(const OpenGLShader& p_other)
        : IShader(p_other), m_source(p_other.m_source)
    {
        if (p_other.m_program != 0)
        ASSERT(ParseSource());
    }

    OpenGLShader::OpenGLShader(OpenGLShader&& p_other) noexcept
        : m_source(std::move(p_other.m_source)), m_program(p_other.m_program)
    {
        p_other.m_program = 0;
    }

    OpenGLShader::~OpenGLShader()
    {
        glDeleteProgram(m_program);
    }

    OpenGLShader& OpenGLShader::operator=(const OpenGLShader& p_other)
    {
        if (&p_other == this)
            return *this;

        m_source = p_other.m_source;

        if (p_other.m_program != 0)
        ASSERT(ParseSource());

        return *this;
    }

    OpenGLShader& OpenGLShader::operator=(OpenGLShader&& p_other) noexcept
    {
        if (&p_other == this)
            return *this;

        m_source  = p_other.m_source;
        m_program = p_other.m_program;

        p_other.m_program = 0;

        return *this;
    }

    bool OpenGLShader::Load(const std::string& p_path)
    {
        const std::ifstream fs(p_path);

        if (!CHECK(fs.is_open(), "Unable to open file at path \"%s\"", p_path.c_str()))
            return false;

        std::ostringstream stringStream;

        stringStream << fs.rdbuf();

        m_source = stringStream.str();
        return true;
    }

    bool OpenGLShader::Init()
    {
        return CHECK(ParseSource(), "Unable to initialize shader - Couldn't pare source");
    }

    void OpenGLShader::Bind()
    {
        glUseProgram(m_program);
    }

    void OpenGLShader::Unbind()
    {
        glUseProgram(0);
    }

    const IShader::UniformInfo& OpenGLShader::GetUniformInfo(const std::string& p_name)
    {
        const auto it = m_uniforms.find(p_name);

        ASSERT(it != m_uniforms.end(), "Failed to find uniform with name \"%s\"", p_name.c_str());
        return it->second;
    }

    void OpenGLShader::SetUniformInt(const std::string& p_name, const int p_value)
    {
        glUniform1i(GetUniformInfo(p_name).m_location, p_value);
    }

    void OpenGLShader::SetUniformUInt(const std::string& p_name, const uint32_t p_value)
    {
        glUniform1ui(GetUniformInfo(p_name).m_location, p_value);
    }

    void OpenGLShader::SetUniformFloat(const std::string& p_name, const float value)
    {
        glUniform1f(GetUniformInfo(p_name).m_location, value);
    }

    void OpenGLShader::SetUniformVec2(const std::string& p_name, const LibMath::Vector2& p_value)
    {
        glUniform2fv(GetUniformInfo(p_name).m_location, 1, p_value.getArray());
    }

    void OpenGLShader::SetUniformVec3(const std::string& p_name, const LibMath::Vector3& p_value)
    {
        glUniform3fv(GetUniformInfo(p_name).m_location, 1, p_value.getArray());
    }

    void OpenGLShader::SetUniformVec4(const std::string& p_name, const LibMath::Vector4& p_value)
    {
        glUniform4fv(GetUniformInfo(p_name).m_location, 1, p_value.getArray());
    }

    void OpenGLShader::SetUniformMat3(const std::string& p_name, const LibMath::Matrix3& p_value)
    {
        glUniformMatrix3fv(GetUniformInfo(p_name).m_location, 1, GL_TRUE, p_value.getArray());
    }

    void OpenGLShader::SetUniformMat4(const std::string& p_name, const LibMath::Matrix4& p_value)
    {
        glUniformMatrix4fv(GetUniformInfo(p_name).m_location, 1, GL_TRUE, p_value.getArray());
    }

    void OpenGLShader::SetUniformTexture(const std::string& p_name, ITexture* p_value)
    {
        if (p_value)
            p_value->Bind(static_cast<uint8_t>(GetUniformInt(p_name)));
        else
            glBindTextureUnit(static_cast<uint8_t>(GetUniformInt(p_name)), 0);
    }

    int OpenGLShader::GetUniformInt(const std::string& p_name)
    {
        int value;
        glGetUniformiv(m_program, GetUniformInfo(p_name).m_location, &value);
        return value;
    }

    float OpenGLShader::GetUniformFloat(const std::string& p_name)
    {
        float value;
        glGetUniformfv(m_program, GetUniformInfo(p_name).m_location, &value);
        return value;
    }

    LibMath::Vector2 OpenGLShader::GetUniformVec2(const std::string& p_name)
    {
        LibMath::Vector2 out;
        glGetUniformfv(m_program, GetUniformInfo(p_name).m_location, out.getArray());
        return out;
    }

    LibMath::Vector3 OpenGLShader::GetUniformVec3(const std::string& p_name)
    {
        LibMath::Vector3 out;
        glGetUniformfv(m_program, GetUniformInfo(p_name).m_location, out.getArray());
        return out;
    }

    LibMath::Vector4 OpenGLShader::GetUniformVec4(const std::string& p_name)
    {
        LibMath::Vector4 out;
        glGetUniformfv(m_program, GetUniformInfo(p_name).m_location, out.getArray());
        return out;
    }

    LibMath::Matrix3 OpenGLShader::GetUniformMat3(const std::string& p_name)
    {
        LibMath::Matrix3 out;
        glGetUniformfv(m_program, GetUniformInfo(p_name).m_location, out.getArray());
        return out;
    }

    LibMath::Matrix4 OpenGLShader::GetUniformMat4(const std::string& p_name)
    {
        LibMath::Matrix4 out;
        glGetUniformfv(m_program, GetUniformInfo(p_name).m_location, out.getArray());
        return out;
    }

    bool OpenGLShader::ProcessIncludes(std::string& p_source)
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

            line.erase(0, 9); // Removes the #include
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

    uint32_t OpenGLShader::ProcessSource(std::string& p_source)
    {
        if (p_source.empty())
            return 0;

        std::istringstream iStrStream(p_source);
        std::string        token;

        iStrStream >> token;
        const EShaderType shaderType = GetTypeFromToken(token);

        if (shaderType == EShaderType::UNKNOWN)
            return 0;

        std::string firstLine;
        std::getline(iStrStream, firstLine);
        p_source.erase(0, token.size() + firstLine.size());

        return CompileSource(shaderType, p_source);
    }

    GLuint OpenGLShader::CompileSource(const EShaderType p_shaderType, std::string& p_source)
    {
        const GLuint shaderId = glCreateShader(ToGLEnum(p_shaderType));

        ProcessIncludes(p_source);
        const char* shaderSource = p_source.c_str();
        const auto  sourceSize   = static_cast<GLint>(p_source.size());

        glShaderSource(shaderId, 1, &shaderSource, &sourceSize);
        glCompileShader(shaderId);

        int success;
        glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);

        if (!success)
        {
            char infoLog[INFO_LOG_SIZE];
            glGetShaderInfoLog(shaderId, INFO_LOG_SIZE, nullptr, infoLog);
            SV_LOG_ERROR("ERROR::SHADER::%s::COMPILATION_FAILED\n%s", GetTokenFromType(p_shaderType).c_str(), infoLog);
            glDeleteShader(shaderId);
            return 0;
        }

        return shaderId;
    }

    bool OpenGLShader::ParseSource()
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
            if (const uint32_t id = ProcessSource(source))
            {
                shaderIds.push_back(id);
                glAttachShader(m_program, id);
            }
        }

        const bool isSuccess = Link();

        for (const GLuint shaderId : shaderIds)
            glDeleteShader(shaderId);

        CacheUniforms();

        return isSuccess;
    }

    bool OpenGLShader::Link() const
    {
        if (m_program == 0)
            return false;

        int success;
        glLinkProgram(m_program);
        glGetProgramiv(m_program, GL_LINK_STATUS, &success);

        if (!success)
        {
            char infoLog[INFO_LOG_SIZE];
            glGetProgramInfoLog(m_program, INFO_LOG_SIZE, nullptr, infoLog);
            SV_LOG_ERROR("ERROR::SHADER::PROGRAM::LINKING_FAILED\n%s", infoLog);
            return false;
        }

        glValidateProgram(m_program);
        glGetProgramiv(m_program, GL_VALIDATE_STATUS, &success);

        if (!success)
        {
            char infoLog[INFO_LOG_SIZE];
            glGetProgramInfoLog(m_program, INFO_LOG_SIZE, nullptr, infoLog);
            SV_LOG_ERROR("ERROR::SHADER::PROGRAM::VALIDATION_FAILED\n%s", infoLog);
            return false;
        }

        return true;
    }

    void OpenGLShader::CacheUniforms()
    {
        m_uniforms.clear();

        if (!glIsProgram(m_program))
            return;

        int uniformCount;
        glGetProgramiv(m_program, GL_ACTIVE_UNIFORMS, &uniformCount);

        int maxLength;
        glGetProgramiv(m_program, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxLength);

        if (uniformCount <= 0 || maxLength <= 0)
            return;

        m_uniforms.reserve(uniformCount);

        std::string nameBuffer(maxLength, '\0');
        for (int i = 0; i < uniformCount; ++i)
        {
            int    length, size;
            GLenum dataType;

            glGetActiveUniform(m_program, i, maxLength, &length, &size, &dataType, nameBuffer.data());
            ASSERT(length > 0, "Failed to read uniform name");

            const std::string name = nameBuffer.substr(0, length);

            m_uniforms[name] = { GetDataType(dataType), glGetUniformLocation(m_program, name.c_str()) };
        }
    }

    void OpenGLShader::Reset()
    {
        glDeleteProgram(m_program);
        m_program = 0;
        m_uniforms.clear();
    }
}
