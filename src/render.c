/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddadi <mhaddadi@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 18:55:52 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/09/08 18:56:15 by mhaddadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static void	project_two_points(t_app *app, int coords[4], t_point2d *pts)
{
	t_proj_params	params;
	double			proj_coords[4];

	params = (t_proj_params){coords[0], coords[1],
		app->map.pts[coords[1]][coords[0]].z,
		&proj_coords[0], &proj_coords[1]};
	project_point_safe(&app->view, &params);
	params = (t_proj_params){coords[2], coords[3],
		app->map.pts[coords[3]][coords[2]].z,
		&proj_coords[2], &proj_coords[3]};
	project_point_safe(&app->view, &params);
	pts[0] = (t_point2d){(int)proj_coords[0], (int)proj_coords[1]};
	pts[1] = (t_point2d){(int)proj_coords[2], (int)proj_coords[3]};
}

void	draw_horizontal_line(t_app *app, int x, int y)
{
	t_point2d		pts[2];
	t_line_gradient	line;
	int				coords[4];

	if (!app || !app->map.pts || x + 1 >= app->map.w || y >= app->map.h)
		return ;
	if (!app->map.pts[y])
		return ;
	coords[0] = x;
	coords[1] = y;
	coords[2] = x + 1;
	coords[3] = y;
	project_two_points(app, coords, pts);
	setup_line_data(&line, &app->mlx.img, pts[0], pts[1]);
	draw_line_with_colors(&line, pick_color(&app->map.pts[y][x], &app->map),
		pick_color(&app->map.pts[y][x + 1], &app->map));
}

void	draw_vertical_line(t_app *app, int x, int y)
{
	t_point2d		pts[2];
	t_line_gradient	line;
	int				coords[4];

	if (!app || !app->map.pts || y + 1 >= app->map.h || x >= app->map.w)
		return ;
	if (!app->map.pts[y] || !app->map.pts[y + 1])
		return ;
	coords[0] = x;
	coords[1] = y;
	coords[2] = x;
	coords[3] = y + 1;
	project_two_points(app, coords, pts);
	setup_line_data(&line, &app->mlx.img, pts[0], pts[1]);
	draw_line_with_colors(&line, pick_color(&app->map.pts[y][x], &app->map),
		pick_color(&app->map.pts[y + 1][x], &app->map));
}

void	render_wireframe(t_app *app)
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
			if (x + 1 < app->map.w)
				draw_horizontal_line(app, x, y);
			if (y + 1 < app->map.h)
				draw_vertical_line(app, x, y);
			x++;
		}
		y++;
	}
}
