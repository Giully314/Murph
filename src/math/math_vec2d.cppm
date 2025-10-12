/*
* gargantua/math/math_vec2d.ixx
* 
* PURPOSE: Vector 2d.
* 
* CLASSES:
* 	Vec2d: vector 2d with x and y components.
*/

export module murph.math.vec2d;

import std;

import murph.types;
import murph.math.concepts;

export namespace murph::math {

template <CIsArithmetic T>
class Vec2d {
public:
	using value_type = T;

	constexpr explicit Vec2d() noexcept = default;

	constexpr explicit Vec2d(const T x_, const T y_) noexcept : x(x_), y(y_) {}

	constexpr auto operator==(const Vec2d&) const noexcept -> bool = default;
	
	template <std::convertible_to<T> U> 
	[[nodiscard]] 
	constexpr explicit operator Vec2d<U>() const noexcept  {
		return Vec2d<U>{static_cast<U>(x), static_cast<U>(y)};
	}

	[[nodiscard]]
	constexpr auto&& operator[](this auto&& self, const u32 idx) {
		switch (idx) {
			case 0: return self.x;
			case 1: return self.y;
		}
		throw std::out_of_range{ "Vec2d access error" };
	}

	constexpr auto operator+=(const Vec2d& rhs) noexcept -> Vec2d& {
		x += rhs.x;
		y += rhs.y;
		return *this;
	}

	constexpr auto operator-=(const Vec2d& rhs) noexcept -> Vec2d& {
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}

	constexpr auto operator*=(const T c) noexcept -> Vec2d& {
		x *= c;
		y *= c;
		return *this;
	}
	
	constexpr auto operator/=(const T c) noexcept -> Vec2d& {
		x /= c;
		y /= c;
		return *this;
	}

	auto Zero() noexcept -> void {
		x = T{ 0 };
		y = T{ 0 };
	}

	constexpr auto Normalize() -> void {
		T l = x * x + y * y;
		if (l != 0)
		{
			l = std::sqrt(l);
			x /= l;
			y /= l;
		}
	}

	[[nodiscard]]
	constexpr auto Normalized() const -> Vec2d {
		Vec2d copy = *this;
		copy.Normalize();
		return copy;
	}

	[[nodiscard]]
	constexpr auto Length() const noexcept -> T {
		return std::sqrt(x * x + y * y);
	}

	[[nodiscard]]
	constexpr auto LengthSqr() const noexcept -> T {
		return x * x + y * y;
	}

	[[nodiscard]]
	constexpr auto Dot(const Vec2d& rhs) const noexcept -> T {
		return x * rhs.x + y * rhs.y;
	}

	[[nodiscard]]
	constexpr auto ToString() const -> std::string {
		return std::format("( {}  {} )", x, y);
	}

public:
	T x{ 0 };
	T y{ 0 };
}; 

/**************** TYPE ALIAS ************************/
using Vec2di = Vec2d<i32>;
using Vec2du = Vec2d<u32>;
using Vec2df = Vec2d<f32>;
/**************** TYPE ALIAS ************************/



/*****************************************************************/
//                  OPERATORS 
/*****************************************************************/


template <CIsArithmetic T>
[[nodiscard]]
constexpr auto operator+(const Vec2d<T>& lhs, const Vec2d<T>& rhs) noexcept -> Vec2d<T>
{
	return Vec2d<T>{ lhs.x + rhs.x, lhs.y + rhs.y };
}


template <CIsArithmetic T>
[[nodiscard]]
constexpr auto operator-(const Vec2d<T>& lhs, const Vec2d<T>& rhs) noexcept -> Vec2d<T>
{
	return Vec2d<T>{ lhs.x - rhs.x, lhs.y - rhs.y };
}


template <CIsArithmetic T>
[[nodiscard]]
constexpr auto operator*(const Vec2d<T>& lhs, const T c) noexcept -> Vec2d<T>
{
	return Vec2d<T>{ c * lhs.x, c * lhs.y };
}


template <CIsArithmetic T>
[[nodiscard]]
constexpr auto operator*(const T c, const Vec2d<T>& lhs) noexcept -> Vec2d<T>
{
	return Vec2d<T>{ c * lhs.x, c * lhs.y };
}


template <CIsArithmetic T>
[[nodiscard]]
constexpr auto operator/(const Vec2d<T>& lhs, const T c) -> Vec2d<T>
{
	return Vec2d<T>{ lhs.x / c, lhs.y / c };
}


template <CIsArithmetic T>
[[nodiscard]]
constexpr auto operator-(const Vec2d<T>& v) noexcept -> Vec2d<T>
{
	return Vec2d<T>{-v.x, -v.y};
}

} //namespace murph::math

