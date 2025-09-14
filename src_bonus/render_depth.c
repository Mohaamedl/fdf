/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_depth.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddadi <mhaddadi@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 21:02:00 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/09/14 14:00:00 by mhaddadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf_bonus.h"

static int	is_line_visible(t_point2d p1, t_point2d p2)
{
	return (!(p1.x < -50 && p2.x < -50) && !(p1.x > 1330 && p2.x > 1330)
		&& !(p1.y < -50 && p2.y < -50) && !(p1.y > 770 && p2.y > 770));
}

static void	draw_depth_line(t_app_bonus *app, int coords[4], t_z_range range)
{
	t_point3d		points[2];
	t_point2d		pts[2];
	t_line_gradient	line;
	double			z_avg;

	points[0] = (t_point3d){coords[0], coords[1],
		app->map.pts[coords[1]][coords[0]].z};
	points[1] = (t_point3d){coords[2], coords[3],
		app->map.pts[coords[3]][coords[2]].z};
	z_avg = (points[0].z + points[1].z) / 2.0;
	if (z_avg < range.z_min || z_avg > range.z_max)
		return ;
	pts[0] = project_bonus_complete(points[0], &app->view, &app->map);
	pts[1] = project_bonus_complete(points[1], &app->view, &app->map);
	if (!is_line_visible(pts[0], pts[1]))
		return ;
	line.img = &app->mlx.img;
	line.start = pts[0];
	line.end = pts[1];
	draw_line_with_colors(&line,
		pick_color_mode(&app->map.pts[coords[1]][coords[0]], &app->map,
			app->color_mode),
		pick_color_mode(&app->map.pts[coords[3]][coords[2]], &app->map,
			app->color_mode));
}

static void	draw_point_lines(t_app_bonus *app, int x, int y, t_z_range range)
{
	int	coords[4];

	if (x + 1 < app->map.w)
	{
		coords[0] = x;
		coords[1] = y;
		coords[2] = x + 1;
		coords[3] = y;
		draw_depth_line(app, coords, range);
	}
	if (y + 1 < app->map.h)
	{
		coords[0] = x;
		coords[1] = y;
		coords[2] = x;
		coords[3] = y + 1;
		draw_depth_line(app, coords, range);
	}
}

static void	process_z_slice(t_app_bonus *app, t_z_range range)
{
	int	x;
	int	y;

	y = -1;
	while (++y < app->map.h)
	{
		x = -1;
		while (++x < app->map.w)
			draw_point_lines(app, x, y, range);
	}
}

void	render_depth_sorted_bonus(t_app_bonus *app)
{
	int			passes;
	int			i;
	t_z_range	range;
	double		z_step;

	if (!app || !app->map.pts)
		return ;
	if (app->map.w * app->map.h > 200000)
		passes = 2;
	else if (app->map.w * app->map.h > 100000)
		passes = 8;
	else
		passes = 20;
	z_step = (app->map.zmax - app->map.zmin + 1.0) / passes;
	if (z_step < 1.0)
		z_step = 1.0;
	i = 0;
	while (i < passes)
	{
		range.z_min = app->map.zmin + (i * z_step);
		range.z_max = range.z_min + z_step;
		process_z_slice(app, range);
		i++;
	}
}
