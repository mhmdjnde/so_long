/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 17:12:36 by mjoundi           #+#    #+#             */
/*   Updated: 2024/08/20 23:20:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_tile(t_data *d, int x, int y, const char *file)
{
	d->img = mlx_xpm_file_to_image(d->mlx, (char *)file, &d->o_w, &d->o_h);
	d->addr = mlx_get_data_addr(d->img, &d->bbp, &d->l_len, &d->end);
	resize_image(d, x, y, 0);
	mlx_destroy_image(d->mlx, d->img);
}

void	draw_steve(t_data *data, int x, int y)
{
	draw_tile(data, x, y, "images/steve.xpm");
}

void	draw_exit(t_data *data, int x, int y)
{
	draw_tile(data, x, y, "images/exit.xpm");
}

void	print_coin(t_data *data, t_coin *coin)
{
	draw_tile(data, coin->x, coin->y, "images/c.xpm");
}

void	ini_c_helper(t_data *d, int i, int j)
{
	static int	k;

	d->c[k].x = j * 32;
	d->c[k].y = i * 32;
	d->c[k].col = 0;
	d->c[k].img = mlx_xpm_file_to_image(d->mlx, "images/c.xpm",
			&d->c[k].o_w, &d->c[k].o_h);
	d->c[k].addr = mlx_get_data_addr(d->c[k].img, &d->c[k].bbp,
			&d->c[k].l_len, &d->c[k].end);
	d->c[k].n_w = 32;
	d->c[k].n_h = 32;
	k++;
}
