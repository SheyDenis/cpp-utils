/**
 * @file enum-map.hpp
 * @author denis.sheyer@gmail.com
 * @brief
 * @date 12025-01-01
 *
 */

#ifndef ENUM_MAP_HPP
#define ENUM_MAP_HPP

#include <type_traits>
#include <unordered_map>

namespace enum_utils {

/// @brief EnumMap is a class template that provides a mapping between an enum and a value, usually a `char const*`.
/// @tparam E struct that contains the enum type, the value type, the number of elements in the enum, and the sentinel value.
/// @details
/// The struct E must contain the following members:
/// - `key_type` is the enum type.
/// - `value_type` is the type of the value associated with the enum.
/// - `sentinel` is the sentinel value of the enum.
/// - `values` is an array of pairs of the enum and the value.
/// - `count` is the number of elements in `values`.
template <typename E>
struct EnumMap {
 public:
  using size_type = std::size_t const;
  /// @brief key_type is the enum type.
  using key_type = typename E::key_type;
  /// @brief value_type is the type of the value associated with the enum.
  using value_type = typename E::value_type;

  static_assert(std::is_enum_v<key_type>, "K must be an enum type");
  static_assert(std::is_same_v<decltype(E::count), size_type>, "E::count must be of type size_type");
  static_assert(std::is_same_v<decltype(E::sentinel), key_type const>, "E::sentinel must be of type key_type");
  static_assert(std::is_const_v<decltype(E::sentinel)>, "E::sentinel must be const");
  static_assert(std::is_const_v<decltype(E::count)>, "E::count must be const");

  static_assert(E::values.size() == E::count, "Invalid number of elements in values array");
  static_assert(static_cast<size_type>(E::sentinel) == E::count, "E::sentinel must be equal to E::count");
  static_assert(std::is_const_v<decltype(E::values)>, "E::values must be const");

 private:
  using Container = std::unordered_map<key_type, value_type>;
  Container values_;

 private:
  EnumMap() {
    for (auto const& [key, value] : E::values) {
      values_.insert({key, value});
    }
  }
  inline static EnumMap const& instance() {
    static EnumMap<E> inst;
    return inst;
  }

 public:
  EnumMap(EnumMap const&) = delete;
  EnumMap(EnumMap&&) = delete;
  EnumMap& operator=(EnumMap const&) = delete;
  EnumMap& operator=(EnumMap&&) = delete;

  [[nodiscard]] inline static value_type const& at(key_type const& key) noexcept {
    return instance().values_.at(key);
  }
  [[nodiscard]] inline static bool contains(key_type const& key) noexcept {
    return instance().values_.contains(key);
  }
  [[nodiscard]] static size_type constexpr size() noexcept {
    return E::count;
  }
};

}  // namespace enum_utils

#endif  // ENUM_MAP_HPP
