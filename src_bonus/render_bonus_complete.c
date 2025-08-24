/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus_complete.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 13:58:43 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/08/24 11:16:40 by mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "fdf_bonus.h"

// 3D rotation with cached trig values for better performance
static t_point3d	rotate_point_centered_fast(t_point3d p,
												   double cx, double cy,
												   double cosx, double sinx,
												   double cosy, double siny,
												   double cosz, double sinz)
{
	t_point3d	result;
	double		temp_y, temp_z;

	// Translate to center
	p.x -= cx;
	p.y -= cy;

	// Rotate X
	temp_y = p.y * cosx - p.z * sinx;
	temp_z = p.y * sinx + p.z * cosx;
	p.y = temp_y;
	p.z = temp_z;

	// Rotate Y
	result.x = p.x * cosy + p.z * siny;
	result.z = -p.x * siny + p.z * cosy;
	result.y = p.y;

	// Rotate Z
	temp_y = result.y;
	result.y = temp_y * cosz - result.x * sinz;
	result.x = temp_y * sinz + result.x * cosz;

	// Translate back
	result.x += cx;
	result.y += cy;
	return (result);
}

// Multi-projection system
t_point2d	project_bonus_complete(t_point3d p3d, t_view *view, t_map *map)
{
	t_point2d	p2d;
	t_point3d	rotated;
	double		proj_x, proj_y;
    
	// Cache reusable values
	const double cx = (map->w - 1) / 2.0;
	const double cy = (map->h - 1) / 2.0;
	const double cosx = cos(view->rot_x);
	const double sinx = sin(view->rot_x);
	const double cosy = cos(view->rot_y);
	const double siny = sin(view->rot_y);
	const double cosz = cos(view->rot_z);
	const double sinz = sin(view->rot_z);

	// Apply 3D rotations
	rotated = rotate_point_centered_fast(p3d, cx, cy, cosx, sinx, cosy, siny, cosz, sinz);

	// Apply different projection modes
	if (view->proj == PROJ_ISO)  // Isometric (classic 30-degree)
	{
		proj_x = (rotated.x - rotated.y) * cos(M_PI / 6.0);
		proj_y = (rotated.x + rotated.y) * sin(M_PI / 6.0) - rotated.z;
	}
	else if (view->proj == PROJ_PAR)  // Parallel (orthographic)
	{
		proj_x = rotated.x;
		proj_y = rotated.y - rotated.z * 0.3;  // Slight Z offset for depth
	}
	else  // Perspective (3D with depth)
	{
		double	fov = 800.0;  // Field of view distance
		double	distance = fov - rotated.z;  // Camera distance
		
		if (distance < 50.0)  // Prevent division by very small numbers
			distance = 50.0;
		proj_x = rotated.x * fov / distance;
		proj_y = rotated.y * fov / distance;
	}

	// Apply scale and translation
	proj_x *= view->scale;
	proj_y *= view->scale;
	proj_x += view->offset_x;
	proj_y += view->offset_y;

	p2d.x = (int)proj_x;
	p2d.y = (int)proj_y;

	return (p2d);
}

// Enhanced line drawing
static void	draw_horizontal_line_bonus(t_app_bonus *app, int x, int y)
{
	const t_point	*p1;
	const t_point	*p2;
	t_point3d		pt1_3d;
	t_point3d		pt2_3d;
	t_point2d		pt1, pt2;

	if (!app || !app->map.pts || x + 1 >= app->map.w || y >= app->map.h)
		return ;
	if (!app->map.pts[y] || !app->map.pts[y][x].color || !app->map.pts[y][x + 1].color)
		return ;
	
	p1 = &app->map.pts[y][x];
	p2 = &app->map.pts[y][x + 1];
	
	// Create 3D points with Z-scale
	pt1_3d.x = x;
	pt1_3d.y = y;
	pt1_3d.z = p1->z * app->view.zscale;
	
	pt2_3d.x = x + 1;
	pt2_3d.y = y;
	pt2_3d.z = p2->z * app->view.zscale;
	
	// Project using bonus projection system
	pt1 = project_bonus_complete(pt1_3d, &app->view, &app->map);
	pt2 = project_bonus_complete(pt2_3d, &app->view, &app->map);
	
	// Simple viewport culling - skip lines completely outside screen
	if ((pt1.x < -100 && pt2.x < -100) || (pt1.x > WIN_W + 100 && pt2.x > WIN_W + 100) ||
		(pt1.y < -100 && pt2.y < -100) || (pt1.y > WIN_H + 100 && pt2.y > WIN_H + 100))
		return;
	
	// Draw line with color interpolation for smooth gradients
	draw_line_pts_color(&app->mlx.img, pt1, pt2, pick_color_mode(p1, &app->map, app->color_mode), pick_color_mode(p2, &app->map, app->color_mode));
}

static void	draw_vertical_line_bonus(t_app_bonus *app, int x, int y)
{
	const t_point	*p1;
	const t_point	*p2;
	t_point3d		pt1_3d;
	t_point3d		pt2_3d;
	t_point2d		pt1, pt2;

	if (!app || !app->map.pts || y + 1 >= app->map.h || x >= app->map.w)
		return ;
	if (!app->map.pts[y] || !app->map.pts[y + 1])
		return ;
	
	p1 = &app->map.pts[y][x];
	p2 = &app->map.pts[y + 1][x];
	
	// Create 3D points with Z-scale
	pt1_3d.x = x;
	pt1_3d.y = y;
	pt1_3d.z = p1->z * app->view.zscale;
	
	pt2_3d.x = x;
	pt2_3d.y = y + 1;
	pt2_3d.z = p2->z * app->view.zscale;
	
	// Project using bonus projection system
	pt1 = project_bonus_complete(pt1_3d, &app->view, &app->map);
	pt2 = project_bonus_complete(pt2_3d, &app->view, &app->map);
	
	// Simple viewport culling - skip lines completely outside screen
	if ((pt1.x < -100 && pt2.x < -100) || (pt1.x > WIN_W + 100 && pt2.x > WIN_W + 100) ||
		(pt1.y < -100 && pt2.y < -100) || (pt1.y > WIN_H + 100 && pt2.y > WIN_H + 100))
		return;
	
	// Draw line with color interpolation for smooth gradients
	draw_line_pts_color(&app->mlx.img, pt1, pt2, pick_color_mode(p1, &app->map, app->color_mode), pick_color_mode(p2, &app->map, app->color_mode));
}

void	render_wireframe_bonus_complete(t_app_bonus *app)
{
	int	x, y;

	if (!app || !app->map.pts)
		return ;

	// Clear screen efficiently
	img_clear(&app->mlx.img, 0x000000);
	
	// Render ALL lines at FULL quality - NEVER compromise quality!
	// Performance comes from optimized algorithms, not reducing quality
	y = 0;
	while (y < app->map.h)
	{
		x = 0;
		while (x < app->map.w)
		{
			draw_horizontal_line_bonus(app, x, y);
			draw_vertical_line_bonus(app, x, y);
			x++;
		}
		y++;
	}
}
