#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

typedef struct Array
{
  int capacity;    // How many elements can this array hold?
  int count;       // How many states does the array currently hold?
  char **elements; // The string elements contained in the array
} Array;

/************************************
 *
 *   CREATE, DESTROY, RESIZE FUNCTIONS
 *
 ************************************/

/*****
 * Allocate memory for a new array
 *****/
Array *create_array(int capacity)
{
  Array *arr_var = malloc(sizeof(Array));
  // Set initial values for capacity and count
  arr_var->capacity = capacity;
  // printf("THE CAPACITY IS %d\n", arr_var->capacity);
  arr_var->count = 0;
  // printf("THE COUNT IS %d\n", arr_var->count);
  // Allocate memory for elements
  arr_var->elements = malloc(capacity * sizeof(char *));
  return arr_var;
}

/*****
 * Free memory for an array and all of its stored elements
 *****/
void destroy_array(Array *arr)
{
  // Free all elements
  free(arr->elements);
  // Free array
  free(arr);
}

/*****
 * Create a new elements array with double capacity and copy elements
 * from old to new
 *****/
void resize_array(Array *arr)
{
  // Create a new element storage with double capacity
  char **arr_doubled = malloc(2 * arr->capacity * sizeof(char *));
  // Copy elements into the new storage
  for (int i = 0; i < arr->count; i++)
  {
    arr_doubled[i] = arr->elements[i];
  }
  // Free the old elements array (but NOT the strings they point to)
  free(arr->elements);
  // Update the elements and capacity to new values
  arr->elements = arr_doubled;
  arr->capacity *= 2;
}

/************************************
 *
 *   ARRAY FUNCTIONS
 *
 ************************************/

/*****
 * Return the element in the array at the given index.
 *
 * Throw an error if the index is out of range.
 *****/
char *arr_read(Array *arr, int index)
{
  char err_string[] = "Insert value failed";
  // Throw an error if the index is greater or equal to than the current count
  if (index >= arr->count)
  {
    return NULL;
  }
  // Otherwise, return the element at the given index
  else
  {
    printf("ELEMENT %s\n", arr->elements[index]);
    printf("INDEX %d\n", index);
    printf("COUNT %d\n", arr->count);
    // printf("ELEMENT %d\n", arr->elements[index]);
    return arr->elements[index];
  }
}

/*****
 * Insert an element to the array at the given index
 *****/
void arr_insert(Array *arr, char *element, int index)
{
  char err_string[] = "Index out of range";
  // Throw an error if the index is greater than the current count
  if (index > arr->count)
  {
    return err_string;
  }
  // Resize the array if the number of elements is over capacity
  // if arr_copy->count > arr_copy->capacity we gonna resize_arr()
  if (arr->count + 1 > arr->capacity)
  {
    resize_array(arr);
  }
  // Move every element after the insert index to the right one position
  for (int i = index; i < arr->count; i++)
  {
    arr->elements[i + 1] = arr->elements[i];
  }
  // Copy the element and add it to the array
  char *ele_copy;
  ele_copy = element;
  arr->elements[index] = ele_copy;
  // Increment count by 1
  arr->count += 1;
}

/*****
 * Append an element to the end of the array
 *****/
void arr_append(Array *arr, char *element)
{

  // Resize the array if the number of elements is over capacity
  // or throw an error if resize isn't implemented yet.

  // Copy the element and add it to the end of the array
  char *ele_copy;
  ele_copy = element;
  int cur_index = arr->count;
  // printf("CURR INDEX BEFORE%d\n", cur_index);
  arr->elements[cur_index] = ele_copy;
  cur_index = (arr->count + 1) % arr->capacity;
  // printf("CURR INDEX AFTER%d\n", cur_index);
  // Increment count by 1
  arr->count++;
}

/*****
 * Remove the first occurence of the given element from the array,
 * then shift every element after that occurence to the left one slot.
 *
 * Throw an error if the value is not found.
 *****/
void arr_remove(Array *arr, char *element)
{
  char *element_copy;
  element_copy = element;
  int index = 0;
  // Search for the first occurence of the element and remove it.
  // Don't forget to free its memory!
  for (int i = 0; i < arr->count; i++)
  {
    if (arr->elements[i] == element_copy)
    {
      index = i;
      arr->elements[index] = 0;
      free(arr->elements[index]);
    }
  }
  // Shift over every element after the removed element to the left one position
  for (int i = index; i < arr->count; i++)
  {
    arr->elements[index] = arr->elements[index + 1];
  }
  // Decrement count by 1
  arr->count -= 1;
}

/*****
 * Utility function to print an array.
 *****/
void arr_print(Array *arr)
{
  printf("[");
  for (int i = 0; i < arr->count; i++)
  {
    printf("%s", arr->elements[i]);
    if (i != arr->count - 1)
    {
      printf(",");
    }
  }
  printf("]\n");
}

#ifndef TESTING
int main(void)
{

  Array *arr = create_array(1);

  arr_insert(arr, "STRING1", 0);
  arr_append(arr, "STRING4");
  arr_insert(arr, "STRING2", 0);
  arr_insert(arr, "STRING3", 1);
  arr_print(arr);
  arr_remove(arr, "STRING3");
  arr_print(arr);

  destroy_array(arr);

  return 0;
}
#endif
