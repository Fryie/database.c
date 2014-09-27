#include "btree.h"
#include <stdlib.h>
#include <stdio.h>

/* private */
void *btree_node_search(BTreeNode *node, int key) {
  int i = 0;

  while (i < BTREE_NUM_ENTRIES && node->entries[i] && key > node->entries[i]->key) {
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

int btree_node_free(BTreeNode *node) {
  if (node) {
    for (int i = 0; i < BTREE_NUM_CHILDREN; i++) {
      /* free children recursively */
      btree_node_free(node->children[i]);
    }

    /* free entries */
    for (int i = 0; i < BTREE_NUM_ENTRIES; i++) {
      if (node->entries[i]) {
        if (node->entries[i]->value) {
          free(node->entries[i]->value);
        }
        free(node->entries[i]);
      }
    }

    free(node);
  }

  return 0;
}

/* public */
BTree *btree_create() { 
  BTree *btree = malloc(sizeof(BTree));
  BTreeNode *root = malloc(sizeof(BTreeNode));
  btree->root = root;
  return btree;
};

int btree_free(BTree *btree) {
  btree_node_free(btree->root);
  free(btree);
  return 0;
};

void *btree_search(BTree *btree, int key) {
  return btree_node_search(btree->root, key);
};
