/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 17:14:15 by mjoundi           #+#    #+#             */
/*   Updated: 2024/08/20 23:20:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	key_press_hook(int keycode, t_data *data)
{
	int	new_x;
	int	new_y;

	new_x = data->s_x;
	new_y = data->s_y;
	if (keycode == 65307)
	{
		write(1, "Escape key pressed. Exiting...\n", 32);
		mlx_destroy_window(data->mlx, data->win);
		exit(0);
	}
	else if (keycode == 119 || keycode == 65362)
		new_y -= data->s_h;
	else if (keycode == 97 || keycode == 65361)
		new_x -= data->s_w;
	else if (keycode == 115 || keycode == 65364)
		new_y += data->s_h;
	else if (keycode == 100 || keycode == 65363)
		new_x += data->s_w;
	key_hook_helper(data, new_x, new_y);
	return (0);
}

int	close_window(t_data *data)
{
	write(1, "closing\n", 8);
	mlx_destroy_window(data->mlx, data->win);
	exit(0);
	return (0);
}

void	draw_map_helper(t_data *data, int i, int j)
{
	if (data->map[i][j] == '1')
		draw_tile(data, j * 32, i * 32, "images/wall.xpm");
	else if (data->map[i][j] == '0')
		draw_tile(data, j * 32, i * 32, "images/grass.xpm");
	else if (data->map[i][j] == 'E')
	{
		data->e_x = j * 32;
		data->e_y = i * 32;
		draw_exit(data, data->e_x, data->e_y);
	}
	else if (data->map[i][j] == 'P')
	{
		data->s_x = j * 32;
		data->s_y = i * 32;
	}
}

void	draw_map(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->w_h / 32)
	{
		j = 0;
		while (j < data->w_w / 32)
		{
			draw_map_helper(data, i, j);
			j++;
		}
		i++;
	}
	draw_c(data);
}

void	ini_data(t_data *data, char **strs)
{
	data->w_w = ft_strlen(strs[0]) * 32;
	data->w_h *= 32;
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, data->w_w, data->w_h, "So Long");
	data->n_w = 32;
	data->n_h = 32;
	data->s_w = 32;
	data->s_h = 32;
	data->c_c = 0;
	data->count = 0;
	data->n_c = 0;
}
