#ifndef _UTILITIES
#define _UTILITIES


enum class ScopedEnum;
enum UnscopedEnum : std::uint8_t;


template <typename E>
constexpr typename std::underlying_type<E>::type toUType(E enumerator) noexcept
{
	return static_cast<typename std::underlying_type<E>::type>(enumerator);
}

class Utilities
{
public:
	static void foo();
	static void printScopedEnum(ScopedEnum myenum);
	static void printUnscopedEnum(UnscopedEnum myenum);
};

#endif
