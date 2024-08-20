/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoundi <mjoundi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 19:19:45 by mjoundi           #+#    #+#             */
/*   Updated: 2024/07/18 17:20:07 by mjoundi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdio.h>
# include <stdlib.h>
# include "mlx/mlx.h"
# include <X11/X.h>
# include <unistd.h>
# include <fcntl.h>

typedef struct s_coin
{
	int		x;
	int		y;
	int		col;
	void	*img;
	char	*addr;
	int		bbp;
	int		l_len;
	int		end;
	int		o_w;
	int		o_h;
	int		n_w;
	int		n_h;
}	t_coin;

typedef struct s_data {
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bbp;
	int		l_len;
	int		end;
	int		n_w;
	int		n_h;
	int		o_w;
	int		o_h;
	int		w_w;
	int		w_h;
	int		s_x;
	int		s_y;
	int		s_w;
	int		s_h;
	int		c_c;
	int		n_c;
	t_coin	*c;
	int		e_x;
	int		e_y;
	char	**map;
	int		count;
}	t_data;

void	negativecheck(int *n);
int		count_words(char *str, char c);
int		checkmin(int n);
void	ft_putnbr(int nb);
int		ft_strlen(char *str);
char	**ft_split(char *s, char c);
int		same_lines(char **strs);
int		valid_char(char **strs);
int		valid_e_p(char **strs);
int		val_borders(char **strs);
int		is_valid_pos(int x, int y, char **strs, int **visited);
void	dfs(int x, int y, char **strs, int **visited);
int		**create_visited_matrix(char **strs, int r_len);
void	find_starting_point(char **strs, int r_len, int *x, int *y);
int		check_all_visited(char **strs, int **visited, int r_len);
int		val_path(char **strs, int r_len);
int		valid_input(char **strs);
int		is_ber_file(char *filename);
char	*resize_buffer(char *old_content, size_t old_size, size_t increment);
char	*read_file(const char *filename);
int		get_pixel_color(t_data *data, int x, int y);
void	mlx_pixel_put_to_image(t_data *data, int x, int y, int color);
void	initialize_images(t_data *data, t_data *new_img, t_data *grass_data);
void	calculate_ratios(t_data *data, float *x_ratio, float *y_ratio);
int		get_grass_color(t_data *grass_data, int i, int j);
void	resize_and_draw(t_data *data, t_data *new_img, t_data *g_d, int i_s);
void	resize_image(t_data *data, int x, int y, int is_steve);
void	draw_tile(t_data *d, int x, int y, const char *file);
void	draw_steve(t_data *data, int x, int y);
void	draw_exit(t_data *data, int x, int y);
void	print_coin(t_data *data, t_coin *coin);
void	ini_c_helper(t_data *d, int i, int j);
void	initialize_c(t_data *d);
void	draw_c(t_data *data);
void	key_hook_helper1(t_data *data, int new_x, int new_y);
void	key_hook_helper2(t_data *data);
void	key_hook_helper(t_data *data, int new_x, int new_y);
int		key_press_hook(int keycode, t_data *data);
int		close_window(t_data *data);
void	draw_map_helper(t_data *data, int i, int j);
void	draw_map(t_data *data);
void	ini_data(t_data *data, char **strs);
void	free_if_invalid(char **strs);
void	main_help(int argc, char **argv, char **file_content);
void	main_help2(char **strs, char **file_content, t_data *data);

#endif
