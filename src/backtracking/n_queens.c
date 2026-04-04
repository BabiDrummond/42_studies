/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_queens.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoreira <bmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 21:09:33 by bmoreira          #+#    #+#             */
/*   Updated: 2026/04/04 02:24:30 by bmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

char	**set_matrix(char **argv)
{
	char	**matrix;
	int		n;
	int		i;
	int		j;

	i = 0;
	n = atoi(argv[1]);
	matrix = calloc(n + 1, sizeof(char *));
	while (i < n)
	{
		j = 0;
		matrix[i] = calloc(n + 1, sizeof(char));
		while (j < n)
		{
			matrix[i][j] = '.';
			j++;
		}
		i++;
	}
	return (matrix);
}

void	print_matrix(char **matrix)
{
	int i;

	i = 0;
	while (matrix[i])
		printf("%s\n", matrix[i++]);
	printf("\n");
}

int	validate_row(char **matrix, int row, int n)
{
	int	q_in_row;
	int	col;

	col = 0;
	q_in_row = 0;
	while (col < n)
	{
		if (matrix[row][col] == 'Q')
		{
			if (q_in_row)
				return (1);
			q_in_row = 1;
		}
		col++;
	}
	return (0);
}

int validate_col(char **matrix, int col, int n)
{
	int	q_in_col;
	int row;

	row = 0;
	q_in_col = 0;
	while (row < n)
	{
		if (matrix[row][col] == 'Q')
		{
			if (q_in_col)
				return (1);
			q_in_col = 1;
		}
		row++;
	}
	return (0);
}

int	validate_diagonal(char **matrix, int row, int col, int n)
{
	int q_in_diag;

	q_in_diag = 0;
	while (row > 0 && col > 0)
	{
		row--;
		col--;
	}
	while (row < n && col < n)
	{
		if (matrix[row][col] == 'Q')
		{
			if (q_in_diag)
				return (1);
			q_in_diag = 1;
		}
		row++;
		col++;
	}
	return (0);
}

int	validate_rev_diagonal(char **matrix, int row, int col, int n)
{	
	int q_in_diag;

	q_in_diag = 0;
	while (row > 0 && col < n - 1)
	{
		row--;
		col++;
	}
	while (row < n && col >= 0)
	{
		if (matrix[row][col] == 'Q')
		{
			if (q_in_diag)
				return (1);
			q_in_diag = 1;
		}
		row++;
		col--;
	}
	return (0);
}

int	validate_matrix(char **matrix, int row, int col, int n)
{
	if (validate_row(matrix, row, n))
		return (1);
	else if (validate_col(matrix, col, n))
		return (2);
	else if (validate_diagonal(matrix, row, col, n))
		return (3);
	else if (validate_rev_diagonal(matrix, row, col, n))
		return (4);
	return (0);
}

void	print_result(char **matrix, int n)
{
	int row;
	int col;

	col = 0;
	while (col < n)
	{
		row = 0;
		while (row < n)
		{
			if(matrix[row][col] == 'Q')
				printf("%d", row);
			row++;
		}
		if (col < n - 1)
			printf(" ");
		col++;
	}
	printf("\n");
}
void	n_queens(char **matrix, int col, int n)
{
	int	row;
	if (col == n)
	{
		print_result(matrix, n);
		return ;
	}
	row = 0;
	while (row < n)
	{
		matrix[row][col] = 'Q';
		if (validate_matrix(matrix, row, col, n) == 0)
			n_queens(matrix, col + 1, n);
		matrix[row][col] = '.';
		row++;
	}
}

int	main(int argc, char **argv)
{
	char	**matrix;
	int		n;

	if (argc != 2)
		return (1);
	n = atoi(argv[1]);
	if (n == 1)
		printf("0\n");
	if (n < 4)
		return (1);
	matrix = set_matrix(argv);
	n_queens(matrix, 0, n);
	return (0);
}