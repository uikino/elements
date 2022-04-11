

#ifndef CYCFI_ELEMENTS_COMPATIBILITY_HPP__
#define CYCFI_ELEMENTS_COMPATIBILITY_HPP__

#include <utility>

namespace cycfi::elements {
#if defined(__cpp_char8_t)
template <std::size_t N> struct char8_t_string_literal {
  static constexpr inline std::size_t size = N;
  template <std::size_t... I>
  constexpr char8_t_string_literal(const char8_t (&r)[N],
                                   std::index_sequence<I...>)
      : s{r[I]...} {}
  constexpr char8_t_string_literal(const char8_t (&r)[N])
      : char8_t_string_literal(r, std::make_index_sequence<N>()) {}
  // auto operator<=>(const char8_t_string_literal &) = default;
  char8_t s[N];
};

template <char8_t_string_literal L, std::size_t... I>
constexpr inline const char as_char_buffer[sizeof...(I)] = {
    static_cast<char>(L.s[I])...};

template <char8_t_string_literal L, std::size_t... I>
constexpr auto &make_as_char_buffer(std::index_sequence<I...>) {
  return as_char_buffer<L, I...>;
}

constexpr char operator""_as_char(char8_t c) { return c; }

template <char8_t_string_literal L> constexpr auto &operator""_as_char() {
  return make_as_char_buffer<L>(std::make_index_sequence<decltype(L)::size>());
}

#define U8(x) u8##x##_as_char
#else
#define U8(x) u8##x
#endif
} // namespace cycfi::elements

#endif // CYCFI_ELEMENTS_COMPATIBILITY_HPP__