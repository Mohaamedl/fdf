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

static void	draw_horizontal_line(t_app *app, int x, int y)
{
	t_point2d		pts[2];
	t_line_gradient	line;
	int				color1;
	int				color2;
	t_proj_params	params;
	double			proj_coords[4];

	if (!app || !app->map.pts || x + 1 >= app->map.w || y >= app->map.h)
		return ;
	if (!app->map.pts[y])
		return ;
	params = (t_proj_params){x, y, app->map.pts[y][x].z,
		&proj_coords[0], &proj_coords[1]};
	project_point_safe(&app->view, &params);
	params = (t_proj_params){x + 1, y, app->map.pts[y][x + 1].z,
		&proj_coords[2], &proj_coords[3]};
	project_point_safe(&app->view, &params);
	pts[0] = (t_point2d){(int)proj_coords[0], (int)proj_coords[1]};
	pts[1] = (t_point2d){(int)proj_coords[2], (int)proj_coords[3]};
	color1 = pick_color(&app->map.pts[y][x], &app->map);
	color2 = pick_color(&app->map.pts[y][x + 1], &app->map);
	setup_line_data(&line, &app->mlx.img, pts[0], pts[1]);
	draw_line_with_colors(&line, color1, color2);
}

static void	draw_vertical_line(t_app *app, int x, int y)
{
	t_point2d		pts[2];
	t_line_gradient	line;
	int				color1;
	int				color2;
	t_proj_params	params;
	double			proj_coords[4];

	if (!app || !app->map.pts || y + 1 >= app->map.h || x >= app->map.w)
		return ;
	if (!app->map.pts[y] || !app->map.pts[y + 1])
		return ;
	params = (t_proj_params){x, y, app->map.pts[y][x].z,
		&proj_coords[0], &proj_coords[1]};
	project_point_safe(&app->view, &params);
	params = (t_proj_params){x, y + 1, app->map.pts[y + 1][x].z,
		&proj_coords[2], &proj_coords[3]};
	project_point_safe(&app->view, &params);
	pts[0] = (t_point2d){(int)proj_coords[0], (int)proj_coords[1]};
	pts[1] = (t_point2d){(int)proj_coords[2], (int)proj_coords[3]};
	color1 = pick_color(&app->map.pts[y][x], &app->map);
	color2 = pick_color(&app->map.pts[y + 1][x], &app->map);
	setup_line_data(&line, &app->mlx.img, pts[0], pts[1]);
	draw_line_with_colors(&line, color1, color2);
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
			draw_horizontal_line(app, x, y);
			draw_vertical_line(app, x, y);
			x++;
		}
		y++;
	}
}
