/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_depth_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddadi <mhaddadi@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 20:40:00 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/09/12 20:40:00 by mhaddadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf_bonus.h"

int	should_render_first_bonus(t_app_bonus *app, int x, int y, int is_horizontal)
{
	double	z_avg;

	if (is_horizontal && x + 1 < app->map.w)
		z_avg = (app->map.pts[y][x].z + app->map.pts[y][x + 1].z) / 2.0;
	else if (!is_horizontal && y + 1 < app->map.h)
		z_avg = (app->map.pts[y][x].z + app->map.pts[y + 1][x].z) / 2.0;
	else
		return (0);
	return (z_avg > 0);
}

void	render_pass_bonus(t_app_bonus *app, int pass)
{
	int	x;
	int	y;

	y = 0;
	while (y < app->map.h)
	{
		x = 0;
		while (x < app->map.w)
		{
			if (should_render_first_bonus(app, x, y, 1) == pass)
				draw_horizontal_line_bonus(app, x, y);
			if (should_render_first_bonus(app, x, y, 0) == pass)
				draw_vertical_line_bonus(app, x, y);
			x++;
		}
		y++;
	}
}

int	is_line_visible_bonus(t_point2d p1, t_point2d p2)
{
	if (p1.x < -50 && p2.x < -50)
		return (0);
	if (p1.x > WIN_W + 50 && p2.x > WIN_W + 50)
		return (0);
	if (p1.y < -50 && p2.y < -50)
		return (0);
	if (p1.y > WIN_H + 50 && p2.y > WIN_H + 50)
		return (0);
	return (1);
}

void	setup_3d_points(int coords[4], t_app_bonus *app, t_point3d *p1,
	t_point3d *p2)
{
	p1->x = coords[0];
	p1->y = coords[1];
	p1->z = app->map.pts[coords[1]][coords[0]].z;
	p2->x = coords[2];
	p2->y = coords[3];
	p2->z = app->map.pts[coords[3]][coords[2]].z;
}
