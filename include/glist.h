/**
 * glist.h - Self-pointed doubly-linker list
 */
#ifndef GLIST_H
#define GLIST_H

#include <stddef.h>
#include <stdint.h>

#define OFFSETOF(struct_name, field_name) \
  (size_t) & ((struct_name *)0)->field_name

// clang-format off
#define LIST_ITERATE_BEGIN(list_ptr, struct_type, node_ptr)              \
  {                                                                      \
    node_t *curr_node = NULL;                                            \
    node_t *next_node = NULL;                                            \
    for (curr_node = list_ptr->head; curr_node; curr_node = next_node) { \
      next_node = curr_node->right;                                      \
      node_ptr  = (struct_type *)((char *)curr_node - list_ptr->offset);

#define LIST_ITERATE_END }}
// clang-format on

typedef enum { LIST_ERROR, LIST_SUCCESS } list_status;

typedef struct node {
  struct node *left;
  struct node *right;
} node_t;

/**
 * @brief Doubly-linked list
 */
typedef struct list {
  node_t *head;
  void (*fprt_print)(const void *);
  int (*fptr_compare)(const void *, const void *);
  size_t offset;
} list_t;

list_status list_init(list_t *list, const size_t offset);

static inline void list_node_init(node_t *node) {
  node->left = NULL;
  node->right = NULL;
}

/**
 * @brief Add new node to the HEAD of the list
 */
extern list_status list_add_node(list_t *list, node_t *node);

extern list_status list_remove_node(list_t *list, node_t *node);

#endif

