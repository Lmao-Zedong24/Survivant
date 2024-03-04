#pragma once
#include "SurvivantRendering/Core/Color.h"
#include "SurvivantRendering/Enums/EBlendFactor.h"
#include "SurvivantRendering/Enums/ECompareAlgorithm.h"
#include "SurvivantRendering/Enums/ECullFace.h"
#include "SurvivantRendering/RHI/EGraphicsAPI.h"
#include "SurvivantRendering/Enums/EPixelDataFormat.h"
#include "SurvivantRendering/Enums/EPixelDataType.h"
#include "SurvivantRendering/Enums/EPrimitiveType.h"
#include "SurvivantRendering/Enums/ERenderingCapability.h"

#include <Vector/Vector2.h>

#include <string>

namespace SvRendering::RHI
{
    using PosT = LibMath::Vector2I;
    using DimensionsT = LibMath::Vector2I;

    class IRenderAPI
    {
    public:
        virtual ~IRenderAPI() = default;

        /**
         * \brief Initializes the graphics API
         * \param p_enableDebug Whether debugging should be enabled or not
         * \return A reference to the current API
         */
        virtual IRenderAPI& Init(bool p_enableDebug) = 0;

        /**
         * \brief Clears the selected buffers
         * \param p_clearColor Whether the color buffer should be cleared
         * \param p_clearDepth Whether the depth buffer should be cleared
         * \param p_clearStencil Whether the stencil buffer should be cleared
         * \return A reference to the current API
         */
        virtual IRenderAPI& Clear(bool p_clearColor, bool p_clearDepth, bool p_clearStencil) = 0;

        /**
         * \brief Reads pixels into the given buffer
         * \param p_position The position of the pixels to read
         * \param p_size The size of the area to read
         * \param p_dataFormat The format in which the pixels should be read
         * \param p_dataType The data type of the pixels to read
         * \param p_out The buffer in which to read pixels
         * \return A reference to the current API
         */
        virtual IRenderAPI& ReadPixels(const PosT& p_position, const DimensionsT& p_size, Enums::EPixelDataFormat p_dataFormat,
                                       Enums::EPixelDataType p_dataType, void* p_out) = 0;

        /**
         * \brief Draws the given number of indices
         * \param p_primitiveType The target primitive draw mode
         * \param p_count The number of elements to draw
         * \return A reference to the current API
         */
        virtual IRenderAPI& DrawElements(Enums::EPrimitiveType p_primitiveType, uint32_t p_count) = 0;

        /**
         * \brief Draws the given number of instances of a model with the given number of indices
         * \param p_primitiveType The target primitive draw mode
         * \param p_count The number of elements to draw
         * \param p_instances The number of instances to draw
         * \return A reference to the current API
         */
        virtual IRenderAPI& DrawElementsInstanced(Enums::EPrimitiveType p_primitiveType, uint32_t p_count, uint32_t p_instances) =
        0;

        /**
         * \brief Draws the given number of vertices
         * \param p_primitiveType The target primitive draw mode
         * \param p_count The number of vertices to draw
         * \return A reference to the current API
         */
        virtual IRenderAPI& DrawArrays(Enums::EPrimitiveType p_primitiveType, uint32_t p_count) = 0;

        /**
         * \brief Draws the given number of instances of a model with the given number of vertices
         * \param p_primitiveType The target primitive draw mode
         * \param p_count The number of vertices to draw
         * \param p_instances The number of instances to draw
         * \return A reference to the current API
         */
        virtual IRenderAPI& DrawArraysInstanced(Enums::EPrimitiveType p_primitiveType, uint32_t p_count, uint32_t p_instances) = 0;

        /**
         * \brief Sets the state of the given rendering capability
         * \param p_capability The rendering capability of which state should be changed
         * \param p_enable Whether the rendering capability should be enabled
         * \return A reference to the current API
         */
        virtual IRenderAPI& SetCapability(Enums::ERenderingCapability p_capability, bool p_enable) = 0;

        /**
         * \brief Checks whether a rendering capability is enabled or not
         * \param p_capability The rendering capability to check
         * \return True if the target rendering capability is enabled. False otherwise
         */
        virtual bool HasCapability(Enums::ERenderingCapability p_capability) = 0;

        /**
         * \brief Sets the sorting algorithm for depth testing
         * \param p_algorithm The new depth algorithm
         * \return A reference to the current API
         */
        virtual IRenderAPI& SetDepthAlgorithm(Enums::ECompareAlgorithm p_algorithm) = 0;

        /**
         * \brief Sets the sorting algorithm and reference value for stencil testing
         * \param p_algorithm The new stencil test algorithm
         * \param p_reference The reference value
         * \param p_mask The stencil mask
         * \return A reference to the current API
         */
        virtual IRenderAPI& SetStencilAlgorithm(Enums::ECompareAlgorithm p_algorithm, int32_t p_reference, uint32_t p_mask) = 0;

        /**
         * \brief Sets the clear color
         * \param p_color The new clear color
         * \return A reference to the current API
         */
        virtual IRenderAPI& SetClearColor(const Core::Color& p_color) = 0;

        /**
         * \brief Gets the current clear color
         * \return The background clear color
         */
        virtual Core::Color GetClearColor() = 0;

        /**
         * \brief Sets which face(s) should be culled
         * \param p_cullFace The new cull face
         * \return A reference to the current API
         */
        virtual IRenderAPI& SetCullFace(Enums::ECullFace p_cullFace) = 0;

        /**
         * \brief Enables/disables depth writing
         * \param p_enable Whether depth writing should be enabled or not
         * \return A reference to the current API
         */
        virtual IRenderAPI& SetDepthWriting(bool p_enable) = 0;

        /**
         * \brief Sets whether writing in the different color channels should be allowed or not
         * \param p_enableRed Whether writing in the red color channel should be allowed
         * \param p_enableGreen Whether writing in the green color channel should be allowed
         * \param p_enableBlue Whether writing in the blue color channel should be allowed
         * \param p_enableAlpha Whether writing in the alpha color channel should be allowed
         * \return A reference to the current API
         */
        virtual IRenderAPI& SetColorWriting(bool p_enableRed, bool p_enableGreen, bool p_enableBlue, bool p_enableAlpha) = 0;

        /**
         * \brief Sets the source and destination blending factors
         * \param p_sourceFactor The blending factor to apply to the source color
         * \param p_destinationFactor The blending factor to apply to the destination color
         * \return A reference to the current API
         */
        virtual IRenderAPI& SetBlendFunc(Enums::EBlendFactor p_sourceFactor, Enums::EBlendFactor p_destinationFactor) = 0;

        /**
         * \brief Sets the viewport's position and size
         * \param p_position The new viewport's position
         * \param p_size The new viewport's size
         * \return A reference to the current API
         */
        virtual IRenderAPI& SetViewport(PosT p_position, DimensionsT p_size) = 0;

        /**
         * \brief Gets the used graphics API
         * \return The current graphics API
         */
        virtual EGraphicsAPI GetBackend() = 0;

        /**
         * \brief Gets the name of the vendor for the current API implementation
         * \return The name of the vendor for the current API implementation
         */
        virtual std::string GetVendor() = 0;

        /**
         * \brief Gets the current hardware's information
         * \return The current hardware string
         */
        virtual std::string GetHardware() = 0;

        /**
         * \brief Gets the rendering API's current version
         * \return The API's current version
         */
        virtual std::string GetVersion() = 0;

        /**
         * \brief Gets the rendering API's shading language version
         * \return The shading language version
         */
        virtual std::string GetShadingLanguageVersion() = 0;

        /**
         * \brief Gets the current render api
         * \return A reference to the current render api
         */
        inline static IRenderAPI& GetCurrent();

        /**
         * \brief Sets the current render api from the given backend
         * \param p_backend The target graphics backend
         * \return A reference to the current render api
         */
        static IRenderAPI& SetCurrent(EGraphicsAPI p_backend);

    private:
        static std::unique_ptr<IRenderAPI> s_instance;
    };
}

#include "SurvivantRendering/RHI/IRenderAPI.inl"
