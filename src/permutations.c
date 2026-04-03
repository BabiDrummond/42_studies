/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permutations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoreira <bmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 20:02:10 by bmoreira          #+#    #+#             */
/*   Updated: 2026/04/03 00:43:50 by bmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "studies.h"

int	ft_strlen(char *str)
{
	int len;
	
	len = 0;
	while (str && str[len])
		len++;
	return (len);
}

char	*ft_strdup(char *str)
{
	char *new;
	int i;

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

int	has_duplicate(char *str, char c)
{
	int dup;

	dup = 0;
	while (*str)
	{
		if (*str == c)
			dup++;
		str++;
	}
	if (dup >= 2)
		return (1);
	return (0);
}

void	permutations(char *set, char *string, int pos)
{
	int i;

	i = 0;
	if (!set[pos])
	{
		printf("%s\n", string);
		return ;
	}
	while (set[i])
	{
		string[pos] = set[i];
		if (!has_duplicate(string, string[pos]))
			permutations(set, string, pos + 1);
		string[pos] = 0;
		i++;
	}
}

int main(int argc, char **argv)
{	
	char *new;

	if (argc != 2)
		return (1);
	new = calloc(ft_strlen(argv[1]) + 1, sizeof(char));
	permutations(ft_strdup(argv[1]), new, 0);
	return (0);
}