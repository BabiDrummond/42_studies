/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoreira <bmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 18:07:03 by bmoreira          #+#    #+#             */
/*   Updated: 2026/04/03 21:08:20 by bmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

typedef struct s_list
{
	int				number;
	struct s_list	*next;
}	t_list;

t_list	*new_node(int number)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->number = number;
	node->next = NULL;
	return (node);
}

void	push(t_list **top, t_list *node)
{
	node->next = *top;
	*top = node;
}

void	pop(t_list **top)
{
	*top = (*top)->next;
}

int	is_empty(t_list **top)
{
	if (*top == NULL)
		return (1);
	return (0);
}
