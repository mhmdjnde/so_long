/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoundi <mjoundi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 17:08:22 by mjoundi           #+#    #+#             */
/*   Updated: 2024/07/18 17:08:42 by mjoundi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	valid_e_p(char **strs)
{
	int	i;
	int	j;
	int	p_count;
	int	e_count;

	p_count = 0;
	e_count = 0;
	i = -1;
	if (strs == NULL)
		return (0);
	while (strs[++i] != NULL)
	{
		j = 0;
		while (strs[i][j] != '\0')
		{
			if (strs[i][j] == 'E')
				e_count++;
			if (strs[i][j] == 'P')
				p_count++;
			j++;
		}
	}
	if (p_count != 1 || e_count != 1)
		return (0);
	return (1);
}

int	val_borders(char **strs)
{
	int	l_len;
	int	r_len;
	int	i;

	if (strs == NULL)
		return (0);
	i = 0;
	l_len = ft_strlen(strs[0]);
	r_len = 0;
	while (strs[r_len] != NULL)
		r_len++;
	while (i < l_len)
	{
		if (strs[0][i] != '1' || strs[r_len - 1][i] != '1')
			return (0);
		i++;
	}
	i = 0;
	while (i < r_len)
	{
		if (strs[i][0] != '1' || strs[i][l_len - 1] != '1')
			return (0);
		i++;
	}
	return (1);
}

int	is_valid_pos(int x, int y, char **strs, int **visited)
{
	char	current_char;

	if (x < 0 || y < 0 || strs[x] == NULL || y >= ft_strlen(strs[0]))
	{
		return (0);
	}
	current_char = strs[x][y];
	if (current_char == '0' || current_char == 'C' || current_char == 'P'
		|| current_char == 'E')
	{
		if (!visited[x][y])
		{
			return (1);
		}
	}
	return (0);
}

void	dfs(int x, int y, char **strs, int **visited)
{
	int	dirs[4][2];
	int	i;
	int	nx;
	int	ny;

	dirs[0][0] = 0;
	dirs[0][1] = 1;
	dirs[1][0] = 1;
	dirs[1][1] = 0;
	dirs[2][0] = 0;
	dirs[2][1] = -1;
	dirs[3][0] = -1;
	dirs[3][1] = 0;
	visited[x][y] = 1;
	i = 0;
	while (i < 4)
	{
		nx = x + dirs[i][0];
		ny = y + dirs[i][1];
		if (is_valid_pos(nx, ny, strs, visited))
			dfs(nx, ny, strs, visited);
		i++;
	}
}

int	**create_visited_matrix(char **strs, int r_len)
{
	int	**visited;
	int	i;
	int	j;

	i = 0;
	visited = (int **)malloc(sizeof(int *) * r_len);
	while (i < r_len)
	{
		visited[i] = (int *)malloc(sizeof(int) * ft_strlen(strs[0]));
		j = 0;
		while (j < ft_strlen(strs[0]))
		{
			visited[i][j] = 0;
			j++;
		}
		i++;
	}
	return (visited);
}
