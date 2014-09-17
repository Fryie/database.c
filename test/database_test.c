#include "database.h"
#include "seatest.h"

/* define tests */
void test_create_and_find_table() {
  init_db();

  create_table("TEST TABLE");
  create_table("TEST 2");
  assert_string_equal("TEST 2", find_table("TEST 2")->name);
  assert_string_equal("TEST TABLE", find_table("TEST TABLE")->name);
  drop_table("TEST TABLE");
  drop_table("TEST 2");
  free_db();
}

void test_drop_table() {
  init_db();
  create_table("TEST TABLE");
  drop_table("TEST TABLE");
  assert_true(find_table("TEST TABLE") == NULL);
  free_db();
}

void test_create_and_find_column() {
  init_db();
  create_table("TEST TABLE");
  Table *table = find_table("TEST TABLE");
  add_column(table, "COL1");
  add_column(table, "COL2");
  assert_string_equal("COL2", find_column(table, "COL2")->name);
  assert_string_equal("COL1", find_column(table, "COL1")->name);
  assert_true(find_column(table, "NONEXISTANT") == NULL);
  drop_table("TEST TABLE");
  free_db();
}

/* run tests */
void test_fixture_database() {
  test_fixture_start();
  run_test(test_create_and_find_table);
  run_test(test_drop_table);
  run_test(test_create_and_find_column);
  test_fixture_end();
}

void all_tests() {
  test_fixture_database();
}

int main(void) {
  return run_tests(all_tests);
}
