#include "binary_trees.h"

/**
 * enqueue_i - Adds an i to a queue
 * @queue_h: A pointer to the queue's head
 * @queue_t: A pointer to the queue's tail
 * @n: A pointer to the queue's size value
 * @i: The item to be added to the queue
 */
void enqueue_i(binary_tree_t **queue_h, binary_tree_t **queue_t,
	int *n, void *i)
{
	binary_tree_t *new_node;
	binary_tree_t *node = (binary_tree_t *)i;

	if ((queue_h != NULL) && (queue_t != NULL))
	{
		new_node = malloc(sizeof(binary_tree_t));
		if (new_node == NULL)
			return;
		new_node->left = *queue_t;
		new_node->right = NULL;
		new_node->n = (node != NULL ? node->n : -1);
		new_node->parent = node;
		if (*queue_h == NULL)
			*queue_h = new_node;
		if (*queue_t != NULL)
			(*queue_t)->right = new_node;
		*queue_t = new_node;
		if (n != NULL)
			(*n)++;
	}
}

/**
 * dequeue_i - Removes an item from a queue
 * @queue_h: A pointer to the queue's head
 * @queue_t: A pointer to the queue's tail
 * @n: A pointer to the queue's size value
 *
 * Return: The value of the removed queue.
 */
binary_tree_t *dequeue_i(binary_tree_t **queue_h,
	binary_tree_t **queue_t, int *n)
{
	binary_tree_t *tmp0;
	binary_tree_t *tmp1;
	binary_tree_t *node = NULL;

	if ((queue_h != NULL) && (queue_t != NULL))
	{
		tmp0 = *queue_h;
		if (tmp0 != NULL)
		{
			node = tmp0->parent;
			if (tmp0->right != NULL)
			{
				tmp1 = tmp0->right;
				tmp1->left = NULL;
				*queue_h = tmp1;
				free(tmp0);
			}
			else
			{
				free(tmp0);
				*queue_h = NULL;
				*queue_t = NULL;
			}
			if (n != NULL)
				(*n)--;
		}
	}
	return (node);
}

/**
 * binary_tree_levelorder - A function that goes through a binary tree
 * using level-order traversal
 * @tree: a pointer to the root node of the tree to traverse
 * @func: The function to handle the traversed node's value
 */
void binary_tree_levelorder(const binary_tree_t *tree, void (*func)(int))
{
	binary_tree_t *queue_head = NULL;
	binary_tree_t *queue_tail = NULL;
	int n = 0;
	binary_tree_t *current = NULL;

	if ((tree != NULL) && (func != NULL))
	{
		enqueue_i(&queue_head, &queue_tail, &n, (void *)tree);
		while (n > 0)
		{
			current = queue_head;
			if (current->parent != NULL)
			{
				func(current->parent->n);
				if (current->parent->left != NULL)
				{
					enqueue_i(
						&queue_head, &queue_tail, &n, (void *)(current->parent->left)
					);
				}
				if (current->parent->right != NULL)
				{
					enqueue_i(
						&queue_head, &queue_tail, &n, (void *)(current->parent->right)
					);
				}
			}
			dequeue_i(&queue_head, &queue_tail, &n);
		}
	}
}
