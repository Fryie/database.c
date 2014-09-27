#include "btree.h"
#include "seatest.h"

/* define tests */
void test_create_btree() {
  BTree *btree = btree_create();
  assert_true(btree->root != NULL);
  btree_free(btree);
}

/* run tests */
void test_fixture_btree() {
  test_fixture_start();
  run_test(test_create_btree);
  test_fixture_end();
}

void all_tests() {
  test_fixture_btree();
}

int main(void) {
  return run_tests(all_tests);
}
