#include "btree.h"
#include <stdlib.h>

BTree *btree_create() { 
  BTree *btree = malloc(sizeof(BTree));
  BTreeNode *root = malloc(sizeof(BTreeNode));
  btree->root = root;
  return btree;
};

int btree_free(BTree *btree) {
  if (btree->root) {
    free(btree->root);
  }
  free(btree);
};

void *btree_search(BTree *btree, int key) {};
