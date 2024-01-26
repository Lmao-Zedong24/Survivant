#include <Matrix.h>
#include <Vector/Vector3.h>
#include <Angle/Radian.h>

#define GLM_ENABLE_EXPERIMENTAL
#define GLM_FORCE_XYZW_ONLY
#include <glm/glm.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

#include "Angle/Degree.h"
#include "Vector/Vector2.h"

using namespace LibMath::Literal;

#define CHECK_MATRIX(matrix, matrixGlm) \
    for (LibMath::length_t i = 0; i < (matrix).getRowCount(); i++) \
        for(LibMath::length_t j = 0; j < (matrix).getColumnCount(); j++) \
            CHECK((matrix)[(matrix).getIndex(i, j)] == Catch::Approx((matrixGlm)[i][j]))

TEST_CASE("Matrix3", "[.all][matrix][Matrix3]")
{
    SECTION("Instantiation")
    {
        // default constructor
        LibMath::Matrix3x3 empty;
        glm::mat3          emptyGlm{};
        CHECK_MATRIX(empty, emptyGlm);

        // destructor
        {
            [[maybe_unused]] LibMath::Matrix3 temp;
        }

        // basic constructor
        LibMath::Matrix3 oneParam{ 2.5f };
        glm::mat3        oneParamGlm = glm::mat3{ 2.5f };
        CHECK_MATRIX(oneParam, oneParamGlm);

        // copy constructor
        LibMath::Matrix3 copy{ oneParam };
        glm::mat3        copyGlm{ oneParamGlm };
        CHECK_MATRIX(copy, copyGlm);

        // assignment operator
        empty = oneParam;
        emptyGlm = oneParamGlm;
        CHECK_MATRIX(empty, emptyGlm);
    }

    SECTION("Accessor")
    {
        LibMath::Matrix3 mat;
        mat[0] = 3.75f;
        mat[1] = 3.f;
        mat[2] = .75f;
        mat[3] = 4.5f;
        mat[4] = 2.5f;
        mat[5] = 4.f;
        mat[6] = 6.5f;
        mat[7] = 4.5f;
        mat[8] = 6.f;

        glm::mat3 matGlm{};
        matGlm[0][0] = 3.75f;
        matGlm[0][1] = 3.f;
        matGlm[0][2] = .75f;
        matGlm[1][0] = 4.5f;
        matGlm[1][1] = 2.5f;
        matGlm[1][2] = 4.f;
        matGlm[2][0] = 6.5f;
        matGlm[2][1] = 4.5f;
        matGlm[2][2] = 6.f;

        for (LibMath::length_t i = 0; i < mat.getRowCount(); i++)
        {
            for (LibMath::length_t j = 0; j < mat.getColumnCount(); j++)
                CHECK(mat[mat.getIndex(i, j)] == Catch::Approx(matGlm[i][j]));
        }

        for (LibMath::length_t i = 0; i < mat.getRowCount(); i++)
        {
            for (LibMath::length_t j = 0; j < mat.getColumnCount(); j++)
                CHECK(mat(i, j) == Catch::Approx(matGlm[i][j]));
        }
    }

    SECTION("Comparator")
    {
        // compare with self
        LibMath::Matrix3 self;
        self(0, 0) = 2.5f;
        self(0, 1) = .5f;
        self(0, 2) = 2.f;
        self(1, 0) = 1.5f;
        self(1, 1) = -.5f;
        self(1, 2) = 1.f;
        self(2, 0) = 3.5f;
        self(2, 1) = 1.5f;
        self(2, 2) = 3.f;

        CHECK(self == self);

        // compare with same
        LibMath::Matrix3 same;
        same(0, 0) = 2.5f;
        same(0, 1) = .5f;
        same(0, 2) = 2.f;
        same(1, 0) = 1.5f;
        same(1, 1) = -.5f;
        same(1, 2) = 1.f;
        same(2, 0) = 3.5f;
        same(2, 1) = 1.5f;
        same(2, 2) = 3.f;

        CHECK(self == same);

        CHECK_FALSE(self.isIdentity());
        CHECK(LibMath::Matrix3{ 1.f }.isIdentity());
    }

    SECTION("Arithmetic")
    {
        LibMath::Matrix3 big;
        big(0, 0) = 3.75f;
        big(0, 1) = 3.f;
        big(0, 2) = .75f;
        big(1, 0) = 4.5f;
        big(1, 1) = 2.5f;
        big(1, 2) = 4.f;
        big(2, 0) = 6.5f;
        big(2, 1) = 4.5f;
        big(2, 2) = 6.f;

        LibMath::Matrix3 small;
        small(0, 0) = 2.5f;
        small(0, 1) = .5f;
        small(0, 2) = 2.f;
        small(1, 0) = 1.5f;
        small(1, 1) = -.5f;
        small(1, 2) = 1.f;
        small(2, 0) = 3.5f;
        small(2, 1) = 1.5f;
        small(2, 2) = 3.f;

        glm::mat3 bigGlm{};
        bigGlm[0][0] = 3.75f;
        bigGlm[0][1] = 3.f;
        bigGlm[0][2] = .75f;
        bigGlm[1][0] = 4.5f;
        bigGlm[1][1] = 2.5f;
        bigGlm[1][2] = 4.f;
        bigGlm[2][0] = 6.5f;
        bigGlm[2][1] = 4.5f;
        bigGlm[2][2] = 6.f;

        glm::mat3 smallGlm{};
        smallGlm[0][0] = 2.5f;
        smallGlm[0][1] = .5f;
        smallGlm[0][2] = 2.f;
        smallGlm[1][0] = 1.5f;
        smallGlm[1][1] = -.5f;
        smallGlm[1][2] = 1.f;
        smallGlm[2][0] = 3.5f;
        smallGlm[2][1] = 1.5f;
        smallGlm[2][2] = 3.f;

        SECTION("Addition")
        {
            {
                LibMath::Matrix3 sumAssignment = big;
                sumAssignment += small;

                glm::mat3 sumAssignmentGlm = bigGlm;
                sumAssignmentGlm += smallGlm;

                CHECK_MATRIX(sumAssignment, sumAssignmentGlm);
            }

            {
                LibMath::Matrix3 sum = big + small;

                glm::mat3 sumGlm = bigGlm + smallGlm;

                CHECK_MATRIX(sum, sumGlm);
            }

            {
                LibMath::Matrix3 sumScalarAssignment = small;
                sumScalarAssignment += 2.64f;

                glm::mat3 sumScalarAssignmentGlm = smallGlm;
                sumScalarAssignmentGlm += 2.64f;

                CHECK_MATRIX(sumScalarAssignment, sumScalarAssignmentGlm);
            }

            {
                LibMath::Matrix3 sumScalar = small + 2.64f;

                glm::mat3 sumScalarGlm = smallGlm + 2.64f;

                CHECK_MATRIX(sumScalar, sumScalarGlm);
            }
        }

        SECTION("Subtraction")
        {
            {
                LibMath::Matrix3 differenceAssignment = big;
                differenceAssignment -= small;

                glm::mat3 differenceAssignmentGlm = bigGlm;
                differenceAssignmentGlm -= smallGlm;

                CHECK_MATRIX(differenceAssignment, differenceAssignmentGlm);
            }

            {
                LibMath::Matrix3 difference = big - small;

                glm::mat3 differenceGlm = bigGlm - smallGlm;

                CHECK_MATRIX(difference, differenceGlm);
            }

            {
                LibMath::Matrix3 differenceScalarAssignment = small;
                differenceScalarAssignment -= 2.64f;

                glm::mat3 differenceScalarAssignmentGlm = smallGlm;
                differenceScalarAssignmentGlm -= 2.64f;

                CHECK_MATRIX(differenceScalarAssignment, differenceScalarAssignmentGlm);
            }

            {
                LibMath::Matrix3 differenceScalar = small - 2.64f;

                glm::mat3 differenceScalarGlm = smallGlm - 2.64f;

                CHECK_MATRIX(differenceScalar, differenceScalarGlm);
            }
        }

        SECTION("Multiplication")
        {
            {
                LibMath::Matrix3 productAssignment = big;
                productAssignment *= small;

                // Transpose since glm matrices are column major unlike ours
                glm::mat3 productAssignmentGlm = glm::transpose(bigGlm);
                productAssignmentGlm *= glm::transpose(smallGlm);

                CHECK_MATRIX(productAssignment, glm::transpose(productAssignmentGlm));
            }

            {
                LibMath::Matrix3 product = big * small;

                // Transpose since glm matrices are column major unlike ours
                glm::mat3 productGlm = glm::transpose(bigGlm) * glm::transpose(smallGlm);

                CHECK_MATRIX(product, glm::transpose(productGlm));
            }

            {
                LibMath::Matrix3 productScalarAssignment = small;
                productScalarAssignment *= 2.64f;

                glm::mat3 productScalarAssignmentGlm = smallGlm;
                productScalarAssignmentGlm *= 2.64f;

                CHECK_MATRIX(productScalarAssignment, productScalarAssignmentGlm);
            }

            {
                LibMath::Matrix3 productScalar = small * 2.64f;

                glm::mat3 productScalarGlm = smallGlm * 2.64f;

                CHECK_MATRIX(productScalar, productScalarGlm);
            }
        }

        SECTION("Division")
        {
            {
                LibMath::Matrix3 quotientAssignment = small;
                quotientAssignment /= big;

                glm::mat3 quotientAssignmentGlm = glm::transpose(smallGlm);
                quotientAssignmentGlm /= glm::transpose(bigGlm);

                CHECK_MATRIX(quotientAssignment, glm::transpose(quotientAssignmentGlm));
            }

            {
                LibMath::Matrix3 quotient = small / big;

                glm::mat3 quotientGlm = glm::transpose(smallGlm) / glm::transpose(bigGlm);

                CHECK_MATRIX(quotient, glm::transpose(quotientGlm));
            }

            {
                LibMath::Matrix3 quotientScalarAssignment = small;
                quotientScalarAssignment /= 2.64f;

                glm::mat3 quotientScalarAssignmentGlm = smallGlm;
                quotientScalarAssignmentGlm /= 2.64f;

                CHECK_MATRIX(quotientScalarAssignment, quotientScalarAssignmentGlm);
            }

            {
                LibMath::Matrix3 quotientScalar = small / 2.64f;

                glm::mat3 quotientScalarGlm = smallGlm / 2.64f;

                CHECK_MATRIX(quotientScalar, quotientScalarGlm);
            }
        }

        SECTION("Negative")
        {
            LibMath::Matrix3 negative = -big;

            glm::mat3 negativeGlm = -bigGlm;

            CHECK_MATRIX(negative, negativeGlm);
        }
    }

    SECTION("Functionality")
    {
        LibMath::Matrix3 big;
        big(0, 0) = 3.75f;
        big(0, 1) = 3.f;
        big(0, 2) = .75f;
        big(1, 0) = 4.5f;
        big(1, 1) = 2.5f;
        big(1, 2) = 4.f;
        big(2, 0) = 6.5f;
        big(2, 1) = 4.5f;
        big(2, 2) = 6.f;

        LibMath::Matrix3 small;
        small(0, 0) = 2.5f;
        small(0, 1) = .5f;
        small(0, 2) = 2.f;
        small(1, 0) = 1.5f;
        small(1, 1) = -.5f;
        small(1, 2) = 1.f;
        small(2, 0) = 3.5f;
        small(2, 1) = 1.5f;
        small(2, 2) = 3.f;

        glm::mat3 bigGlm{};
        bigGlm[0][0] = 3.75f;
        bigGlm[0][1] = 3.f;
        bigGlm[0][2] = .75f;
        bigGlm[1][0] = 4.5f;
        bigGlm[1][1] = 2.5f;
        bigGlm[1][2] = 4.f;
        bigGlm[2][0] = 6.5f;
        bigGlm[2][1] = 4.5f;
        bigGlm[2][2] = 6.f;

        glm::mat3 smallGlm{};
        smallGlm[0][0] = 2.5f;
        smallGlm[0][1] = .5f;
        smallGlm[0][2] = 2.f;
        smallGlm[1][0] = 1.5f;
        smallGlm[1][1] = -.5f;
        smallGlm[1][2] = 1.f;
        smallGlm[2][0] = 3.5f;
        smallGlm[2][1] = 1.5f;
        smallGlm[2][2] = 3.f;

        SECTION("Determinant")
        {
            float determinant = big.determinant();

            float determinantGlm = glm::determinant(bigGlm);

            CHECK(determinant == Catch::Approx(determinantGlm));
        }

        SECTION("Transpose")
        {
            LibMath::Matrix3 transposed = big.transposed();
            glm::mat3        transposedGlm = glm::transpose(bigGlm);

            CHECK_MATRIX(transposed, transposedGlm);
        }

        SECTION("Cofactor")
        {
            glm::mat3 cofactorMatGlm = glm::transpose(glm::inverse(bigGlm) * glm::determinant(bigGlm));

            for (LibMath::length_t row = 0; row < big.getRowCount(); row++)
            {
                for (LibMath::length_t col = 0; col < big.getColumnCount(); col++)
                {
                    const float cofactor = big.cofactor(row, col);

                    CHECK(cofactor == Catch::Approx(cofactorMatGlm[row][col]));
                }
            }
        }

        SECTION("CofactorMatrix")
        {
            LibMath::Matrix3 cofactorMat = big.coMatrix();
            glm::mat3        cofactorMatGlm = glm::transpose(glm::inverse(bigGlm) * glm::determinant(bigGlm));

            CHECK_MATRIX(cofactorMat, cofactorMatGlm);
        }

        SECTION("Inverse")
        {
            {
                LibMath::Matrix3 inverse = big.inverse();
                glm::mat3        inverseGlm = glm::inverse(bigGlm);

                CHECK_MATRIX(inverse, inverseGlm);

                CHECK(inverse * big == big * inverse);
                CHECK((inverse * big).isIdentity());
            }

            {
                LibMath::Matrix3 nonInvertible;
                nonInvertible[0] = 1;
                nonInvertible[1] = 6.f;
                nonInvertible[2] = 4.f;
                nonInvertible[3] = 2.f;
                nonInvertible[4] = 4.f;
                nonInvertible[5] = -1.f;
                nonInvertible[6] = -1.f;
                nonInvertible[7] = 2.f;
                nonInvertible[8] = 5.f;

                CHECK_THROWS(nonInvertible.inverse());
            }
        }

        SECTION("Array")
        {
            constexpr size_t matSize = big.getSize();

            for (size_t i = 0; i < matSize; i++)
                CHECK(big.getArray()[i] == Catch::Approx(glm::value_ptr(bigGlm)[i]));
        }
    }

    SECTION("Extra")
    {
        LibMath::Matrix3x2 input;
        input(0, 0) = 3.75f;
        input(0, 1) = 3.f;
        input(1, 0) = .75f;
        input(1, 1) = 4.5f;
        input(2, 0) = 2.5f;
        input(2, 1) = 4.f;

        {
            std::stringstream buffer;
            buffer << input;
            CHECK(buffer.str() == "{3.75,3,0.75,4.5,2.5,4}");

            buffer << " extra";

            LibMath::Matrix3x2 output;
            buffer >> output;
            CHECK(output == input);

            std::string extra;
            buffer >> extra;
            CHECK(extra == "extra");
        }

        {
            CHECK(input.string() == "{3.75,3,0.75,4.5,2.5,4}");

            CHECK(input.stringLong() == "Matrix3x2{ 0_0: 3.75, 0_1: 3, 1_0: 0.75, 1_1: 4.5, 2_0: 2.5, 2_1: 4 }");
        }
    }

    SECTION("Debug")
    {
#if (defined _DEBUG) || (! defined NDEBUG)
        LibMath::Matrix3 matrix{};

        CHECK_THROWS(matrix[matrix.getIndex(-1, 0)]);
        CHECK_THROWS(matrix[matrix.getIndex(0, -1)]);
        CHECK_THROWS(matrix[matrix.getIndex(-1, -1)]);
        CHECK_THROWS(matrix[matrix.getIndex(3, 0)]);
        CHECK_THROWS(matrix[matrix.getIndex(0, 3)]);
        CHECK_THROWS(matrix[matrix.getIndex(3, 3)]);
        CHECK_THROWS(matrix[9]);
#endif // DEBUG
    }
}

TEST_CASE("Matrix4", "[.all][matrix][Matrix4]")
{
    constexpr glm::mat4 idMatGlm{ 1 };

    SECTION("Transformation")
    {
        const LibMath::Vector3 transformation{ -2.f, 0.f, 1.25f };

        constexpr glm::vec3 transformationGlm{ -2.f, 0.f, 1.25f };

        SECTION("Translation")
        {
            LibMath::Matrix4 translate = LibMath::translation(transformation.m_x, transformation.m_y, transformation.m_z);

            glm::mat4 translateGlm = glm::translate(idMatGlm, transformationGlm);

            // Transpose since glm matrices are column major unlike ours
            CHECK_MATRIX(translate, glm::transpose(translateGlm));
        }

        SECTION("Scale")
        {
            LibMath::Matrix4 scale = LibMath::scaling(transformation.m_x, transformation.m_y, transformation.m_z);

            glm::mat4 scaleGlm = glm::scale(idMatGlm, transformationGlm);

            // Transpose since glm matrices are column major unlike ours
            CHECK_MATRIX(scale, glm::transpose(scaleGlm));
        }

        SECTION("Rotation")
        {
            SECTION("Axis")
            {
                LibMath::Matrix4 rotate = LibMath::rotation(-3_rad, transformation);
                glm::mat4        rotateGlm = glm::rotate(idMatGlm, -3.f, transformationGlm);

                // Transpose since glm matrices are column major unlike ours
                CHECK_MATRIX(rotate, glm::transpose(rotateGlm));
            }

            SECTION("Euler Angle")
            {
                LibMath::Matrix4 rotate = LibMath::rotation(LibMath::Radian{ transformation.m_x },
                    LibMath::Radian{ transformation.m_y }, LibMath::Radian{ transformation.m_z });

                glm::mat4 rotateGlm = glm::yawPitchRoll(transformationGlm.x, transformationGlm.y, transformationGlm.z);

                // Transpose since glm matrices are column major unlike ours
                CHECK_MATRIX(rotate, glm::transpose(rotateGlm));

                rotate = LibMath::rotation(transformation);

                rotateGlm = glm::yawPitchRoll(transformationGlm.x, transformationGlm.y, transformationGlm.z);

                // Transpose since glm matrices are column major unlike ours
                CHECK_MATRIX(rotate, glm::transpose(rotateGlm));

                rotate = LibMath::rotationEuler(LibMath::Radian{ transformation.m_x }, LibMath::Radian{ transformation.m_y },
                    LibMath::Radian{ transformation.m_z });

                rotateGlm = glm::orientate4(transformationGlm);

                // Transpose since glm matrices are column major unlike ours
                CHECK_MATRIX(rotate, glm::transpose(rotateGlm));

                rotate = LibMath::rotationEuler(transformation);

                // Transpose since glm matrices are column major unlike ours
                CHECK_MATRIX(rotate, glm::transpose(rotateGlm));

                // XYZ
                {
                    LibMath::TVector3<LibMath::Radian> euler = LibMath::toEuler(rotate, LibMath::ERotationOrder::XYZ);

                    glm::vec3 eulerGlm;
                    glm::extractEulerAngleXYZ(rotateGlm, eulerGlm.x, eulerGlm.y, eulerGlm.z);

                    CHECK(LibMath::floatEquals(euler.m_x.raw(), eulerGlm.x));
                    CHECK(LibMath::floatEquals(euler.m_y.raw(), eulerGlm.y));
                    CHECK(LibMath::floatEquals(euler.m_z.raw(), eulerGlm.z));
                }

                // XZY
                {
                    LibMath::TVector3<LibMath::Radian> euler = LibMath::toEuler(rotate, LibMath::ERotationOrder::XZY);

                    glm::vec3 eulerGlm;
                    glm::extractEulerAngleXZY(rotateGlm, eulerGlm.x, eulerGlm.z, eulerGlm.y);

                    CHECK(LibMath::floatEquals(euler.m_x.raw(), eulerGlm.x));
                    CHECK(LibMath::floatEquals(euler.m_y.raw(), eulerGlm.y));
                    CHECK(LibMath::floatEquals(euler.m_z.raw(), eulerGlm.z));
                }

                // YXZ
                {
                    LibMath::TVector3<LibMath::Radian> euler = LibMath::toEuler(rotate, LibMath::ERotationOrder::YXZ);

                    glm::vec3 eulerGlm;
                    glm::extractEulerAngleYXZ(rotateGlm, eulerGlm.y, eulerGlm.x, eulerGlm.z);

                    CHECK(LibMath::floatEquals(euler.m_x.raw(), eulerGlm.x));
                    CHECK(LibMath::floatEquals(euler.m_y.raw(), eulerGlm.y));
                    CHECK(LibMath::floatEquals(euler.m_z.raw(), eulerGlm.z));
                }

                // YZX
                {
                    LibMath::TVector3<LibMath::Radian> euler = LibMath::toEuler(rotate, LibMath::ERotationOrder::YZX);

                    glm::vec3 eulerGlm;
                    glm::extractEulerAngleYZX(rotateGlm, eulerGlm.y, eulerGlm.z, eulerGlm.x);

                    CHECK(LibMath::floatEquals(euler.m_x.raw(), eulerGlm.x));
                    CHECK(LibMath::floatEquals(euler.m_y.raw(), eulerGlm.y));
                    CHECK(LibMath::floatEquals(euler.m_z.raw(), eulerGlm.z));
                }

                // ZXY
                {
                    LibMath::TVector3<LibMath::Radian> euler = LibMath::toEuler(rotate, LibMath::ERotationOrder::ZXY);

                    glm::vec3 eulerGlm;
                    glm::extractEulerAngleZXY(rotateGlm, eulerGlm.z, eulerGlm.x, eulerGlm.y);

                    CHECK(LibMath::floatEquals(euler.m_x.raw(), eulerGlm.x));
                    CHECK(LibMath::floatEquals(euler.m_y.raw(), eulerGlm.y));
                    CHECK(LibMath::floatEquals(euler.m_z.raw(), eulerGlm.z));
                }

                // ZYX
                {
                    LibMath::TVector3<LibMath::Radian> euler = LibMath::toEuler(rotate, LibMath::ERotationOrder::ZYX);

                    glm::vec3 eulerGlm;
                    glm::extractEulerAngleZYX(rotateGlm, eulerGlm.z, eulerGlm.y, eulerGlm.x);

                    CHECK(LibMath::floatEquals(euler.m_x.raw(), eulerGlm.x));
                    CHECK(LibMath::floatEquals(euler.m_y.raw(), eulerGlm.y));
                    CHECK(LibMath::floatEquals(euler.m_z.raw(), eulerGlm.z));
                }
            }

            SECTION("Quaternion")
            {
                LibMath::Quaternion quat(LibMath::Radian{ transformation.m_x }, LibMath::Radian{ transformation.m_y },
                    LibMath::Radian{ transformation.m_z });
                LibMath::Matrix4 rotate = LibMath::rotation(quat);
                glm::mat4        rotateGlm = glm::yawPitchRoll(transformationGlm.x, transformationGlm.y, transformationGlm.z);

                // Transpose since glm matrices are column major unlike ours
                CHECK_MATRIX(rotate, glm::transpose(rotateGlm));
            }
        }

        SECTION("Projection")
        {
            constexpr float near = 0.f;
            constexpr float far = 2.f;

            SECTION("Orthographic")
            {
                constexpr float top = 1.f;
                constexpr float bottom = -1.f;
                constexpr float left = -1.f;
                constexpr float right = 1.f;

                LibMath::Matrix4 projection = LibMath::orthographicProjection(left, right, bottom, top, near, far);
                glm::mat4        projectionGlm = glm::ortho(left, right, bottom, top, near, far);

                // Transpose since glm matrices are column major unlike ours
                CHECK_MATRIX(projection, glm::transpose(projectionGlm));
            }

            SECTION("Perspective")
            {
                constexpr float fovY = 180.f;
                constexpr float aspect = 16.f / 9.f;

                LibMath::Matrix4 projection = LibMath::perspectiveProjection(LibMath::Degree(fovY), aspect, near, far);
                glm::mat4        projectionGlm = glm::perspective(glm::radians(fovY), aspect, near, far);

                // Transpose since glm matrices are column major unlike ours
                CHECK_MATRIX(projection, glm::transpose(projectionGlm));
            }
        }

        SECTION("LookAt")
        {
            LibMath::Matrix4 lookAt = LibMath::lookAt(transformation, transformation + LibMath::Vector3::front(),
                LibMath::Vector3::up());
            glm::mat4 lookAtGlm = glm::lookAt(transformationGlm, transformationGlm + glm::vec3{ 0, 0, 1 }, glm::vec3{ 0, 1, 0 });

            // Transpose since glm matrices are column major unlike ours
            CHECK_MATRIX(lookAt, glm::transpose(lookAtGlm));
        }
    }
}
