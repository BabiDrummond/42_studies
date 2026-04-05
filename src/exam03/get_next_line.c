/*
 * EXERCISE: BROKEN_GNL (Get Next Line)
 * 
 * DESCRIPTION:
 * Implement get_next_line that reads line by line from a file descriptor.
 * This version may contain special cases or intentional "bugs".
*/

#include "get_next_line.h"

char *ft_strchr(char *s, int c)
{
	int i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == c)
			return (s + i);
		i++;
	}
	return (NULL);
}

void *ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*dst_cpy;
	char	*src_cpy;

	i = 0;
	if (!dest && !src)
		return (NULL);
	dst_cpy = dest;
	src_cpy = (char *) src;
	while (i < n)
	{
		dst_cpy[i] = src_cpy[i];
		i++;
	}
	return (dest);
}

size_t ft_strlen(char *s)
{
	size_t	len;

	len = 0;
	if (!s)
		return (len);
	while (s[len])
		len++;
	return (len);
}

int str_append_mem(char **s1, char *s2, size_t size2) // colocar o buffer ATÉ \n (ou até onde leu) no retorno (linha)
{
	size_t size1 = ft_strlen(*s1); // pega o tamanho do s1 (retorno)
	char *tmp = malloc(size2 + size1 + 1); // aloca tmp do tamanho de s1 + s2 (buffer)
	if (!tmp)
		return (0);
	ft_memcpy(tmp, *s1, size1); // coloca no começo do tmp o s1 (retorno)
	ft_memcpy(tmp + size1, s2, size2); // coloca o s2 (buffer) no tmp + s1 (final da string do retorno)
	tmp[size1 + size2] = '\0'; // coloca nulo
	if (*s1)
		free(*s1); // free s1
	*s1 = tmp; // s1 (retorno) = tmp
	return (1);
}

void *ft_memmove(void *dest, const void *src, size_t n)
{
	char	*dst_cpy;
	char	*src_cpy;

	if (!dest && !src)
		return (NULL);
	dst_cpy = dest;
	src_cpy = (char *)src;
	if (dest <= src)
		return (ft_memcpy(dest, src, n));
	src_cpy += n - 1;
	dst_cpy += n - 1;
  	while (n--)
		*dst_cpy-- = *src_cpy--;
  	return (dest);
}

char *get_next_line(int fd)
{
	static char b[BUFFER_SIZE + 1] = "";
	char *ret = NULL;
	char *tmp = NULL;
	while (!tmp)
  	{
		tmp = ft_strchr(b, '\n'); // procura \n no buffer (b)
		if (tmp) // se achou um \n
		{
			if (!str_append_mem(&ret, b, tmp - b + 1)) // append/strjoin do buffer no retorno até o \n encontrado
	  			return (NULL);
			size_t tmp_len = ft_strlen(tmp + 1); // pega tamanho de tmp + 1 (a partir do \n pra frente)
			ft_memmove(b, tmp + 1, tmp_len); // move o restante do buffer (a partir do \n) para o início do buffer (posição 0)
			b[tmp_len] = '\0'; // adiciona um NULO no final do conteúdo restante do buffer (tamanho de tmp + 1)
			return (ret); // retorna a linha
		}
		// se não havia \n no buffer
		if (b[0]) // verificar se há conteúdo no buffer
		{
			if (!str_append_mem(&ret, b, ft_strlen(b))) // se há conteúdo, append no retorno
		  		return (NULL);
			b[0] = '\0'; // zerar o buffer
		}
		int read_ret = read(fd, b, BUFFER_SIZE); // ler mais buffer
		if (read_ret <  0) // se deu erro, retorna NULL
	  		return (NULL);
		if (read_ret == 0) // se leu 0, chegamos ao final do arquivo, BREAK NO WHILE
			break ;
		b[read_ret] = '\0'; // se leu alguma coisa, coloca um NULO ao final da quantidade de bytes lidos
  	}
	return (ret);
}

#include <stdio.h>
int main(void)
{
	char	*line;
	int		fd;
	
	fd = open("batatas.txt", O_RDONLY);
	if (fd == -1)
		return (1);
	line = get_next_line(fd);
	while (line)
	{
		printf("line: '%s'\n", line);
		free(line);
		line = get_next_line(fd);
	}
	printf("end\n");
	close(fd);
	return (0);
}
