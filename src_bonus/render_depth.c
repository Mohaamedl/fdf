/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_depth_fast.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddadi <mhaddadi@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 21:02:00 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/09/12 21:02:00 by mhaddadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf_bonus.h"

static void	render_z_range_bonus(t_app_bonus *app, t_z_range range);
static void	draw_lines_for_point(t_app_bonus *app, int x, int y,
				t_z_range range);
static void	draw_line_if_in_range_bonus(t_app_bonus *app, int coords[4],
				t_z_range range);
static int	line_in_z_range_bonus(t_app_bonus *app, int coords[4],
				t_z_range range);

void	render_depth_sorted_bonus(t_app_bonus *app)
{
	double		z_step;
	double		z_current;
	int			passes;
	int			i;
	t_z_range	range;

	if (!app || !app->map.pts)
		return ;
	passes = 20;
	z_step = (app->map.zmax - app->map.zmin + 1.0) / passes;
	if (z_step < 1.0)
		z_step = 1.0;
	i = 0;
	while (i < passes)
	{
		z_current = app->map.zmin + (i * z_step);
		range.z_min = z_current;
		range.z_max = z_current + z_step;
		render_z_range_bonus(app, range);
		i++;
	}
}

static void	draw_lines_for_point(t_app_bonus *app, int x, int y,
	t_z_range range)
{
	int	coords[4];

	if (x + 1 < app->map.w)
	{
		coords[0] = x;
		coords[1] = y;
		coords[2] = x + 1;
		coords[3] = y;
		draw_line_if_in_range_bonus(app, coords, range);
	}
	if (y + 1 < app->map.h)
	{
		coords[0] = x;
		coords[1] = y;
		coords[2] = x;
		coords[3] = y + 1;
		draw_line_if_in_range_bonus(app, coords, range);
	}
}

static void	render_z_range_bonus(t_app_bonus *app, t_z_range range)
{
	int	x;
	int	y;

	y = 0;
	while (y < app->map.h)
	{
		x = 0;
		while (x < app->map.w)
		{
			draw_lines_for_point(app, x, y, range);
			x++;
		}
		y++;
	}
}

static int	line_in_z_range_bonus(t_app_bonus *app, int coords[4],
		t_z_range range)
{
	double	z1;
	double	z2;
	double	z_avg;

	z1 = app->map.pts[coords[1]][coords[0]].z;
	z2 = app->map.pts[coords[3]][coords[2]].z;
	z_avg = (z1 + z2) / 2.0;
	return (z_avg >= range.z_min && z_avg <= range.z_max);
}

static void	draw_line_if_in_range_bonus(t_app_bonus *app, int coords[4],
	t_z_range range)
{
	t_point2d		pts[2];
	t_line_gradient	line;
	t_point3d		p1;
	t_point3d		p2;

	if (!line_in_z_range_bonus(app, coords, range))
		return ;
	setup_3d_points(coords, app, &p1, &p2);
	pts[0] = project_bonus_complete(p1, &app->view, &app->map);
	pts[1] = project_bonus_complete(p2, &app->view, &app->map);
	if (!is_line_visible_bonus(pts[0], pts[1]))
		return ;
	line.img = &app->mlx.img;
	line.start = pts[0];
	line.end = pts[1];
	draw_line_with_colors(&line,
		pick_color(&app->map.pts[coords[1]][coords[0]], &app->map),
		pick_color(&app->map.pts[coords[3]][coords[2]], &app->map));
}
