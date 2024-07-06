/**
 * @file dummy.cpp
 * @author denis
 * @brief
 * @date 12024-07-06
 *
 */

#include <fmt/format.h>

namespace dummy {

std::string get_hello_string() {
  return "hello";
}

void print_hello() {
  fmt::println(get_hello_string());
}

}  // namespace dummy
