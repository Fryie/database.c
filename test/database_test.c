#include "database.h"
#include "seatest.h"

void test_create_and_find() {
  create_table("TEST TABLE");
  create_table("TEST 2");
  assert_string_equal("TEST 2", find_table("TEST 2")->name);
  assert_string_equal("TEST TABLE", find_table("TEST TABLE")->name);
  drop_table("TEST TABLE");
  drop_table("TEST 2");
}

void test_fixture_database() {
  test_fixture_start();
  run_test(test_create_and_find);
  test_fixture_end();
}

void all_tests() {
  test_fixture_database();
}

int main(void) {
  return run_tests(all_tests);
}
