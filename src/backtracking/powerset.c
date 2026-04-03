/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   powerset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoreira <bmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 17:13:03 by bmoreira          #+#    #+#             */
/*   Updated: 2026/04/03 17:24:26 by bmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "studies.h"

typedef struct s_set
{
	int	*values;
	int	size;
}	t_set;

t_set	*set_values(char **argv)
{
	t_set	*set;
	int		i;

	i = 0;
	set = calloc(1, sizeof(t_set));
	while (argv[i])
		i++;
	set->size = i;
	set->values = calloc(i + 1, (sizeof(int)));
	i = 0;
	while (i < set->size)
	{
		set->values[i] = atoi(argv[i]);
		i++;
	}
	return (set);
}

int main(int argc, char **argv)
{
	t_set	*set;
	int		i;

	if (argc < 2)
		return (1);
	i = 0;
	set = set_values(argv + 2);
	while (i < set->size)
		printf("num: %d\n", set->values[i++]);
	return (0);
}