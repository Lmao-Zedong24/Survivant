#pragma once
#include "SurvivantRendering/Enums/EAccessMode.h"
#include "SurvivantRendering/RHI/IRenderAPI.h"

namespace SvRendering::RHI
{
    class OpenGLAPI final : public IRenderAPI
    {
    public:
        ~OpenGLAPI() override = default;

        OpenGLAPI& Init(bool enableDebug) override;

        OpenGLAPI& Clear(bool clearColor, bool clearDepth, bool clearStencil) override;

        OpenGLAPI& ReadPixels(const PosT&           position, const DimensionsT& size, Enums::EPixelDataFormat dataFormat,
                              Enums::EPixelDataType dataType, void*              out) override;

        OpenGLAPI& DrawElements(Enums::EPrimitiveType primitiveType, uint32_t indexCount) override;
        OpenGLAPI& DrawElementsInstanced(Enums::EPrimitiveType primitiveType, uint32_t indexCount, uint32_t instances) override;

        OpenGLAPI& DrawArrays(Enums::EPrimitiveType primitiveType, uint32_t vertexCount) override;
        OpenGLAPI& DrawArraysInstanced(Enums::EPrimitiveType primitiveType, uint32_t vertexCount, uint32_t instances) override;

        OpenGLAPI& SetCapability(Enums::ERenderingCapability capability, bool enable) override;
        bool       HasCapability(Enums::ERenderingCapability capability) override;

        OpenGLAPI& SetDepthAlgorithm(Enums::ECompareAlgorithm algorithm) override;
        OpenGLAPI& SetStencilAlgorithm(Enums::ECompareAlgorithm algorithm, int32_t reference, uint32_t mask) override;

        OpenGLAPI&  SetClearColor(const Core::Color& color) override;
        Core::Color GetClearColor() override;

        OpenGLAPI& SetCullFace(Enums::ECullFace cullFace) override;

        OpenGLAPI& SetDepthWriting(bool enable) override;
        OpenGLAPI& SetColorWriting(bool enableRed, bool enableGreen, bool enableBlue, bool enableAlpha) override;

        OpenGLAPI& SetBlendFunc(Enums::EBlendFactor sourceFactor, Enums::EBlendFactor destinationFactor) override;

        OpenGLAPI& SetViewport(PosT position, DimensionsT size) override;

        EGraphicsAPI GetBackend() override;

        std::string GetVendor() override;
        std::string GetHardware() override;
        std::string GetVersion() override;
        std::string GetShadingLanguageVersion() override;

        static unsigned ToGLEnum(Enums::EPixelDataFormat dataFormat);
        static unsigned ToGLEnum(Enums::EPixelDataType dataType);
        static unsigned ToGLEnum(Enums::EPrimitiveType primitiveType);
        static unsigned ToGLEnum(Enums::ERenderingCapability capability);
        static unsigned ToGLEnum(Enums::ECompareAlgorithm algorithm);
        static unsigned ToGLEnum(Enums::ECullFace cullFace);
        static unsigned ToGLEnum(Enums::EBlendFactor blendFactor);
        static unsigned ToGLEnum(Enums::EAccessMode accessSpecifier);
    };
}
