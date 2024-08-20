/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_and_some_pixel.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoundi <mjoundi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 17:10:50 by mjoundi           #+#    #+#             */
/*   Updated: 2024/08/06 15:56:46 by mjoundi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	*resize_buffer(char *old_content, size_t old_size, size_t increment)
{
	char	*new_content;
	size_t	i;

	new_content = malloc(old_size + increment);
	if (!new_content)
	{
		free(old_content);
		return (NULL);
	}
	i = 0;
	while (i < old_size)
	{
		new_content[i] = old_content[i];
		i++;
	}
	free(old_content);
	return (new_content);
}

void	read_helper(size_t *read_size, size_t *t_r, char **content, int fd)
{
	char	*new_content;
	size_t	allocated_size;

	allocated_size = *t_r + 1000;
	while (*read_size > 0)
	{
		*t_r += *read_size;
		if (*t_r + 1000 > allocated_size)
		{
			new_content = resize_buffer(*content, allocated_size, 1000);
			if (!new_content)
			{
				free(*content);
				close(fd);
				return ;
			}
			*content = new_content;
			allocated_size += 1000;
		}
		*read_size = read(fd, *content + *t_r, 1000);
	}
}

char	*read_file(const char *filename)
{
	int		fd;
	char	*content;
	size_t	total_read;
	ssize_t	read_size;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		write(1, "file not found\n", 15);
		exit(1);
	}
	content = malloc(1000);
	total_read = 0;
	read_size = read(fd, content, 1000);
	read_helper(&read_size, &total_read, &content, fd);
	if (read_size < 0)
	{
		free(content);
		return (NULL);
	}
	content[total_read] = '\0';
	close(fd);
	return (content);
}

int	get_pixel_color(t_data *data, int x, int y)
{
	char	*dst;

	dst = data->addr + (y * data->l_len + x * (data->bbp / 8));
	return (*(unsigned int *)dst);
}

void	mlx_pixel_put_to_image(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->l_len + x * (data->bbp / 8));
	*(unsigned int *)dst = color;
}
