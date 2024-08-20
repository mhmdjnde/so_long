/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs_and_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoundi <mjoundi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 17:09:07 by mjoundi           #+#    #+#             */
/*   Updated: 2024/07/18 17:10:13 by mjoundi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"so_long.h"

void	find_starting_point(char **strs, int r_len, int *x, int *y)
{
	int	i;
	int	j;

	i = 0;
	while (i < r_len)
	{
		j = 0;
		while (j < ft_strlen(strs[0]))
		{
			if (strs[i][j] == 'P')
			{
				*x = i;
				*y = j;
				return ;
			}
			j++;
		}
		i++;
	}
}

int	check_all_visited(char **strs, int **visited, int r_len)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < r_len)
	{
		j = 0;
		while (j < ft_strlen(strs[0]))
		{
			if ((strs[i][j] == 'C' || strs[i][j] == 'E') && !visited[i][j])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	val_path(char **strs, int r_len)
{
	int	**visited;
	int	x;
	int	y;
	int	path_valid;
	int	i;

	i = 0;
	if (strs == NULL)
		return (0);
	visited = create_visited_matrix(strs, r_len);
	find_starting_point(strs, r_len, &x, &y);
	dfs(x, y, strs, visited);
	path_valid = check_all_visited(strs, visited, r_len);
	while (i < r_len)
	{
		free(visited[i]);
		i++;
	}
	free(visited);
	return (path_valid);
}

int	valid_input(char **strs)
{
	int	r_len;

	r_len = 0;
	while (strs[r_len] != NULL)
		r_len++;
	if (!same_lines(strs) || !valid_char(strs) || !valid_e_p(strs)
		|| !val_borders(strs) || !val_path(strs, r_len))
		return (0);
	return (1);
}

int	is_ber_file(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len > 4)
	{
		if (filename[len - 4] == '.' && filename[len - 3] == 'b'
			&& filename[len - 2] == 'e' && filename[len - 1] == 'r')
		{
			return (1);
		}
	}
	return (0);
}
