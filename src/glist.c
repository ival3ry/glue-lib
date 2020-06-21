#include "common.h"

list_status list_init(list_t *list, const size_t offset) {
  assert(list && "MSG: list is NULL");

  list->head = NULL;
  list->fprt_print = NULL;
  list->fptr_compare = NULL;
  list->offset = offset;

  return LIST_SUCCESS;
}

/* Add new_node to the right of current_node */
static list_status list_add_right(node_t *current_node, node_t *new_node) {
  list_status ret_status = LIST_ERROR;

  if (current_node == NULL) {
    fprintf(stderr, "Invalid current_node: NULL\n");
    goto error;
  }
  if (new_node == NULL) {
    fprintf(stderr, "Invalid new_node: NULL\n");
    goto error;
  }

  /* case: list is an one element */
  if (current_node->right == NULL) {
    current_node->right = new_node;
    new_node->left = current_node;
  } else {
    node_t *temp = current_node->right;
    current_node->right = new_node;
    new_node->left = current_node;
    new_node->right = temp;
    temp->left = new_node;
  }

  ret_status = LIST_SUCCESS;

error:
  return ret_status;
}

extern list_status list_add_node(list_t *list, node_t *node) {
  list_status ret_status = LIST_ERROR;

  if (node == NULL) {
    fprintf(stderr, "Failed to add an empty node");
    goto error;
  }
  if (list == NULL) {
    fprintf(stderr, "Failed to add a node to the list: list is empty");
    goto error;
  }

  node->left = NULL;
  node->right = NULL;

  if (list->head == NULL) {
    list->head = node;
    return LIST_SUCCESS;
  }

  node_t *head = list->head;
  if (list_add_right(node, head) == LIST_ERROR) {
    goto error;
  }
  list->head = node;

  ret_status = LIST_SUCCESS;

error:
  return ret_status;
}

static list_status _list_remove_node(node_t *node) {
  list_status ret_status = LIST_ERROR;

  if (!node) {
    fprintf(stderr, "Cannot remove the node: NULL\n");
    goto error;
  }

  /* case: null <- {remove node} -> <- {node} */
  if (!node->left) {
    if (node->right) {
      node->right->left = NULL;
      node->right = NULL;

      return LIST_SUCCESS;
    }
    return LIST_SUCCESS;
  }

  /* case: {node} -> <- {remove node} -> null */
  if (!node->right) {
    node->left->right = NULL;
    node->left = NULL;

    return LIST_SUCCESS;
  }

  /* case: ... {node} -> <- {remove node} -> <- {node} ... */
  node->left->right = node->right;
  node->right->left = node->left;
  node->left = NULL;
  node->right = NULL;

  ret_status = LIST_ERROR;

error:
  return ret_status;
}

extern list_status list_remove_node(list_t *list, node_t *node) {
  list_status ret_status = LIST_ERROR;

  if (!list) {
    fprintf(stderr, "Invalid list: NULL\n");
    goto error;
  }
  if (!node) {
    fprintf(stderr, "Invalid node: NULL\n");
    goto error;
  }

  node_t *head = list->head;
  if (head == node) {
    list->head = head->right;
    return LIST_SUCCESS;
  }

  ret_status = _list_remove_node(node);

error:
  return ret_status;
}

