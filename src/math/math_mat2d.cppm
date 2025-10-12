/*
* PURPOSE: Matrix 2x2.
* 
* 
* CLASSES:
* 	Mat2d: matrix 2x2 with row representation.
* 
* DESCRIPTION:
* 	The internal format used is row-major order. Consider that this is only relevant in terms of
* 	HOW operations are executed and not what they mean.
* 	So for example C = A * B means that the matrix B is applied first and then A.
*/

export module murph.math.mat2d;

import std;

import murph.types;
import murph.math.concepts;
import murph.math.vec2d;

export namespace murph::math {

template <CIsArithmetic T>
class Mat2d
{
public:
	using value_type = T;
	using col_t = Vec2d<T>; //column type
	using row_t = Vec2d<T>; //row type

	constexpr explicit Mat2d() noexcept = default;

	//Initialize the diagonal of the matrix with the value d
	constexpr explicit Mat2d(const T& d) noexcept {
		m[0].x = d;
		m[1].y = d;
	}


	constexpr explicit Mat2d(const row_t& row0, const row_t& row1) noexcept {
		m[0] = row0;
		m[1] = row1;
	}


	constexpr explicit Mat2d(const T a, const T b, const T c, const T d) noexcept :
		m{ row_t{a, b}, row_t{c, d} } { }

	constexpr auto operator==(const Mat2d&) const noexcept -> bool = default;

	template <std::convertible_to<T> U>
	[[nodiscard]]
	constexpr explicit operator Mat2d<U>() const noexcept {
		return Mat2d<U>{ static_cast<Vec2d<U>>(m[0]), static_cast<Vec2d<U>>(m[1]) };
	}

	template <typename Self>
	[[nodiscard]]
	constexpr auto&& operator[](this Self&& self, const i32 i, const i32 j) {
		return std::forward<Self>(self).m[i][j];
	}

	template <typename Self>
	[[nodiscard]]
	constexpr auto&& operator[](this Self&& self, const i32 i) {
		return std::forward<Self>(self).m[i];
	} 

	[[nodiscard]]
	constexpr auto operator+=(const Mat2d& rhs) noexcept -> Mat2d& {
		m[0] += rhs.m[0];
		m[1] += rhs.m[1];
		return *this;
	}

	[[nodiscard]]
	constexpr auto operator-=(const Mat2d& rhs) noexcept -> Mat2d& {
		m[0] -= rhs.m[0];
		m[1] -= rhs.m[1];
		return *this;
	}

	[[nodiscard]]
	constexpr auto operator*=(const T c) noexcept -> Mat2d& {
		m[0] *= c;
		m[1] *= c;
		return *this;
	}

	[[nodiscard]]
	constexpr auto operator*=(const Mat2d& rhs) noexcept -> Mat2d& {
		T x = m[0][0];
		T y = m[0][1];

		m[0][0] = x * rhs.m[0][0] + y * rhs.m[1][0];
		m[0][1] = x * rhs.m[1][0] + y * rhs.m[1][1];

		x = m[1][0];
		y = m[1][1];
		m[1][0] = x * rhs.m[0][0] + y * rhs.m[1][0];
		m[1][1] = x * rhs.m[1][0] + y * rhs.m[1][1];
		return *this;
	}

	[[nodiscard]]
	constexpr auto operator/=(const T c) -> Mat2d& {
		m[0] /= c;
		m[1] /= c;
		return *this;
	}
	
	constexpr auto Zero() noexcept -> void {
		m[0].Zero();
		m[1].Zero();
	}

	constexpr auto Identity() noexcept -> void {
		m[0].x = T{ 1 };
		m[0].y = T{ 0 };

		m[1].x = T{ 0 };
		m[1].y = T{ 1 };
	}

	[[nodiscard]]
	constexpr auto Determinant() const noexcept -> T {
		return m[0].x * m[1].y - m[0].y * m[1].x;
	}


	// Precondition: Determinant is != 0.
	[[nodiscard]]
	constexpr auto Inverse() const -> Mat2d {
		const auto d = Determinant();
		return Mat2d{ m[1][1] / d, -m[0][1] / d,
					-m[1][0] / d,  m[0][0] / d };
	}

	[[nodiscard]]
	constexpr auto ToString() const -> std::string
	{
		return std::format("{}\n{}", m[0].ToString(), m[1].ToString());
	}

private:
	row_t m[2];
}; 


/**************** TYPE ALIAS ************************/
using Mat2di = Mat2d<i32>;
using Mat2df = Mat2d<f32>;
/**************** TYPE ALIAS ************************/



/*****************************************************************/
//                  INLINE OPERATORS 
/*****************************************************************/


template <CIsArithmetic T>
[[nodiscard]]
constexpr auto operator+(const Mat2d<T>& lhs, const Mat2d<T>& rhs) noexcept -> Mat2d<T>
{
	return Mat2d<T>{ lhs(0) + rhs(0), lhs(1) + rhs(1) };
}


template <CIsArithmetic T>
[[nodiscard]]
constexpr auto operator-(const Mat2d<T>& lhs, const Mat2d<T>& rhs) noexcept -> Mat2d<T>
{
	return Mat2d<T>{ lhs(0) - rhs(0), lhs(1) - rhs(1) };
}


template <CIsArithmetic T>
[[nodiscard]]
constexpr auto operator*(Mat2d<T> lhs, const T c) -> Mat2d<T>
{
	return Mat2d<T>{ lhs(0) * c, lhs(1) * c };
}


template <CIsArithmetic T>
[[nodiscard]]
constexpr auto operator/(const Mat2d<T>& lhs, const T c) -> Mat2d<T>
{
	return Mat2d<T>{ lhs(0) / c, lhs(1) / c };
}


template <CIsArithmetic T>
[[nodiscard]]
constexpr auto operator*(Mat2d<T> lhs, const Mat2d<T>& rhs) noexcept -> Mat2d<T>
{
	lhs *= rhs;
	return lhs;
}


template <CIsArithmetic T>
[[nodiscard]]
constexpr auto operator*(const Mat2d<T>& lhs, const Vec2d<T>& rhs) noexcept -> Vec2d<T>
{
	return Mat2d<T>{ lhs(0).Dot(rhs), lhs(1).Dot(rhs) };
}

} //namespace murph::math