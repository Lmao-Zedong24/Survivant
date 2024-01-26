#ifndef __LIBMATH__ARITHMETIC_H__
#define __LIBMATH__ARITHMETIC_H__
#include <limits>
#include <type_traits>
#include <cstddef>

namespace LibMath
{
	template <typename T>
	using floating_t = std::conditional_t<std::is_floating_point_v<T>, T, double>;

	/**
	 * \brief Returns the highest integer lower than or equal to the received value
	 * \param value The value to floor
	 * \return The highest integer value lower than or equal to the received value
	 */
    template <typename T>
	constexpr T	floor(T value);

	/**
	 * \brief Returns the lowest integer greater than or equal to the received value
	 * \param value The value to ceil
	 * \return The highest integer value lower than or equal to the received value
	 */
    template <typename T>
	constexpr T	ceil(T value);

	/**
	 * \brief Rounds a given value to the nearest integer
	 * \param value The value to round
	 * \return The received value rounded to the nearest integer
	 */
    template <typename T>
	constexpr T	round(T value);

	/**
	 * \brief Returns the received value limited to the given range
	 * \param value The value to clamp
	 * \param a The first value of the range
	 * \param b The second value of the range
	 * \return The received value limited to the given range
	 */
	template <typename T>
	constexpr T		clamp(T value, T a, T b);

	/**
	 * \brief Returns the closest bound of the given range to the received value
	 * \param value The value to snap
	 * \param a The first bound of the range
	 * \param b The second bound of the range
	 * \return The received value snapped to the closest bound of the given range
	 */
	template <typename T>
	constexpr T		snap(T value, T a, T b);

	/**
	 * \brief Wraps the given value inside a given range
	 * \param value The value to wrap
	 * \param a The first value of the range
	 * \param b The second value of the range
	 * \return value wrapped between min and max
	 */
    template <typename T>
	constexpr T	wrap(T value, T a, T b);

	/**
	 * \brief Approximates the square root of a value up to the given precision.
	 * \param value The value to compute the square root of
	 * \param precision The target precision of the computed square root
	 * \param maxSteps The maximum number of babylonian steps to perform
	 * \return An approximation of the square root of the given value
	 */
	template <typename T>
	constexpr T squareRoot(T value, floating_t<T> precision = std::numeric_limits<floating_t<T>>::epsilon(),
		size_t maxSteps = 16);

	/**
	 * \brief Raises the received value to the given exponent
	 * \param value The value to raise to the given exponent
	 * \param exponent The exponent to which the value must be raised
	 * \return The received value raised to the given exponent
	 */
    template <typename T>
	constexpr T	pow(T value, int exponent);

	/**
	 * \brief Returns the smallest of two given values
	 * \param a The first value
	 * \param b The second value
	 * \return a if a < b. b otherwise
	 */
	template <typename T>
	constexpr T		min(T a, T b);

	/**
	 * \brief Returns the largest of two given values
	 * \param a The first value
	 * \param b The second value
	 * \return a if a > b. b otherwise
	 */
	template <typename T>
	constexpr T		max(T a, T b);

	/**
	 * \brief Returns the absolute value of the given number
	 * \paran value The number whose absolute value must be returned
	 * \return The absolute value of the received number
	 */
    template <typename T>
	constexpr T	abs(T value);

	/**
	 * \brief Returns the sign of the given number
	 * \paran value The number whose absolute value must be returned
	 * \return -1 if the number is negative, 1 otherwise
	 */
    template <typename T>
	constexpr T	sign(T value);

	/**
	 * \brief Checks whether two floats can be considered equal
	 * \param a The first value to check
	 * \param b The second value to check
	 * \param scale The comparison's epsilon's scale
	 * \return True if a can be considered equal to b. False otherwise.
	 */
	template <typename T>
	constexpr bool	floatEquals(T a, T b, T scale = T(100));

	/**
	 * \brief Checks whether a given value is in the given range.
	 * \param value The value to check
	 * \param a The lower bound of the range
	 * \param b The upper bound of the range
	 * \return True if the value is between a and b inclusive. False otherwise.
	 */
	template <typename T>
	constexpr bool	isInRange(T value, T a, T b);
}

#include "Arithmetic.inl"

#endif // !__LIBMATH__ARITHMETIC_H__
