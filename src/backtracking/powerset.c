/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   powerset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoreira <bmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 17:13:03 by bmoreira          #+#    #+#             */
/*   Updated: 2026/04/03 21:26:47 by bmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

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
	if (!argv && !*argv)
		return (NULL);
	set = calloc(1, sizeof(t_set));
	while (argv && argv[i])
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

int	sum_set(t_set *set)
{
	int	sum;
	int	i;

	i = 0;
	sum = 0;
	while (i < set->size)
		sum += set->values[i++];
	return (sum);
}

void	print_set(t_set *set)
{
	int	i;

	i = 0;
	while (i < set->size)
	{
		printf("%d", set->values[i++]);
		if (i < set->size)
			printf(" ");
	}
	printf("\n");
}

void	powerset(t_set *set, t_set *aux, int n, int i)
{
	while (i < set->size)
	{
		aux->values[aux->size] = set->values[i];
		aux->size++;
		if (sum_set(aux) == n)
			print_set(aux);
		powerset(set, aux, n, i + 1);
		aux->values[aux->size] = 0;
		aux->size--;
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_set	*set;
	t_set	*aux;
	int		n;

	if (argc < 3)
		return (1);
	n = atoi(argv[1]);
	if (n == 0)
		printf("\n");
	set = set_values(argv + 2);
	aux = calloc(1, sizeof(t_set));
	aux->values = calloc(set->size + 1, sizeof(int));
	aux->size = 0;
	powerset(set, aux, n, 0);
	return (0);
}
