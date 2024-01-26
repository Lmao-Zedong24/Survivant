#include <Transform.h>

#include <Angle/Degree.h>

#define GLM_ENABLE_EXPERIMENTAL
#define GLM_FORCE_XYZW_ONLY

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

#include <glm/glm.hpp>
#include <glm/detail/type_quat.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtc/quaternion.hpp>

using namespace LibMath::Literal;

#define CHECK_MATRIX(matrix, matrixGlm)                                                 \
    for (LibMath::length_t i = 0; i < (matrix).getRowCount(); i++)                      \
        for(LibMath::length_t j = 0; j < (matrix).getColumnCount(); j++)                \
            CHECK((matrix)[(matrix).getIndex(i, j)] == Catch::Approx((matrixGlm)[i][j]))

#define CHECK_LOCAL_TRANSFORM(transform, position, rotation, scale, matrix) \
    CHECK((transform).getPosition() == (position));                         \
    CHECK((transform).getRotation() == (rotation));                         \
    CHECK((transform).getScale() == (scale));                               \
    CHECK_MATRIX((transform).getMatrix(), glm::transpose(matrix));

#define CHECK_WORLD_TRANSFORM(transform, position, rotation, scale, matrix) \
    CHECK((transform).getWorldPosition() == (position));                    \
    CHECK((transform).getWorldRotation() == (rotation));                    \
    CHECK((transform).getWorldScale() == (scale));                          \
    CHECK_MATRIX((transform).getWorldMatrix(), glm::transpose(matrix));

#define CHECK_TRANSFORM(transform, position, rotation, scale, matrix)   \
    CHECK_LOCAL_TRANSFORM(transform, position, rotation, scale, matrix) \
    CHECK_WORLD_TRANSFORM(transform, position, rotation, scale, matrix)

void decomposeGlm(const glm::mat4& matGlm, LibMath::Vector3& pos, LibMath::Quaternion& rot, LibMath::Vector3& scale)
{
    pos = { matGlm[3].x, matGlm[3].y, matGlm[3].z };

    const glm::vec3 mat0 = glm::vec3(matGlm[0]);
    const glm::vec3 mat1 = glm::vec3(matGlm[1]);
    const glm::vec3 mat2 = glm::vec3(matGlm[2]);

    scale = {
        glm::length(mat0),
        glm::length(mat1),
        glm::length(mat2)
    };

    const glm::mat3 rotMtx(
        mat0 / scale[0],
        mat1 / scale[1],
        mat2 / scale[2]
    );

    const glm::quat rotGlm = glm::quat_cast(rotMtx);
    rot = { rotGlm.w, rotGlm.x, rotGlm.y, rotGlm.z };
}

TEST_CASE("Transform", "[.all][transform]")
{
    const LibMath::Vector3 position{ 2.5f, .5f, 2.f };
    constexpr glm::vec3    positionGlm{ 2.5f, .5f, 2.f };

    const LibMath::TVector3<LibMath::Radian> angles{ 45_deg, 30_deg, 65_deg };

    const LibMath::Quaternion rotation{ angles };
    const glm::quat           rotationGlm{ glm::yawPitchRoll(glm::radians(45.f), glm::radians(30.f), glm::radians(65.f)) };
    const glm::quat           rotationMatGlm{ glm::mat4_cast(rotationGlm) };

    const LibMath::Vector3 scale{ 3.f, .75f, 3.75f };
    constexpr glm::vec3    scaleGlm{ 3.f, .75f, 3.75f };

    const LibMath::Matrix4 matrix = LibMath::translation(position) * LibMath::rotation(rotation) * LibMath::scaling(scale);

    const LibMath::Vector3 positionOther{ 4.5f, .9f, 5.4f };
    constexpr glm::vec3    positionOtherGlm{ 4.5f, .9f, 5.4f };

    const LibMath::Quaternion rotationOther{ 60_deg, 25_deg, 80_deg };
    const glm::quat           rotationOtherGlm{ glm::yawPitchRoll(glm::radians(60.f), glm::radians(25.f), glm::radians(80.f)) };

    const LibMath::Vector3 scaleOther{ 8.4f, 2.1f, 10.5f };
    constexpr glm::vec3    scaleOtherGlm{ 8.4f, 2.1f, 10.5f };

    constexpr glm::mat4 idMatGlm{ 1.f };
    const glm::mat4     matrixGlm = glm::translate(idMatGlm, positionGlm) * glm::mat4_cast(rotationGlm) *
        glm::scale(idMatGlm, scaleGlm);
    const glm::mat4 matrixOtherGlm = glm::translate(idMatGlm, positionOtherGlm) * glm::mat4_cast(rotationOtherGlm)
        * glm::scale(idMatGlm, scaleOtherGlm);

    SECTION("Instantiation")
    {
        // default constructor
        LibMath::Transform empty;
        CHECK_TRANSFORM(empty, LibMath::Vector3{}, LibMath::Quaternion::identity(), LibMath::Vector3::one(), idMatGlm);

        // destructor
        {
            [[maybe_unused]] LibMath::Transform temp;
        }

        // basic constructor
        LibMath::Transform allParam(position, rotation, scale);
        CHECK_TRANSFORM(allParam, position, rotation, scale, matrixGlm);

        // euler angles
        LibMath::Transform euler(position, angles, scale);
        CHECK_TRANSFORM(euler, position, rotation, scale, matrixGlm);

        // copy constructor
        LibMath::Transform copy{ allParam };
        CHECK_TRANSFORM(copy, position, rotation, scale, matrixGlm);

        // assignment operator
        empty = allParam;
        CHECK_TRANSFORM(empty, position, rotation, scale, matrixGlm);

        LibMath::Transform fromMat(matrix);
        CHECK_TRANSFORM(fromMat, position, rotation, scale, matrixGlm);
    }

    SECTION("Accessor")
    {
        {
            const LibMath::Transform transform{ position, rotation, scale };

            CHECK(transform.getPosition() == position);
            CHECK(transform.getRotation() == rotation);
            CHECK(transform.getScale() == scale);
            CHECK_MATRIX(transform.getMatrix(), glm::transpose(matrixGlm));

            CHECK(transform.getWorldPosition() == position);
            CHECK(transform.getWorldRotation() == rotation);
            CHECK(transform.getWorldScale() == scale);
            CHECK_MATRIX(transform.getWorldMatrix(), glm::transpose(matrixGlm));
        }

        {
            LibMath::Transform transform{ {}, rotation, scale };
            transform.setPosition(position);
            CHECK_TRANSFORM(transform, position, rotation, scale, matrixGlm);
        }

        {
            LibMath::Transform transform{ position, LibMath::Quaternion(), scale };
            transform.setRotation(rotation);
            CHECK_TRANSFORM(transform, position, rotation, scale, matrixGlm);
        }

        {
            LibMath::Transform transform{ position, rotation, LibMath::Vector3::one() };
            transform.setScale(scale);
            CHECK_TRANSFORM(transform, position, rotation, scale, matrixGlm);
        }

        {
            LibMath::Transform transform{ LibMath::Matrix4(1.f) };
            transform.setAll(position, rotation, scale);
            CHECK_TRANSFORM(transform, position, rotation, scale, matrixGlm);
        }

        {
            LibMath::Transform transform{ LibMath::Matrix4(1.f) };
            transform.setMatrix(matrix);
            CHECK_TRANSFORM(transform, position, rotation, scale, matrixGlm);
        }

        {
            LibMath::Transform transform{ {}, rotation, scale };
            transform.setWorldPosition(position);
            CHECK_TRANSFORM(transform, position, rotation, scale, matrixGlm);
        }

        {
            LibMath::Transform transform{ position, LibMath::Quaternion(), scale };
            transform.setWorldRotation(rotation);
            CHECK_TRANSFORM(transform, position, rotation, scale, matrixGlm);
        }

        {
            LibMath::Transform transform{ position, rotation, LibMath::Vector3::one() };
            transform.setWorldScale(scale);
            CHECK_TRANSFORM(transform, position, rotation, scale, matrixGlm);
        }

        {
            LibMath::Transform transform{ LibMath::Matrix4(1.f) };
            transform.setAllWorld(position, rotation, scale);
            CHECK_TRANSFORM(transform, position, rotation, scale, matrixGlm);
        }

        {
            LibMath::Transform transform{ LibMath::Matrix4(1.f) };
            transform.setWorldMatrix(matrix);
            CHECK_TRANSFORM(transform, position, rotation, scale, matrixGlm);
        }
    }

    SECTION("Arithmetic")
    {
        const LibMath::Transform base{ position, rotation, scale };
        const LibMath::Transform other{ positionOther, rotationOther, scaleOther };

        SECTION("Multiplication")
        {
            glm::mat4 productGlm = matrixGlm * matrixOtherGlm;

            LibMath::Vector3    productPos, productScale;
            LibMath::Quaternion productRot;

            decomposeGlm(productGlm, productPos, productRot, productScale);

            {
                LibMath::Transform productAssignment = base;
                productAssignment *= other;

                CHECK_TRANSFORM(productAssignment, productPos, productRot, productScale, productGlm);
            }

            {
                LibMath::Transform product = base * other;

                CHECK_TRANSFORM(product, productPos, productRot, productScale, productGlm);
            }
        }
    }

    SECTION("Functionality")
    {
        const LibMath::Transform base{ position, rotation, scale };
        const LibMath::Transform other{ positionOther, rotationOther, scaleOther };

        SECTION("Inverse")
        {
            LibMath::Transform inverse = base.inverse();
            LibMath::Vector3   invScale = { 1.f / scale.m_x, 1.f / scale.m_y, 1.f / scale.m_z };

            glm::mat4 inverseGlm = glm::translate(idMatGlm, -positionGlm) * glm::mat4_cast(glm::inverse(rotationGlm)) *
                glm::scale(idMatGlm, { 1.f / scaleGlm.x, 1.f / scaleGlm.y, 1.f / scaleGlm.z });

            CHECK_TRANSFORM(inverse, -position, rotation.inverse(), invScale, inverseGlm);
        }

        SECTION("Interpolation")
        {
            constexpr int interpolationSteps = 10;

            {
                // Local transform interpolation
                const LibMath::Transform lerpStartTransform = LibMath::Transform::interpolate(base, other, 0.f);
                CHECK_TRANSFORM(lerpStartTransform, position, rotation, scale, matrixGlm)

                const LibMath::Transform lerpEndTransform = LibMath::Transform::interpolate(base, other, 1.f);
                CHECK_TRANSFORM(lerpEndTransform, positionOther, rotationOther, scaleOther, matrixOtherGlm)

                for (int step = 1; step < interpolationSteps; ++step)
                {
                    const float alpha = static_cast<float>(step) / interpolationSteps;

                    const LibMath::Transform lerpTransform = LibMath::Transform::interpolate(base, other, alpha);

                    const LibMath::Vector3 lerpPos = LibMath::lerp(position, positionOther, alpha);
                    const glm::vec3        lerpPosGlm = glm::lerp(positionGlm, positionOtherGlm, alpha);

                    const LibMath::Quaternion slerpRotation = LibMath::slerp(rotation, rotationOther, alpha);
                    const glm::quat           slerpRotationGlm = glm::slerp(rotationGlm, rotationOtherGlm, alpha);

                    const LibMath::Vector3 lerpScale = LibMath::lerp(scale, scaleOther, alpha);
                    const glm::vec3        lerpScaleGlm = glm::lerp(scaleGlm, scaleOtherGlm, alpha);

                    glm::mat4 lerpMatrixGlm = glm::translate(idMatGlm, lerpPosGlm) * glm::mat4_cast(slerpRotationGlm) *
                        glm::scale(idMatGlm, lerpScaleGlm);

                    CHECK_TRANSFORM(lerpTransform, lerpPos, slerpRotation, lerpScale, lerpMatrixGlm);
                }
            }

            {
                // World transform interpolation
                const LibMath::Transform lerpStartTransform = LibMath::Transform::interpolateWorld(base, other, 0.f);
                CHECK_TRANSFORM(lerpStartTransform, position, rotation, scale, matrixGlm)

                const LibMath::Transform lerpEndTransform = LibMath::Transform::interpolateWorld(base, other, 1.f);
                CHECK_TRANSFORM(lerpEndTransform, positionOther, rotationOther, scaleOther, matrixOtherGlm)

                for (int step = 1; step < interpolationSteps; ++step)
                {
                    const float alpha = static_cast<float>(step) / interpolationSteps;

                    const LibMath::Transform lerpTransform = LibMath::Transform::interpolateWorld(base, other, alpha);

                    const LibMath::Vector3 lerpPos = LibMath::lerp(position, positionOther, alpha);
                    const glm::vec3        lerpPosGlm = glm::lerp(positionGlm, positionOtherGlm, alpha);

                    const LibMath::Quaternion slerpRotation = LibMath::slerp(rotation, rotationOther, alpha);
                    const glm::quat           slerpRotationGlm = glm::slerp(rotationGlm, rotationOtherGlm, alpha);

                    const LibMath::Vector3 lerpScale = LibMath::lerp(scale, scaleOther, alpha);
                    const glm::vec3        lerpScaleGlm = glm::lerp(scaleGlm, scaleOtherGlm, alpha);

                    glm::mat4 lerpMatrixGlm = glm::translate(idMatGlm, lerpPosGlm) * glm::mat4_cast(slerpRotationGlm) *
                        glm::scale(idMatGlm, lerpScaleGlm);

                    CHECK_TRANSFORM(lerpTransform, lerpPos, slerpRotation, lerpScale, lerpMatrixGlm);
                }
            }
        }

        SECTION("Parenting")
        {
            LibMath::Transform parent(position, rotation, scale);

            {
                // Keep local transform
                LibMath::Vector3    transformedPos, transformedScale;
                LibMath::Quaternion transformedRot;

                glm::mat4 transformedMatGlm = matrixGlm * matrixOtherGlm;
                decomposeGlm(transformedMatGlm, transformedPos, transformedRot, transformedScale);

                LibMath::Transform childLocal(positionOther, rotationOther, scaleOther);

                bool result = childLocal.setParent(&parent, false);
                CHECK(result);

                result = childLocal.setParent(&parent, false);
                CHECK_FALSE(result);

                CHECK(childLocal.getParent() == &parent);

                CHECK_TRANSFORM(parent, position, rotation, scale, matrixGlm);

                CHECK_LOCAL_TRANSFORM(childLocal, positionOther, rotationOther, scaleOther, matrixOtherGlm);
                CHECK_WORLD_TRANSFORM(childLocal, transformedPos, transformedRot, transformedScale, transformedMatGlm);
            }

            {
                // Keep world transform
                LibMath::Vector3    transformedPos, transformedScale;
                LibMath::Quaternion transformedRot;

                glm::mat4 transformedMatGlm = glm::inverse(matrixGlm) * matrixOtherGlm;
                decomposeGlm(transformedMatGlm, transformedPos, transformedRot, transformedScale);

                LibMath::Transform childWorld(positionOther, rotationOther, scaleOther);

                bool result = childWorld.setParent(&parent, true);
                CHECK(result);

                result = childWorld.setParent(&parent, true);
                CHECK_FALSE(result);

                CHECK(childWorld.getParent() == &parent);

                CHECK_TRANSFORM(parent, position, rotation, scale, matrixGlm);

                CHECK_LOCAL_TRANSFORM(childWorld, transformedPos, transformedRot, transformedScale, transformedMatGlm);
                CHECK_WORLD_TRANSFORM(childWorld, positionOther, rotationOther, scaleOther, matrixOtherGlm);
            }
        }

        SECTION("Matrix")
        {
            // Generation
            {
                const LibMath::Matrix4 generatedMat = LibMath::Transform::generateMatrix(position, rotation, scale);
                CHECK_MATRIX(generatedMat, glm::transpose(matrixGlm));
            }

            // Decomposition
            {
                LibMath::Vector3    outPos, outScale;
                LibMath::Quaternion outRot;

                LibMath::Transform::decomposeMatrix(matrix, outPos, outRot, outScale);
                CHECK(outPos == position);
                CHECK(outRot == rotation);
                CHECK(outScale == scale);

                const LibMath::Matrix4 mat = LibMath::Transform::generateMatrix(outPos, outRot, outScale);
                CHECK(mat == matrix);
            }
        }

        SECTION("Direction")
        {
            const LibMath::Transform transform(position, rotation, scale);

            {
                const LibMath::Vector3 right = transform.right();
                const LibMath::Vector3 worldRight = transform.worldRight();
                const glm::vec3        rightGlm = rotationGlm * glm::vec3{ 1, 0, 0 };

                CHECK(right.m_x == Catch::Approx(rightGlm.x));
                CHECK(right.m_y == Catch::Approx(rightGlm.y));
                CHECK(right.m_z == Catch::Approx(rightGlm.z));
                CHECK(worldRight == right);
            }

            {
                const LibMath::Vector3 left = transform.left();
                const LibMath::Vector3 worldLeft = transform.worldLeft();
                const glm::vec3        leftGlm = rotationGlm * glm::vec3{ -1, 0, 0 };

                CHECK(left.m_x == Catch::Approx(leftGlm.x));
                CHECK(left.m_y == Catch::Approx(leftGlm.y));
                CHECK(left.m_z == Catch::Approx(leftGlm.z));
                CHECK(worldLeft == left);
            }

            {
                const LibMath::Vector3 up = transform.up();
                const LibMath::Vector3 worldUp = transform.worldUp();
                const glm::vec3        upGlm = rotationGlm * glm::vec3{ 0, 1, 0 };

                CHECK(up.m_x == Catch::Approx(upGlm.x));
                CHECK(up.m_y == Catch::Approx(upGlm.y));
                CHECK(up.m_z == Catch::Approx(upGlm.z));
                CHECK(worldUp == up);
            }

            {
                const LibMath::Vector3 down = transform.down();
                const LibMath::Vector3 worldDown = transform.worldDown();
                const glm::vec3        downGlm = rotationGlm * glm::vec3{ 0, -1, 0 };

                CHECK(down.m_x == Catch::Approx(downGlm.x));
                CHECK(down.m_y == Catch::Approx(downGlm.y));
                CHECK(down.m_z == Catch::Approx(downGlm.z));
                CHECK(worldDown == down);
            }

            {
                const LibMath::Vector3 fwd = transform.forward();
                const LibMath::Vector3 worldFwd = transform.worldForward();
                const glm::vec3        fwdGlm = rotationGlm * glm::vec3{ 0, 0, 1 };

                CHECK(fwd.m_x == Catch::Approx(fwdGlm.x));
                CHECK(fwd.m_y == Catch::Approx(fwdGlm.y));
                CHECK(fwd.m_z == Catch::Approx(fwdGlm.z));
                CHECK(worldFwd == fwd);
            }

            {
                const LibMath::Vector3 back = transform.back();
                const LibMath::Vector3 worldBack = transform.worldBack();
                const glm::vec3        backGlm = rotationGlm * glm::vec3{ 0, 0, -1 };

                CHECK(back.m_x == Catch::Approx(backGlm.x));
                CHECK(back.m_y == Catch::Approx(backGlm.y));
                CHECK(back.m_z == Catch::Approx(backGlm.z));
                CHECK(worldBack == back);
            }
        }
    }
}
