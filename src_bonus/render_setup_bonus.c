/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_setup_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddadi <mhaddadi@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 20:25:06 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/09/07 20:25:16 by mhaddadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf_bonus.h"

static void	create_3d_points(t_point_setup setup, t_point3d *pt1_3d,
	t_point3d *pt2_3d)
{
	const t_point	*p1;
	const t_point	*p2;

	if (setup.is_horizontal)
	{
		p1 = &setup.app->map.pts[setup.y][setup.x];
		p2 = &setup.app->map.pts[setup.y][setup.x + 1];
		*pt1_3d = (t_point3d){setup.x, setup.y,
			p1->z * setup.app->view.zscale};
		*pt2_3d = (t_point3d){setup.x + 1, setup.y,
			p2->z * setup.app->view.zscale};
	}
	else
	{
		p1 = &setup.app->map.pts[setup.y][setup.x];
		p2 = &setup.app->map.pts[setup.y + 1][setup.x];
		*pt1_3d = (t_point3d){setup.x, setup.y,
			p1->z * setup.app->view.zscale};
		*pt2_3d = (t_point3d){setup.x, setup.y + 1,
			p2->z * setup.app->view.zscale};
	}
}

void	setup_horizontal_points(t_app_bonus *app, int x, int y, t_point2d *pts)
{
	t_point_setup	setup;
	t_point3d		pt1_3d;
	t_point3d		pt2_3d;

	setup = (t_point_setup){app, x, y, 1};
	create_3d_points(setup, &pt1_3d, &pt2_3d);
	pts[0] = project_bonus_complete(pt1_3d, &app->view, &app->map);
	pts[1] = project_bonus_complete(pt2_3d, &app->view, &app->map);
}

void	setup_vertical_points(t_app_bonus *app, int x, int y, t_point2d *pts)
{
	t_point_setup	setup;
	t_point3d		pt1_3d;
	t_point3d		pt2_3d;

	setup = (t_point_setup){app, x, y, 0};
	create_3d_points(setup, &pt1_3d, &pt2_3d);
	pts[0] = project_bonus_complete(pt1_3d, &app->view, &app->map);
	pts[1] = project_bonus_complete(pt2_3d, &app->view, &app->map);
}
