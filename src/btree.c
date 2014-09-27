#include "btree.h"
#include <stdlib.h>
#include <stdio.h>

/* private */
void *btree_node_search(BTreeNode *node, int key) {
  int i = 0;
  while (i < BTREE_NUM_ENTRIES && node->entries[i] != NULL && key > node->entries[i]->key) {
    i++;
  }

  /* key found */
  if (i < BTREE_NUM_ENTRIES && node->entries[i] && node->entries[i]->key == key) {
    return node->entries[i]->value;
  }

  BTreeNode *child = node->children[i];

  /* key does not exist */
  if (!child) {
    return NULL;
  }

  return btree_node_search(child, key);
}

/* public */
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

void *btree_search(BTree *btree, int key) {
  return btree_node_search(btree->root, key);
};
