/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoundi <mjoundi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 19:19:30 by mjoundi           #+#    #+#             */
/*   Updated: 2024/07/18 17:15:05 by mjoundi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_if_invalid(char **strs)
{
	int	i;

	i = 0;
	if (!valid_input(strs))
	{
		write(1, "Error: Invalid map.\n", 21);
		i = 0;
		while (strs[i])
		{
			free(strs[i]);
			i++;
		}
	}
}

void	main_help(int argc, char **argv, char **file_content)
{
	if (argc != 2)
	{
		write(1, "usage: ./so_long file.ber\n", 26);
		exit(1);
	}
	if (!is_ber_file(argv[1]))
	{
		write(1, "Error: File must have a .ber extension.\n", 41);
		exit(1);
	}
	*file_content = read_file(argv[1]);
	if (!file_content)
	{
		write(1, "could not read file", 1);
		exit(1);
	}
}

void	main_help2(char **strs, char **file_content, t_data *data)
{
	int	i;
	int	j;

	strs = ft_split(*file_content, '\n');
	free(*file_content);
	free_if_invalid(strs);
	data->map = strs;
	data->w_h = 0;
	while (strs[data->w_h])
		data->w_h++;
	ini_data(data, strs);
	i = 0;
	while (strs[i] != NULL)
	{
		j = 0;
		while (strs[i][j] != '\0')
		{
			if (strs[i][j] == 'C')
				data->n_c++;
			j++;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	char	*file_content;
	char	**strs;
	t_data	data;
	int		i;
	int		j;

	strs = NULL;
	main_help(argc, argv, &file_content);
	main_help2(strs, &file_content, &data);
	initialize_c(&data);
	draw_map(&data);
	draw_steve(&data, data.s_x, data.s_y);
	mlx_hook(data.win, KeyPress, KeyPressMask, (int (*)())key_press_hook,
		&data);
	mlx_hook(data.win, ClientMessage, StructureNotifyMask,
		(int (*)())close_window, &data);
	mlx_loop(data.mlx);
	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	return (0);
}
