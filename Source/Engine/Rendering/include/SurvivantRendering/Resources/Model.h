#pragma once
#include "SurvivantRendering/Geometry/BoundingBox.h"
#include "SurvivantRendering/Resources/Mesh.h"

#include <SurvivantCore/Resources/IResource.h>

#include <string>
#include <vector>

namespace SvRendering::Resources
{
    class Model final : public SvCore::Resources::IResource
    {
    public:
        /**
         * \brief Creates an empty model
         */
        Model();

        /**
         * \brief Creates a model with the given meshes
         * \param p_meshes The model's meshes
         */
        Model(std::vector<Mesh> p_meshes);

        /**
         * \brief Creates a copy of the given model
         * \param p_other The model to copy
         */
        Model(const Model& p_other) = default;

        /**
         * \brief Creates a move copy of the given model
         * \param p_other The model to move
         */
        Model(Model&& p_other) noexcept = default;

        /**
         * \brief Destroys the model
         */
        ~Model() override = default;

        /**
         * \brief Assigns a copy of the given model to this one
         * \param p_other The model to copy
         * \return A reference to the modified model
         */
        Model& operator=(const Model& p_other) = default;

        /**
         * \brief Moves the given model into this one
         * \param p_other The moved model
         * \return A reference to the modified model
         */
        Model& operator=(Model&& p_other) noexcept = default;

        /**
         * \brief Loads the model from the given file
         * \param p_path The path of the model to load
         * \return True if the model was successfully loaded. False otherwise.
         */
        bool Load(const std::string& p_path) override;

        /**
         * \brief Initializes the model
         * \return True if the model was successfully initialized. False otherwise.
         */
        bool Init() override;

        /**
         * \brief Gets the model's mesh at the given index
         * \return The model's mesh at the given index
         * \param p_index The target mesh's index
         */
        const Mesh& GetMesh(size_t p_index) const;

        /**
         * \brief Gets the number of meshes composing the model
         * \return The model's mesh count
         */
        size_t GetMeshCount() const;

        /**
         * \brief Gets the mesh's bounding box
         * \return The mesh's bounding box
         */
        Geometry::BoundingBox GetBoundingBox() const;

    private:
        std::vector<Mesh>     m_meshes;
        Geometry::BoundingBox m_boundingBox;
    };
}
