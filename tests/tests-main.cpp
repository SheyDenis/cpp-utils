/**
 * @file tests-main.cpp
 * @author denis.sheyer@gmail.com
 * @brief
 * @date 12024-07-06
 *
 */

#include <catch2/catch_session.hpp>

int main(int argc, char* argv[]) {
  Catch::Session session;
  return session.run(argc, argv);
}
