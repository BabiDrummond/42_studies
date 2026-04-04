/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_queens.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoreira <bmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 21:09:33 by bmoreira          #+#    #+#             */
/*   Updated: 2026/04/04 00:49:59 by bmoreira         ###   ########.fr       */
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
	j = 0;
	n = atoi(argv[1]);
	matrix = calloc(n + 1, sizeof(char *));
	while (i < n)
	{
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

int	main(int argc, char **argv)
{
	// char	**matrix;
	(void) argv;

	if (argc != 2)
		return (1);
	//matrix = set_matrix(argv + 1);
	char *mat[5] = {0};
	mat[0] = ".Q..";
	mat[1] = "...Q";
	mat[2] = "..Q.";
	mat[3] = "....";
	mat[4] = NULL;
	int n = 4;
	for (int row = 0; row < n; row++)
	{
		printf("row: %d\n", row);
		for (int col = 0; col < n; col++)
			printf("is_valid? %d\n", validate_matrix(mat, row, col, n));
		printf("\n");
	}
	return (0);
}