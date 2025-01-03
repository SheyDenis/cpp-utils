/**
 * @file test-enum-utils.cpp
 * @author denis.sheyer@gmail.com
 * @brief
 * @date 12024-09-29
 *
 */

#include <fmt/format.h>

#include <array>
#include <catch2/catch_all.hpp>
#include <cstdint>
#include <string>
#include <vector>

#include "enum-utils/enum-utils.hpp"

enum class DummyEnum : std::uint8_t {
  FIRST = 0,
  SECOND,
  THIRD,
  FOURTH,
  SENTINEL,
};
static std::initializer_list<std::pair<DummyEnum, char const*>> constexpr dummy_enum_values = {
    {DummyEnum::FIRST, "FIRST"},
    {DummyEnum::SECOND, "SECOND"},
    {DummyEnum::THIRD, "THIRD"},
    {DummyEnum::FOURTH, "FOURTH"},
    {DummyEnum::SENTINEL, "SENTINEL"},
};

template <typename T, typename S>
struct DummyEnumGenerator : public Catch::Generators::IGenerator<std::pair<DummyEnum, char const*>> {
 public:
  using EnumType = T;
  using StringType = S;
  using ValueType = std::pair<T, S>;

 private:
  std::vector<ValueType> values_;
  std::size_t idx_;

 public:
  DummyEnumGenerator(std::initializer_list<ValueType> values) : values_(values), idx_(0) {}
  bool next() override {
    if (idx_ < values_.size()) {
      ++idx_;
      return true;
    }
    return false;
  }

  ValueType const& get() const override {
    return values_.at(idx_);
  }

  T enum_value() const {
    return values_.at(idx_).first;
  }

  S string_value() const {
    return values_.at(idx_).second;
  }
};

ENUM_VALUES(DummyEnum, std::string_view, dummy_enum_values.begin(), dummy_enum_values.end());
ENUM_VALUES(DummyEnum, std::string, dummy_enum_values.begin(), dummy_enum_values.end());

TEST_CASE("Test enum values") {
  using DummyEnumValuesStringView = enum_utils::EnumValues<DummyEnum, std::string_view>;
  using DummyEnumValuesString = enum_utils::EnumValues<DummyEnum, std::string>;
  for (std::uint8_t i = 0; i <= static_cast<std::uint8_t>(DummyEnum::SENTINEL); ++i) {
    REQUIRE(DummyEnumValuesStringView::values.find(static_cast<DummyEnum>(i)) != DummyEnumValuesStringView::values.end());
    REQUIRE(DummyEnumValuesString::values.find(static_cast<DummyEnum>(i)) != DummyEnumValuesString::values.end());
  }
}

TEST_CASE("Test with std::string_view") {
  using RetType = std::string_view;
  std::array const test_data = {
      std::pair<DummyEnum, RetType>{DummyEnum::FIRST, "FIRST"},
      std::pair<DummyEnum, RetType>{DummyEnum::SECOND, "SECOND"},
      std::pair<DummyEnum, RetType>{DummyEnum::THIRD, "THIRD"},
      std::pair<DummyEnum, RetType>{DummyEnum::FOURTH, "FOURTH"},
      std::pair<DummyEnum, RetType>{DummyEnum::SENTINEL, "SENTINEL"},
  };
  for (auto const& [enum_val, str_val] : test_data) {
    RetType const result = enum_utils::enum_to_string<DummyEnum, RetType>(enum_val);
    REQUIRE_THAT(result.data(), Catch::Matchers::Equals(str_val.data()));
  }
}

TEST_CASE("Test with std::string") {
  using RetType = std::string;
  std::array const test_data = {
      std::pair<DummyEnum, RetType>{DummyEnum::FIRST, "FIRST"},
      std::pair<DummyEnum, RetType>{DummyEnum::SECOND, "SECOND"},
      std::pair<DummyEnum, RetType>{DummyEnum::THIRD, "THIRD"},
      std::pair<DummyEnum, RetType>{DummyEnum::FOURTH, "FOURTH"},
      std::pair<DummyEnum, RetType>{DummyEnum::SENTINEL, "SENTINEL"},
  };
  for (auto const& [enum_val, str_val] : test_data) {
    RetType const result = enum_utils::enum_to_string<DummyEnum, RetType>(enum_val);
    REQUIRE_THAT(result, Catch::Matchers::Equals(str_val));
  }
}

TEST_CASE("Test with std::string_view, invalid enum value") {
  REQUIRE_THROWS_AS(enum_utils::enum_to_string(static_cast<DummyEnum>(static_cast<int>(DummyEnum::SENTINEL) + 1)), std::out_of_range);
}

template <>
struct fmt::formatter<DummyEnum> : fmt::formatter<std::string> {
  static auto format(DummyEnum const& v, format_context& ctx) -> decltype(ctx.out()) {
    return format_to(ctx.out(), enum_utils::enum_to_string<DummyEnum, std::string>(v));
  }
};

TEST_CASE("Test with libfmt formatter") {
  auto enum_val = GENERATE(DummyEnumGenerator<DummyEnum, char const*>(dummy_enum_values));
  REQUIRE(fmt::format(FMT_STRING("{:s}"), enum_val.enum_value()) == enum_val.string_value());
}
