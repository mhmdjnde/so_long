/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoundi <mjoundi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 17:07:44 by mjoundi           #+#    #+#             */
/*   Updated: 2024/07/18 17:07:57 by mjoundi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	ft_strncpy(char *str, char const *src, int n)
{
	int	i;

	i = 0;
	while (src[i] != '\0' && i < n)
	{
		str[i] = (char)src[i];
		i++;
	}
	str[i] = '\0';
}

static void	helper(char c, char const *s, char **strs, int k)
{
	int	j;
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			j = 0;
			while (s[i + j] != c && s[i + j] != '\0')
				j++;
			strs[k] = malloc((j + 1) * sizeof(char));
			ft_strncpy(strs[k], (char *)s + i, j);
			k++;
			i += j;
		}
		else
			i++;
	}
	strs[k] = NULL;
}

char	**ft_split(char *s, char c)
{
	char	**strs;
	int		k;

	strs = (char **)malloc((count_words(s, c) + 1) * sizeof(char *));
	k = 0;
	if (strs == NULL)
		return (NULL);
	helper(c, s, strs, k);
	return (strs);
}

int	same_lines(char **strs)
{
	int	i;
	int	len;

	if (strs == NULL || strs[0] == NULL)
		return (0);
	i = 1;
	len = ft_strlen(strs[0]);
	while (strs[i] != NULL)
	{
		if (len != ft_strlen(strs[i]))
			return (0);
		i++;
	}
	return (1);
}

int	valid_char(char **strs)
{
	int	i;
	int	j;
	int	c_count;

	c_count = 0;
	i = 0;
	if (strs == NULL)
		return (0);
	while (strs[i] != NULL)
	{
		j = 0;
		while (strs[i][j] != '\0')
		{
			if (strs[i][j] != '0' && strs[i][j] != '1' && strs[i][j] != 'C' &&
				strs[i][j] != 'E' && strs[i][j] != 'P')
				return (0);
			if (strs[i][j] == 'C')
				c_count++;
			j++;
		}
		i++;
	}
	if (c_count == 0)
		return (0);
	return (1);
}
