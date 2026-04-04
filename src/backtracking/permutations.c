/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permutations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoreira <bmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 20:02:10 by bmoreira          #+#    #+#             */
/*   Updated: 2026/04/03 20:55:25 by bmoreira         ###   ########.fr       */
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

char	*ft_strdup(char *str)
{
	char	*new;
	int		i;

	i = 0;
	if (!str)
		return (NULL);
	new = calloc(ft_strlen(str) + 1, sizeof(char));
	while (str[i])
	{
		new[i] = str[i];
		i++;
	}
	return (new);
}

void	order_str(char *string, char *ascii)
{
	char	*new;
	int		i;

	i = 0;
	while (string[i])
	{
		ascii[(int)string[i]] = 1;
		i++;
	}
	i = 0;
	new = ascii;
	while (i < 256)
	{
		if (ascii[i])
			*new++ = i;
		i++;
	}
	*new = 0;
}

void	permutations(char *set, char *used, char *string, int pos)
{
	int	i;

	i = -1;
	if (!set[pos])
	{
		puts(string);
		return ;
	}
	while (set[++i])
	{
		if (used[(int) set[i]])
			continue ;
		used[(int) set[i]] = 1;
		string[pos] = set[i];
		permutations(set, used, string, pos + 1);
		used[(int) set[i]] = 0;
	}
}

int	main(int argc, char **argv)
{
	char	ordered[256] = {0};
	char	used[256] = {0};
	char	*new;
	char	*dup;

	if (argc != 2)
		return (1);
	new = calloc(ft_strlen(argv[1]) + 1, sizeof(char));
	dup = ft_strdup(argv[1]);
	order_str(dup, ordered);
	permutations(ordered, used, new, 0);
	return (0);
}
