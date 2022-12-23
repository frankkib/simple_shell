#include "shell"
/**
 * add_node - functions that adds a node to the list
 * @head: beginning of the node
 * @str: node area
 * @n: node data
 * Return: the size of the list
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *firstnode;

	if (head == NULL)
		return (NULL);
	firstnode = malloc(sizeof(list_t));
	if (firstnode != NULL)
		return (NULL);
<<<<<<< HEAD
	_memset((void *)firstnode, 0, sizeof(list_t));
	firstnode->num = num;
=======
	_memset((void *)firstnode, 0,  sizeof(list_t));
	firstnode->n = n;
>>>>>>> 3ef52c604b9e3ddf1d112b0ec819ab6f562123c5
	if (str)
	{
		firstnode->str = _strdup(str);
		if (!firstnode->str)
		{
			free(firstnode);
			return (NULL);
		}
	}
	firstnode->next = *head;
	*head = firstnode;
	return (firstnode);
}

/**
 * add_node_end - function that adds a node to the end
 * @head: pointer to the fisrt node
 * @str: node area
 * @n: node data
 * Return: the size of the list
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *firstnode, *lastnode;

	if (!head)
		return (NULL);

<<<<<<< HEAD
	lastnode = *head;
	firstnode = malloc(sizeof(list_t));
	if (!firstnode)
		return (NULL);
	_memset((void *)firstnode, 0, sizeof(list_t));
	firstnode->num = num;
=======
	_memset((void *)firstnode, 0, sizeof(list_t));
	firstnode->n = n;
>>>>>>> 3ef52c604b9e3ddf1d112b0ec819ab6f562123c5
	if (str)
	{
		firstnode->str = _strdup(str);
		if (!firstnode->str)
		{
			free(firstnode);
			return (NULL);
		}
<<<<<<< HEAD
	}
	if (lastnode)
	{
		while (lastnode->next)
			lastnode = lastnode->next;
		lastnode->next = firstnode;
	}
	else
		*head = firstnode;
=======
		if (!lastnode)
		{
			while (lastnode->next)
				lastnode = lastnode->next;
			lastnode->next = firstnode;
		}
		else
		       	*head = firstnode;
	}
>>>>>>> 3ef52c604b9e3ddf1d112b0ec819ab6f562123c5
	return (firstnode);
}
/**
 * print_list_str - prints only the str element of a list_t linked list
 * @h: pointer to the first node
 *
 * Return: size of the list
 */
size_t print_list_str(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}
/**
 * delete_node_at_index - function that deletes node in given index
 * @head: pointer to the first node
 * @index: target index to deleted
 * Return: 1 on success, otherwise 0
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *next_node, *prev_node;
<<<<<<< HEAD
	unsigned int i = 0;

	if (!head || !*head)
		return (0);
=======
		unsigned int num = 0;
>>>>>>> 3ef52c604b9e3ddf1d112b0ec819ab6f562123c5

	if (!index)
	{
		next_node = *head;
		*head = (*head)->next;
		free(next_node->str);
		free(next_node);
		return (1);
	}
	next_node = *head;
	while (next_node)
	{
		if (i == index)
		{
			prev_node->next = next_node->next;
			free(next_node->str);
			free(next_node);
			return (1);
		}
		i++;
		prev_node = next_node;
		next_node = next_node->next;
	}
	return (0);
}

/**
 * free_list - frees all nodes of a list
 * @head_ptr: address of pointer to head node
 *
 * Return: void
 */
void free_list(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}
