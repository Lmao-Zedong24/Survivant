#include "SurvivantRendering/RHI/OpenGL/OpenGLAPI.h"

#include "SurvivantRendering/Enums/EAccessMode.h"

#include <SurvivantCore/Debug/Assertion.h>
#include <SurvivantCore/Debug/Logger.h>

#include <glad/gl.h>

#include <GLFW/glfw3.h>

using namespace SvCore::Debug;
using namespace SvRendering::Core;
using namespace SvRendering::Enums;

namespace SvRendering::RHI
{
    void GLAPIENTRY glDebugOutput(const uint32_t source, const uint32_t type, const uint32_t id, const uint32_t severity, const int,
                                  const char*    message, const void*)
    {
        // ignore non-significant error/warning codes
        // NOTE: Here there are the details with a sample output:
        // - #131169 - Framebuffer detailed info: The driver allocated storage for renderbuffer 2. (severity: low)
        // - #131185 - Buffer detailed info: Buffer object 1 (bound to GL_ELEMENT_ARRAY_BUFFER_ARB, usage hint is GL_ENUM_88e4)
        //             will use VIDEO memory as the source for buffer object operations. (severity: low)
        // - #131218 - Program/shader state performance warning: Vertex shader in program 7 is being recompiled based on GL state. (severity: medium)
        // - #131204 - Texture state usage warning: The texture object (0) bound to texture image unit 0 does not have
        //             a defined base level and cannot be used for texture mapping. (severity: low)
        if (id == 131169 || id == 131185 || id == 131218 || id == 131204)
            return;

        Logger& logger = Logger::GetInstance();

        logger.Print("---------------\n");
        logger.Print("Debug message (%u): %s\n", false, id, message);

        switch (source)
        {
        case GL_DEBUG_SOURCE_API:
            logger.Print("Source: API");
            break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
            logger.Print("Source: Window System");
            break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER:
            logger.Print("Source: Shader Compiler");
            break;
        case GL_DEBUG_SOURCE_THIRD_PARTY:
            logger.Print("Source: Third Party");
            break;
        case GL_DEBUG_SOURCE_APPLICATION:
            logger.Print("Source: Application");
            break;
        case GL_DEBUG_SOURCE_OTHER:
        default:
            logger.Print("Source: Other");
            break;
        }

        logger.Print("\n");

        switch (type)
        {
        case GL_DEBUG_TYPE_ERROR:
            logger.Print("Type: Error", true);
            break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
            logger.Print("Type: Deprecated Behaviour", true);
            break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
            logger.Print("Type: Undefined Behaviour", true);
            break;
        case GL_DEBUG_TYPE_PORTABILITY:
            logger.Print("Type: Portability", true);
            break;
        case GL_DEBUG_TYPE_PERFORMANCE:
            logger.Print("Type: Performance", true);
            break;
        case GL_DEBUG_TYPE_MARKER:
            logger.Print("Type: Marker");
            break;
        case GL_DEBUG_TYPE_PUSH_GROUP:
            logger.Print("Type: Push Group");
            break;
        case GL_DEBUG_TYPE_POP_GROUP:
            logger.Print("Type: Pop Group");
            break;
        case GL_DEBUG_TYPE_OTHER:
        default:
            logger.Print("Type: Other");
            break;
        }

        logger.Print("\n");

        switch (severity)
        {
        case GL_DEBUG_SEVERITY_HIGH:
            logger.Print("Severity: high");
            break;
        case GL_DEBUG_SEVERITY_MEDIUM:
            logger.Print("Severity: medium");
            break;
        case GL_DEBUG_SEVERITY_LOW:
            logger.Print("Severity: low");
            break;
        case GL_DEBUG_SEVERITY_NOTIFICATION:
            logger.Print("Severity: notification");
            break;
        default:
            logger.Print("Severity: unknown");
            break;
        }

        logger.Print("\n\n");
    }

    std::string GetGLString(const GLenum name)
    {
        const GLubyte* result = glGetString(name);
        return result ? reinterpret_cast<const char*>(result) : std::string();
    }

    GLenum OpenGLAPI::ToGLEnum(const EPixelDataFormat dataFormat)
    {
        switch (dataFormat)
        {
        case EPixelDataFormat::STENCIL_INDEX:
            return GL_STENCIL_INDEX;
        case EPixelDataFormat::DEPTH_COMPONENT:
            return GL_DEPTH_COMPONENT;
        case EPixelDataFormat::DEPTH_STENCIL:
            return GL_DEPTH_STENCIL;
        case EPixelDataFormat::RED:
            return GL_RED;
        case EPixelDataFormat::GREEN:
            return GL_GREEN;
        case EPixelDataFormat::BLUE:
            return GL_BLUE;
        case EPixelDataFormat::ALPHA:
            return GL_ALPHA;
        case EPixelDataFormat::RG:
            return GL_RG;
        case EPixelDataFormat::RGB:
            return GL_RGB;
        case EPixelDataFormat::BGR:
            return GL_BGR;
        case EPixelDataFormat::RGBA:
            return GL_RGBA;
        case EPixelDataFormat::BGRA:
            return GL_BGRA;
        }

        return GL_INVALID_ENUM;
    }

    GLenum OpenGLAPI::ToGLEnum(const EPixelDataType dataType)
    {
        switch (dataType)
        {
        case EPixelDataType::BYTE:
            return GL_BYTE;
        case EPixelDataType::UNSIGNED_BYTE:
            return GL_UNSIGNED_BYTE;
        case EPixelDataType::SHORT:
            return GL_SHORT;
        case EPixelDataType::UNSIGNED_SHORT:
            return GL_UNSIGNED_SHORT;
        case EPixelDataType::INT:
            return GL_INT;
        case EPixelDataType::UNSIGNED_INT:
            return GL_UNSIGNED_INT;
        case EPixelDataType::FLOAT:
            return GL_FLOAT;
        case EPixelDataType::UNSIGNED_BYTE_3_3_2:
            return GL_UNSIGNED_BYTE_3_3_2;
        case EPixelDataType::UNSIGNED_BYTE_2_3_3_REV:
            return GL_UNSIGNED_BYTE_2_3_3_REV;
        case EPixelDataType::UNSIGNED_SHORT_5_6_5:
            return GL_UNSIGNED_SHORT_5_6_5;
        case EPixelDataType::UNSIGNED_SHORT_5_6_5_REV:
            return GL_UNSIGNED_SHORT_5_6_5_REV;
        case EPixelDataType::UNSIGNED_SHORT_4_4_4_4:
            return GL_UNSIGNED_SHORT_4_4_4_4;
        case EPixelDataType::UNSIGNED_SHORT_4_4_4_4_REV:
            return GL_UNSIGNED_SHORT_4_4_4_4_REV;
        case EPixelDataType::UNSIGNED_SHORT_5_5_5_1:
            return GL_UNSIGNED_SHORT_5_5_5_1;
        case EPixelDataType::UNSIGNED_SHORT_1_5_5_5_REV:
            return GL_UNSIGNED_SHORT_1_5_5_5_REV;
        case EPixelDataType::UNSIGNED_INT_8_8_8_8:
            return GL_UNSIGNED_INT_8_8_8_8;
        case EPixelDataType::UNSIGNED_INT_8_8_8_8_REV:
            return GL_UNSIGNED_INT_8_8_8_8_REV;
        case EPixelDataType::UNSIGNED_INT_10_10_10_2:
            return GL_UNSIGNED_INT_10_10_10_2;
        case EPixelDataType::UNSIGNED_INT_2_10_10_10_REV:
            return GL_UNSIGNED_INT_2_10_10_10_REV;
        }

        return GL_INVALID_ENUM;
    }

    GLenum OpenGLAPI::ToGLEnum(const EPrimitiveType primitiveType)
    {
        switch (primitiveType)
        {
        case EPrimitiveType::POINTS:
            return GL_POINTS;
        case EPrimitiveType::LINES:
            return GL_LINES;
        case EPrimitiveType::LINE_LOOP:
            return GL_LINE_LOOP;
        case EPrimitiveType::LINE_STRIP:
            return GL_LINE_STRIP;
        case EPrimitiveType::TRIANGLES:
            return GL_TRIANGLES;
        case EPrimitiveType::TRIANGLE_STRIP:
            return GL_TRIANGLE_STRIP;
        case EPrimitiveType::TRIANGLE_FAN:
            return GL_TRIANGLE_FAN;
        case EPrimitiveType::LINES_ADJACENCY:
            return GL_LINES_ADJACENCY;
        case EPrimitiveType::LINE_STRIP_ADJACENCY:
            return GL_LINE_STRIP_ADJACENCY;
        case EPrimitiveType::TRIANGLES_ADJACENCY:
            return GL_TRIANGLES_ADJACENCY;
        case EPrimitiveType::TRIANGLE_STRIP_ADJACENCY:
            return GL_TRIANGLE_STRIP_ADJACENCY;
        case EPrimitiveType::PATCHES:
            return GL_PATCHES;
        }

        return GL_INVALID_ENUM;
    }

    GLenum OpenGLAPI::ToGLEnum(const ERenderingCapability capability)
    {
        switch (capability)
        {
        case ERenderingCapability::BLEND:
            return GL_BLEND;
        case ERenderingCapability::CULL_FACE:
            return GL_CULL_FACE;
        case ERenderingCapability::DEPTH_TEST:
            return GL_DEPTH_TEST;
        case ERenderingCapability::DITHER:
            return GL_DITHER;
        case ERenderingCapability::POLYGON_OFFSET_FILL:
            return GL_POLYGON_OFFSET_FILL;
        case ERenderingCapability::SAMPLE_ALPHA_TO_COVERAGE:
            return GL_SAMPLE_ALPHA_TO_COVERAGE;
        case ERenderingCapability::SAMPLE_COVERAGE:
            return GL_SAMPLE_COVERAGE;
        case ERenderingCapability::SCISSOR_TEST:
            return GL_SCISSOR_TEST;
        case ERenderingCapability::STENCIL_TEST:
            return GL_STENCIL_TEST;
        case ERenderingCapability::MULTISAMPLE:
            return GL_MULTISAMPLE;
        }

        return GL_INVALID_ENUM;
    }

    GLenum OpenGLAPI::ToGLEnum(const ECompareAlgorithm algorithm)
    {
        switch (algorithm)
        {
        case ECompareAlgorithm::NEVER:
            return GL_NEVER;
        case ECompareAlgorithm::LESS:
            return GL_LESS;
        case ECompareAlgorithm::EQUAL:
            return GL_EQUAL;
        case ECompareAlgorithm::LESS_EQUAL:
            return GL_LEQUAL;
        case ECompareAlgorithm::GREATER:
            return GL_GREATER;
        case ECompareAlgorithm::NOT_EQUAL:
            return GL_NOTEQUAL;
        case ECompareAlgorithm::GREATER_EQUAL:
            return GL_GEQUAL;
        case ECompareAlgorithm::ALWAYS:
            return GL_ALWAYS;
        }

        return GL_INVALID_ENUM;
    }

    GLenum OpenGLAPI::ToGLEnum(const ECullFace cullFace)
    {
        switch (cullFace)
        {
        case ECullFace::FRONT:
            return GL_FRONT;
        case ECullFace::BACK:
            return GL_BACK;
        case ECullFace::FRONT_AND_BACK:
            return GL_FRONT_AND_BACK;
        }

        return GL_INVALID_ENUM;
    }

    GLenum OpenGLAPI::ToGLEnum(const EBlendFactor blendFactor)
    {
        switch (blendFactor)
        {
        case EBlendFactor::ZERO:
            return GL_ZERO;
        case EBlendFactor::ONE:
            return GL_ONE;
        case EBlendFactor::SRC_COLOR:
            return GL_SRC_COLOR;
        case EBlendFactor::ONE_MINUS_SRC_COLOR:
            return GL_ONE_MINUS_SRC_COLOR;
        case EBlendFactor::SRC_ALPHA:
            return GL_SRC_ALPHA;
        case EBlendFactor::ONE_MINUS_SRC_ALPHA:
            return GL_ONE_MINUS_SRC_ALPHA;
        case EBlendFactor::DST_ALPHA:
            return GL_DST_ALPHA;
        case EBlendFactor::ONE_MINUS_DST_ALPHA:
            return GL_ONE_MINUS_DST_ALPHA;
        case EBlendFactor::DST_COLOR:
            return GL_DST_COLOR;
        case EBlendFactor::ONE_MINUS_DST_COLOR:
            return GL_ONE_MINUS_DST_COLOR;
        case EBlendFactor::CONSTANT_COLOR:
            return GL_CONSTANT_COLOR;
        case EBlendFactor::ONE_MINUS_CONSTANT_COLOR:
            return GL_ONE_MINUS_CONSTANT_COLOR;
        case EBlendFactor::CONSTANT_ALPHA:
            return GL_CONSTANT_ALPHA;
        case EBlendFactor::ONE_MINUS_CONSTANT_ALPHA:
            return GL_ONE_MINUS_CONSTANT_ALPHA;
        }

        return GL_INVALID_ENUM;
    }

    GLenum OpenGLAPI::ToGLEnum(const EAccessMode accessSpecifier)
    {
        switch (accessSpecifier)
        {
        case EAccessMode::STREAM_DRAW:
            return GL_STREAM_DRAW;
        case EAccessMode::STREAM_READ:
            return GL_STREAM_READ;
        case EAccessMode::STREAM_COPY:
            return GL_STREAM_COPY;
        case EAccessMode::DYNAMIC_DRAW:
            return GL_DYNAMIC_DRAW;
        case EAccessMode::DYNAMIC_READ:
            return GL_DYNAMIC_READ;
        case EAccessMode::DYNAMIC_COPY:
            return GL_DYNAMIC_COPY;
        case EAccessMode::STATIC_DRAW:
            return GL_STATIC_DRAW;
        case EAccessMode::STATIC_READ:
            return GL_STATIC_READ;
        case EAccessMode::STATIC_COPY:
            return GL_STATIC_COPY;
        default:
            ASSERT(false, "Invalid access specifier");
            return GL_INVALID_ENUM;
        }
    }

    OpenGLAPI& OpenGLAPI::Init(const bool enableDebug)
    {
        ASSERT(gladLoadGL(glfwGetProcAddress), "Failed to initialize GLAD");

        if (enableDebug)
        {
            GLint flags = 0;
            glGetIntegerv(GL_CONTEXT_FLAGS, &flags);

            if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
            {
                glEnable(GL_DEBUG_OUTPUT);
                glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
                glDebugMessageCallback(glDebugOutput, nullptr);
                glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
            }
        }

        return *this;
    }

    OpenGLAPI& OpenGLAPI::Clear(const bool clearColor, const bool clearDepth, const bool clearStencil)
    {
        glClear
        (
            (clearColor ? GL_COLOR_BUFFER_BIT : 0) |
            (clearDepth ? GL_DEPTH_BUFFER_BIT : 0) |
            (clearStencil ? GL_STENCIL_BUFFER_BIT : 0)
        );

        return *this;
    }

    OpenGLAPI& OpenGLAPI::ReadPixels(const PosT&          position, const DimensionsT& size, const EPixelDataFormat dataFormat,
                                     const EPixelDataType dataType, void*              out)
    {
        glReadPixels(position.m_x, position.m_y, size.m_x, size.m_y, ToGLEnum(dataFormat), ToGLEnum(dataType), out);
        return *this;
    }

    OpenGLAPI& OpenGLAPI::DrawElements(const EPrimitiveType primitiveType, const uint32_t indexCount)
    {
        glDrawElements(ToGLEnum(primitiveType), static_cast<GLsizei>(indexCount), GL_UNSIGNED_INT, nullptr);
        return *this;
    }

    OpenGLAPI& OpenGLAPI::DrawElementsInstanced(const EPrimitiveType primitiveType, const uint32_t indexCount,
                                                const uint32_t       instances)
    {
        glDrawElementsInstanced(ToGLEnum(primitiveType), static_cast<GLsizei>(indexCount), GL_UNSIGNED_INT, nullptr,
            static_cast<GLsizei>(instances));
        return *this;
    }

    OpenGLAPI& OpenGLAPI::DrawArrays(const EPrimitiveType primitiveType, const uint32_t vertexCount)
    {
        glDrawArrays(ToGLEnum(primitiveType), 0, static_cast<GLsizei>(vertexCount));
        return *this;
    }

    OpenGLAPI& OpenGLAPI::DrawArraysInstanced(const EPrimitiveType primitiveType, const uint32_t vertexCount,
                                              const uint32_t       instances)
    {
        glDrawArraysInstanced(ToGLEnum(primitiveType), 0, static_cast<GLsizei>(vertexCount), static_cast<GLsizei>(instances));
        return *this;
    }

    OpenGLAPI& OpenGLAPI::SetCapability(const ERenderingCapability capability, const bool enable)
    {
        (enable ? glEnable : glDisable)(ToGLEnum(capability));
        return *this;
    }

    bool OpenGLAPI::HasCapability(const ERenderingCapability capability)
    {
        return glIsEnabled(ToGLEnum(capability));
    }

    OpenGLAPI& OpenGLAPI::SetDepthAlgorithm(const ECompareAlgorithm algorithm)
    {
        glDepthFunc(ToGLEnum(algorithm));
        return *this;
    }

    OpenGLAPI& OpenGLAPI::SetStencilAlgorithm(const ECompareAlgorithm algorithm, const int32_t reference, const uint32_t mask)
    {
        glStencilFunc(ToGLEnum(algorithm), reference, mask);
        return *this;
    }

    OpenGLAPI& OpenGLAPI::SetClearColor(const Color& color)
    {
        glClearColor(color.m_r, color.m_g, color.m_b, color.m_a);
        return *this;
    }

    Color OpenGLAPI::GetClearColor()
    {
        Color clearColor;
        glGetFloatv(GL_COLOR_CLEAR_VALUE, &clearColor.m_r);

        return clearColor;
    }

    OpenGLAPI& OpenGLAPI::SetCullFace(const ECullFace cullFace)
    {
        glCullFace(ToGLEnum(cullFace));
        return *this;
    }

    OpenGLAPI& OpenGLAPI::SetDepthWriting(const bool enable)
    {
        glDepthMask(enable);
        return *this;
    }

    OpenGLAPI& OpenGLAPI::SetColorWriting(const bool enableRed, const bool enableGreen, const bool enableBlue,
                                          const bool enableAlpha)
    {
        glColorMask(enableRed, enableGreen, enableBlue, enableAlpha);
        return *this;
    }

    OpenGLAPI& OpenGLAPI::SetBlendFunc(const EBlendFactor sourceFactor, const EBlendFactor destinationFactor)
    {
        glBlendFunc(ToGLEnum(sourceFactor), ToGLEnum(destinationFactor));
        return *this;
    }

    OpenGLAPI& OpenGLAPI::SetViewport(const PosT position, const DimensionsT size)
    {
        glViewport(position.m_x, position.m_y, size.m_x, size.m_y);
        return *this;
    }

    EGraphicsAPI OpenGLAPI::GetBackend()
    {
        return EGraphicsAPI::OPENGL;
    }

    std::string OpenGLAPI::GetVendor()
    {
        return GetGLString(GL_VENDOR);
    }

    std::string OpenGLAPI::GetHardware()
    {
        return GetGLString(GL_RENDERER);
    }

    std::string OpenGLAPI::GetVersion()
    {
        return GetGLString(GL_VERSION);
    }

    std::string OpenGLAPI::GetShadingLanguageVersion()
    {
        return GetGLString(GL_SHADING_LANGUAGE_VERSION);
    }
}
