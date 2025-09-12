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
		if (c >= '0' && c <= '9')
		{
			result = result << 4;
			result += (c - '0');
		}
		else if (c >= 'A' && c <= 'F')
		{
			result = result << 4;
			result += (c - 'A' + 10);
		}
		else if (c >= 'a' && c <= 'f')
		{
			result = result << 4;
			result += (c - 'a' + 10);
		}
		else
			break ;
		i++;
	}
	return (result);
}

int	string_to_int_len(const char *str, int len)
{
	int		result;
	int		sign;
	int		i;

	result = 0;
	sign = 1;
	i = 0;
	if (str[0] == '-')
	{
		sign = -1;
		i = 1;
	}
	else if (str[0] == '+')
		i = 1;
	while (i < len && str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

void	free_string_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
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
