/**
 * @file test_dummy.cpp
 * @author denis
 * @brief
 * @date 12024-07-06
 *
 */

#include <catch2/catch_all.hpp>

#include "dummy/dummy.hpp"

TEST_CASE("Dummy Test") {
  REQUIRE_THAT(dummy::get_hello_string(), Catch::Matchers::Equals("hello"));
  REQUIRE_NOTHROW(dummy::print_hello());
}
