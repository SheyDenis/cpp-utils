/**
 * @file enum-utils.hpp
 * @author denis.sheyer@gmail.com
 * @brief
 * @date 12024-09-29
 *
 */

#ifndef ENUM_UTILS_HPP_
#define ENUM_UTILS_HPP_

#include <string_view>
#include <unordered_map>

#define ENUM_VALUES(enum_type, return_type, ...)                    \
  namespace enum_utils {                                            \
  template <>                                                       \
  struct EnumValues<enum_type, return_type> {                       \
    static const std::unordered_map<enum_type, return_type> values; \
  };                                                                \
  }                                                                 \
  const std::unordered_map<enum_type, return_type> enum_utils::EnumValues<enum_type, return_type>::values = {__VA_ARGS__}

namespace enum_utils {

template <typename T, typename R>
struct EnumValues {
  using enum_type = T;
  using return_type = R;
};

/// @brief Convert enum value to string representation using EnumValues map for enum type T and return type RT.
/// @tparam T enum type.
/// @tparam R return type.
/// @param val enum value.
/// @return string representation of enum value.
/// @throws std::out_of_range if val is not found in EnumValues map.
template <typename T, typename R = std::string_view>
static R const& enum_to_string(T val) noexcept(false) {
  static_assert(std::is_enum_v<T>, "T must be an enum type");
  return EnumValues<T, R>::values.at(val);
}

}  // namespace enum_utils

#endif  // ENUM_UTILS_HPP_
