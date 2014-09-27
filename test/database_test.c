#include "database.h"
#include "seatest.h"

/* define tests */
void test_create_and_find_table() {
  init_db();
  create_table("TEST TABLE");
  create_table("TEST 2");
  assert_string_equal("TEST 2", find_table("TEST 2")->name);
  assert_string_equal("TEST TABLE", find_table("TEST TABLE")->name);
  free_db();
}

void test_drop_table() {
  init_db();
  create_table("TEST TABLE");
  drop_table(find_table("TEST TABLE"));
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
  free_db();
}

void test_drop_column() {
  init_db();
  create_table("TEST TABLE");
  Table *table = find_table("TEST TABLE");
  add_column(table, "COLUMN");
  drop_column(table, find_column(table, "COLUMN"));
  assert_true(find_column(table, "COLUMN") == NULL);
  free_db();
}

void test_insert_into_and_select_from() {
  init_db();
  create_table("TEST TABLE");
  Table *table = find_table("TEST TABLE");
  add_column(table, "COL1");
  add_column(table, "COL2");
  char *column_names[] = { "COL1", "COL2" };
  char *values[] = { "VAL1", "VAL2" };
  insert_into(table, column_names, values, 2);
  char *query_columns_1[] = {"COL2"};
  char *query_columns_2[] = {"COL2", "COL1"};
  hash_t *result1 = select_from(table, query_columns_1, 1, 0);
  hash_t *result2 = select_from(table, query_columns_2, 2, 0);
  assert_true(hash_size(result1) == 1);
  assert_string_equal(hash_get(result1, "COL2"), "VAL2");
  assert_true(hash_size(result2) == 2);
  assert_string_equal(hash_get(result2, "COL2"), "VAL2");
  assert_string_equal(hash_get(result2, "COL1"), "VAL1");

  hash_free(result1);
  hash_free(result2);
  free_db();
}

/* run tests */
void test_fixture_database() {
  test_fixture_start();
  run_test(test_create_and_find_table);
  run_test(test_drop_table);
  run_test(test_create_and_find_column);
  run_test(test_drop_column);
  run_test(test_insert_into_and_select_from);
  test_fixture_end();
}

void all_tests() {
  test_fixture_database();
}

int main(void) {
  return run_tests(all_tests);
}
