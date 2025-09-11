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

static void	collect_horizontal_line(t_app *app, int x, int y, 
				t_line_depth *lines, int *count)
{
	t_proj_params	params;
	const t_point	*p1;
	const t_point	*p2;
	double			s[4];
	double			depth1;
	double			depth2;

	if (x + 1 >= app->map.w)
		return ;
	p1 = &app->map.pts[y][x];
	p2 = &app->map.pts[y][x + 1];
	params = (t_proj_params){x, y, p1->z, &s[0], &s[1]};
	project_point_safe(&app->view, &params);
	depth1 = s[1];
	params = (t_proj_params){x + 1, y, p2->z, &s[2], &s[3]};
	project_point_safe(&app->view, &params);
	depth2 = s[3];
	lines[*count].p1 = (t_point2d){(int)s[0], (int)s[1]};
	lines[*count].p2 = (t_point2d){(int)s[2], (int)s[3]};
	if (should_cull_line(lines[*count].p1, lines[*count].p2))
		return ;
	lines[*count].color1 = pick_color(p1, &app->map);
	lines[*count].color2 = pick_color(p2, &app->map);
	lines[*count].avg_depth = (depth1 + depth2) / 2.0;
	(*count)++;
}

static void	collect_vertical_line(t_app *app, int x, int y, 
				t_line_depth *lines, int *count)
{
	t_proj_params	params;
	const t_point	*p1;
	const t_point	*p2;
	double			s[4];
	double			depth1;
	double			depth2;

	if (y + 1 >= app->map.h)
		return ;
	p1 = &app->map.pts[y][x];
	p2 = &app->map.pts[y + 1][x];
	params = (t_proj_params){x, y, p1->z, &s[0], &s[1]};
	project_point_safe(&app->view, &params);
	depth1 = s[1];
	params = (t_proj_params){x, y + 1, p2->z, &s[2], &s[3]};
	project_point_safe(&app->view, &params);
	depth2 = s[3];
	lines[*count].p1 = (t_point2d){(int)s[0], (int)s[1]};
	lines[*count].p2 = (t_point2d){(int)s[2], (int)s[3]};
	if (should_cull_line(lines[*count].p1, lines[*count].p2))
		return ;
	lines[*count].color1 = pick_color(p1, &app->map);
	lines[*count].color2 = pick_color(p2, &app->map);
	lines[*count].avg_depth = (depth1 + depth2) / 2.0;
	(*count)++;
}

static int	view_changed_significantly(t_app *app)
{
	t_view	*v;
	t_render_cache	*c;
	double	rot_threshold;
	double	scale_threshold;

	v = &app->view;
	c = &app->cache;
	rot_threshold = 0.01;
	scale_threshold = 0.05;
	if (c->dirty)
		return (1);
	if (fabs(v->rot_x - c->last_rot_x) > rot_threshold)
		return (1);
	if (fabs(v->rot_y - c->last_rot_y) > rot_threshold)
		return (1);
	if (fabs(v->rot_z - c->last_rot_z) > rot_threshold)
		return (1);
	if (fabs(v->scale - c->last_scale) > scale_threshold)
		return (1);
	return (0);
}

static void	update_cache_view_state(t_app *app)
{
	t_render_cache	*c;

	c = &app->cache;
	c->last_rot_x = app->view.rot_x;
	c->last_rot_y = app->view.rot_y;
	c->last_rot_z = app->view.rot_z;
	c->last_scale = app->view.scale;
	c->dirty = 0;
}

void	render_wireframe(t_app *app)
{
	int				x;
	int				y;
	int				i;
	int				need_resort;

	if (!app->cache.lines)
	{
		app->cache.capacity = (app->map.w - 1) * app->map.h + app->map.w * (app->map.h - 1);
		app->cache.lines = malloc(sizeof(t_line_depth) * app->cache.capacity);
		if (!app->cache.lines)
			return ;
		app->cache.dirty = 1;
	}
	need_resort = view_changed_significantly(app);
	if (need_resort)
	{
		app->cache.count = 0;
		y = 0;
		while (y < app->map.h)
		{
			x = 0;
			while (x < app->map.w)
			{
				collect_horizontal_line(app, x, y, app->cache.lines, &app->cache.count);
				collect_vertical_line(app, x, y, app->cache.lines, &app->cache.count);
				x++;
			}
			y++;
		}
		sort_lines_by_depth(app->cache.lines, app->cache.count);
		update_cache_view_state(app);
	}
	img_clear(&app->mlx.img, 0x000000);
	i = 0;
	while (i < app->cache.count)
	{
		draw_line_gradient(&app->mlx.img, app->cache.lines[i].p1, app->cache.lines[i].p2,
			app->cache.lines[i].color1, app->cache.lines[i].color2);
		i++;
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
