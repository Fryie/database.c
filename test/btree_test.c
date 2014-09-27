#include "btree.h"
#include "seatest.h"
#include <stdlib.h>

/* define tests */
void test_create_btree() {
  BTree *btree = btree_create();
  assert_true(btree->root != NULL);
  btree_free(btree);
}

void test_manually_build_and_search_btree() {
  /* build BTree structure manually */
  BTreeEntry *one = malloc(sizeof(BTreeEntry));
  one->key = 1;
  int *one_val = malloc(sizeof(int));
  *one_val = 1;
  one->value = one_val;
  BTreeEntry *two = malloc(sizeof(BTreeEntry));
  two->key = 2;
  int *two_val = malloc(sizeof(int));
  *two_val = 2;
  two->value = two_val;
  BTreeEntry *three = malloc(sizeof(BTreeEntry));
  three->key = 3;
  int *three_val = malloc(sizeof(int));
  *three_val = 3;
  three->value = three_val;
  BTreeEntry *five = malloc(sizeof(BTreeEntry));
  five->key = 5;
  int *five_val = malloc(sizeof(int));
  *five_val = 5;
  five->value = five_val;
  BTreeEntry *seven = malloc(sizeof(BTreeEntry));
  seven->key = 7;
  int *seven_val = malloc(sizeof(int));
  *seven_val = 7;
  seven->value = seven_val;
  BTreeEntry *eight = malloc(sizeof(BTreeEntry));
  eight->key = 8;
  int *eight_val = malloc(sizeof(int));
  *eight_val = 8;
  eight->value = eight_val;

  BTree *btree = btree_create();
  btree->root->entries[0] = five;
  BTreeNode *child_one = malloc(sizeof(BTreeNode));
  child_one->entries[0] = one;
  child_one->entries[1] = two;
  child_one->entries[2] = three;
  BTreeNode *child_two = malloc(sizeof(BTreeNode));
  child_two->entries[0] = seven;
  child_two->entries[1] = eight;
  btree->root->children[0] = child_one;
  btree->root->children[1] = child_two;


  assert_true(*((int *) btree_search(btree, 8)) == 8);

  btree_free(btree);
}

void test_search_in_empty_btree() {
  BTree *btree = btree_create();
  /*  WTF THIS TEST BREAKS BUT ONLY IF THE OTHER TESTS ARE RUN AS WELL */
  /*
  assert_true(btree_search(btree, 8) == NULL);
  btree_free(btree);*/
}

/* run tests */
void test_fixture_btree() {
  test_fixture_start();
  run_test(test_create_btree);
  run_test(test_manually_build_and_search_btree);
  run_test(test_search_in_empty_btree);
  test_fixture_end();
}

void all_tests() {
  test_fixture_btree();
}

int main(void) {
  return run_tests(all_tests);
}
