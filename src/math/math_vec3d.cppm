/*
* PURPOSE: Vector 3d.
* 
* CLASSES:
* 	Vec3d: vector 3d with x, y and z components.
*/

export module murph.math.vec3d;

import std;

import murph.types;
import murph.math.concepts;
import murph.math.vec2d;

export namespace murph::math {
	
template <CIsArithmetic T>
class Vec3d {
public:
	using value_type = T;

	constexpr explicit Vec3d() noexcept = default;

	constexpr explicit Vec3d(const T x_, const T y_, const T z_) noexcept : x(x_), y(y_), z(z_) { }

	constexpr explicit Vec3d(const Vec2d<T>& v, const T z_) noexcept : x(v.x), y(v.y), z(z_) { }

	constexpr auto operator==(const Vec3d&) const noexcept -> bool = default;

	template <std::convertible_to<T> U>
	[[nodiscard]]
	constexpr explicit operator Vec3d<U>() const noexcept {
		return Vec3d<U>{static_cast<U>(x), static_cast<U>(y), static_cast<U>(z)};
	}
	
	[[nodiscard]]
	constexpr auto&& operator[](this auto&& self, const u32 idx) {
		switch (idx) {
			case 0: return self.x;
			case 1: return self.y;
			case 2: return self.z;
		}
		throw std::out_of_range{ "Vec3d access error" };
	}
	
	[[nodiscard]]
	constexpr auto operator+=(const Vec3d& rhs) noexcept -> Vec3d& {
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		return *this;
	}

	[[nodiscard]]
	constexpr auto operator-=(const Vec3d& rhs) noexcept -> Vec3d& {
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		return *this;
	}

	[[nodiscard]]
	constexpr auto operator*=(const T c) noexcept -> Vec3d& {
		x *= c;
		y *= c;
		z *= c;
		return *this;
	}

	[[nodiscard]]
	constexpr auto operator/=(const T c) -> Vec3d& {
		x /= c;
		y /= c;
		z /= c;
		return *this;
	}

	constexpr auto Zero() noexcept -> void {
		x = T{ 0 };
		y = T{ 0 };
		z = T{ 0 };
	}

	constexpr auto Normalize() -> void {
		T l = x * x + y * y + z * z;
		if (l != 0) {
			l = std::sqrt(l);
			x /= l;
			y /= l;
			z /= l;
		}
	}

	[[nodiscard]]
	constexpr auto Normalized() const -> Vec3d {
		Vec3d copy = *this;
		copy.Normalize();
		return copy;
	}

	[[nodiscard]]
	constexpr auto Length() const noexcept -> T {
		return std::sqrt(x * x + y * y + z * z);
	}

	[[nodiscard]]
	constexpr auto LengthSqr() const noexcept -> T {
		return x * x + y * y + z * z;
	}

	[[nodiscard]]
	constexpr auto Dot(const Vec3d& rhs) const noexcept -> T {
		return x * rhs.x + y * rhs.y + z * rhs.z;
	}

	[[nodiscard]]
	constexpr auto ToString() const -> std::string {
		return std::format("( {}  {}  {})", x, y, z);
	}


public:
	T x{ 0 };
	T y{ 0 };
	T z{ 0 };
}; 


/**************** TYPE ALIAS ************************/
using Vec3di = Vec3d<i32>;
using Vec3du = Vec3d<u32>;
using Vec3df = Vec3d<f32>;
/**************** TYPE ALIAS ************************/



/*****************************************************************/
//                   OPERATORS 
/*****************************************************************/


template <CIsArithmetic T>
[[nodiscard]]
constexpr auto operator+(const Vec3d<T>& lhs, const Vec3d<T>& rhs) noexcept -> Vec3d<T>
{
	return Vec3d<T>{ lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z };
}


template <CIsArithmetic T>
[[nodiscard]]
constexpr auto operator-(const Vec3d<T>& lhs, const Vec3d<T>& rhs) noexcept -> Vec3d<T>
{
	return Vec3d<T>{ lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z };
}


template <CIsArithmetic T>
[[nodiscard]]
constexpr auto operator*(const Vec3d<T>& lhs, const T c) noexcept -> Vec3d<T>
{
	return Vec3d<T>{ lhs.x * c, lhs.y * c, lhs.z * c };
}

template <CIsArithmetic T>
[[nodiscard]]
constexpr auto operator*(const T c, const Vec3d<T>& lhs) noexcept -> Vec3d<T>
{
	return Vec3d<T>{ lhs.x * c, lhs.y * c, lhs.z * c };
}


template <CIsArithmetic T>
[[nodiscard]]
constexpr auto operator/(Vec3d<T> lhs, const T c) -> Vec3d<T>
{
	return Vec3d<T>{ lhs.x / c, lhs.y / c, lhs.z / c };
}

} //namespace murph::math


// ********************* CUSTOM FORMATTER **************************

template <typename T>
struct std::formatter<murph::math::Vec3d<T>> {
    constexpr auto parse(std::format_parse_context& ctx) {
        return ctx.begin();
    }

    auto format(const murph::math::Vec3d<T>& obj, std::format_context& ctx) const {
        return std::format_to(ctx.out(), "({}, {}, {})", obj.x, obj.y, obj.z);
    }
};