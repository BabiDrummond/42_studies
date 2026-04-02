/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rip.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoreira <bmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 17:03:55 by bmoreira          #+#    #+#             */
/*   Updated: 2026/04/02 20:01:39 by bmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "studies.h"

int	ft_strlen(const char *s)
{
	int	len;

	len = 0;
	while (s && s[len])
		len++;
	return (len);
}

char	*ft_strdup(const char *s)
{
	char	*new;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	new = calloc(ft_strlen(s) + 1, sizeof(char));
	while (s && s[i])
	{
		new[i] = s[i];
		i++;
	}
	return (new);
}

int	is_balanced(char *string)
{
	int	openings;
	int	i;

	i = 0;
	openings = 0;
	while (string[i])
	{
		if (string[i] == '(')
			openings++;
		else if (string[i] == ')')
		{
			if (openings == 0)
				return (0);
			else
				openings--;
		}
		i++;
	}
	return (openings == 0);
}

int	count_pairs(char *string)
{
	int	openings;
	int	pairs;
	int	i;

	i = 0;
	pairs = 0;
	openings = 0;
	while (string[i])
	{
		if (string[i] == '(')
			openings++;
		else if (string[i] == ')')
		{
			if (openings)
			{
				openings--;
				pairs++;
			}
		}
		i++;
	}
	return (pairs);
}

int	rip(char *string, int pairs, int pos)
{
	char	curr;

	if (is_balanced(string))
	{
		printf("%s\n", string);
		return (1);
	}
	while (string[pos])
	{
		curr = string[pos];
		string[pos] = ' ';
		if (count_pairs(string) == pairs)
			rip(string, pairs, pos + 1);
		string[pos] = curr;
		pos++;
	}
	return (0);
}

int	main(void)
{
	char	*str;
	int		pairs;

	str = ft_strdup("(()(()(");
	pairs = count_pairs(str);
	if (str)
		rip(str, pairs, 0);
	return (0);
}
