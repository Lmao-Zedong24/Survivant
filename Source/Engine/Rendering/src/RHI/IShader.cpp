#include "SurvivantRendering/RHI/IShader.h"

#include "SurvivantRendering/RHI/IRenderAPI.h"
#include "SurvivantRendering/RHI/OpenGL/OpenGLShader.h"

#include <SurvivantCore/Debug/Assertion.h>
#include <SurvivantCore/Debug/Logger.h>
#include <SurvivantCore/Utility/utility.h>

using namespace SvCore::Utility;
using namespace SvRendering::Enums;

using namespace SvRendering::Enums;
using namespace SvRendering::RHI;

namespace SvRendering::RHI
{
    std::string IShader::GetTokenFromType(const EShaderType p_shaderType)
    {
        switch (p_shaderType)
        {
        case EShaderType::VERTEX:
            return "vertex";
        case EShaderType::FRAGMENT:
            return "fragment";
        case EShaderType::GEOMETRY:
            return "geometry";
        case EShaderType::TESSELATION_EVALUATION:
            return "tess_evaluation";
        case EShaderType::TESSELATION_CONTROL:
            return "tess_control";
        case EShaderType::COMPUTE:
            return "compute";
        case EShaderType::UNKNOWN:
        default:
            return "unknown";
        }
    }

    const std::unordered_map<std::string, IShader::UniformInfo>& IShader::GetUniforms() const
    {
        return m_uniforms;
    }

    std::shared_ptr<IShader> IShader::Create()
    {
        switch (IRenderAPI::GetCurrent().GetBackend())
        {
        case EGraphicsAPI::OPENGL:
            return std::make_shared<OpenGLShader>();
        case EGraphicsAPI::NONE:
        default:
            ASSERT(false, "Failed to create shader - Unsupported graphics api");
            return {};
        }
    }

    EShaderType IShader::GetTypeFromToken(std::string p_shaderType)
    {
        ToLowerInPlace(p_shaderType);

        if (p_shaderType == "vertex" || p_shaderType == "vert" || p_shaderType == "vs")
            return EShaderType::VERTEX;

        if (p_shaderType == "fragment" || p_shaderType == "frag" || p_shaderType == "fs")
            return EShaderType::FRAGMENT;

        if (p_shaderType == "geometry" || p_shaderType == "geo" || p_shaderType == "gs")
            return EShaderType::GEOMETRY;

        if (p_shaderType == "tesselation_evaluation" || p_shaderType == "tess_evaluation" || p_shaderType == "tes"
            || p_shaderType == "tesselation_eval" || p_shaderType == "tess_eval")
            return EShaderType::TESSELATION_EVALUATION;

        if (p_shaderType == "tesselation_control" || p_shaderType == "tess_control" || p_shaderType == "tcs"
            || p_shaderType == "tesselation_ctrl" || p_shaderType == "tess_ctrl")
            return EShaderType::TESSELATION_CONTROL;

        if (p_shaderType == "compute" || p_shaderType == "com" || p_shaderType == "cs")
            return EShaderType::COMPUTE;

        return EShaderType::UNKNOWN;
    }
}
