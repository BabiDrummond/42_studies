/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoreira <bmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 23:31:13 by bmoreira          #+#    #+#             */
/*   Updated: 2026/04/04 23:58:21 by bmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

# define BUFFER_SIZE 1

int	ft_strlen(char *s)
{
	int len;

	len = 0;
	if (!s)
		return (len);
	while (s[len])
		len++;
	return (len);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*new;
	int		i;
	int		j;
	int		k;
	
	i = 0;
	j = 0;
	k = 0;
	if (!s1 && !s2)
		return (NULL);
	new = calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	while (s1 && s1[i])
		new[k++] = s1[i++];
	while (s2 && s2[j])
		new[k++] = s2[j++];
	return (new);
}

char	*read_buffer(void)
{
	char	*tmp;
	char	*buffer;
	int		bytes;

	bytes = 1;
	buffer = NULL;
	while (bytes)
	{
		tmp = calloc(BUFFER_SIZE + 1, sizeof(char));
		bytes = read(STDIN_FILENO, tmp, BUFFER_SIZE);
		if (bytes < 0)
			return (NULL);
		if (bytes == 0)
			return (buffer);
		buffer = ft_strjoin(buffer, tmp);
	}
	return (buffer);
}

char	*filter(char *str, int start, int end)
{
	char	*result;
	int		i;

	i = 0;
	result = calloc(ft_strlen(str) + 1, sizeof(char));
	while (i < start)
	{
		result[i] = str[i];
		i++;
	}
	while (i < end)
		result[i++] = '*';
	while (str[i])
	{
		result[i] = str[i];
		i++;
	}
	return (result);
}

int main(int argc, char **argv)
{
	char	*buffer;
	char	*start;
	int		start_pos;
	int		end_pos;

	if (argc != 2)
		return (1);
	buffer = read_buffer();
	start = memmem(buffer, ft_strlen(buffer), argv[1], ft_strlen(argv[1]));
	while (start)
	{
		start_pos = start - buffer;
		end_pos = start_pos + ft_strlen(argv[1]);
		buffer = filter(buffer, start_pos, end_pos);
		start = memmem(buffer, ft_strlen(buffer), argv[1], ft_strlen(argv[1]));
	}
	printf("%s\n", buffer);
}