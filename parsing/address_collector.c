#include "parse.h"
#include "../minishell.h"

static void ft_bzero(void *s, size_t n)
{
	unsigned int i;
	unsigned char *temp;

	temp = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		temp[i] = 0;
		i++;
	}
}

void *ft_calloc(t_addr **addr, size_t count, size_t size)
{
	char *copy;

	if (count != 0 && size > 9223372036854775807ULL / count)
		return (NULL);
	copy = (char *)malloc(count * size);
	if (!copy)
		return (NULL);
	ft_bzero(copy, size * count);
	add_addr(addr, new_addr(copy));
	return (copy);
}

t_addr *new_addr(char *value)
{
	t_addr *node;

	node = malloc(sizeof(t_addr));
	if (!node)
		return (NULL);
	node->nxt = NULL;
	node->address = value;
	return (node);
}

int add_addr(t_addr **list, t_addr *new)
{
	t_addr *temp;

	if (!list || !new)
		return (1);
	new->nxt = NULL;
	if (!*list)
	{
		*list = new;
		return (0);
	}
	temp = *list;
	while (temp->nxt != NULL)
		temp = temp->nxt;
	temp->nxt = new;
	return (0);
}

int is_duplicate(t_addr *list, t_addr *node)
{
	t_addr *curr = list;

	while (curr && curr != node)
	{
		if (curr->address == node->address)
			return 1;
		curr = curr->nxt;
	}
	return 0;
}
void ft_lstdelone(t_addr *lst, void (*del)(void *))
{
	if (lst && del)
	{
		del(lst->address);
		free(lst);
	}
}

void ft_lstclear(t_addr **lst, void (*del)(void *))
{
	t_addr *tmp;

	if (!lst || !del)
		return;
	while (*lst)
	{
		if (!is_duplicate(*lst, *lst))
		{
			tmp = (*lst)->nxt;
			ft_lstdelone(*lst, del);
			*lst = tmp;
		}
		else
			*lst = (*lst)->nxt;
	}
	*lst = NULL;
}

// void print_addr(t_addr *list)
// {
// 	t_addr *temp;

// 	printf("\n======== Adresses to free : ===========\n");
// 	temp = list;
// 	while (temp)
// 	{
// 		printf("address :  %p\n", temp->address);
// 		temp = temp->nxt;
// 	}
// }
