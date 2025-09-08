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
	t_proj_params	params;
	const t_point	*p1;
	const t_point	*p2;
	double			s[4];
	t_point2d		pt[2];

	if (x + 1 >= app->map.w)
		return ;
	p1 = &app->map.pts[y][x];
	p2 = &app->map.pts[y][x + 1];
	params = (t_proj_params){x, y, p1->z, &s[0], &s[1]};
	project_point_safe(&app->view, &params);
	params = (t_proj_params){x + 1, y, p2->z, &s[2], &s[3]};
	project_point_safe(&app->view, &params);
	pt[0] = (t_point2d){(int)s[0], (int)s[1]};
	pt[1] = (t_point2d){(int)s[2], (int)s[3]};
	draw_line_pts(&app->mlx.img, pt[0], pt[1], pick_color(p1, &app->map));
}

static void	draw_vertical_line(t_app *app, int x, int y)
{
	t_proj_params	params;
	const t_point	*p1;
	const t_point	*p2;
	double			s[4];
	t_point2d		pt[2];

	if (y + 1 >= app->map.h)
		return ;
	p1 = &app->map.pts[y][x];
	p2 = &app->map.pts[y + 1][x];
	params = (t_proj_params){x, y, p1->z, &s[0], &s[1]};
	project_point_safe(&app->view, &params);
	params = (t_proj_params){x, y + 1, p2->z, &s[2], &s[3]};
	project_point_safe(&app->view, &params);
	pt[0] = (t_point2d){(int)s[0], (int)s[1]};
	pt[1] = (t_point2d){(int)s[2], (int)s[3]};
	draw_line_pts(&app->mlx.img, pt[0], pt[1], pick_color(p1, &app->map));
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

void	put_px(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (!img || !img->addr)
		return ;
	if (x < 0 || y < 0 || x >= img->w || y >= img->h)
		return ;
	dst = img->addr + y * img->line_len + x * (img->bpp / 8);
	*(unsigned int *)dst = (unsigned int)color;
}
