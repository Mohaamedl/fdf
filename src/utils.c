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

void	recompute_view_fit(t_app *app)
{
	double	margin;
	double	span;
	double	map_w;
	double	map_h;

	margin = 40.0;
	span = (app->map.w + app->map.h);
	map_w = span * cos(app->view.angle);
	map_h = span * sin(app->view.angle)
		+ fabs((app->map.zmax - app->map.zmin) * app->view.zscale);
	if (map_w <= 1)
		map_w = 1;
	if (map_h <= 1)
		map_h = 1;
	if ((WIN_W - 2 * margin) / map_w < (WIN_H - 2 * margin) / map_h)
		app->view.scale = (WIN_W - 2 * margin) / map_w;
	else
		app->view.scale = (WIN_H - 2 * margin) / map_h;
	app->view.offset_x = WIN_W / 2.0;
	app->view.offset_y = WIN_H / 2.0;
}
