#include "database.h"
#include "seatest.h"

/* define tests */
void test_create_and_find_database() {
  create_table("TEST TABLE");
  create_table("TEST 2");
  assert_string_equal("TEST 2", find_table("TEST 2")->name);
  assert_string_equal("TEST TABLE", find_table("TEST TABLE")->name);
  drop_table("TEST TABLE");
  drop_table("TEST 2");
}

void test_drop_database() {
  create_table("TEST TABLE");
  drop_table("TEST TABLE");
  assert_true(find_table("TEST TABLE") == NULL);
}

void test_create_and_find_columns() {
  create_table("TEST TABLE");
  Table *table = find_table("TEST TABLE");
  add_column("TEST TABLE", "COL1");
  add_column("TEST TABLE", "COL2");
  assert_int_equal(1, find_column(table, "COL2"));
  assert_int_equal(0, find_column(table, "COL1"));
  assert_int_equal(-1, find_column(table, "NONEXISTANT"));
}

/* run tests */
void test_fixture_database() {
  test_fixture_start();
  run_test(test_create_and_find_database);
  run_test(test_drop_database);
  run_test(test_create_and_find_columns);
  test_fixture_end();
}

void all_tests() {
  test_fixture_database();
}

int main(void) {
  return run_tests(all_tests);
}
