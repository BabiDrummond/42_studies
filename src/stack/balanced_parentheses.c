/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   balanced_parentheses.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoreira <bmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 22:31:11 by bmoreira          #+#    #+#             */
/*   Updated: 2026/04/03 21:08:13 by bmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

typedef struct s_list
{
	int				number;
	struct s_list	*next;
}	t_list;

// Stack
t_list	*new_node(int number);
void	push(t_list **top, t_list *node);
void	pop(t_list **top);
int		is_empty(t_list **top);

static int	is_opening(char c)
{
	return (c == '(' || c == '[' || c == '{');
}

static int	is_closing(char c)
{
	return (c == ')' || c == ']' || c == '}');
}

static int	are_pair(char opening, char closing)
{
	return ((opening == '(' && closing == ')')
		|| (opening == '[' && closing == ']')
		|| (opening == '{' && closing == '}'));
}

static int	is_balanced_parentheses(t_list **top, const char *expression)
{
	int	i;

	i = 0;
	while (expression[i])
	{
		if (is_opening(expression[i]))
			push(top, new_node(expression[i]));
		else if (is_closing(expression[i]))
		{
			if (is_empty(top) || !are_pair((*top)->number, expression[i]))
				return (0);
			else
				pop(top);
		}
		i++;
	}
	return (is_empty(top));
}

int	main(void)
{
	t_list	*top;

	top = NULL;
	printf("is empty? %d\n", is_empty(&top));
	printf("isBalanced? %d\n", is_balanced_parentheses(&top, "[( )]"));
	printf("isBalanced? %d\n", is_balanced_parentheses(&top, "{[()}]"));
	printf("isBalanced? %d\n", is_balanced_parentheses(&top, "{[(()}]"));
	printf("isBalanced? %d\n", is_balanced_parentheses(&top, " })({"));
	printf("is empty? %d\n", is_empty(&top));
}
