/*
* PURPOSE: define math concepts.
* 
* CONCEPTS:
*	CIsArithmetic: Check if a type is an arithmetic type (integral or floating).
*/

export module murph.math.concepts;

import std;

export namespace murph::math {
	template <typename T>
	concept CIsArithmetic = std::is_arithmetic_v<T>;
} // namespace murph::math