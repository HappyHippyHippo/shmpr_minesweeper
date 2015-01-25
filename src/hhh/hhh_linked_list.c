#include <hhh/hhh_linked_list.h>
#include <hhh/hhh_error.h>

#include <string.h>
#include <stdio.h>

/* definition od the linked list structure */
struct LinkedList {
  size_t max;
  size_t size;
  size_t element_size;
  int innode;
  void * first;
};

/* allusion of the linked list internal auxiliary functions */
void * llnode_get_next(LinkedList * ll, void * node);
void * llnode_set_next(LinkedList * ll, void * node, void * target);
void * llnode_get_element(LinkedList * ll, void * node);
void * llnode_set_element(LinkedList * ll, void * node, void * target);
int    ll_swap_ex(LinkedList * ll, void * node1, void * node2);

LinkedList * ll_create(size_t element_size, size_t max, int innode) {
  LinkedList * created = NULL;

  /* argument check */
  if (element_size == 0) {
    return NULL;
  }

  /* allocate memory to store the linked list */
  if ((created = malloc(sizeof(LinkedList))) == NULL) {
    return NULL;
  }

  /* initialize the created linked list */
  created->max = max;
  created->size = 0;
  created->element_size = element_size;
  created->innode = innode;

  /* return the created linked list */
  return created;
}

int ll_destroy(LinkedList ** ll) {
  /* argument check */
  if (ll == NULL || *ll == NULL) {
    return ERROR_INVALID_ARGUMENT;
  }

  /* clear the linked list of all his stored contents */
  ll_clear(*ll);

  /* free the allocated memory of the linked list */
  free(*ll);
  *ll = NULL;

  /* signal successful operation */
  return ERROR_OK;
}

int ll_max(LinkedList * ll, size_t * size) {
  /* argument check */
  if (ll == NULL || size == NULL) {
    return ERROR_INVALID_ARGUMENT;
  }

  /* retrieve the maximum number of elements of the linked list */
  *size = ll->max;

  /* signal successful operation */
  return ERROR_OK;
}

int ll_size(LinkedList * ll, size_t * size) {
  /* argument check */
  if (ll == NULL || size == NULL) {
    return ERROR_INVALID_ARGUMENT;
  }

  /* retrieve the current number of elements stored in the linked list */
  *size = ll->size;

  /* signal successful operation */
  return ERROR_OK;
}

int ll_swap(LinkedList * ll, size_t pos1, size_t pos2) {
  void * node1 = NULL, * node2 = NULL;
  size_t index = 0;

  /* argument check */
  if (ll == NULL) {
    return ERROR_INVALID_ARGUMENT;
  }

  /* argument check */
  if (pos1 >= ll->size || pos2 >= ll->size) {
    return ERROR_INVALID_INDEX;
  }

  /* check if the elements to be swapped are in the same position */
  if (pos1 == pos2) {
    return ERROR_OK;
  }

  /* elements search cycle */
  for (index = 0, node1 = node2 = ll->first; index < pos1 || index < pos2; index++) {
    /* check if the first element pointer is to be incremented */
    if (index < pos1) {
      node1 = llnode_get_next(ll, node1);
    }
    /* check if the second element pointer is to be incremented */
    if (index < pos2) {
      node2 = llnode_get_next(ll, node2);
    }
  }

  /* return the result of the two elements swapping function call */
  return ll_swap_ex(ll, node1, node2);
}

int ll_sort(LinkedList * ll, int (*compare)(void *, void *)) {
  void * unorded = NULL, * smaller = NULL, * iter = NULL;
  int result = ERROR_OK;

  /* argument check */
  if (ll == NULL || compare == NULL) {
    return ERROR_INVALID_ARGUMENT;
  }

  /* check if the linked list as enough elements to be sorted */
  if (ll->size <= 1) {
    return ERROR_OK;
  }

  /* start the selectino sort algorithm */
  unorded = ll->first;
  do {
    /* choose the first element of the unorded elements as the smallest one */
    smaller = unorded;

    /* iterate thru all the remaining unorded elements searching fo the smallest */
    iter = * (void **) unorded;
    while (iter != NULL) {
      if (compare(llnode_get_element(ll, iter), llnode_get_element(ll, smaller)) < 0) {
        smaller = iter;
      }
      iter = llnode_get_next(ll, iter);
    }

    /* check if the smallest is the first element or a swap is needed */
    if (smaller != unorded) {
      /* swap the smallest to the first element of the unorded elements */
      if ((result = ll_swap_ex(ll, smaller, unorded)) != ERROR_OK) {
        return result;
      }
    }

    /* insert the smallest element found in the orded list */
    unorded = * (void **) unorded;
  } while (unorded != NULL);

  /* signal successful operation */
  return ERROR_OK;
}

int ll_at(LinkedList * ll, size_t pos, void * element) {
  void * node = NULL;
  size_t index = 0;

  /* argument check */
  if (ll == NULL || element == NULL) {
    return ERROR_INVALID_ARGUMENT;
  }

  /* argument check */
  if (pos >= ll->size) {
    return ERROR_INVALID_INDEX;
  }

  /* element search cycle */
  for (index = 0, node = ll->first; index < pos; index++) {
    node = llnode_get_next(ll, node);
  }

  /* copy the stored element value to the returning argument */
  memcpy(element, llnode_get_element(ll, node), ll->element_size);

  /* signal successful operation */
  return ERROR_OK;
}

int ll_insert(LinkedList * ll, void * element, size_t pos) {
  void * node = NULL, * iter = NULL;
  size_t index = 0;

  /* argument check */
  if (ll == NULL || element == NULL) {
    return ERROR_INVALID_ARGUMENT;
  }

  /* argument check */
  if (pos > ll->size) {
    return ERROR_INVALID_INDEX;
  }

  /* check if the linked list is full */
  if (ll->max != 0 && ll->size == ll->max) {
    return ERROR_CONTAINER_FULL;
  }

  if (ll->innode) {
    /* allocate memory to the new linked list node */
    if ((node = malloc(sizeof(void *) + ll->element_size)) == NULL) {
      return ERROR_NO_MEMORY;
    }
  } else {
    /* allocate memory to the new linked list node */
    if ((node = malloc(sizeof(void *))) == NULL) {
      return ERROR_NO_MEMORY;
    }
    /* allocate memory to the new linked list node element */
    if ((* (void **)((size_t)node + sizeof(void *)) = malloc(ll->element_size)) == NULL) {
      free(node);

      return ERROR_NO_MEMORY;
    }
  }

  /* initialize the created linked list node */
  * (void **) node = NULL;
  llnode_set_element(ll, node, element);

  /* check if the created node is to be inserted at the front position of the linked list */
  if (pos == 0) {
    /* insert the created node at the front position */
    llnode_set_next(ll, node, ll->first);
    ll->first = node;
  } else {
    /* element search cycle */
    for (index = 0, iter = ll->first; index + 1 < pos; index++) {
      iter = llnode_get_next(ll, iter);
    }

    /* insert the created node in the requested position */
    llnode_set_next(ll, node, llnode_get_next(ll, iter));
    llnode_set_next(ll, iter, node);
  }

  /* increment the linked list number of stored elements */
  ll->size++;

  /* signal successful operation */
  return ERROR_OK;
}

int ll_push_front(LinkedList * ll, void * element) {
  /* argument check */
  if (ll == NULL || element == NULL) {
    return ERROR_INVALID_ARGUMENT;
  }

  /* return the position insertion function call */
  return ll_insert(ll, element, 0);
}

int ll_push_back(LinkedList * ll, void * element) {
  /* argument check */
  if (ll == NULL || element == NULL) {
    return ERROR_INVALID_ARGUMENT;
  }

  /* return the position insertion function call */
  return ll_insert(ll, element, ll->size);
}

int ll_pop(LinkedList * ll, void * element, size_t pos) {
  void * node = NULL, *iter = NULL;
  size_t index = 0;

  /* argument check */
  if (ll == NULL) {
    return ERROR_INVALID_ARGUMENT;
  }

  /* argument check */
  if (pos > ll->size) {
    return ERROR_INVALID_INDEX;
  }

  /* check if the linked list is empty */
  if (ll->size == 0) {
    return ERROR_CONTAINER_EMPTY;
  }

  /* check if the element to be removed is at the front position of the linked list */
  if (pos == 0) {
    /* remove the front node of the linked list */
    node = ll->first;
    ll->first = llnode_get_next(ll, ll->first);
  } else {
    /* element search cycle */
    for (index = 0, iter = ll->first; index + 1 < pos; index++) {
      iter = llnode_get_next(ll, iter);
    }

    /* remove the requested node from the linked list */
    node = llnode_get_next(ll, iter);
    llnode_set_next(ll, iter, llnode_get_next(ll, llnode_get_next(ll, iter)));
  }

  /* decrement the current number of stored element in the linked list */
  ll->size--;

  /* check if the removed element is to be returned */
  if (element != NULL) {
    /* copy the removed stored element value to the returning argument */
    memcpy(element, llnode_get_element(ll, node), ll->element_size);
  }

  /* release the memory allocated/used by the linked list node */
  if (!ll->innode) {
    free(* (void **)((size_t)node + sizeof(void *)));
  }
  free(node);

  /* signal successful operation */
  return ERROR_OK;
}

int ll_pop_front(LinkedList * ll, void * element) {
  /* argument check */
  if (ll == NULL || element == NULL) {
    return ERROR_INVALID_ARGUMENT;
  }

  /* return the position poping function call */
  return ll_pop(ll, element, 0);
}

int ll_pop_back(LinkedList * ll, void * element) {
  /* argument check */
  if (ll == NULL || element == NULL) {
    return ERROR_INVALID_ARGUMENT;
  }

  /* return the position poping function call */
  return ll_pop(ll, element, ll->size - 1);
}

int ll_remove(LinkedList * ll, size_t pos) {
  /* argument check */
  if (ll == NULL) {
    return ERROR_INVALID_ARGUMENT;
  }

  /* return the position poping function call */
  return ll_pop(ll, NULL, pos);
}

int ll_remove_front(LinkedList * ll) {
  /* argument check */
  if (ll == NULL) {
    return ERROR_INVALID_ARGUMENT;
  }

  /* return the position removal function call */
  return ll_remove(ll, 0);
}

int ll_remove_back(LinkedList * ll) {
  /* argument check */
  if (ll == NULL) {
    return ERROR_INVALID_ARGUMENT;
  }

  /* return the position removal function call */
  return ll_remove(ll, ll->size - 1);
}

int ll_clear(LinkedList * ll) {
  /* argument check */
  if (ll == NULL) {
    return ERROR_INVALID_ARGUMENT;
  }

  /* elements removal cycle */
  while (ll->size != 0) {
    ll_remove_front(ll);
  }

  /* signal successful operation */
  return ERROR_OK;
}

int ll_swap_ex(LinkedList * ll, void * node1, void * node2) {
  void * aux = NULL;

  if (ll->innode) {
    /* allocate memory to be used as a auxiliary copy position of the swapping element */
    if ((aux = malloc(ll->element_size)) == NULL) {
      return ERROR_NO_MEMORY;
    }

    /* swap the elements */
    memcpy(aux, llnode_get_element(ll, node1), ll->element_size);
    memcpy(llnode_get_element(ll, node1), llnode_get_element(ll, node2), ll->element_size);
    memcpy(llnode_get_element(ll, node2), aux, ll->element_size);

    /* free the swapped elements */
    free(aux);
  } else {
    /* swap the elements */
    aux = * (void **)((size_t)node1 + sizeof(void *));
    * (void **)((size_t)node1 + sizeof(void *)) = * (void **)((size_t)node2 + sizeof(void *));
    * (void **)((size_t)node2 + sizeof(void *)) = aux;
  }

  /* signal successful operation */
  return ERROR_OK;
}

void * llnode_get_next(LinkedList * ll, void * node) {
  return * (void **) node;
}

void * llnode_set_next(LinkedList * ll, void * node, void * target) {
  return * (void **) node = target;
}

void * llnode_get_element(LinkedList * ll, void * node) {
  /* return a pointer to the linked list node stored element position */
  if (ll->innode) {
    return (void *)((size_t)node + sizeof(void *));
  }
  return * (void **)((size_t)node + sizeof(void *));
}

void * llnode_set_element(LinkedList * ll, void * node, void * target) {
  memcpy(llnode_get_element(ll, node), target, ll->element_size);
  return llnode_get_element(ll, node);
}
