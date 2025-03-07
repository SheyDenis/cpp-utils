/**
 * @file test-enum-map.cpp
 * @author denis.sheyer@gmail.com
 * @brief
 * @date 12025-01-01
 *
 */

#include <fmt/format.h>

#include <array>
#include <catch2/catch_all.hpp>
#include <cstdint>
#include <string>
#include <string_view>

#include "enum-utils/enum-map.hpp"

enum class DummyEnum : std::uint8_t {
  FIRST = 0,
  SECOND,
  THIRD,
  FOURTH,
  SENTINEL,
};

struct DummyEnumEnumMap {
  using key_type = DummyEnum;
  using value_type = std::pair<DummyEnum, char const*>;
  static key_type constexpr sentinel = key_type::SENTINEL;

  static std::array constexpr values = {
      value_type{key_type::FIRST, "FIRST"},
      value_type{key_type::SECOND, "SECOND"},
      value_type{key_type::THIRD, "THIRD"},
      value_type{key_type::FOURTH, "FOURTH"},
  };  // Omit template arguments to std::array so that they are deduced automatically.
  static std::size_t constexpr count = values.size();
  static_assert(count == 4, "Invalid number of elements in values array");
};

struct DummyEnumStringViewEnumMap {
  using key_type = DummyEnum;
  using value_type = std::pair<DummyEnum, std::string_view>;
  static key_type constexpr sentinel = key_type::SENTINEL;

  static std::array constexpr values = {
      value_type{key_type::FIRST, "FIRST"},
      value_type{key_type::SECOND, "SECOND"},
      value_type{key_type::THIRD, "THIRD"},
      value_type{key_type::FOURTH, "FOURTH"},
  };  // Omit template arguments to std::array so that they are deduced automatically.
  static std::size_t constexpr count = values.size();
  static_assert(count == 4, "Invalid number of elements in values array");
};

template <typename T>
std::string const& dummy_enum_to_value_type(DummyEnum const val) {
  return enum_utils::EnumMap<T>::at(val);
}

TEST_CASE("Test with DummyEnumEnumMap") {
  using enum_type = DummyEnumEnumMap;
  using value_type = enum_type::value_type::second_type;
  static_assert(std::is_same_v<value_type, char const*>, "value_type must be char const*");
  std::array const test_data = {
      std::pair<DummyEnum, std::string>{DummyEnum::FIRST, "FIRST"},
      std::pair<DummyEnum, std::string>{DummyEnum::SECOND, "SECOND"},
      std::pair<DummyEnum, std::string>{DummyEnum::THIRD, "THIRD"},
      std::pair<DummyEnum, std::string>{DummyEnum::FOURTH, "FOURTH"},
  };
  for (auto const& [enum_val, str_val] : test_data) {
    std::string const& result = dummy_enum_to_value_type<enum_type>(enum_val);
    REQUIRE_THAT(result, Catch::Matchers::Equals(str_val));
  }
}

TEST_CASE("Test with DummyEnumStringViewEnumMap") {
  using enum_type = DummyEnumStringViewEnumMap;
  using value_type = enum_type::value_type::second_type;
  static_assert(std::is_same_v<value_type, std::string_view>, "value_type must be std::string_view");
  std::array const test_data = {
      std::pair<DummyEnum, std::string>{DummyEnum::FIRST, "FIRST"},
      std::pair<DummyEnum, std::string>{DummyEnum::SECOND, "SECOND"},
      std::pair<DummyEnum, std::string>{DummyEnum::THIRD, "THIRD"},
      std::pair<DummyEnum, std::string>{DummyEnum::FOURTH, "FOURTH"},
  };
  for (auto const& [enum_val, str_val] : test_data) {
    std::string const& result = dummy_enum_to_value_type<enum_type>(enum_val);
    REQUIRE_THAT(result, Catch::Matchers::Equals(str_val));
  }
}

template <>
struct fmt::formatter<DummyEnum> : fmt::formatter<std::string> {
  static auto format(DummyEnum const& v, format_context& ctx) -> decltype(ctx.out()) {
    return format_to(ctx.out(), dummy_enum_to_value_type<DummyEnumEnumMap>(v));
  }
};

TEST_CASE("Test DummyEnumEnumMap with libfmt formatter") {
  std::array const test_data = {
      std::pair<DummyEnum, char const*>{DummyEnum::FIRST, "FIRST"},
      std::pair{DummyEnum::SECOND, "SECOND"},
      std::pair{DummyEnum::THIRD, "THIRD"},
      std::pair{DummyEnum::FOURTH, "FOURTH"},
  };

  for (auto const& [enum_val, str_val] : test_data) {
    REQUIRE_THAT(fmt::format(FMT_STRING("{:s}"), enum_val), Catch::Matchers::Equals(str_val));
  }
}
