/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus_complete.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddadi <mhaddadi@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 13:58:43 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/08/23 13:58:56 by mhaddadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "fdf.h"

typedef struct s_point3d
{
	double	x;
	double	y;
	double	z;
}	t_point3d;

typedef struct s_app_bonus
{
	t_mlx	mlx;
	t_map	map;
	t_view	view;
	int		show_help;
	int		demo_mode;
}	t_app_bonus;

// 3D rotation functions
t_point3d	rotate_point_bonus(t_point3d p, t_view *view)
{
	t_point3d	result;
	double		cos_x, sin_x, cos_y, sin_y, cos_z, sin_z;
	double		temp_y, temp_z;

	cos_x = cos(view->rot_x);
	sin_x = sin(view->rot_x);
	cos_y = cos(view->rot_y);
	sin_y = sin(view->rot_y);
	cos_z = cos(view->rot_z);
	sin_z = sin(view->rot_z);

	// Rotation around X axis (pitch)
	temp_y = p.y * cos_x - p.z * sin_x;
	temp_z = p.y * sin_x + p.z * cos_x;
	p.y = temp_y;
	p.z = temp_z;

	// Rotation around Y axis (yaw)
	result.x = p.x * cos_y + p.z * sin_y;
	result.z = -p.x * sin_y + p.z * cos_y;
	result.y = p.y;

	// Rotation around Z axis (roll)
	temp_y = result.y;
	result.y = temp_y * cos_z - result.x * sin_z;
	result.x = temp_y * sin_z + result.x * cos_z;

	return (result);
}

// Multi-projection system
t_point2d	project_bonus_complete(t_point3d p3d, t_view *view)
{
	t_point2d	p2d;
	t_point3d	rotated;
	double		proj_x, proj_y;

	// Apply 3D rotations
	rotated = rotate_point_bonus(p3d, view);

	// Apply different projection modes
	if (view->proj == PROJ_ISO)  // Isometric
	{
		proj_x = (rotated.x - rotated.y) * cos(M_PI / 6.0);
		proj_y = (rotated.x + rotated.y) * sin(M_PI / 6.0) - rotated.z;
	}
	else if (view->proj == PROJ_PAR)  // Parallel
	{
		proj_x = rotated.x;
		proj_y = rotated.y - rotated.z * 0.5;
	}
	else  // Perspective
	{
		double	perspective = 1000.0;
		double	distance = perspective + rotated.z;
		
		if (distance < 1)
			distance = 1;
		proj_x = rotated.x * perspective / distance;
		proj_y = rotated.y * perspective / distance;
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

	if (x + 1 >= app->map.w)
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
	pt1 = project_bonus_complete(pt1_3d, &app->view);
	pt2 = project_bonus_complete(pt2_3d, &app->view);
	
	// Draw line with color
	draw_line_pts(&app->mlx.img, pt1, pt2, pick_color(p1, &app->map));
}

static void	draw_vertical_line_bonus(t_app_bonus *app, int x, int y)
{
	const t_point	*p1;
	const t_point	*p2;
	t_point3d		pt1_3d;
	t_point3d		pt2_3d;
	t_point2d		pt1, pt2;

	if (y + 1 >= app->map.h)
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
	pt1 = project_bonus_complete(pt1_3d, &app->view);
	pt2 = project_bonus_complete(pt2_3d, &app->view);
	
	// Draw line with color
	draw_line_pts(&app->mlx.img, pt1, pt2, pick_color(p1, &app->map));
}

void	render_wireframe_bonus_complete(t_app_bonus *app)
{
	int	x;
	int	y;

	// Clear screen
	img_clear(&app->mlx.img, 0x000000);
	
	// Draw all wireframe lines
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
