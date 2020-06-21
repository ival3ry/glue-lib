/**
 * File for testing stuff
 */

#include "../src/common.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

typedef struct human
{
  char   name[30]; /* offset: 0 */
  int    age;      /* offset: 32 */
  node_t node;     /* offset: 40 */
} human_t;
void
human_print_info(const human_t *human);
/* print function needed by list's fptr_print */
void
human_print_info(const human_t *human)
{
  assert(human && "MSG: human_print_info: human is NULL");

  puts("Human Info:");
  fprintf(stdout, "\tName: %s\n", human->name);
  fprintf(stdout, "\tAge : %d\n", human->age);
}

int
main(void)
{

  human_t *adam = calloc(1, sizeof(human_t));
  assert(adam && "MSG: adam calloc failed");
  strncpy(adam->name, "Adam", strlen("Adam") + 1);
  adam->age = 120;
  list_node_init(&adam->node);

  human_t *eva = calloc(1, sizeof(human_t));
  assert(eva && "MSG: eva calloc failed");
  strncpy(eva->name, "Eva", strlen("Eva") + 1);
  eva->age = 120;
  list_node_init(&eva->node);

  /* List creation */
  list_t *list = calloc(1, sizeof(list_t));
  assert(list && "MSG: list calloc failed");

  list_init(list, OFFSETOF(human_t, node));
  // printf("sizeof(int)            : %ld\n", sizeof(int));
  // printf("OFFSETOF(human_t, name): %ld\n", OFFSETOF(human_t, name));
  // printf("OFFSETOF(human_t, age) : %ld\n", OFFSETOF(human_t, age));
  // printf("OFFSETOF(human_t, node): %ld\n", OFFSETOF(human_t, node));

  list_add_node(list, &adam->node);
  list_add_node(list, &eva->node);

  // clang-format off
  human_t *iterator = NULL;
  LIST_ITERATE_BEGIN(list, human_t, iterator) { 
    
    human_print_info(iterator); 
  
  } LIST_ITERATE_END
  // clang-format on

  /* Remove a node */
  list_remove_node(list, &adam->node);
  puts("List after removing the eva");

  // clang-format off
  iterator = NULL;
  LIST_ITERATE_BEGIN(list, human_t, iterator) { 
    
    human_print_info(iterator); 
  
  } LIST_ITERATE_END
  // clang-format on

  puts("Done!");
  return 0;
}