#include <string.h>
#include "container/treemap.h"
#include "utility/alloc.h"
#include "utility/macros.h"

struct TreeMapNode {
    struct TreeMapNode *parent;
    struct TreeMapNode *left;
    struct TreeMapNode *right;
    i8 balance;
};

#define tree_map_key(node) ((node) + 1)
#define tree_map_value(map, node) (((byte *) tree_map_key(node)) + (map)->key_size)

static inline void
tree_map_set_left(struct TreeMapNode *node, struct TreeMapNode *left) {
    node->left = left;
    if (left != NULL)
        left->parent = node;
}

static inline void
tree_map_set_right(struct TreeMapNode *node, struct TreeMapNode *right) {
    node->right = right;
    if (right != NULL)
        right->parent = node;
}

static inline void
tree_map_move_parent(struct TreeMap *map, struct TreeMapNode *to, struct TreeMapNode *from) {
    struct TreeMapNode *parent = from->parent;
    to->parent = parent;
    if (map->root == from)
        map->root = to;
    else
        (parent->left == from) ? tree_map_set_left(parent, to)
                               : tree_map_set_right(parent, to);
}

static inline struct TreeMapNode *
tree_map_new_node(struct TreeMap *map, const void *key) {
    struct TreeMapNode *node = xmalloc(sizeof(struct TreeMapNode) + map->key_size + map->value_size);
    node->parent = NULL;
    node->left = NULL;
    node->right = NULL;
    node->balance = 0;
    memcpy(tree_map_key(node), key, map->key_size);
    return node;
}

static inline void
tree_map_delete_node(struct TreeMap *map, struct TreeMapNode *node) {
    if (map->root == node)
        map->root = NULL;
    else {
        struct TreeMapNode *parent = node->parent;
        (parent->left == node) ? tree_map_set_left(parent, NULL)
                               : tree_map_set_right(parent, NULL);
    }
    xfree(node);
}

static inline void
tree_map_rotate_left(struct TreeMap *map, struct TreeMapNode *node) {
    struct TreeMapNode *right = node->right;
    tree_map_move_parent(map, right, node);
    tree_map_set_right(node, right->left);
    tree_map_set_left(right, node);
    node->balance -= MAX(right->balance, 0) + 1;
    right->balance += MIN(node->balance, 0) - 1;
}

static inline void
tree_map_rotate_right(struct TreeMap *map, struct TreeMapNode *node) {
    struct TreeMapNode *left = node->left;
    tree_map_move_parent(map, left, node);
    tree_map_set_left(node, left->right);
    tree_map_set_right(left, node);
    node->balance -= MIN(left->balance, 0) - 1;
    left->balance += MAX(node->balance, 0) + 1;
}
#include "stdio.h"
static inline void
tree_map_swap_node(struct TreeMap *map, struct TreeMapNode *node, struct TreeMapNode *successor) {
    struct TreeMapNode *temp_parent = successor->parent;
    tree_map_move_parent(map, successor, node);

    struct TreeMapNode *temp_left = node->left;
    tree_map_set_left(node, successor->left);

    struct TreeMapNode *temp_right = node->right;
    tree_map_set_right(node, successor->right);

    i8 temp_balance = node->balance;
    node->balance = successor->balance;
    successor->balance = temp_balance;

    if (temp_parent == node) {
        if (temp_left == successor) {
            tree_map_set_left(successor, node);
            tree_map_set_right(successor, temp_right);
        } else {
            tree_map_set_left(successor, temp_left);
            tree_map_set_right(successor, node);
        }
    } else {
        (temp_parent->left == successor) ? tree_map_set_left(temp_parent, node)
                                         : tree_map_set_right(temp_parent, node);
        tree_map_set_left(successor, temp_left);
        tree_map_set_right(successor, temp_right);
    }
}

static inline void
tree_map_destruct_recursive(struct TreeMapNode *node) {
    if (node == NULL)
        return;
    tree_map_destruct_recursive(node->left);
    tree_map_destruct_recursive(node->right);
    xfree(node);
}

static inline void
tree_map_emplace_fix_up(struct TreeMap *map, struct TreeMapNode *node) {
    for (struct TreeMapNode *parent = node->parent;
         parent != NULL;
         node = parent, parent = node->parent)
    {
        if (parent->left == node) {
            switch (--(parent->balance)) {
                case -2:
                    if (node->balance == 1)
                        tree_map_rotate_left(map, node);
                    tree_map_rotate_right(map, parent);
                    return;
                case -1:
                    continue;
                case 0:
                    return;
            }
        } else {
            switch (++(parent->balance)) {
                case 0:
                    return;
                case 1:
                    continue;
                case 2:
                    if (node->balance == -1)
                        tree_map_rotate_right(map, node);
                    tree_map_rotate_left(map, parent);
                    return;
            }
        }
    }
}

static inline void
tree_map_erase_fix_up(struct TreeMap *map, struct TreeMapNode *node) {
    for (struct TreeMapNode *parent = node->parent, *sibling;
         parent != NULL;
         node = parent, parent = node->parent)
    {
        if (parent->left == node) {
            switch (++(parent->balance)) {
                case 0:
                    continue;
                case 1:
                    return;
                case 2:
                    sibling = parent->right;
                    if (sibling->balance == -1)
                        tree_map_rotate_right(map, sibling);
                    tree_map_rotate_left(map, parent);
                    parent = parent->parent;
                    if (parent->balance == -1)
                        return;
                    continue;
            }
        } else {
            switch (--(parent->balance)) {
                case -2:
                    sibling = parent->left;
                    if (sibling->balance == 1)
                        tree_map_rotate_left(map, sibling);
                    tree_map_rotate_right(map, parent);
                    parent = parent->parent;
                    if (parent->balance == 1)
                        return;
                    continue;
                case -1:
                    return;
                case 0:
                    continue;
            }
        }
    }
}

void
tree_map_construct(struct TreeMap *map, usize key_size, usize value_size, Compare compare) {
    map->root = NULL;
    map->key_size = key_size;
    map->value_size = value_size;
    map->compare = compare;
}

void
tree_map_destruct(struct TreeMap *map) {
    tree_map_destruct_recursive(map->root);
}

void *
tree_map_emplace(struct TreeMap *map, const void *key) {
    if (map->root == NULL) {
        map->root = tree_map_new_node(map, key);
        return tree_map_value(map, map->root);
    }
    for (struct TreeMapNode *node = map->root, *new;;) {
        switch (map->compare(key, tree_map_key(node))) {
            case -1:
                if (node->left != NULL) {
                    node = node->left;
                    continue;
                }
                tree_map_set_left(node, new = tree_map_new_node(map, key));
                tree_map_emplace_fix_up(map, new);
                return tree_map_value(map, new);
            case 0:
                return tree_map_value(map, node);
            case 1:
                if (node->right != NULL) {
                    node = node->right;
                    continue;
                }
                tree_map_set_right(node, new = tree_map_new_node(map, key));
                tree_map_emplace_fix_up(map, new);
                return tree_map_value(map, new);
        }
    }
}

void
tree_map_insert(struct TreeMap *map, const void *key, const void *value) {
    memcpy(tree_map_emplace(map, key), value, map->value_size);
}

void
tree_map_erase(struct TreeMap *map, const void *key) {
    struct TreeMapNode *node = map->root;
    for (;;) {
        if (node == NULL)
            return;
        switch (map->compare(key, tree_map_key(node))) {
            case -1:
                node = node->left;
                continue;
            case 0:
                break;
            case 1:
                node = node->right;
                continue;
        }
        break;
    }
    for (;;) {
        if (node->left == node->right) {
            tree_map_erase_fix_up(map, node);
            tree_map_delete_node(map, node);
            return;
        }
        struct TreeMapNode *successor = (node->left != NULL) ? node->left : node->right;
        while (successor->right != NULL)
            successor = successor->right;
        tree_map_swap_node(map, node, successor);
    }
}

void *
tree_map_at(const struct TreeMap *map, const void *key) {
    for (struct TreeMapNode *node = map->root; node != NULL;) {
        switch (map->compare(key, tree_map_key(node))) {
            case -1:
                node = node->left;
                continue;
            case 0:
                return tree_map_value(map, node);
            case 1:
                node = node->right;
                continue;
        }
    }
    return NULL;
}

struct TreeMapIterator
tree_map_iterator_begin(struct TreeMap *map) {
    struct TreeMapNode **node = &(map->root);
    while (*node != NULL)
        node = &((*node)->left);
    return (struct TreeMapIterator) { map, *node, false };
}

struct TreeMapIterator
tree_map_iterator_rbegin(struct TreeMap *map) {
    struct TreeMapNode **node = &(map->root);
    while (*node != NULL)
        node = &((*node)->right);
    return (struct TreeMapIterator) { map, *node, true };
}

void
tree_map_iterator_increment(struct TreeMapIterator *it) {
    if (it->reverse) {
        
    } else {

    }
}

void
tree_map_iterator_erase(struct TreeMapIterator *it) {

}

void *
tree_map_iterator_key(struct TreeMapIterator *it) {
    return tree_map_key(it->node);
}

void *
tree_map_iterator_value(struct TreeMapIterator *it) {
    return tree_map_value(it->map, it->node);
}
