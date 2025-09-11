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

static t_color	create_color(unsigned char r, unsigned char g, unsigned char b)
{
	t_color	color;

	color.r = r;
	color.g = g;
	color.b = b;
	color.a = 255;
	return (color);
}

static int	color_to_int(t_color color)
{
	return ((color.r << 16) | (color.g << 8) | color.b);
}

static t_color	lerp_colors(t_color c1, t_color c2, double t)
{
	t_color	result;

	if (t <= 0.0)
		return (c1);
	if (t >= 1.0)
		return (c2);
	result.r = (unsigned char)(c1.r + t * (c2.r - c1.r));
	result.g = (unsigned char)(c1.g + t * (c2.g - c1.g));
	result.b = (unsigned char)(c1.b + t * (c2.b - c1.b));
	result.a = 255;
	return (result);
}

static double	get_percent(int z, const t_map *map)
{
	unsigned int	range;

	range = map->zmax - map->zmin;
	if (range == 0)
		return (0.5);
	return ((double)(z - map->zmin) / range);
}

static int	get_elevation_color(double percent)
{
	t_color	low;
	t_color	high;
	t_color	result;

	low = create_color(0, 0, 128);
	high = create_color(255, 0, 0);
	result = lerp_colors(low, high, percent);
	return (color_to_int(result));
}

int	pick_color(const t_point *p, const t_map *map)
{
	if (p->color != -1)
	{
		return (p->color);
	}
	return (get_elevation_color(get_percent(p->z, map)));
}

int	interpolate_line_color(const t_point *p1, const t_point *p2, 
			const t_map *map, double t)
{
	int		color1;
	int		color2;
	t_color	c1;
	t_color	c2;
	t_color	result;

	color1 = pick_color(p1, map);
	color2 = pick_color(p2, map);
	if (color1 == color2)
		return (color1);
	c1.r = (color1 >> 16) & 0xFF;
	c1.g = (color1 >> 8) & 0xFF;
	c1.b = color1 & 0xFF;
	c1.a = 255;
	c2.r = (color2 >> 16) & 0xFF;
	c2.g = (color2 >> 8) & 0xFF;
	c2.b = color2 & 0xFF;
	c2.a = 255;
	result = lerp_colors(c1, c2, t);
	return (color_to_int(result));
}

int	interpolate_colors_direct(int color1, int color2, double t)
{
	t_color	c1;
	t_color	c2;
	t_color	result;

	if (t <= 0.0)
		return (color1);
	if (t >= 1.0)
		return (color2);
	c1.r = (color1 >> 16) & 0xFF;
	c1.g = (color1 >> 8) & 0xFF;
	c1.b = color1 & 0xFF;
	c1.a = 255;
	c2.r = (color2 >> 16) & 0xFF;
	c2.g = (color2 >> 8) & 0xFF;
	c2.b = color2 & 0xFF;
	c2.a = 255;
	result = lerp_colors(c1, c2, t);
	return (color_to_int(result));
}
