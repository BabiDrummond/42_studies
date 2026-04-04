/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permutations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoreira <bmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 20:02:10 by bmoreira          #+#    #+#             */
/*   Updated: 2026/04/03 21:46:53 by bmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str && str[len])
		len++;
	return (len);
}

int	ft_strchr(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	ft_swap(char *i, char *j)
{
	char	aux;

	aux = *i;
	*i = *j;
	*j = aux;
}

char	*sort_str(char *string)
{
	int	swapped;
	int	len;
	int	i;

	len = ft_strlen(string);
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		i = 0;
		while (i < len - 1)
		{
			if (string[i] > string[i + 1])
			{
				ft_swap(&string[i], &string[i + 1]);
				swapped = 1;
			}
			i++;
		}
	}
	return (string);
}

void	permutations(char *set, char *string, int pos)
{
	int	i;

	i = 0;
	if (!set[pos])
	{
		puts(string);
		return ;
	}
	while (set[i])
	{
		if (!ft_strchr(string, set[i]))
		{
			string[pos] = set[i];
			permutations(set, string, pos + 1);
			string[pos] = 0;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	char	*new;
	char	*sorted;

	if (argc != 2)
		return (1);
	new = calloc(ft_strlen(argv[1]) + 1, sizeof(char));
	sorted = sort_str(argv[1]);
	permutations(sorted, new, 0);
	return (0);
}
