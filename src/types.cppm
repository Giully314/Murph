export module murph.types;

import std;

export namespace murph {
    using u8 = std::uint8_t;
	using u16 = std::uint16_t;
	using u32 = std::uint32_t;
	using u64 = std::uint64_t;

	using i8 = std::int8_t;
	using i16 = std::int16_t;
	using i32 = std::int32_t;
	using i64 = std::int64_t;

	using f32 = float;
	using f64 = double;

	template <typename T>
	using non_null_ptr = T*;

	// template <typename T>
	// using non_owned_ptr = T*;


	inline constexpr auto operator ""_u8 (unsigned long long a) noexcept -> u8 {
		return static_cast<u8>(a);
	}
	
	inline constexpr auto operator ""_u16 (unsigned long long a) noexcept -> u16 {
		return static_cast<u16>(a);
	}
	
	inline constexpr auto operator ""_u32 (unsigned long long a) noexcept -> u32 {
		return static_cast<u32>(a);
	}
	
	inline constexpr auto operator ""_i8 (unsigned long long a) noexcept -> i8 {
		return static_cast<i8>(a);
	}
	
	inline constexpr auto operator ""_i16 (unsigned long long a) noexcept -> i16 {
		return static_cast<i16>(a);
	}
	
	inline constexpr auto operator ""_i32 (unsigned long long a) noexcept -> i32 {
		return static_cast<i32>(a);
	}
} // namespace murph
