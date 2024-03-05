#pragma once
#include "SurvivantRendering/Geometry/Vertex.h"
#include "SurvivantRendering/Geometry/BoundingBox.h"
#include "SurvivantRendering/RHI/IVertexArray.h"

#include <vector>

namespace SvRendering::Resources
{
    class Mesh
    {
    public:
        /**
         * \brief Creates a mesh with the given vertices and indices
         * \param p_vertices The mesh's vertices
         * \param p_indices The mesh's indices
         */
        Mesh(std::vector<Geometry::Vertex> p_vertices, std::vector<uint32_t> p_indices);

        /**
         * \brief Creates a copy of the given mesh
         * \param p_other The mesh to copy
         */
        Mesh(const Mesh& p_other);

        /**
         * \brief Creates a move copy of the given mesh
         * \param p_other The mesh to move
         */
        Mesh(Mesh&& p_other) noexcept = default;

        /**
         * \brief Destroys the mesh
         */
        ~Mesh() = default;

        /**
         * \brief Assigns a copy of the given mesh to this one
         * \param p_other The mesh to copy
         * \return A reference to the modified mesh
         */
        Mesh& operator=(const Mesh& p_other);

        /**
         * \brief Moves the given mesh into this one
         * \param p_other The moved mesh
         * \return A reference to the modified mesh
         */
        Mesh& operator=(Mesh&& p_other) noexcept = default;

        /**
         * \brief Initializes the mesh
         * \return True if the mesh was successfully initialized. False otherwise.
         */
        bool Init();

        /**
         * \brief Binds the mesh's buffers
         */
        void Bind() const;

        /**
         * \brief Unbinds the mesh's buffers
         */
        void Unbind() const;

        /**
         * \brief Gets the mesh's element count
         * \return The mesh's number of indices
         */
        uint32_t GetIndexCount() const;

        /**
         * \brief Gets the mesh's bounding box
         * \return The mesh's bounding box
         */
        Geometry::BoundingBox GetBoundingBox() const;

    private:
        std::vector<Geometry::Vertex> m_vertices;
        std::vector<uint32_t>         m_indices;

        Geometry::BoundingBox m_boundingBox;

        std::unique_ptr<RHI::IVertexBuffer> m_vbo;
        std::unique_ptr<RHI::IIndexBuffer>  m_ebo;
        std::unique_ptr<RHI::IVertexArray>  m_vao;
    };
}
