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
	double	cz;
	double	cx;
	double	cy;

	cz = ((map->zmin + map->zmax) / 2.0) * view->zscale;
	p3d.z -= cz;
	cx = (map->w - 1) / 2.0;
	cy = (map->h - 1) / 2.0;
	*rotated = apply_rotations(p3d, cx, cy, view);
}

t_point2d	project_bonus_complete(t_point3d p3d, t_view *view, t_map *map)
{
	t_point2d	p2d;
	t_point3d	rotated;
	double		proj_x;
	double		proj_y;

	setup_projection_vars(p3d, view, map, &rotated);
	if (view->proj == PROJ_ISO)
	{
		proj_x = (rotated.x - rotated.y) * cos(M_PI / 6.0);
		proj_y = (rotated.x + rotated.y) * sin(M_PI / 6.0) - rotated.z;
	}
	else if (view->proj == PROJ_PAR)
	{
		proj_x = rotated.x;
		proj_y = rotated.y;
	}
	else
		project_perspective(&proj_x, &proj_y, rotated);
	proj_x *= view->scale;
	proj_y *= view->scale;
	proj_x += view->offset_x;
	proj_y += view->offset_y;
	p2d.x = (int)proj_x;
	p2d.y = (int)proj_y;
	return (p2d);
}

static void	draw_horizontal_line_bonus(t_app_bonus *app, int x, int y)
{
	t_point2d	pts[2];

	if (!app || !app->map.pts || x + 1 >= app->map.w || y >= app->map.h)
		return ;
	if (!app->map.pts[y])
		return ;
	setup_horizontal_points(app, x, y, pts);
	if (should_cull_line(pts[0], pts[1]))
		return ;
	draw_line_pts_color(&app->mlx.img, pts[0], pts[1],
		pick_color_mode(&app->map.pts[y][x], &app->map, app->color_mode));
}

static void	draw_vertical_line_bonus(t_app_bonus *app, int x, int y)
{
	t_point2d	pts[2];

	if (!app || !app->map.pts || y + 1 >= app->map.h || x >= app->map.w)
		return ;
	if (!app->map.pts[y] || !app->map.pts[y + 1])
		return ;
	setup_vertical_points(app, x, y, pts);
	if (should_cull_line(pts[0], pts[1]))
		return ;
	draw_line_pts_color(&app->mlx.img, pts[0], pts[1],
		pick_color_mode(&app->map.pts[y][x], &app->map, app->color_mode));
}

void	render_wireframe_bonus_complete(t_app_bonus *app)
{
	int	x;
	int	y;

	if (!app || !app->map.pts)
		return ;
	img_clear(&app->mlx.img, 0x000000);
	y = 0;
	while (y < app->map.h)
	{
		x = 0;
		while (x < app->map.w)
		{
			draw_horizontal_line_bonus(app, x, y);
			draw_vertical_line_bonus(app, x, y);
			x++;
		}
		y++;
	}
}
