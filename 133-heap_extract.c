#include "binary_trees.h"

/**
 * max_value - Gets the maximum node in a tree
 * @tree: The pointer to the root of the binary tree
 * Return: The pointer to the node with the maximum value
 */
heap_t *max_value(heap_t *tree)
{
	heap_t *curr_max_value, *left_max_value, *right_max_value;

	if (!tree->left)
		return (tree);
	left_max_value = max_value(tree->left);
	if (left_max_value->n > tree->n)
		curr_max_value = left_max_value;
	else
		curr_max_value = tree;
	if (tree->right)
	{
		right_max_value = max_value(tree->right);
		if (right_max_value->n > curr_max_value->n)
			curr_max_value = right_max_value;
		else
			curr_max_value = tree;
	}
	return (curr_max_value);
}

/**
 * recurse_extract - Recursively extracts the max_value from the binary tree
 * @tree: The pointer to the root of the binary tree
 */
void recurse_extract(heap_t *tree)
{
	heap_t *sub_max_value, *right_max_value = NULL;

	if (!tree->left)
		return;
	sub_max_value = max_value((tree)->left);
	if (tree->right)
		right_max_value = max_value(tree->right);
	if (right_max_value && right_max_value->n > sub_max_value->n)
		sub_max_value = right_max_value;
	tree->n = sub_max_value->n;
	if (!sub_max_value->left)
	{
		if (sub_max_value->parent && sub_max_value->parent->left == sub_max_value)
			sub_max_value->parent->left = NULL;
		if (sub_max_value->parent && sub_max_value->parent->right == sub_max_value)
			sub_max_value->parent->right = NULL;
		free(sub_max_value);
	}
	else
		recurse_extract(sub_max_value);
}

/**
 * heap_extract - A function that extracts the root node of a Max Binary Heap
 * @root: A double pointer to the root node of heap
 * Return: The value stored in the root node, 0 otherwise
 */
int heap_extract(heap_t **root)
{
	int value;

	if (!*root)
		return (0);
	value = (*root)->n;
	if (!(*root)->left)
	{
		value = (*root)->n;
		free(*root);
		*root = NULL;
		return (value);
	}
	recurse_extract(*root);
	return (value);
}
