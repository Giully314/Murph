/*
* PURPOSE: Mathematical functions for different purposes.
* 
* CLASSES:
* 	Projection: Provide functions for projections.
* 	Transform3d: Provide functions for 3d transformations. (really temporary, not so much useful for a 2d engine)
* 	Transform2d: Functions for 2d transformations.
* 	Angles: Conversion between angles.
* 
* DESCRIPTION:
*	Utility math functions.
*/

export module murph.math.functions;

import std;

import murph.types;
import murph.math.concepts;
import murph.math.vector;
import murph.math.matrix;


export namespace murph::math {
 
struct Product
{
	template <CIsArithmetic T>
	[[nodiscard]]
	static constexpr auto Dot(const Vec2d<T>& v1, const Vec2d<T>& v2) noexcept -> T {
		return v1.Dot(v2);
	}


	template <CIsArithmetic T>
	[[nodiscard]]
	static constexpr auto Hadamard(const Vec2d<T>& v1, const Vec2d<T>& v2) noexcept -> Vec2d<T> {
		return { v1.x * v2.x, v1.y * v2.y };
	}


	template <CIsArithmetic T>
	[[nodiscard]]
	static constexpr auto Cross(const Vec2d<T>& v1, const Vec2d<T>& v2) noexcept -> T {
		return v1.x * v2.y - v1.y * v2.x;
	}

	template <CIsArithmetic T>
	[[nodiscard]]
	static constexpr auto Cross(const Vec3d<T>& v1, const Vec3d<T>& v2) noexcept -> Vec3d<T> {
		return Vec3d<T>{v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x};
	}
};



//*********************** PROJECTION *********************************************

struct Projection
{

	// https://www.scratchapixel.com/lessons/3d-basic-rendering/perspective-and-orthographic-projection-matrix/orthographic-projection-matrix
	template <CIsArithmetic T>
	[[nodiscard]]
	static constexpr auto Orthographic(const T l, const T b, const T r, const T t, 
										const T n, const T f) -> Mat4d<T>
	{
		Mat4d<T> ortho;

		ortho[0, 0] = static_cast<T>(2) / (r - l);
		ortho[0, 3] = -(r + l) / (r - l);
		ortho[1, 1] = static_cast<T>(2) / (t - b);
		ortho[1, 3] = -(t + b) / (t - b);
		ortho[2, 2] = -static_cast<T>(2) / (f - n);
		ortho[2, 3] = -(f + n) / (f - n);
		ortho[3, 3] = static_cast<T>(1);

		return ortho;
	}


	template <CIsArithmetic T>
	[[nodiscard]]
	static constexpr auto Orthographic(const T l, const T b, const T r, const T t) -> Mat4d<T>
	{
		Mat4d<T> ortho;

		ortho[0, 0] = static_cast<T>(2) / (r - l);
		ortho[0, 3] = -(r + l) / (r - l);
		ortho[1, 1] = static_cast<T>(2) / (t - b);
		ortho[1, 3] = -(t + b) / (t - b);
		ortho[2, 2] = -static_cast<T>(1);
		ortho[3, 3] = static_cast<T>(1);

		return ortho;
	}


	template <CIsArithmetic T>
	[[nodiscard]]
	static constexpr auto Viewport(const T width, const T height) -> Mat4d<T> {
		const auto c1 = static_cast<T>(1);
		const auto c2 = static_cast<T>(2);

		Mat4d<T> viewport{c1};

		viewport[0, 0] = width / c2;
		viewport[0, 3] = width / c2;

		viewport[1, 1] = height / c2;
		viewport[1, 3] = height / c2;

		return viewport;
	}

	template <CIsArithmetic T>
	[[nodiscard]]
	static constexpr auto Viewport(const T width, const T height, const T depth) -> Mat4d<T> {
		auto viewport = Viewport(width, height);
		const auto c1 = static_cast<T>(1);
		const auto c2 = static_cast<T>(2);

		viewport[2, 2] = depth / c2;
		viewport[2, 3] = depth / c2;

		return viewport;
	}


	// This is a simplified version of the perspective matrix.
	template <CIsArithmetic T>
	[[nodiscard]]
	static constexpr auto Perspective(const T f) -> Mat4d<T> {
		math::Mat4d<T> m{static_cast<T>(1)};

		m[3, 2] = -static_cast<T>(1)/f;

		return m;
	}
};

//*********************** PROJECTION *********************************************



//*********************** TRANSFORM 3D *****************************************

struct Transform3d
{
	template <CIsArithmetic T>
	[[nodiscard]]
	static constexpr auto Translate(const Vec3d<T>& v) noexcept -> Mat4d<T>
	{
		Mat4d<T> translation;

		translation[0, 0] = static_cast<T>(1);
		translation[0, 3] = v.x;
		translation[1, 1] = static_cast<T>(1);
		translation[1, 3] = v.y;
		translation[2, 2] = static_cast<T>(1);
		translation[2, 3] = v.z;
		translation[3, 3] = static_cast<T>(1);

		return translation;
	}

	/*Angle in radians*/
	template <CIsArithmetic T>
	[[nodiscard]]
	static constexpr auto RotateZ(const T a) noexcept -> Mat4d<T>
	{
		T c = std::cos(a);
		T s = std::sin(a);
		Mat4d<T> rotation;

		rotation[0, 0] = c;
		rotation[0, 1] = -s;
		rotation[1, 0] = s;
		rotation[1, 1] = c;
		rotation[2, 2] = static_cast<T>(1);
		rotation[3, 3] = static_cast<T>(1);

		return rotation;
	}

	template <CIsArithmetic T>
	[[nodiscard]]
	static constexpr auto Rotate(const T a) noexcept -> Mat4d<T>
	{
		T c = std::cos(a);
		T s = std::sin(a);
		Mat4d<T> rotation{static_cast<T>(1)};

		rotation[0, 0] = c;
		rotation[0, 2] = s;

		rotation[2, 0] = -s;
		rotation[2, 2] = c;

		return rotation;
	}


	template <CIsArithmetic T>
	[[nodiscard]]
	static constexpr auto Scale(const T c) noexcept -> Mat4d<T>
	{
		Mat4d<T> scale{ c };

		scale[3, 3] = static_cast<T>(1);

		return scale;
	}


	template <CIsArithmetic T>
	[[nodiscard]]
	static constexpr auto Scale(const Vec3d<T>& v) noexcept -> Mat4d<T>
	{
		Mat4d<T> scale;

		scale(0, 0) = v.x;

		scale(1, 1) = v.y;

		scale(2, 2) = v.z;

		scale(3, 3) = static_cast<T>(1);

		return scale;
	}
};

//*********************** TRANSFORM 3D *****************************************




//*********************** TRANSFORM 2D *****************************************

struct Transform2d
{
	//Positive theta values rotate counter clockwise.
	template <CIsArithmetic T>
	[[nodiscard]]
	static constexpr auto Rotate(const T theta) noexcept -> Mat2d<T>
	{
		Mat2d<T> rotation;

		const T c = std::cos(theta);
		const T s = std::sin(theta);

		rotation(0, 0) = c;
		rotation(0, 1) = -s;

		rotation(1, 0) = s;
		rotation(1, 1) = c;

		return rotation;
	}


	template <CIsArithmetic T>
	[[nodiscard]]
	static constexpr auto Scale(const T c) -> Mat2d<T>
	{
		Mat2d<T> scale{ c };
		return scale;
	}


	template <CIsArithmetic T>
	[[nodiscard]]
	static constexpr auto Scale(const Vec2d<T>& v) noexcept -> Mat2d<T>
	{
		Mat2d<T> scale;

		scale(0, 0) = v.x;
		scale(1, 1) = v.y;

		return scale;
	}


	template <CIsArithmetic T>
	[[nodiscard]]
	static constexpr auto RotateCounterClock90(const Vec2d<T>& v) noexcept -> Vec2d<T>
	{
		return Vec2d<T>{-v.y, v.x};
	}

	template <CIsArithmetic T>
	[[nodiscard]]
	static constexpr auto RotateClock90(const Vec2d<T>& v) noexcept -> Vec2d<T>
	{
		return Vec2d<T>{v.y, -v.x};
	}

};

//*********************** TRANSFORM 2D *****************************************




//*************************** ANGLES ********************************************

struct Angles
{
	template <CIsArithmetic T>
	[[nodiscard]]
	static constexpr auto ToRad(const T a) -> T
	{
		return static_cast<T>(a * std::numbers::pi / 180.0);
	}

	template <CIsArithmetic T>
	[[nodiscard]]
	static constexpr auto ToDeg(const T a) -> T
	{
		return static_cast<T>(a * 180.0 / std::numbers::pi);
	}
};

//*************************** ANGLES ********************************************


} //namespace murph::math