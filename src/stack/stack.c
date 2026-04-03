/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoreira <bmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 18:07:03 by bmoreira          #+#    #+#             */
/*   Updated: 2026/01/28 18:12:25 by bmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "studies.h"

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
