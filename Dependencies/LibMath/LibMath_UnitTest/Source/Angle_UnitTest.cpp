#include <Angle.h>

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

using namespace LibMath::Literal;

TEST_CASE("Degree", "[.all][angle]")
{
    SECTION("Instantiation")
    {
        // default constructor
        LibMath::Degree empty;
        CHECK(empty.raw() == 0.f);

        // destructor
        {
            LibMath::Degree temp;
        }

        // basic constructor
        float           value = 60.f;
        LibMath::Degree angle{ value };
        CHECK(angle.raw() == value);

        // copy constructor
        LibMath::Degree copy{ angle };
        CHECK(copy.raw() == value);

        // assignment operator
        empty = angle;
        CHECK(empty.raw() == value);

        LibMath::Degree literal = 60_deg;
        CHECK(literal.raw() == value);
        literal = 22.5_deg;
        [[maybe_unused]] float f = literal.raw();
        CHECK(literal.raw() == 22.5f);

        CHECK(sizeof(LibMath::Degree) == sizeof(float));
    }

    SECTION("Accessor")
    {
        {
            // 0 value
            LibMath::Degree zeroDegree;
            CHECK(zeroDegree.degree(true) == 0.f);
            CHECK(zeroDegree.degree(false) == 0.f);
            CHECK(zeroDegree.radian(true) == 0.f);
            CHECK(zeroDegree.radian(false) == 0.f);
        }

        {
            // no change value
            LibMath::Degree sixtyDegree{ 60.f };
            CHECK(sixtyDegree.degree(true) == 60.f);
            CHECK(sixtyDegree.degree(false) == 60.f);
            CHECK(sixtyDegree.radian(true) == Catch::Approx(glm::radians(60.f)));
            CHECK(sixtyDegree.radian(false) == Catch::Approx(glm::radians(60.f)));
        }

        {
            // wrap when true value
            LibMath::Degree threeHundredDegree{ 300.f };
            CHECK(threeHundredDegree.degree(true) == -60.f);
            CHECK(threeHundredDegree.degree(false) == 300.f);
            CHECK(threeHundredDegree.radian(true) == Catch::Approx(glm::radians(-60.f)));
            CHECK(threeHundredDegree.radian(false) == Catch::Approx(glm::radians(300.f)));
        }

        {
            // wrap when false value
            LibMath::Degree minusSixtyDegree{ -60.f };
            CHECK(minusSixtyDegree.degree(true) == -60.f);
            CHECK(minusSixtyDegree.degree(false) == 300.f);
            CHECK(minusSixtyDegree.radian(true) == Catch::Approx(glm::radians(-60.f)));
            CHECK(minusSixtyDegree.radian(false) == Catch::Approx(glm::radians(300.f)));
        }

        {
            // positive wrap value
            LibMath::Degree oneThousandDegree{ 1000.f };
            CHECK(oneThousandDegree.degree(true) == -80.f);
            CHECK(oneThousandDegree.degree(false) == 280.f);
            CHECK(oneThousandDegree.radian(true) == Catch::Approx(glm::radians(-80.f)));
            CHECK(oneThousandDegree.radian(false) == Catch::Approx(glm::radians(280.f)));
        }

        {
            // negative wrap value
            LibMath::Degree minusOneThousandDegree{ -1000.f };
            CHECK(minusOneThousandDegree.degree(true) == 80.f);
            CHECK(minusOneThousandDegree.degree(false) == 80.f);
            CHECK(minusOneThousandDegree.radian(true) == Catch::Approx(glm::radians(80.f)));
            CHECK(minusOneThousandDegree.radian(false) == Catch::Approx(glm::radians(80.f)));
        }
    }

    SECTION("Comparator")
    {
        // compare with self
        LibMath::Degree self{ 60.f };
        CHECK(self == self);

        // compare with same
        CHECK(LibMath::Degree{ 60.f } == LibMath::Degree{ 60.f });

        // compare with wrapped value
        CHECK(LibMath::Degree{ 90.f } == LibMath::Degree(450.f));

        // compare with wrap edge value
        CHECK(LibMath::Degree{ 0.f } == LibMath::Degree{ 360.f });
        CHECK(LibMath::Degree{ -180.f } == LibMath::Degree{ 180.f });
    }

    SECTION("Arithmetic")
    {
        {
            // operator +
            LibMath::Degree sum = LibMath::Degree(45.f) + LibMath::Degree(30.f);
            CHECK(sum.degree() == 75.f);
        }

        {
            // operator +=
            LibMath::Degree sum(45.f);
            sum += LibMath::Degree(30.f);
            CHECK(sum.degree() == 75.f);
        }

        {
            // operator -
            LibMath::Degree inverse = -LibMath::Degree(45.f);
            CHECK(inverse.degree() == 315.f);
        }

        {
            // operator -
            LibMath::Degree difference = LibMath::Degree(45.f) - LibMath::Degree(30.f);
            CHECK(difference.degree() == 15.f);
        }

        {
            // operator -=
            LibMath::Degree difference(45.f);
            difference -= LibMath::Degree(30.f);
            CHECK(difference.degree() == 15.f);
        }

        {
            // operator *
            LibMath::Degree product = LibMath::Degree(45.f) * 10.f;
            CHECK(product.degree() == 90.f);
        }

        {
            // operator *=
            LibMath::Degree product(45.f);
            product *= 10.f;
            CHECK(product.degree() == 90.f);
        }

        {
            // operator /
            LibMath::Degree quotient = LibMath::Degree(45.f) / 5.f;
            CHECK(quotient.degree() == 9.f);
        }

        {
            // operator /=
            LibMath::Degree quotient(45.f);
            quotient /= 5.f;
            CHECK(quotient.degree() == 9.f);
        }
    }

    SECTION("Functionality")
    {
        {
            // wrap value
            LibMath::Degree wrapAngle{ 900.f };
            wrapAngle.wrap(false);
            CHECK(wrapAngle.raw() == 180.f);
        }

        {
            // prefere lower edge value
            LibMath::Degree wrapEdge{ 360.f };
            wrapEdge.wrap(false);
            CHECK(wrapEdge.raw() == 0.f);

            wrapEdge = LibMath::Degree{ 900.f };
            wrapEdge.wrap(true);
            CHECK(wrapEdge.raw() == -180.f);
        }
    }
}

TEST_CASE("Radian", "[.all][angle]")
{
    constexpr float halfRadianCircle = glm::pi<float>();
    constexpr float radianCircle = glm::two_pi<float>();

    SECTION("Instantiation")
    {
        // default constructor
        LibMath::Radian empty;
        CHECK(empty.raw() == 0.f);

        // destructor
        {
            LibMath::Radian temp;
        }

        // basic constructor
        float           value = 1.2f;
        LibMath::Radian angle{ value };
        CHECK(angle.raw() == value);

        // copy constructor
        LibMath::Radian copy{ angle };
        CHECK(copy.raw() == value);

        // assignment operator
        empty = angle;
        CHECK(empty.raw() == value);

        LibMath::Radian literal = 1.2_rad;
        CHECK(literal.raw() == value);
        literal = 1_rad;
        CHECK(literal.raw() == 1.f);

        CHECK(sizeof(LibMath::Radian) == sizeof(float));
    }

    SECTION("Accessor")
    {
        {
            // 0 value
            LibMath::Radian zeroRadian;
            CHECK(zeroRadian.degree(true) == 0.f);
            CHECK(zeroRadian.degree(false) == 0.f);
            CHECK(zeroRadian.radian(true) == 0.f);
            CHECK(zeroRadian.radian(false) == 0.f);
        }

        {
            // no change value
            LibMath::Radian oneRadian{ 1.2f };
            CHECK(oneRadian.degree(true) == Catch::Approx(glm::degrees(1.2f)));
            CHECK(oneRadian.degree(false) == Catch::Approx(glm::degrees(1.2f)));
            CHECK(oneRadian.radian(true) == 1.2f);
            CHECK(oneRadian.radian(false) == 1.2f);
        }

        {
            // wrap when true value
            constexpr float wrapRadian = 5.8f - radianCircle;

            LibMath::Radian sixRadian{ 5.8f };
            CHECK(sixRadian.degree(true) == Catch::Approx(glm::degrees(wrapRadian)));
            CHECK(sixRadian.degree(false) == Catch::Approx(glm::degrees(5.8f)));
            CHECK(sixRadian.radian(true) == Catch::Approx(wrapRadian));
            CHECK(sixRadian.radian(false) == 5.8f);
        }

        {
            // wrap when false value
            constexpr float wrapRadian = radianCircle - 1.2f;

            LibMath::Radian minusOneRadian{ -1.2f };
            CHECK(minusOneRadian.degree(true) == Catch::Approx(glm::degrees(-1.2f)));
            CHECK(minusOneRadian.degree(false) == Catch::Approx(glm::degrees(wrapRadian)));
            CHECK(minusOneRadian.radian(true) == -1.2f);
            CHECK(minusOneRadian.radian(false) == Catch::Approx(wrapRadian));
        }

        {
            // positive wrap value
            constexpr float radian = 15.f - 2.f * radianCircle;

            LibMath::Radian fifteenRadian{ 15.f };
            CHECK(fifteenRadian.degree(true) == Catch::Approx(glm::degrees(radian)));
            CHECK(fifteenRadian.degree(false) == Catch::Approx(glm::degrees(radian)));
            CHECK(fifteenRadian.radian(true) == Catch::Approx(radian));
            CHECK(fifteenRadian.radian(false) == Catch::Approx(radian));
        }

        {
            // negative wrap value
            constexpr float radian = -15.f + 3.f * radianCircle;
            constexpr float wrapRadian = -15.f + 2.f * radianCircle;

            LibMath::Radian minusFifteenRadian{ -15.f };
            CHECK(minusFifteenRadian.degree(true) == Catch::Approx(glm::degrees(wrapRadian)));
            CHECK(minusFifteenRadian.degree(false) == Catch::Approx(glm::degrees(radian)));
            CHECK(minusFifteenRadian.radian(true) == Catch::Approx(wrapRadian));
            CHECK(minusFifteenRadian.radian(false) == Catch::Approx(radian));
        }
    }

    SECTION("Comparator")
    {
        // compare with self
        LibMath::Radian self{ 1.2f };
        CHECK(self == self);

        // compare with same
        CHECK(LibMath::Radian{ 1.2f } == LibMath::Radian{ 1.2f });

        // compare with wrapped value
        CHECK(LibMath::Radian{ 1.2f } == LibMath::Radian(1.2f + radianCircle));

        // compare with wrap edge value
        CHECK(LibMath::Radian{ 0.f } == LibMath::Radian{ radianCircle });

        CHECK(LibMath::Radian{ -halfRadianCircle } == LibMath::Radian{ halfRadianCircle });
    }

    SECTION("Arithmetic")
    {
        {
            // operator +
            LibMath::Radian sum = LibMath::Radian(0.75f) + LibMath::Radian(0.5f);
            CHECK(sum.radian() == 1.25f);
        }

        {
            // operator +=
            LibMath::Radian sum(0.75f);
            sum += LibMath::Radian(0.5f);
            CHECK(sum.radian() == 1.25f);
        }

        {
            // operator -
            LibMath::Radian inverse = -LibMath::Radian(0.75f);
            CHECK(inverse.radian() == -0.75f);
        }

        {
            // operator -
            LibMath::Radian difference = LibMath::Radian(0.75f) - LibMath::Radian(0.5f);
            CHECK(difference.radian() == 0.25f);
        }

        {
            // operator -=
            LibMath::Radian difference(0.75f);
            difference -= LibMath::Radian(0.5f);
            CHECK(difference.radian() == 0.25f);
        }

        {
            // operator *
            LibMath::Radian product = LibMath::Radian(0.75f) * 10.f;
            CHECK(product.radian() == 7.5f - radianCircle);
        }

        {
            // operator *=
            LibMath::Radian product(0.75f);
            product *= 10.f;
            CHECK(product.radian() == 7.5f - radianCircle);
        }

        {
            // operator /
            LibMath::Radian quotient = LibMath::Radian(0.75f) / 4.f;
            CHECK(quotient.radian() == 0.1875f);
        }

        {
            // operator /=
            LibMath::Radian quotient(0.75f);
            quotient /= 4.f;
            CHECK(quotient.radian() == 0.1875f);
        }
    }

    SECTION("Functionality")
    {
        {
            // wrap value
            LibMath::Radian wrapAngle{ halfRadianCircle * 5.f };
            wrapAngle.wrap(false);
            CHECK(wrapAngle.raw() == Catch::Approx(halfRadianCircle));
        }

        {
            // prefere lower edge value
            LibMath::Radian wrapEdge{ radianCircle };
            wrapEdge.wrap(false);
            CHECK(wrapEdge.raw() == 0.f);

            wrapEdge = LibMath::Radian{ halfRadianCircle };
            wrapEdge.wrap(true);
            CHECK(wrapEdge.raw() == Catch::Approx(-halfRadianCircle));
        }
    }

    SECTION("Conversion")
    {
        LibMath::Radian radian{ LibMath::Degree{ 60.f } };
        CHECK(radian.raw() == Catch::Approx(glm::radians(60.f)));

        LibMath::Degree degree{ LibMath::Radian{ 1.2f } };
        CHECK(degree.raw() == Catch::Approx(glm::degrees(1.2f)));
    }
}
