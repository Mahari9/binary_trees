#include "binary_trees.h"

/**
 * heap_to_sorted_array - A function that converts a Binary Max Heap
 * to a sorted array of integers
 * @heap: A pointer to the root node of the heap to be converted
 * @size: An address to store the size of the array
 * Return: Sorted array in descending order
 */
int *heap_to_sorted_array(heap_t *heap, size_t *size)
{
	int *sorted_array;
	int extract, i = 0;
	size_t heap_size;

	if (!heap)
		return (NULL);
	heap_size = binary_tree_size(heap);
	*size = heap_size;
	sorted_array = malloc(heap_size * sizeof(int));
	if (!sorted_array)
		return (NULL);
	while (heap)
	{
		extract = heap_extract(&heap);
		sorted_array[i] = extract;
		i++;
	}
	return (sorted_array);
}
