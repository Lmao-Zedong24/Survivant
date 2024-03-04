#pragma once
#include "SurvivantRendering/Enums/EAccessMode.h"
#include "SurvivantRendering/RHI/IRenderAPI.h"

namespace SvRendering::RHI
{
    class OpenGLAPI final : public IRenderAPI
    {
    public:
        ~OpenGLAPI() override = default;

        OpenGLAPI& Init(bool p_enableDebug) override;

        OpenGLAPI& Clear(bool p_clearColor, bool p_clearDepth, bool p_clearStencil) override;

        OpenGLAPI& ReadPixels(const PosT&           p_position, const DimensionsT& p_size, Enums::EPixelDataFormat p_dataFormat,
                              Enums::EPixelDataType p_dataType, void*              p_out) override;

        OpenGLAPI& DrawElements(Enums::EPrimitiveType p_primitiveType, uint32_t p_indexCount) override;
        OpenGLAPI& DrawElementsInstanced(Enums::EPrimitiveType p_primitiveType, uint32_t p_indexCount,
                                         uint32_t              p_instances) override;

        OpenGLAPI& DrawArrays(Enums::EPrimitiveType p_primitiveType, uint32_t p_vertexCount) override;
        OpenGLAPI& DrawArraysInstanced(Enums::EPrimitiveType p_primitiveType, uint32_t p_vertexCount,
                                       uint32_t              p_instances) override;

        OpenGLAPI& SetCapability(Enums::ERenderingCapability p_capability, bool p_enable) override;
        bool       HasCapability(Enums::ERenderingCapability p_capability) override;

        OpenGLAPI& SetDepthAlgorithm(Enums::ECompareAlgorithm p_algorithm) override;
        OpenGLAPI& SetStencilAlgorithm(Enums::ECompareAlgorithm p_algorithm, int32_t p_reference, uint32_t p_mask) override;

        OpenGLAPI&  SetClearColor(const Core::Color& p_color) override;
        Core::Color GetClearColor() override;

        OpenGLAPI& SetCullFace(Enums::ECullFace p_cullFace) override;

        OpenGLAPI& SetDepthWriting(bool p_enable) override;
        OpenGLAPI& SetColorWriting(bool p_enableRed, bool p_enableGreen, bool p_enableBlue, bool p_enableAlpha) override;

        OpenGLAPI& SetBlendFunc(Enums::EBlendFactor p_sourceFactor, Enums::EBlendFactor p_destinationFactor) override;

        OpenGLAPI& SetViewport(PosT p_position, DimensionsT p_size) override;

        EGraphicsAPI GetBackend() override;

        std::string GetVendor() override;
        std::string GetHardware() override;
        std::string GetVersion() override;
        std::string GetShadingLanguageVersion() override;

        static unsigned ToGLEnum(Enums::EPixelDataFormat p_dataFormat);
        static unsigned ToGLEnum(Enums::EPixelDataType p_dataType);
        static unsigned ToGLEnum(Enums::EPrimitiveType p_primitiveType);
        static unsigned ToGLEnum(Enums::ERenderingCapability p_capability);
        static unsigned ToGLEnum(Enums::ECompareAlgorithm p_algorithm);
        static unsigned ToGLEnum(Enums::ECullFace p_cullFace);
        static unsigned ToGLEnum(Enums::EBlendFactor p_blendFactor);
        static unsigned ToGLEnum(Enums::EAccessMode p_accessMode);
    };
}
