/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 17:13:21 by mjoundi           #+#    #+#             */
/*   Updated: 2024/08/20 23:20:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	initialize_c(t_data *d)
{
	int	i;
	int	j;
	int	k;

	d->c = malloc(sizeof(t_coin) * d->n_c);
	k = 0;
	i = 0;
	while (i < d->w_h / 32)
	{
		j = 0;
		while (j < d->w_w / 32)
		{
			if (d->map[i][j] == 'C')
			{
				ini_c_helper(d, i, j);
			}
			j++;
		}
		i++;
	}
}

void	draw_c(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_c)
	{
		if (!data->c[i].col)
		{
			print_coin(data, &data->c[i]);
		}
		i++;
	}
}

void	key_hook_helper1(t_data *data, int new_x, int new_y)
{
	write(1, "you did: ", 9);
	ft_putnbr(data->count);
	write(1, " moves\n", 7);
	draw_tile(data, data->s_x, data->s_y, "images/grass.xpm");
	data->s_x = new_x;
	data->s_y = new_y;
	draw_steve(data, data->s_x, data->s_y);
}

void	key_hook_helper2(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_c)
	{
		if (data->c[i].x == data->s_x && data->c[i].y == data->s_y
			&& !data->c[i].col)
		{
			data->c[i].col = 1;
			data->c_c++;
			break ;
		}
		i++;
	}
}

void	key_hook_helper(t_data *data, int new_x, int new_y)
{
	if (new_x >= 0 && new_x < data->w_w && new_y >= 0 && new_y < data->w_h
		&& data->map[new_y / 32][new_x / 32] != '1' &&
		(data->map[new_y / 32][new_x / 32] != 'E' || data->c_c == data->n_c))
	{
		data->count++;
		key_hook_helper1(data, new_x, new_y);
		key_hook_helper2(data);
		if (data->s_x == data->e_x && data->s_y == data->e_y)
		{
			if (data->c_c == data->n_c)
			{
				write(1, "Steve reached the exit and col all c. Exiting...\n",
					50);
				mlx_destroy_window(data->mlx, data->win);
				exit(0);
			}
			else
				write(1, "Collect all c before exiting!\n", 30);
		}
	}
}
