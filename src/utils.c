/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddadi <mhaddadi@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 18:56:04 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/09/08 18:56:15 by mhaddadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static int	process_hex_char(char c, int *result)
{
	if (c >= '0' && c <= '9')
	{
		*result = *result << 4;
		*result += (c - '0');
		return (1);
	}
	else if (c >= 'A' && c <= 'F')
	{
		*result = *result << 4;
		*result += (c - 'A' + 10);
		return (1);
	}
	else if (c >= 'a' && c <= 'f')
	{
		*result = *result << 4;
		*result += (c - 'a' + 10);
		return (1);
	}
	return (0);
}

int	hex_color_to_int(const char *hex_str)
{
	int		result;
	int		i;
	char	c;

	result = 0;
	i = 0;
	while (hex_str[i] && (hex_str[i] != ' ' && hex_str[i] != '\t'
			&& hex_str[i] != '\n' && hex_str[i] != '\r'))
	{
		c = hex_str[i];
		if (!process_hex_char(c, &result))
			break ;
		i++;
	}
	return (result);
}

void	free_map(t_map *map)
{
	int	i;

	if (!map || !map->pts)
		return ;
	i = 0;
	while (i < map->h)
	{
		if (map->pts[i])
			free(map->pts[i]);
		i++;
	}
	free(map->pts);
	map->pts = NULL;
}

void	init_map_parsing(t_map *map)
{
	map->zmin = 2147483647;
	map->zmax = -2147483648;
}
