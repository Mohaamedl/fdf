/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddadi <mhaddadi@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 13:50:34 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/08/23 13:50:44 by mhaddadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static void	draw_horizontal_line(t_app *app, int x, int y)
{
	t_proj_params	params1;
	t_proj_params	params2;
	const t_point	*p1;
	const t_point	*p2;
	double			sx1;
	double			sy1;
	double			sx2;
	double			sy2;
	t_point2d		pt1;
	t_point2d		pt2;

	if (x + 1 >= app->map.w)
		return ;
	p1 = &app->map.pts[y][x];
	p2 = &app->map.pts[y][x + 1];
	params1 = (t_proj_params){x, y, p1->z, &sx1, &sy1};
	params2 = (t_proj_params){x + 1, y, p2->z, &sx2, &sy2};
	project_point_safe(&app->view, &params1);
	project_point_safe(&app->view, &params2);
	pt1 = (t_point2d){(int)sx1, (int)sy1};
	pt2 = (t_point2d){(int)sx2, (int)sy2};
	draw_line_pts(&app->mlx.img, pt1, pt2, pick_color(p1, &app->map));
}

static void	draw_vertical_line(t_app *app, int x, int y)
{
	t_proj_params	params1;
	t_proj_params	params2;
	const t_point	*p1;
	const t_point	*p2;
	double			sx1;
	double			sy1;
	double			sx2;
	double			sy2;
	t_point2d		pt1;
	t_point2d		pt2;

	if (y + 1 >= app->map.h)
		return ;
	p1 = &app->map.pts[y][x];
	p2 = &app->map.pts[y + 1][x];
	params1 = (t_proj_params){x, y, p1->z, &sx1, &sy1};
	params2 = (t_proj_params){x, y + 1, p2->z, &sx2, &sy2};
	project_point_safe(&app->view, &params1);
	project_point_safe(&app->view, &params2);
	pt1 = (t_point2d){(int)sx1, (int)sy1};
	pt2 = (t_point2d){(int)sx2, (int)sy2};
	draw_line_pts(&app->mlx.img, pt1, pt2, pick_color(p1, &app->map));
}

void	render_wireframe(t_app *app)
{
	int	x;
	int	y;

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
