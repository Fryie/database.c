typedef struct BTreeNode {
} BTreeNode;

typedef struct BTree {
  BTreeNode *root;
} BTree;

BTree *btree_create();
int btree_free();
