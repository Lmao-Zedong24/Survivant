#include <Vector/Vector3.h>
#include <Angle/Radian.h>

#define GLM_ENABLE_EXPERIMENTAL
#define GLM_FORCE_XYZW_ONLY
#include <glm/glm.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/projection.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

using namespace LibMath::Literal;

#define CHECK_VECTOR3(vector, vectorGlm) CHECK((vector).m_x == Catch::Approx((vectorGlm).x)); CHECK((vector).m_y == Catch::Approx((vectorGlm).y)); CHECK((vector).m_z == Catch::Approx((vectorGlm).z))

TEST_CASE("Vector3", "[.all][vector][Vector3]")
{
    SECTION("Instantiation")
    {
        // default constructor
        LibMath::Vector3 empty;
        glm::vec3        emptyGlm{};
        CHECK_VECTOR3(empty, emptyGlm);

        // destructor
        {
            LibMath::Vector3 temp;
        }

        // basic constructor
        LibMath::Vector3 oneParam{ 2.5f };
        glm::vec3        oneParamGlm{ 2.5f };
        CHECK_VECTOR3(oneParam, oneParamGlm);

        LibMath::Vector3 allParam{ 2.5f, .5f, 2.f };
        glm::vec3        allParamGlm{ 2.5f, .5f, 2.f };
        CHECK_VECTOR3(allParam, allParamGlm);

        // copy constructor
        LibMath::Vector3 copy{ allParam };
        glm::vec3        copyGlm{ allParamGlm };
        CHECK_VECTOR3(copy, copyGlm);

        LibMath::Vector3I iCopy{ allParam };
        glm::ivec3        iCopyGlm{ allParamGlm };
        CHECK_VECTOR3(iCopy, iCopyGlm);

        // assignment operator
        empty = allParam;
        emptyGlm = allParamGlm;
        CHECK_VECTOR3(empty, emptyGlm);

        empty = iCopy;
        emptyGlm = iCopyGlm;
        CHECK_VECTOR3(empty, emptyGlm);

        CHECK(sizeof(LibMath::Vector3) == sizeof(glm::vec3));
    }

    SECTION("Accessor")
    {
        constexpr float  x = 2.5f;
        constexpr float  y = .5f;
        constexpr float  z = 2.f;
        LibMath::Vector3 vector{ x, y, z };

        {
            const LibMath::Vector3& vectorConst = vector;
            CHECK(vectorConst[0] == Catch::Approx(x));
            CHECK(vectorConst[1] == Catch::Approx(y));
            CHECK(vectorConst[2] == Catch::Approx(z));
        }

        {
            vector[0] += 1.f;
            vector[1] += 1.f;
            vector[2] += 1.f;
            CHECK(vector[0] == Catch::Approx(x + 1.f));
            CHECK(vector[1] == Catch::Approx(y + 1.f));
            CHECK(vector[2] == Catch::Approx(z + 1.f));
        }
    }

    SECTION("Comparator")
    {
        // compare with self
        LibMath::Vector3 self{ 2.5f, .5f, 2.f };
        CHECK(self == self);

        // compare with same
        CHECK(LibMath::Vector3{ 2.5f, .5f, 2.f } == LibMath::Vector3{ 2.5f, .5f, 2.f });

        // trying to find copy/paste mistake
        LibMath::Vector3 twos{ 2.f, 2.f, 2.f };
        CHECK_FALSE(LibMath::Vector3{ .5f, 2.f, 2.f } == twos);
        CHECK_FALSE(LibMath::Vector3{ 2.f, .5f, 2.f } == twos);
        CHECK_FALSE(LibMath::Vector3{ 2.f, 2.f, .5f } == twos);
        CHECK_FALSE(twos == LibMath::Vector3{ .5f, 2.f, 2.f });
        CHECK_FALSE(twos == LibMath::Vector3{ 2.f, .5f, 2.f });
        CHECK_FALSE(twos == LibMath::Vector3{ 2.f, 2.f, .5f });

        // testing comparaision fonctionnality
        LibMath::Vector3 small{ 2.5f, .5f, 2.f };
        LibMath::Vector3 big{ 3.75f, 3.f, .75f };

        CHECK(big.isLongerThan(small));
        CHECK_FALSE(small.isLongerThan(big));

        CHECK(small.isShorterThan(big));
        CHECK_FALSE(big.isShorterThan(small));

        CHECK_FALSE(self.isUnitVector());
        CHECK(LibMath::Vector3{ 0.771516740f, 0.154303357f, 0.617213428f }.isUnitVector());
    }

    SECTION("Constant")
    {
        CHECK_VECTOR3(LibMath::Vector3::back(), glm::vec3(0.f, 0.f, -1.f));

        CHECK_VECTOR3(LibMath::Vector3::down(), glm::vec3(0.f, -1.f, 0.f));

        CHECK_VECTOR3(LibMath::Vector3::front(), glm::vec3(0.f, 0.f, 1.f));

        CHECK_VECTOR3(LibMath::Vector3::left(), glm::vec3(-1.f, 0.f, 0.f));

        CHECK_VECTOR3(LibMath::Vector3::one(), glm::vec3(1.f, 1.f, 1.f));

        CHECK_VECTOR3(LibMath::Vector3::right(), glm::vec3(1.f, 0.f, 0.f));

        CHECK_VECTOR3(LibMath::Vector3::up(), glm::vec3(0.f, 1.f, 0.f));

        CHECK_VECTOR3(LibMath::Vector3::zero(), glm::vec3(0.f, 0.f, 0.f));
    }

    SECTION("Arithmetic")
    {
        const LibMath::Vector3 small{ 2.5f, .5f, 2.f };
        const LibMath::Vector3 big{ 3.75f, 3.f, .75f };

        constexpr glm::vec3 smallGlm{ 2.5f, .5f, 2.f };
        constexpr glm::vec3 bigGlm{ 3.75f, 3.f, .75f };

        constexpr float scalar = 3.75f;

        SECTION("Addition")
        {
            {
                LibMath::Vector3 sumAssignment = big;
                sumAssignment += small;

                glm::vec3 sumAssignmentGlm = bigGlm;
                sumAssignmentGlm += smallGlm;

                CHECK_VECTOR3(sumAssignment, sumAssignmentGlm);
            }

            {
                LibMath::Vector3 sum = big + small;

                glm::vec3 sumGlm = bigGlm + smallGlm;

                CHECK_VECTOR3(sum, sumGlm);
            }
        }

        SECTION("Inverse")
        {
            LibMath::Vector3 inverse = -LibMath::Vector3{ 3.7f, 3.f, .7f };

            glm::vec3 inverseGlm = -glm::vec3{ 3.7f, 3.f, .7f };

            CHECK_VECTOR3(inverse, inverseGlm);
        }

        SECTION("Substraction")
        {
            {
                LibMath::Vector3 differenceAssignment = big;
                differenceAssignment -= small;

                glm::vec3 differenceAssignmentGlm = bigGlm;
                differenceAssignmentGlm -= smallGlm;

                CHECK_VECTOR3(differenceAssignment, differenceAssignmentGlm);
            }

            {
                LibMath::Vector3 difference = big - small;

                glm::vec3 differenceGlm = bigGlm - smallGlm;

                CHECK_VECTOR3(difference, differenceGlm);
            }
        }

        SECTION("Multiplication")
        {
            {
                LibMath::Vector3 productAssignment = big;
                productAssignment *= small;

                glm::vec3 productAssignmentGlm = bigGlm;
                productAssignmentGlm *= smallGlm;

                CHECK_VECTOR3(productAssignment, productAssignmentGlm);
            }

            {
                LibMath::Vector3 product = big * small;

                glm::vec3 productGlm = bigGlm * smallGlm;

                CHECK_VECTOR3(product, productGlm);
            }

            {
                LibMath::Vector3 productAssignment = big;
                productAssignment *= scalar;

                glm::vec3 productAssignmentGlm = bigGlm;
                productAssignmentGlm *= scalar;

                CHECK_VECTOR3(productAssignment, productAssignmentGlm);
            }

            {
                LibMath::Vector3 product = big * scalar;

                glm::vec3 productGlm = bigGlm * scalar;

                CHECK_VECTOR3(product, productGlm);
            }
        }

        SECTION("Division")
        {
            {
                LibMath::Vector3 quotientAssignment = big;
                quotientAssignment /= small;

                glm::vec3 quotientAssignmentGlm = bigGlm;
                quotientAssignmentGlm /= smallGlm;

                CHECK_VECTOR3(quotientAssignment, quotientAssignmentGlm);
            }

            {
                LibMath::Vector3 quotient = big / small;

                glm::vec3 quotientGlm = bigGlm / smallGlm;

                CHECK_VECTOR3(quotient, quotientGlm);
            }

            {
                LibMath::Vector3 quotientAssignment = big;
                quotientAssignment /= scalar;

                glm::vec3 quotientAssignmentGlm = bigGlm;
                quotientAssignmentGlm /= scalar;

                CHECK_VECTOR3(quotientAssignment, quotientAssignmentGlm);
            }

            {
                LibMath::Vector3 quotient = big / scalar;

                glm::vec3 quotientGlm = bigGlm / scalar;

                CHECK_VECTOR3(quotient, quotientGlm);
            }
        }
    }

    SECTION("Transformation")
    {
        const LibMath::Vector3 origin{ 2.5f, .5f, 2.f };
        const LibMath::Vector3 transformation{ -2.f, 0.f, 1.25f };

        constexpr glm::vec4 originGlm{ 2.5f, .5f, 2.f, 1.f };
        constexpr glm::vec3 transformationGlm{ -2.f, 0.f, 1.25f };

        SECTION("Translation")
        {
            LibMath::Vector3 translate = origin;
            translate.translate(transformation);

            glm::vec4 translateGlm = glm::translate(transformationGlm) * originGlm;

            CHECK_VECTOR3(translate, translateGlm);
        }

        SECTION("Scale")
        {
            LibMath::Vector3 scale = origin;
            scale.scale(transformation);

            glm::vec4 scaleGlm = glm::scale(transformationGlm) * originGlm;

            CHECK_VECTOR3(scale, scaleGlm);
        }

        SECTION("Rotation")
        {
            SECTION("Euler Angle")
            {
                LibMath::Vector3 rotate = origin;
                rotate.rotate(LibMath::Radian{ transformation.m_x }, LibMath::Radian{ transformation.m_y },
                    LibMath::Radian{ transformation.m_z });

                glm::vec4 rotateGlm = glm::orientate4(transformationGlm) * originGlm;

                CHECK_VECTOR3(rotate, rotateGlm);
            }

            SECTION("Axis")
            {
                LibMath::Vector3 rotate = origin;
                rotate.rotate(-3_rad, transformation);

                glm::vec4 rotateGlm = glm::rotate(-3.f, transformationGlm) * originGlm;

                CHECK_VECTOR3(rotate, rotateGlm);
            }

            SECTION("Quaternion")
            {
                LibMath::Vector3 rotate = origin;
                rotate.rotate(LibMath::Quaternion(-3_rad, transformation));

                glm::vec4 rotateGlm = glm::rotate(-3.f, transformationGlm) * originGlm;

                CHECK_VECTOR3(rotate, rotateGlm);
            }
        }
    }

    SECTION("Functionality")
    {
        const LibMath::Vector3 base{ 2.5f, .5f, 2.f };
        const LibMath::Vector3 other{ 3.75f, 3.f, .75f };

        constexpr glm::vec3 baseGlm{ 2.5f, .5f, 2.f };
        constexpr glm::vec3 otherGlm{ 3.75f, 3.f, .75f };

        SECTION("Angle")
        {
            LibMath::Radian angle = base.angleFrom(other);

            float angleGlm = glm::angle(glm::normalize(baseGlm), glm::normalize(otherGlm));

            float glmDegrees = glm::degrees(angleGlm);

            CHECK(angle.radian() == Catch::Approx(angleGlm));
            CHECK(angle.degree() == Catch::Approx(glmDegrees));
        }

        SECTION("Cross")
        {
            LibMath::Vector3 cross = base.cross(other);

            glm::vec3 crossGlm = glm::cross(baseGlm, otherGlm);

            CHECK_VECTOR3(cross, crossGlm);
        }

        SECTION("Dot")
        {
            float dot = base.dot(other);

            float dotGlm = glm::dot(baseGlm, otherGlm);

            CHECK(dot == Catch::Approx(dotGlm));
        }

        SECTION("Distance")
        {
            {
                float distance = base.distanceFrom(other);

                float distanceGlm = glm::distance(baseGlm, otherGlm);

                CHECK(distance == Catch::Approx(distanceGlm));
            }

            {
                float distanceSquare = base.distanceSquaredFrom(other);

                float distanceSquareGlm = glm::distance2(baseGlm, otherGlm);

                CHECK(distanceSquare == Catch::Approx(distanceSquareGlm));
            }

            {
                float distance2D = base.distance2DFrom(other);

                float distance2DGlm = glm::distance(glm::vec2(baseGlm), glm::vec2(otherGlm));

                CHECK(distance2D == Catch::Approx(distance2DGlm));
            }

            {
                float distance2DSquare = base.distance2DSquaredFrom(other);

                float distance2DSquareGlm = glm::distance2(glm::vec2(baseGlm), glm::vec2(otherGlm));

                CHECK(distance2DSquare == Catch::Approx(distance2DSquareGlm));
            }
        }

        SECTION("Magnitude")
        {
            {
                float magnitude = base.magnitude();

                float magnitudeGlm = glm::length(baseGlm);

                CHECK(magnitude == Catch::Approx(magnitudeGlm));
            }

            {
                float magnitudeSquare = base.magnitudeSquared();

                float magnitudeSquareGlm = glm::length2(baseGlm);

                CHECK(magnitudeSquare == Catch::Approx(magnitudeSquareGlm));
            }
        }

        SECTION("Normal")
        {
            LibMath::Vector3 normalize = base;
            normalize.normalize();

            glm::vec3 normalizeGlm = glm::normalize(baseGlm);

            CHECK_VECTOR3(normalize, normalizeGlm);
        }

        SECTION("ProjectOnto")
        {
            LibMath::Vector3 project = base;
            project.projectOnto(other);

            glm::vec3 projectGlm = glm::proj(baseGlm, otherGlm);

            CHECK_VECTOR3(project, projectGlm);
        }

        SECTION("ReflectOnto")
        {
            LibMath::Vector3 reflect = base;
            reflect.reflectOnto(other);

            glm::vec3 reflectGlm = glm::reflect(baseGlm, glm::normalize(otherGlm));

            CHECK_VECTOR3(reflect, reflectGlm);
        }
    }

    SECTION("Extra")
    {
        const LibMath::Vector3 input{ 2.5f, -.5f, 2.f };
        {
            std::stringstream buffer;
            buffer << input;
            CHECK(buffer.str() == "{2.5,-0.5,2}");

            buffer << " extra";

            LibMath::Vector3 output;
            buffer >> output;
            CHECK(output == input);

            std::string extra;
            buffer >> extra;
            CHECK(extra == "extra");
        }

        {
            CHECK(input.string() == "{2.5,-0.5,2}");

            CHECK(input.stringLong() == "Vector3{ x:2.5, y:-0.5, z:2 }");
        }
    }

    SECTION("Debug")
    {
#if (defined _DEBUG) || (! defined NDEBUG)
        LibMath::Vector3 vector{ 2.5f, .5f, 2.f };

        CHECK_THROWS(vector[-1]);
        CHECK_THROWS(vector[3]);
#endif // DEBUG
    }
}
