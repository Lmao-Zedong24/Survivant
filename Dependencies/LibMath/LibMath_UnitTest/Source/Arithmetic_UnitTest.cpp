#include <Arithmetic.h>

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include <glm/glm.hpp>

TEST_CASE("Arithmetic", "[.all][arithmetic]")
{
    float val{ 1.2f };

    CHECK(LibMath::floor(val) == Catch::Approx(glm::floor(val)));
    CHECK(LibMath::floor(val + .5f) == Catch::Approx(glm::floor(val + .5f)));

    CHECK(LibMath::ceil(val) == Catch::Approx(glm::ceil(val)));
    CHECK(LibMath::ceil(val + .5f) == Catch::Approx(glm::ceil(val + .5f)));

    CHECK(LibMath::round(val) == Catch::Approx(glm::round(val)));
    CHECK(LibMath::round(val + .5f) == Catch::Approx(glm::round(val + .5f)));

    CHECK(LibMath::clamp(val, 0.f, 1.f) == Catch::Approx(glm::clamp(val, 0.f, 1.f)));
    CHECK(LibMath::clamp(val, 1.f, 1.5f) == Catch::Approx(glm::clamp(val, 1.f, 1.5f)));
    CHECK(LibMath::clamp(val, 1.5f, 2.f) == Catch::Approx(glm::clamp(val, 1.5f, 2.f)));

    CHECK(LibMath::squareRoot(val) == Catch::Approx(glm::sqrt(val)));
    CHECK(LibMath::squareRoot(val * 2.f) == Catch::Approx(glm::sqrt(val * 2.f)));
    CHECK(LibMath::squareRoot(val * 4.f) == Catch::Approx(glm::sqrt(val * 4.f)));
    CHECK(LibMath::squareRoot(val * 20.f) == Catch::Approx(glm::sqrt(val * 20.f)));
    CHECK(LibMath::squareRoot(val * .5f) == Catch::Approx(glm::sqrt(val * .5f)));
    CHECK(LibMath::squareRoot(val * .25f) == Catch::Approx(glm::sqrt(val * .25f)));
    CHECK(LibMath::squareRoot(val * .01f) == Catch::Approx(glm::sqrt(val * .01f)));
    CHECK(LibMath::squareRoot(val * .001f) == Catch::Approx(glm::sqrt(val * .001f)));

    CHECK(LibMath::pow(val, 3) == Catch::Approx(glm::pow(val, 3)));
    CHECK(LibMath::pow(val, 2) == Catch::Approx(glm::pow(val, 2)));
    CHECK(LibMath::pow(val, 1) == Catch::Approx(glm::pow(val, 1)));
    CHECK(LibMath::pow(val, 0) == Catch::Approx(glm::pow(val, 0)));
    CHECK(LibMath::pow(val, -1) == Catch::Approx(glm::pow(val, -1)));
    CHECK(LibMath::pow(val, -2) == Catch::Approx(glm::pow(val, -2)));
    CHECK(LibMath::pow(val, -3) == Catch::Approx(glm::pow(val, -3)));

    CHECK(LibMath::wrap(90.f, -180.f, 180.f) == Catch::Approx(90.f));
    CHECK(LibMath::wrap(270.f, -180.f, 180.f) == Catch::Approx(-90.f));
    CHECK(LibMath::wrap(-375.f, -180.f, 180.f) == Catch::Approx(-15.f));

    CHECK(LibMath::min(val, 2.f * val) == Catch::Approx(glm::min(val, 2.f * val)));
    CHECK(LibMath::min(2.f * val, val) == Catch::Approx(glm::min(2.f * val, val)));

    CHECK(LibMath::max(val, 2.f * val) == Catch::Approx(glm::max(val, 2.f * val)));
    CHECK(LibMath::max(2.f * val, val) == Catch::Approx(glm::max(2.f * val, val)));

    CHECK(LibMath::abs(-val) == Catch::Approx(glm::abs(-val)));

    CHECK(LibMath::floatEquals(1.0f, 1.0f));
    CHECK(LibMath::floatEquals(1.1f, 1.1f));
    CHECK(LibMath::floatEquals(1.01f, 1.01f));
    CHECK(LibMath::floatEquals(1.001f, 1.001f));
    CHECK(LibMath::floatEquals(1.0001f, 1.0001f));
    CHECK(LibMath::floatEquals(1.00001f, 1.00001f));
    CHECK(LibMath::floatEquals(1.000001f, 1.000001f));
    CHECK(LibMath::floatEquals(1.000001f, 1.0000001f));
    CHECK(!LibMath::floatEquals(1.0001f, 1.00001f));
    CHECK(!LibMath::floatEquals(10.001f, 10.0001f));
    CHECK(!LibMath::floatEquals(100.01f, 100.001f));
    CHECK(!LibMath::floatEquals(1.000001f, 1.0000001f, 1.f));
    CHECK(!LibMath::floatEquals(10.00001f, 10.000001f, 1.f));
    CHECK(!LibMath::floatEquals(100.0001f, 100.00001f, 1.f));
}
