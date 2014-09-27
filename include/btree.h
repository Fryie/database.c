#ifndef BTREE_H
#define BTREE_H

#define BTREE_DEGREE 2

typedef struct BTreeEntry {
  int key;
  void *value;
} BTreeEntry;

struct BTreeNode {
  BTreeEntry *entries[2*BTREE_DEGREE-1];
  struct BTreeNode *children[2*BTREE_DEGREE];
};

typedef struct BTreeNode BTreeNode;

typedef struct BTree {
  BTreeNode *root;
} BTree;

BTree *btree_create();
int btree_free(BTree *btree);
void *btree_search(BTree *btree, int key);
#endif
