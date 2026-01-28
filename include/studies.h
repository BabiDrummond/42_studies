/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   studies.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoreira <bmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 22:30:19 by bmoreira          #+#    #+#             */
/*   Updated: 2026/01/28 18:13:28 by bmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STUDIES_H
# define STUDIES_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

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

#endif