#ifndef BTREE_H
#define BTREE_H

#define BTREE_DEGREE 2
#define BTREE_NUM_ENTRIES 2*BTREE_DEGREE
#define BTREE_NUM_CHILDREN BTREE_NUM_ENTRIES+1

typedef struct BTreeEntry {
  int key;
  void *value;
} BTreeEntry;

struct BTreeNode {
  BTreeEntry *entries[BTREE_NUM_ENTRIES];
  struct BTreeNode *children[BTREE_NUM_CHILDREN];
  int next_index;
};

typedef struct BTreeNode BTreeNode;

typedef struct BTree {
  BTreeNode *root;
} BTree;

BTree *btree_create();
int btree_free(BTree *btree);
void *btree_search(BTree *btree, int key);
void btree_insert(BTree *btree, int key, void *value);
#endif
