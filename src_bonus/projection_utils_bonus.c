/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection_utils_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddadi <mhaddadi@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 22:20:00 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/09/12 22:20:01 by mhaddadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf_bonus.h"

static double	calculate_z_center(t_map *map)
{
	double	z_min;
	double	z_max;
	int		x;
	int		y;

	if (!map || !map->pts || map->h == 0 || map->w == 0)
		return (0.0);
	z_min = map->pts[0][0].z;
	z_max = map->pts[0][0].z;
	y = 0;
	while (y < map->h)
	{
		x = 0;
		while (x < map->w && map->pts[y])
		{
			if (map->pts[y][x].z < z_min)
				z_min = map->pts[y][x].z;
			if (map->pts[y][x].z > z_max)
				z_max = map->pts[y][x].z;
			x++;
		}
		y++;
	}
	return ((z_min + z_max) / 2.0);
}

static double	get_cached_z_center(t_map *map, int proj)
{
	static double	cached_z_center = 0.0;
	static int		cached_proj = -1;
	static t_map	*cached_map = NULL;

	if (proj == 1 || !map)
		return (0.0);
	if (cached_map != map || cached_proj != proj)
	{
		cached_z_center = calculate_z_center(map);
		cached_map = map;
		cached_proj = proj;
	}
	return (cached_z_center);
}

void	apply_planar_projection(t_point3d p3d, t_view *view, t_map *map,
	t_point2d *result)
{
	double	z_center;

	z_center = get_cached_z_center(map, view->proj);
	if (view->proj == 1)
	{
		result->x = (int)((p3d.x - (map->w - 1) / 2.0) * view->scale
				+ view->offset_x);
		result->y = (int)((p3d.y - (map->h - 1) / 2.0) * view->scale
				+ view->offset_y);
	}
	else if (view->proj == 2)
	{
		result->x = (int)((p3d.x - (map->w - 1) / 2.0) * view->scale
				+ view->offset_x);
		result->y = (int)((-p3d.z + z_center) * view->scale + view->offset_y);
	}
	else
	{
		result->x = (int)((p3d.y - (map->h - 1) / 2.0) * view->scale
				+ view->offset_x);
		result->y = (int)((-p3d.z + z_center) * view->scale + view->offset_y);
	}
}
