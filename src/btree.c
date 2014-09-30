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
        free(node->entries[i]);
      }
    }

    free(node);
  }

  return 0;
}

BTreeNode *btree_node_create() {
  BTreeNode *node = malloc(sizeof(BTreeNode));
  node->next_index = 0;

  /* initialize entries and children to NULL */
  /* this is to avoid weird segfaulting */
  for (int i = 0; i < BTREE_NUM_ENTRIES; i++) {
    node->entries[i] = NULL;
  }
  for (int i = 0; i < BTREE_NUM_CHILDREN; i++) {
    node->children[i] = NULL;
  }

  return node;
}

/* public */
BTree *btree_create() { 
  BTree *btree = malloc(sizeof(BTree));
  btree->root = btree_node_create();

  return btree;
}

/* This will free the tree and its nodes
 * Freeing the values in the tree remains the
 * client's responsibility! */
int btree_free(BTree *btree) {
  btree_node_free(btree->root);
  free(btree);
  return 0;
}

void *btree_search(BTree *btree, int key) {
  return btree_node_search(btree->root, key);
}

/* WIP */
void btree_insert(BTree *btree, int key, void *value) {
  BTreeEntry *entry = malloc(sizeof(BTreeEntry));
  entry->key = key;
  entry->value = value;

  if (btree->root->next_index >= BTREE_NUM_ENTRIES) {
    printf("inserting into child: %d\n", key);
    if (!btree->root->children[0]) {
      btree->root->children[0] = btree_node_create();
    }
    printf("inserting at child index: %d\n", btree->root->children[0]->next_index);
    btree->root->children[0]->entries[btree->root->children[0]->next_index++] = entry;
    printf("next index is now: %d\n", btree->root->children[0]->next_index);
  }

  /* find place to insert */
  int i = btree->root->next_index;
  while (i > 0 && btree->root->entries[i-1]->key > key) {
    /* shift values as needed */
    btree->root->entries[i] = btree->root->entries[i-1];
    i--;
  }

  btree->root->entries[i] = entry;
  btree->root->next_index++;
}
