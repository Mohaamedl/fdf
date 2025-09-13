/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddadi <mhaddadi@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 18:55:04 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/09/08 18:56:15 by mhaddadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static int	get_scheme_color(double percent, int scheme)
{
	static const int	colors[5][4] = {
	{0x432371, 0x714674, 0xCC8B79, 0xFAAE7B},
	{0xFF0000, 0xFFFF00, 0x00FF00, 0x8000FF},
	{0x000000, 0x808080, 0xC0C0C0, 0xFFFFFF},
	{0x000000, 0x8B0000, 0xFF4500, 0xFFFF00},
	{0x000080, 0x4169E1, 0x87CEEB, 0xF0F8FF}
	};
	int					index;

	if (scheme == 2)
	{
		index = (int)(255 * percent);
		if (index > 255)
			index = 255;
		if (index < 0)
			index = 0;
		return ((index << 16) | (index << 8) | index);
	}
	index = (int)(percent * 4);
	if (index >= 4)
		index = 3;
	return (colors[scheme][index]);
}

static double	get_percent(int z, const t_map *map)
{
	unsigned int	range;

	range = map->zmax - map->zmin;
	if (range == 0)
		return (0.5);
	return ((double)(z - map->zmin) / range);
}

int	pick_color_mode(const t_point *p, const t_map *map, int color_mode)
{
	double	percent;

	if (color_mode == 0 && p->color != -1)
		return (p->color);
	percent = get_percent(p->z, map);
	if (color_mode < 0 || color_mode > 4)
		color_mode = 0;
	return (get_scheme_color(percent, color_mode));
}

int	pick_color(const t_point *p, const t_map *map)
{
	if (p->color != -1)
		return (p->color);
	return (get_scheme_color(get_percent(p->z, map), 0));
}

int	lerp_color(int color1, int color2, double t)
{
	int	rgb1[3];
	int	rgb2[3];

	rgb1[0] = (color1 >> 16) & 0xFF;
	rgb1[1] = (color1 >> 8) & 0xFF;
	rgb1[2] = color1 & 0xFF;
	rgb2[0] = (color2 >> 16) & 0xFF;
	rgb2[1] = (color2 >> 8) & 0xFF;
	rgb2[2] = color2 & 0xFF;
	return (((int)(rgb1[0] + (rgb2[0] - rgb1[0]) * t) << 16)
					| ((int)(rgb1[1] + (rgb2[1] - rgb1[1]) * t) << 8)
					| (int)(rgb1[2] + (rgb2[2] - rgb1[2]) * t));
}
