/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 17:11:53 by mjoundi           #+#    #+#             */
/*   Updated: 2024/08/20 23:20:22 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	initialize_images(t_data *data, t_data *new_img, t_data *grass_data)
{
	new_img->img = mlx_new_image(data->mlx, data->n_w, data->n_h);
	new_img->addr = mlx_get_data_addr(new_img->img, &new_img->bbp,
			&new_img->l_len, &new_img->end);
	grass_data->img = mlx_xpm_file_to_image(data->mlx, "images/grass.xpm",
			&grass_data->o_w, &grass_data->o_h);
	grass_data->addr = mlx_get_data_addr(grass_data->img, &grass_data->bbp,
			&grass_data->l_len, &grass_data->end);
}

void	calculate_ratios(t_data *data, float *x_ratio, float *y_ratio)
{
	*x_ratio = (float)data->o_w / data->n_w;
	*y_ratio = (float)data->o_h / data->n_h;
}

int	get_grass_color(t_data *grass_data, int i, int j)
{
	return (get_pixel_color(grass_data, i % grass_data->o_w,
			j % grass_data->o_h));
}

void	resize_and_draw(t_data *data, t_data *new_img, t_data *g_d, int i_s)
{
	float	x_ratio;
	float	y_ratio;
	int		i;
	int		j;
	int		color;

	calculate_ratios(data, &x_ratio, &y_ratio);
	j = 0;
	while (j < data->n_h)
	{
		i = 0;
		while (i++ < data->n_w)
		{
			color = get_pixel_color(data, (int)(i * x_ratio),
					(int)(j * y_ratio));
			if (i_s && (color & 0xFF000000) == 0xFF000000)
			{
				mlx_pixel_put_to_image(new_img, i, j,
					get_grass_color(g_d, i, j));
			}
			else
				mlx_pixel_put_to_image(new_img, i, j, color);
		}
		j++;
	}
}

void	resize_image(t_data *data, int x, int y, int is_steve)
{
	t_data	new_img;
	t_data	grass_data;

	initialize_images(data, &new_img, &grass_data);
	resize_and_draw(data, &new_img, &grass_data, is_steve);
	mlx_destroy_image(data->mlx, grass_data.img);
	mlx_put_image_to_window(data->mlx, data->win, new_img.img, x, y);
	mlx_destroy_image(data->mlx, new_img.img);
}
