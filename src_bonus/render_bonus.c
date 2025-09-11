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

static void	collect_horizontal_line_bonus(t_app_bonus *app, int x, int y, 
				t_line_depth *lines, int *count)
{
	t_point2d	pts[2];
	const t_point	*p1;
	const t_point	*p2;

	if (!app || !app->map.pts || x + 1 >= app->map.w || y >= app->map.h)
		return ;
	if (!app->map.pts[y])
		return ;
	p1 = &app->map.pts[y][x];
	p2 = &app->map.pts[y][x + 1];
	setup_horizontal_points(app, x, y, pts);
	if (should_cull_line(pts[0], pts[1]))
		return ;
	lines[*count].p1 = pts[0];
	lines[*count].p2 = pts[1];
	lines[*count].color1 = pick_color(p1, &app->map);
	lines[*count].color2 = pick_color(p2, &app->map);
	lines[*count].avg_depth = (pts[0].y + pts[1].y) / 2.0;
	(*count)++;
}

static void	collect_vertical_line_bonus(t_app_bonus *app, int x, int y, 
				t_line_depth *lines, int *count)
{
	t_point2d	pts[2];
	const t_point	*p1;
	const t_point	*p2;

	if (!app || !app->map.pts || y + 1 >= app->map.h || x >= app->map.w)
		return ;
	if (!app->map.pts[y] || !app->map.pts[y + 1])
		return ;
	p1 = &app->map.pts[y][x];
	p2 = &app->map.pts[y + 1][x];
	setup_vertical_points(app, x, y, pts);
	if (should_cull_line(pts[0], pts[1]))
		return ;
	lines[*count].p1 = pts[0];
	lines[*count].p2 = pts[1];
	lines[*count].color1 = pick_color(p1, &app->map);
	lines[*count].color2 = pick_color(p2, &app->map);
	lines[*count].avg_depth = (pts[0].y + pts[1].y) / 2.0;
	(*count)++;
}

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
	else
	{
		proj_x = rotated.x;
		proj_y = rotated.y - rotated.z;
	}
	proj_x *= view->scale;
	proj_y *= view->scale;
	proj_x += view->offset_x;
	proj_y += view->offset_y;
	p2d.x = (int)proj_x;
	p2d.y = (int)proj_y;
	return (p2d);
}

void	render_wireframe_bonus_complete(t_app_bonus *app)
{
	t_line_depth	*lines;
	int				max_lines;
	int				count;
	int				x;
	int				y;
	int				i;

	if (!app || !app->map.pts)
		return ;
	max_lines = (app->map.w - 1) * app->map.h + app->map.w * (app->map.h - 1);
	lines = malloc(sizeof(t_line_depth) * max_lines);
	if (!lines)
		return ;
	img_clear(&app->mlx.img, 0x000000);
	count = 0;
	y = 0;
	while (y < app->map.h)
	{
		x = 0;
		while (x < app->map.w)
		{
			collect_horizontal_line_bonus(app, x, y, lines, &count);
			collect_vertical_line_bonus(app, x, y, lines, &count);
			x++;
		}
		y++;
	}
	sort_lines_by_depth(lines, count);
	i = 0;
	while (i < count)
	{
		draw_line_gradient(&app->mlx.img, lines[i].p1, lines[i].p2,
			lines[i].color1, lines[i].color2);
		i++;
	}
	free(lines);
}
