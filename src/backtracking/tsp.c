/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tsp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoreira <bmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 19:51:12 by bmoreira          #+#    #+#             */
/*   Updated: 2026/04/03 20:48:31 by bmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "studies.h"

typedef struct s_city
{
	float	x;
	float	y;
}	t_city;

/*
** You must implement this function
** It should return the Euclidean distance between 2 cities
*/
float	power(float x)
{
	return (x * x);
}

float	distance(t_city a, t_city b)
{
	return (sqrtf
		(
			power(b.x - a.x)
			+ power(b.y - a.y)
		)
	);
}

/*
** You must implement this function
** It should compute total distance of the path
** including the return to the starting city
*/
float	total_distance(t_city *cities, int *path, int n)
{
	float	total;
	int		i;

	i = 0;
	total = 0;
	while (i < n - 1)
	{
		total += distance(cities[path[i]], cities[path[i + 1]]);
		i++;
	}
	total += distance(cities[path[i]], cities[path[0]]);
	return (total);
}

void	swap(int *i, int *j)
{
	int aux;

	aux = *i;
	*i = *j;
	*j = aux;
}

/*
** You must implement this function
** Use backtracking to try all permutations
*/
void	solve(t_city *cities, int *path, int n, int pos, float *min)
{
	float	new_dist;
	int		i;
		
	if (pos >= n)
		return ;
	i = 1;
	while (i < n - 1)
	{
		swap(&path[i], &path[i + 1]);
		new_dist = total_distance(cities, path, n);
		if (new_dist < *min)
			*min = new_dist;
		solve(cities, path, n, pos + 1, min);
		i++;
	}
}

int	main(void)
{
	t_city	cities[11];
	int		n = 0;

	// Read input from stdin
	while (n < 11 && fscanf(stdin, "%f, %f", &cities[n].x, &cities[n].y) == 2)
		n++;
	// If less than 2 cities → distance = 0
	if (n < 2)
	{
		printf("0.00\n");
		return (0);
	}
	// Initialize path: [0,1,2,...]
	int	path[11];
	for (int i = 0; i < n; i++)
		path[i] = i;
	float	min = FLT_MAX;
	/*
	** Optimization:
	** Fix first city → start from pos = 1
	*/
	solve(cities, path, n, 1, &min);
	printf("%.2f\n", min);
	return (0);
}
