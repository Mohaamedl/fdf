/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 13:47:22 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/08/24 14:36:19 by mohamed          ###   ########.fr       */
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

	if (p->color != -1)
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

int	pick_color_bonus(const t_point *p, const t_map *map, const void *app)
{
	const int	*color_mode_ptr;

	color_mode_ptr = (const int *)((const char *)app
			+ sizeof(void *) * 3 + sizeof(double) * 14 + sizeof(int) * 6);
	return (pick_color_mode(p, map, *color_mode_ptr));
}
