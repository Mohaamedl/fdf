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

int	should_cull_line(t_point2d p1, t_point2d p2)
{
	if ((p1.x < -100 && p2.x < -100) || (p1.x > WIN_W + 100 && p2.x > WIN_W + 100))
		return (1);
	if ((p1.y < -100 && p2.y < -100) || (p1.y > WIN_H + 100 && p2.y > WIN_H + 100))
		return (1);
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
		result = result << 4;
		if (c >= '0' && c <= '9')
			result += (c - '0');
		else if (c >= 'A' && c <= 'F')
			result += (c - 'A' + 10);
		else if (c >= 'a' && c <= 'f')
			result += (c - 'a' + 10);
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

void	swap_lines(t_line_depth *a, t_line_depth *b)
{
	t_line_depth	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

int	partition_lines(t_line_depth *lines, int low, int high)
{
	double			pivot;
	int				i;
	int				j;

	pivot = lines[high].avg_depth;
	i = low - 1;
	j = low;
	while (j < high)
	{
		if (lines[j].avg_depth <= pivot)
		{
			i++;
			swap_lines(&lines[i], &lines[j]);
		}
		j++;
	}
	swap_lines(&lines[i + 1], &lines[high]);
	return (i + 1);
}

void	quicksort_lines(t_line_depth *lines, int low, int high)
{
	int	pi;

	if (low < high)
	{
		pi = partition_lines(lines, low, high);
		quicksort_lines(lines, low, pi - 1);
		quicksort_lines(lines, pi + 1, high);
	}
}

void	sort_lines_by_depth(t_line_depth *lines, int count)
{
	if (count > 1)
		quicksort_lines(lines, 0, count - 1);
}
