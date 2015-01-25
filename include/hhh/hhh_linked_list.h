#ifndef HHH_LINKED_LIST_H
#define HHH_LINKED_LIST_H

#include <stdlib.h>

/**
 * @brief Linked List
 * Type definition of an opaque structure that olds and manages a generic and homogenious linked list.
 */
typedef struct LinkedList LinkedList;

/**
 * @brief Linked list creation function.
 * Function used to create a new generic and homogeneous linked list.
 *
 * @param[in] element_size Size of the memory needed to store a single element.
 * @param[in] max Maximum number of elements that the linked list can hold.<br />
 *                If the maximum value is zero, then the linked list will grow as it can.
 * @param[in] innode Flag telling if the element to be stored is to be saveed in the linked list nodes or in a seperate memory position
 *
 * @return Pointer to the created linekd list or NULL on error.
 */
LinkedList * ll_create(size_t element_size, size_t max, int innode);

/**
 * @brief Linked list destruction function.
 * Function used to destroy a previously created linked list.
 *
 * @param[in] ll Pointer to the the pointer to the linked list that hold the linked list to be destroyed
 *
 * @return Error value representing the operation successfulness (hhh_error.h)
 */
int ll_destroy(LinkedList ** ll);

/**
 * @brief Linked list maximum storing elements limits retrieving function.
 * Function used to retrieve the maximum number of storing elements limits of the linked list.<br />
 * If the returned value is zero, it means that the linked list is not limited and can grow until the system memory allows it.
 *
 * @param[in] ll Pointer to the linked list to be checked.
 * @param[out] size Pointer that will store the maximum number of storing elements limit of the linked list.
 *
 * @return Error value representing the operation successfulness (hhh_error.h)
 */
int ll_max(LinkedList * ll, size_t * size);

/**
 * @brief Linked list current stored elements count retrieving function.
 * Function used to retrieve the current number of stored elements on the linked list.
 *
 * @param[in] ll Pointer to the linked list to be checked.
 * @param[out] size Pointer that will store the current number of stored elements on the linked list.
 *
 * @return Error value representing the operation successfulness (hhh_error.h)
 */
int ll_size(LinkedList * ll, size_t * size);

/**
 * @brief Linked list element position swap function.
 * Function used to swap the position of two stored elements in the linked list.
 *
 * @param[in] ll Pointer to the linked list where the swap will be applied.
 * @param[in] pos1 Position of the first element to be swapped.
 * @param[in] pos2 Position of the second element to be swapped.
 *
 * @return Error value representing the operation successfulness (hhh_error.h)
 */
int ll_swap(LinkedList * ll, size_t pos1, size_t pos2);

/**
 * @brief Linked list element sorting function.
 * Function used to sort the stored elements in the linked list.
 *
 * @param[in] ll Pointer to the linked list where the sort will be applied.
 * @param[in] compare Pointer to the elements comparison function used to perform the ordering of the stored elements to be sorted.
 *
 * @return Error value representing the operation successfulness (hhh_error.h)
 */
int ll_sort(LinkedList * ll, int (*compare)(void *, void *));

/**
 * @brief Linked list element retrieving function.
 * Function used to retrieve the value of a stored elements of the linked list at a specific position.
 *
 * @param[in] ll Pointer to the linked list where the data will be retreived.
 * @param[in] pos Position of the element to be retrieved.
 * @param[out] element Pointer that will save the stored element value.
 *
 * @return Error value representing the operation successfulness (hhh_error.h)
 */
int ll_at(LinkedList * ll, size_t pos, void * element);

/**
 * @brief Linked list insertion function.
 * Function used to store a value into the linked list.<br />
 * The stored value will be a copy of the pointed data, not the pointer itself.
 *
 * @param[in] ll Pointer to the linked list where the element will be stored.
 * @param[in] element Pointer to the element that holds the data to be stored.
 * @param[in] pos Position of the element to be stored.
 *
 * @return Error value representing the operation successfulness (hhh_error.h)
 */
int ll_insert(LinkedList * ll, void * element, size_t pos);

/**
 * @brief Linked list front insertion function.
 * Function used to store a value into the front position of the linked list.<br />
 * The stored value will be a copy of the pointed data, not the pointer itself.
 *
 * @param[in] ll Pointer to the linked list where the element will be stored.
 * @param[in] element Pointer to the element that holds the data to be stored.
 *
 * @return Error value representing the operation successfulness (hhh_error.h)
 */
int ll_push_front(LinkedList * ll, void * element);

/**
 * @brief Linked list back insertion function.
 * Function used to store a value into the back position of the linked list.<br />
 * The stored value will be a copy of the pointed data, not the pointer itself.
 *
 * @param[in] ll Pointer to the linked list where the element will be stored.
 * @param[in] element Pointer to the element that holds the data to be stored.
 *
 * @return Error value representing the operation successfulness (hhh_error.h)
 */
int ll_push_back(LinkedList * ll, void * element);

/**
 * @brief Linked list element poping function.
 * Function used to retrieve with removal of a element from the linked list at a specific.<br />
 *
 * @param[in] ll Pointer to the linked list where the element will be removed.
 * @param[in] element Pointer to the element that will hold the data of the removed element.
 * @param[in] pos Position of the element to be removed.
 *
 * @return Error value representing the operation successfulness (hhh_error.h)
 */
int ll_pop(LinkedList * ll, void * element, size_t pos);

/**
 * @brief Linked list front element poping function.
 * Function used to retrieve with removal of a element from the front position of the linked list.<br />
 *
 * @param[in] ll Pointer to the linked list where the element will be removed.
 * @param[in] element Pointer to the element that will hold the data of the removed element.
 *
 * @return Error value representing the operation successfulness (hhh_error.h)
 */
int ll_pop_front(LinkedList * ll, void * element);

/**
 * @brief Linked list back element poping function.
 * Function used to retrieve with removal of a element from the back position of the linked list.<br />
 *
 * @param[in] ll Pointer to the linked list where the element will be removed.
 * @param[in] element Pointer to the element that will hold the data of the removed element.
 *
 * @return Error value representing the operation successfulness (hhh_error.h)
 */
int ll_pop_back(LinkedList * ll, void * element);

/**
 * @brief Linked list element removing function.
 * Function used to remove of a element from the linked list at a specific.<br />
 *
 * @param[in] ll Pointer to the linked list where the element will be removed.
 * @param[in] pos Position of the element to be removed.
 *
 * @return Error value representing the operation successfulness (hhh_error.h)
 */
int ll_remove(LinkedList * ll, size_t pos);

/**
 * @brief Linked list front element removing function.
 * Function used to remove of a element from the front position of the linked list.<br />
 *
 * @param[in] ll Pointer to the linked list where the element will be removed.
 *
 * @return Error value representing the operation successfulness (hhh_error.h)
 */
int ll_remove_front(LinkedList * ll);

/**
 * @brief Linked list back element removing function.
 * Function used to remove of a element from the back position of the linked list.<br />
 *
 * @param[in] ll Pointer to the linked list where the element will be removed.
 *
 * @return Error value representing the operation successfulness (hhh_error.h)
 */
int ll_remove_back(LinkedList * ll);

/**
 * @brief Linked list clear function.
 * Function used to remove all the stored elements from the linked list.<br />
 *
 * @param[in] ll Pointer to the linked list where all the elements will be removed.
 *
 * @return Error value representing the operation successfulness (hhh_error.h)
 */
int ll_clear(LinkedList * ll);

#endif
