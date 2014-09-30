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
  assert_true(*((int *) btree_search(btree, 5)) == 5);
  assert_true(*((int *) btree_search(btree, 1)) == 1);
  assert_true(*((int *) btree_search(btree, 2)) == 2);
  assert_true(*((int *) btree_search(btree, 3)) == 3);
  assert_true(*((int *) btree_search(btree, 7)) == 7);

  btree_free(btree);
}

void test_search_in_empty_btree() {
  BTree *btree = btree_create();
  assert_true(btree_search(btree, 8) == NULL);
  btree_free(btree);
}

void test_search_with_only_one_node() {
  BTree *btree = btree_create();
  BTreeEntry *entry = malloc(sizeof(BTreeEntry));
  int *value = malloc(sizeof(int));
  *value = 4;
  entry->key = 4;
  entry->value = value;
  btree->root->entries[0] = entry;
  assert_true(*((int *) btree_search(btree, 4)) == 4);
  btree_free(btree);
}

void test_when_value_not_in_tree() {
  BTree *btree = btree_create();
  BTreeEntry *entry = malloc(sizeof(BTreeEntry));
  int *value = malloc(sizeof(int));
  *value = 3;
  entry->key = 4;
  entry->value = value;

  /* Avoid memory issues */
  for (int i = 0; i < BTREE_NUM_ENTRIES; i++) {
    btree->root->entries[i] = NULL;
  }
  for (int i = 0; i < BTREE_NUM_CHILDREN; i++) {
    btree->root->children[i] = NULL;
  }

  btree->root->entries[0] = entry;

  assert_true(btree_search(btree, 12) == NULL);
  btree_free(btree);
}

void test_insert_sequentially_into_root() {
  BTree *btree = btree_create();
  int *value1 = malloc(sizeof(int));
  *value1 = 1;
  int *value2 = malloc(sizeof(int));
  *value2 = 30;
  int *value3 = malloc(sizeof(int));
  *value3 = 33;
  btree_insert(btree, 1, value1);
  btree_insert(btree, 30, value2);
  btree_insert(btree, 33, value3);
  assert_true(*((int *)btree->root->entries[0]->value) == 1);
  assert_true(*((int *)btree->root->entries[1]->value) == 30);
  assert_true(*((int *)btree->root->entries[2]->value) == 33);
}

void test_insert_nonsequentially_into_root() {
  BTree *btree = btree_create();
  int *value1 = malloc(sizeof(int));
  *value1 = 1;
  int *value2 = malloc(sizeof(int));
  *value2 = 30;
  int *value3 = malloc(sizeof(int));
  *value3 = 33;
  btree_insert(btree, 33, value3);
  btree_insert(btree, 30, value2);
  btree_insert(btree, 1, value1);
  assert_true(*((int *)btree->root->entries[0]->value) == 1);
  assert_true(*((int *)btree->root->entries[1]->value) == 30);
  assert_true(*((int *)btree->root->entries[2]->value) == 33);
}


/* run tests */
void test_fixture_btree() {
  test_fixture_start();
  run_test(test_create_btree);
  run_test(test_manually_build_and_search_btree);
  run_test(test_search_in_empty_btree);
  run_test(test_search_with_only_one_node);
  run_test(test_when_value_not_in_tree);
  run_test(test_insert_sequentially_into_root);
  run_test(test_insert_nonsequentially_into_root);
  test_fixture_end();
}

void all_tests() {
  test_fixture_btree();
}

int main(void) {
  return run_tests(all_tests);
}
