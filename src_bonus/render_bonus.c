/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddadi <mhaddadi@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 20:25:28 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/09/07 20:25:37 by mhaddadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf_bonus.h"

static void	setup_projection_vars(t_point3d p3d, t_view *view, t_map *map,
	t_point3d *rotated)
{
	double	cx;
	double	cy;

	p3d.z *= view->zscale;
	cx = (map->w - 1) / 2.0;
	cy = (map->h - 1) / 2.0;
	*rotated = apply_rotations(p3d, cx, cy, view);
}

t_point2d	project_bonus_complete(t_point3d p3d, t_view *view, t_map *map)
{
	t_point2d	p2d;
	t_point3d	rotated;

	p3d.z *= view->zscale;
	if (view->proj == PROJ_ISO)
	{
		setup_projection_vars(p3d, view, map, &rotated);
		p2d.x = (int)((rotated.x - rotated.y) * cos(M_PI / 6.0) * view->scale
				+ view->offset_x);
		p2d.y = (int)(((rotated.x + rotated.y) * sin(M_PI / 6.0) - rotated.z)
				* view->scale + view->offset_y);
	}
	else
		apply_planar_projection(p3d, view, map, &p2d);
	return (p2d);
}

void	render_wireframe_bonus_complete(t_app_bonus *app)
{
	if (!app || !app->map.pts)
		return ;
	img_clear(&app->mlx.img, 0x000000);
	render_depth_sorted_bonus(app);
}
