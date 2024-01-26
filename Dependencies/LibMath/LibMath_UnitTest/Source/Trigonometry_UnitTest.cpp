#include <Trigonometry.h>

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include <glm/glm.hpp>

TEST_CASE("Trigonometry", "[.all][trigonometry]")
{
    LibMath::Radian radian{ 1.2f };

    CHECK(LibMath::sin(radian) == Catch::Approx(glm::sin(1.2f)));
    CHECK(LibMath::cos(radian) == Catch::Approx(glm::cos(1.2f)));
    CHECK(LibMath::tan(radian) == Catch::Approx(glm::tan(1.2f)));

    CHECK(LibMath::asin(0.5f).radian() == Catch::Approx(glm::asin(0.5f)));
    CHECK(LibMath::acos(0.5f).radian() == Catch::Approx(glm::acos(0.5f)));
    CHECK(LibMath::atan(0.5f).radian() == Catch::Approx(glm::atan(0.5f)));
    CHECK(LibMath::atan(1.f, -2.f).radian() == Catch::Approx(glm::atan(1.f, -2.f)));
}
